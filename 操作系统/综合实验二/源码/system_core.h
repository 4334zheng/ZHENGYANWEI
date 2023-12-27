#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// 一个数据块大小
#define BLOCK_SIZE 4096

// 96MB对应24576个数据块
#define BLOCK_NUM 24576

// 每块对应1bit, 需要3072bytes表示
#define BLOCK_MAP_LENGTH 3072

// inode最多每块一个, 共24576个
#define INODE_MAP_LENGTH 3072

// FCB考虑后续可能有硬链接、软链接等, 开多一倍
#define FCB_MAP_LENGTH 6144

// 硬盘管理核心占4MB(剩余96MB)
#define CORE_SIZE (1 << 22)

// 32 bytes
struct Inode {
    int file_type; // 文件类型, 0是文件夹, 1是可读写文件
    int iblock; // 文件数据块起始下标(在FAT表中进行跳转)
    int size; // 文件大小, 可在touch创建文件时指定, 可大于内容长度
    int parent_inode_number; // 父节点(当前所处文件夹)inode下标
    int child_inode_number; // 第一个子节点下标
    int brother_inode_number_left; // 左兄弟节点inode下标
    int brother_inode_number_right; // 右兄弟inode下标
    int FCB_number; // 该文件对应FCB下标
};

// 16 bytes
struct FCB {
    int inode; // 该FCB对应inode下标
    char FileName[12]; // 文件名
};

// 4KB
union BlockMap {
    char block_map[BLOCK_MAP_LENGTH];
    char temp[BLOCK_SIZE]; // 撑开一个数据块
};

// 789504 bytes
struct InodeArray {
    char inode_map[INODE_MAP_LENGTH];
    struct Inode inode_array[BLOCK_NUM];
};

// 792576 bytes
struct FCBArray {
    char FCB_map[FCB_MAP_LENGTH];
    struct FCB FCB_array[BLOCK_NUM << 1];
};

// 790528 bytes -> 772KB -> 193 * 4KB
union InodeArrayBlock {
    struct InodeArray inode_array;
    char temp[790528];
};

// 194 * 4KB
union FCBArrayBlock {
    struct FCBArray fcb_array;
    char temp[794624];
};

// 1648 KB + 8 bytes
struct SystemCore {
    int block_used; // 已使用的数据块, 
    int block_rest; // 剩余空闲的数据块, 
    union BlockMap bit_map; // 4KB
    union InodeArrayBlock inode_array; // 193 * 4KB
    union FCBArrayBlock FCB_array; // 194 * 4KB
    int FAT[24576]; // 96KB
};

// 4MB
union SystemCore_union {
    struct SystemCore core;
    char temp[1 << 22];
};

// 管理信号量的数据结构
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

int sem_id; // 信号量集id

// 查看1bytes, 即8bit中哪一位为0(0表示可用)
int searchBit(char byte) {
    int res = 0;
    while (byte < 0) {
        res++;
        byte <<= 1;
    }
    return res < 8 ? res : -1;
}

// 查找一个位图中, 第一个为0的bit的下标(0表示可用)
int searchFirstBit(char *bytes, int length) {
    int res, count = 0;
    while ((res = searchBit(*bytes)) == -1) {
        count++;
        if (count == length)
            break;
    }
    return count == length ? -1 : res + (count << 3);
}

// 设置一个位图中第pos位的bit
void setBit(char *bytes, int pos, int val) {
    while (pos / 8) {
        pos -= 8;
        bytes++;
    }
    char new_val = 1 << (7 - pos);
    if (val == 0) {
        new_val = ~new_val;
        *bytes = *bytes & new_val;
    }
    else {
        *bytes = *bytes | new_val;
    }
}

// 在当前文件夹下创建名为dir_name的文件夹
void mkdir(struct FCB *dir_now, char dir_name[], union SystemCore_union *system_core) {
    // 获取当前文件夹下最后一个文件的inode编号
    int last_childe_inode_number = system_core->core.inode_array.inode_array.inode_array[dir_now->inode].child_inode_number;
    if (last_childe_inode_number != -1) // 可能当前文件夹为空
        while (system_core->core.inode_array.inode_array.inode_array[last_childe_inode_number].brother_inode_number_right != -1)
            last_childe_inode_number = system_core->core.inode_array.inode_array.inode_array[last_childe_inode_number].brother_inode_number_right;

    // 为新文件夹获取可用的inode
    int new_dir_inode_number = searchFirstBit(system_core->core.inode_array.inode_array.inode_map, INODE_MAP_LENGTH);
    if (new_dir_inode_number == -1) {
        printf("FAIL: All inode have been used!\n");
        return;
    }
    setBit(system_core->core.inode_array.inode_array.inode_map, new_dir_inode_number, 1);

    // 获取inode后, 初始化inode信息
    struct Inode *new_dir_inode = &system_core->core.inode_array.inode_array.inode_array[new_dir_inode_number];
    new_dir_inode->file_type = 0; // 文件夹类型为0
    new_dir_inode->parent_inode_number = dir_now->inode;
    new_dir_inode->brother_inode_number_left = -1;
    new_dir_inode->brother_inode_number_right = -1;
    new_dir_inode->child_inode_number = -1;
    if (last_childe_inode_number != -1) { // 如果当前文件夹不为空, 挂在最后一个孩子后
        new_dir_inode->brother_inode_number_left = last_childe_inode_number;
        system_core->core.inode_array.inode_array.inode_array[last_childe_inode_number].brother_inode_number_right = new_dir_inode_number; // 新文件夹装入当前文件夹(连接在最后一个孩子后面)
    }
    else // 当前文件夹为空, 直接挂在当前文件夹的child_inode, 作为第一个孩子
        system_core->core.inode_array.inode_array.inode_array[dir_now->inode].child_inode_number = new_dir_inode_number;

    // 获取可用的FCB
    int new_dir_fcb_number = searchFirstBit(system_core->core.FCB_array.fcb_array.FCB_map, FCB_MAP_LENGTH);
    if (new_dir_fcb_number == -1) {
        setBit(system_core->core.inode_array.inode_array.inode_map, new_dir_inode_number, 0);
        printf("FAIL: All FCB have been used!\n");
        return;
    }
    setBit(system_core->core.FCB_array.fcb_array.FCB_map, new_dir_fcb_number, 1);
    new_dir_inode->FCB_number = new_dir_fcb_number;

    // 初始化FCB
    struct FCB *new_dir_fcb = &system_core->core.FCB_array.fcb_array.FCB_array[new_dir_fcb_number];
    new_dir_fcb->inode = new_dir_inode_number;
    strncpy(new_dir_fcb->FileName, dir_name, 12);
}

// cd进入指定的子目录
struct FCB* cd(struct FCB *dir_now, char file_name[], union SystemCore_union *system_core) {
    struct Inode *dir_now_inode = &system_core->core.inode_array.inode_array.inode_array[dir_now->inode];
    int child_inode_number = dir_now_inode->child_inode_number;

    // 遍历当前文件夹的子inode, 查看是否有同名的文件夹，有则返回
    while (child_inode_number != -1) {
        struct Inode *child_inode = &system_core->core.inode_array.inode_array.inode_array[child_inode_number];
        int child_FCB_number = child_inode->FCB_number;
        struct FCB *child_FCB = &system_core->core.FCB_array.fcb_array.FCB_array[child_FCB_number];
        if (child_inode->file_type == 0 && strncmp(child_FCB->FileName, file_name, 12) == 0)
            return child_FCB;
        child_inode_number = child_inode->brother_inode_number_right;
    }
    return NULL;
}

// 列出当前文件夹下子目录和文件的信息(文件inode编号, 文件类型, 文件大小, 文件名)
void ls(struct FCB *dir_now, union SystemCore_union *system_core) {
    struct Inode *dir_now_inode = &system_core->core.inode_array.inode_array.inode_array[dir_now->inode];
    int child_inode_number = dir_now_inode->child_inode_number;
    while (child_inode_number != -1) {
        struct Inode *child_inode = &system_core->core.inode_array.inode_array.inode_array[child_inode_number];
        printf("inode:%d file_type:%d file_size:%d %s\n", child_inode_number, child_inode->file_type, child_inode->size, system_core->core.FCB_array.fcb_array.FCB_array[child_inode->FCB_number].FileName);
        child_inode_number = child_inode->brother_inode_number_right;
    }
}

// 递归获取当前目录的路径
void getPath(struct FCB *dir_now, union SystemCore_union *system_core, char res[]) {
    if (dir_now->inode != 0) {
        int father_inode_number = system_core->core.inode_array.inode_array.inode_array[dir_now->inode].parent_inode_number;
        int father_FCB_number = system_core->core.inode_array.inode_array.inode_array[father_inode_number].FCB_number;
        struct FCB *father_FCB = &system_core->core.FCB_array.fcb_array.FCB_array[father_FCB_number];
        getPath(father_FCB, system_core, res);
    }
    strncat(res, dir_now->FileName, 12);
    strcat(res, "/");
}

// 循环释放以iblock开始的数据块(操作位图实现)
void freeMemBlock(int iblock, union SystemCore_union *system_core) {
    int *FAT = system_core->core.FAT;
    while (iblock != -1) {
        setBit(system_core->core.bit_map.block_map, iblock, 0);
        iblock = FAT[iblock];
        system_core->core.block_used--;
        system_core->core.block_rest++;
    }
}

// 申请block_num个数据块, 自动连接FAT表, 返回起始数据块下标
int allocMemBlock(int block_num, union SystemCore_union *system_core) {
    if (block_num > system_core->core.block_rest) {
        printf("FAIL: no enough memory block.\n");
        return -1;
    }
    system_core->core.block_used += block_num;
    system_core->core.block_rest -= block_num;

    int block_number = searchFirstBit(system_core->core.bit_map.block_map, BLOCK_MAP_LENGTH);
    int res = block_number;
    block_num--;
    int temp = block_number;
    setBit(system_core->core.bit_map.block_map, block_number, 1);
    while (block_num > 0) {
        block_number = searchFirstBit(system_core->core.bit_map.block_map, BLOCK_MAP_LENGTH);
        system_core->core.FAT[temp] = block_number;
        temp = block_number;
        setBit(system_core->core.bit_map.block_map, block_number, 1);
        block_num--;
    }
    system_core->core.FAT[temp] = -1;
    return res;
}

struct Inode* serachInodeByName(struct FCB *dir_now, char name[], int file_type, union SystemCore_union *system_core) {
    struct Inode *res = NULL;
    struct Inode *dir_now_inode = &system_core->core.inode_array.inode_array.inode_array[dir_now->inode];
    int child_inode_number = dir_now_inode->child_inode_number;
    while (child_inode_number != -1) {
        struct Inode *child_inode = &system_core->core.inode_array.inode_array.inode_array[child_inode_number];
        int child_FCB_number = child_inode->FCB_number;
        struct FCB *child_FCB = &system_core->core.FCB_array.fcb_array.FCB_array[child_FCB_number];
        if (child_inode->file_type == file_type && strncmp(child_FCB->FileName, name, 12) == 0)
            return child_inode;
        child_inode_number = child_inode->brother_inode_number_right;
    }
    return res;
}

// 读取文件内容, 放入data中
void readFile(struct Inode *inode, union SystemCore_union *system_core, char data[]) {
    char *data_start = (void *)system_core;
    data_start += CORE_SIZE; // 定位到数据块开始位置
    int count = 1, block_number = inode->iblock, write_pos = 0;
    int *FAT = system_core->core.FAT;
    char *read_p = data_start + block_number * BLOCK_SIZE;

    while (*read_p != 0) { // 读取到结束符退出
        data[write_pos++] = *read_p;
        read_p++;
        count++;

        if (count == BLOCK_SIZE) { // 读取完一个数据块, 跳转到下一个
            count = 1;
            block_number = FAT[block_number];
            read_p = data_start + block_number * BLOCK_SIZE;
        }
    }
    data[write_pos] = *read_p;
}

// 把data中的内容写入文件对应的数据块
void writeFile(struct Inode *inode, union SystemCore_union *system_core, char data[]) {
    int block_num = inode->size / 4096 + 1;

    if (block_num * 4096 <= strlen(data)) { // 如果这个文件的大小不足以装下data, 重新分配
        block_num = strlen(data) / 4096 + 1;
        int temp = allocMemBlock(block_num, system_core);
        if (temp == -1)
            return;
        freeMemBlock(inode->iblock, system_core);
        inode->iblock = temp;
        inode->size = strlen(data);
    }

    char *data_start = (void *)system_core;
    data_start += CORE_SIZE;
    int read_pos = 0, count = 1, block_number = inode->iblock;
    int *FAT = system_core->core.FAT;
    char *write_p = data_start + block_number * BLOCK_SIZE;
    while (data[read_pos] != 0) { // 类似文件读取
        *write_p = data[read_pos];
        write_p++;
        read_pos++;
        count++;

        if (count == BLOCK_SIZE) {
            count = 1;
            block_number = FAT[block_number];
            write_p = data_start + block_number * BLOCK_SIZE;
        }
    }
    *write_p = 0;
    if (inode->size < strlen(data))
        inode->size = strlen(data);
}

char* open_file_read(struct Inode *inode, union SystemCore_union *system_core) {
    int size = inode->size;
    char *data = (char*)malloc((size + 1) * sizeof(char));
    readFile(inode, system_core, data);
    return data;
}

// 删除文件
void remove_file(struct Inode *inode, union SystemCore_union *system_core) {
    
    int FCB_number = inode->FCB_number;
    struct FCB *fcb = &system_core->core.FCB_array.fcb_array.FCB_array[FCB_number];
    int inode_number = fcb->inode;

    freeMemBlock(inode->iblock, system_core); // 释放对应的数据块
    if (inode->brother_inode_number_left == -1) { // 如果是当前文件夹下第一个文件
        int father_inode_number = inode->parent_inode_number; // 右兄弟充当当前文件夹第一个孩子
        struct Inode *father_inode = &system_core->core.inode_array.inode_array.inode_array[father_inode_number];
        father_inode->child_inode_number = inode->brother_inode_number_right;

        int brother_right_inode_number = inode->brother_inode_number_right; // 右兄弟左指针清空
        struct Inode *brother_right_inode = &system_core->core.inode_array.inode_array.inode_array[brother_right_inode_number];
        brother_right_inode->brother_inode_number_left = -1;
    }
    else {
        int brother_inode_number = inode->brother_inode_number_left; // 左兄弟指向右兄弟
        struct Inode *brother_inode = &system_core->core.inode_array.inode_array.inode_array[brother_inode_number];
        brother_inode->brother_inode_number_right = inode->brother_inode_number_right;

        int brother_right_inode_number = inode->brother_inode_number_right; // 右兄弟指向左兄弟
        struct Inode *brother_right_inode = &system_core->core.inode_array.inode_array.inode_array[brother_right_inode_number];
        brother_right_inode->brother_inode_number_left = brother_inode_number;
    }
    setBit(system_core->core.inode_array.inode_array.inode_map, inode_number, 0); // 释放inode
    setBit(system_core->core.FCB_array.fcb_array.FCB_map, FCB_number, 0); // 释放FCB
}

// 根据文件名、文件大小创建文件
void touch(struct FCB *dir_now, char file_name[], union SystemCore_union *system_core, int file_size) {
    // 可能当前剩余块不够用
    int block_to_use = file_size / BLOCK_SIZE + 1;
    if (block_to_use > system_core->core.block_rest) {
        printf("FAIL: the file is too large.\n");
        return;
    }
    system_core->core.block_used += block_to_use;
    system_core->core.block_rest -= block_to_use;

    // 获取当前文件夹下最后一个文件的inode编号
    int last_childe_inode_number = system_core->core.inode_array.inode_array.inode_array[dir_now->inode].child_inode_number;
    if (last_childe_inode_number != -1)
        while (system_core->core.inode_array.inode_array.inode_array[last_childe_inode_number].brother_inode_number_right != -1)
            last_childe_inode_number = system_core->core.inode_array.inode_array.inode_array[last_childe_inode_number].brother_inode_number_right;

    // 为新文件夹获取inode
    int new_file_inode_number = searchFirstBit(system_core->core.inode_array.inode_array.inode_map, INODE_MAP_LENGTH);
    if (new_file_inode_number == -1) {
        printf("FAIL: All inode have been used!\n");
        return;
    }
    setBit(system_core->core.inode_array.inode_array.inode_map, new_file_inode_number, 1);

    // 获取inode后, 初始化inode信息
    struct Inode *new_file_inode = &system_core->core.inode_array.inode_array.inode_array[new_file_inode_number];
    new_file_inode->file_type = 1;
    new_file_inode->parent_inode_number = dir_now->inode;
    new_file_inode->brother_inode_number_left = -1;
    new_file_inode->brother_inode_number_right = -1;
    new_file_inode->child_inode_number = -1;
    new_file_inode->size = file_size;
    if (last_childe_inode_number != -1) {
        setBit(system_core->core.inode_array.inode_array.inode_map, new_file_inode_number, 0);
        new_file_inode->brother_inode_number_left = last_childe_inode_number;
        system_core->core.inode_array.inode_array.inode_array[last_childe_inode_number].brother_inode_number_right = new_file_inode_number; // 新文件装入当前文件夹(连接在最后一个孩子后面)
    }
    else
        system_core->core.inode_array.inode_array.inode_array[dir_now->inode].child_inode_number = new_file_inode_number;

    // 分配数据块，默认分配一块
    new_file_inode->iblock = allocMemBlock(block_to_use, system_core);
    writeFile(new_file_inode, system_core, ""); // 清空文件内容

    // 获取FCB
    int new_file_fcb_number = searchFirstBit(system_core->core.FCB_array.fcb_array.FCB_map, FCB_MAP_LENGTH);
    if (new_file_fcb_number == -1) {
        printf("FAIL: All FCB have been used!\n");
        return;
    }
    setBit(system_core->core.FCB_array.fcb_array.FCB_map, new_file_fcb_number, 1);
    new_file_inode->FCB_number = new_file_fcb_number;

    struct FCB *new_file_fcb = &system_core->core.FCB_array.fcb_array.FCB_array[new_file_fcb_number];
    new_file_fcb->inode = new_file_inode_number;
    strncpy(new_file_fcb->FileName, file_name, 12);
}

// 删除文件夹
void remove_dir(struct Inode *inode, union SystemCore_union *system_core) {

    int FCB_number = inode->FCB_number;
    struct FCB *fcb = &system_core->core.FCB_array.fcb_array.FCB_array[FCB_number];
    int inode_number = fcb->inode;

    while (inode->child_inode_number != -1) { // 如果文件夹不为空
        struct Inode *child_inode = &system_core->core.inode_array.inode_array.inode_array[inode->child_inode_number];
        if (child_inode->file_type == 1) // 孩子是文件直接删除
            remove_file(child_inode, system_core);
        else // 孩子是文件夹, 递归删除
            remove_dir(child_inode, system_core);
    }
    // 文件夹已清空, 下面与普通文件删除过程一样
    if (inode->brother_inode_number_left == -1) {
        int father_inode_number = inode->parent_inode_number;
        struct Inode *father_inode = &system_core->core.inode_array.inode_array.inode_array[father_inode_number];
        father_inode->child_inode_number = inode->brother_inode_number_right;

        int brother_right_inode_number = inode->brother_inode_number_right;
        struct Inode *brother_right_inode = &system_core->core.inode_array.inode_array.inode_array[brother_right_inode_number];
        brother_right_inode->brother_inode_number_left = -1;
    }
    else {
        int brother_inode_number = inode->brother_inode_number_left;
        struct Inode *brother_inode = &system_core->core.inode_array.inode_array.inode_array[brother_inode_number];
        brother_inode->brother_inode_number_right = inode->brother_inode_number_right;

        int brother_right_inode_number = inode->brother_inode_number_right;
        struct Inode *brother_right_inode = &system_core->core.inode_array.inode_array.inode_array[brother_right_inode_number];
        brother_right_inode->brother_inode_number_left = brother_inode_number;
    }
    setBit(system_core->core.inode_array.inode_array.inode_map, inode_number, 0);
    setBit(system_core->core.FCB_array.fcb_array.FCB_map, FCB_number, 0);
}

// 重命名文件夹(文件同理, 改文件类型参数即可)
void rename_file(struct FCB *dir_now, char old_name[], char new_name[], union SystemCore_union *system_core) {
    struct Inode *inode = serachInodeByName(dir_now, old_name, 1, system_core);
    if (inode == NULL) {
        printf("No such file!\n");
        return;
    }
    int FCB_number = inode->FCB_number;
    struct FCB *fcb = &system_core->core.FCB_array.fcb_array.FCB_array[FCB_number];
    strncpy(fcb->FileName, new_name, 12);
}

void rename_dir(struct FCB *dir_now, char old_name[], char new_name[], union SystemCore_union *system_core) {
    struct Inode *inode = serachInodeByName(dir_now, old_name, 0, system_core);
    if (inode == NULL) {
        printf("No such folder!\n");
        return;
    }
    int FCB_number = inode->FCB_number;
    struct FCB *fcb = &system_core->core.FCB_array.fcb_array.FCB_array[FCB_number];
    strncpy(fcb->FileName, new_name, 12);
}

// inode_number即信号量集中该文件对应的信号量的下标, 这里等待信号量为1, 获取到后上锁, 信号量置0
void wait(int inode_number) {
    struct sembuf sem_b;
    sem_b.sem_num = inode_number;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_b, 1);
}

// 信号量置1
void notify(int inode_number) {
    struct sembuf sem_b;
    sem_b.sem_num = inode_number;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_b, 1);
}
