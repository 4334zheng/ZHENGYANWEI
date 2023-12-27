#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define memory_size 100 * 1024 * 1024 // 100M内存空间
#define BLOCK_SIZE 1024               // 块的大小
#define BLOCK_NUM 100 * 1024          // 块的数量
#define MAX_INODE_NUM 20              // 每个目录inode最大值
#define READER_NUM 100                // reader数量最大值
int shm_id;                          
char *address;
char path[100];

/* 文件控制块 */
typedef struct
{
    /* 文件信息 */
    int begin_block_index; // 文件数据起始盘块号
    int file_size;         // 文件大小，单位为盘块
    int data_size;         // 已写入的内容大小，单位为字节
    int readptr;           // 读指针，单位为字节
    int reader_count;

    /* 整形信号量 */
    int reader_mutex;
    int writer_mutex;
} FCB;

/* Inode */
typedef struct
{
    char file_name[30];    // 文件名
    char file_type;        // 类型，0为目录 1为普通文件
    int start_block_index; // 起始索引号
} Inode;

/* 索引表 */
typedef struct
{
    int inode_number;           // inode数量
    Inode nodes[MAX_INODE_NUM]; // 索引节点信息
} Index_Table;

Index_Table *curr_dir; // 当前表索引


/***************内存相关函数****************/

/*创建100 MB大小的共享内存空间*/
int create_shared_memory()
{
    int shm_id;
    shm_id = shmget((key_t)123, memory_size, 0666 | IPC_CREAT); //创建共享内存
    //创建失败
    if (shm_id < 0)                                             
    {
        perror("shmget fail!\n");
        exit(1);
    }
    // 创建成功
    printf("Successfully created segment : %d \n", shm_id);
    system("ipcs -m");
    return shm_id;
}

/* 在磁盘中分配块 */
int malloc_block(int block_wanted)
{
    int sum = 0;                       
    int start = BLOCK_NUM / BLOCK_SIZE; 
    for (int i = BLOCK_NUM / BLOCK_SIZE; i < BLOCK_NUM; i++)
    {
        if (address[i] == '0') // 空白块
        {
            if (sum == 0)            // 如果是第一块空白块
                start = i;           // 记录起始索引号
            sum++;                  
            if (sum == block_wanted) // 满足要求
            {
                for (int j = start; j < start + block_wanted; j++)
                    address[j] = '1'; // 将状态改为 "used"
                return start;       
            }
        }
        else        
            sum = 0; // 重新开始
    }
    //内存不足
    printf("Not enough memory!\n");
    return -1;
}

/* 根据块索引获取块的物理地址 */
char *get_block_addr_from_index(int block_index)
{
    // 起始地址加偏移量
    return address + block_index * BLOCK_SIZE;
}

/* 根据物理地址获取块的索引 */
int get_block_index_from_address(char* addr)
{
    // 地址偏移量（字节）除以块的大小
    return (addr - address) / BLOCK_SIZE;
}

/* 释放数据块 */
int free_block(int start_block_index, int number)
{
    // 只需要改变位图
    for(int i=start_block_index; i<start_block_index+number; i++)
        address[i] = '0';
    return 0;
}

/* 删除共享内存 */
void delete_shared_menory(int shm_id)
{
    shmctl(shm_id,IPC_RMID,0);
    system ( "ipcs -m " );
}


/*******************文件系统********************/

/* 查找Inode */
int find_inode(Index_Table* T, char dir_name[])
{
    int inode_number = T->inode_number; // 获取数量
    int ans_index = -1;
    for(int i=0; i<inode_number; i++)   
        if(strcmp(dir_name,T->nodes[i].file_name)==0)
            ans_index = i;
    return ans_index;
}

/* 创建Inode */
int add_Inode(Index_Table* T, char file_name[], int type, int start_index)
{
    int inode_number = T->inode_number; 
    if(inode_number + 1 == MAX_INODE_NUM)
    {
        printf("Error：文件过多!\n");
        return -1;
    }
    
    if(find_inode(T, file_name) != -1)  // 判断是否有文件重名
    {
        printf("Error：该文件已经存在!\n");
           return -1;
    }
    Inode* new_inode = &T->nodes[inode_number];    // 创建一个新的inode
    T->inode_number++;  
    strcpy(new_inode->file_name, file_name); 
    new_inode->file_type = type;
    new_inode->start_block_index = start_index; 

    return 0;
}

/* 删除Inode */
int delete_inode(Index_Table* T, int inode_index)
{
    int inode_number = T->inode_number;     // move front
    for(int i=inode_index; i<inode_number-1; i++)
        T->nodes[i] = T->nodes[i+1];
    T->inode_number--;
    return 0;
}

/* 删除FCB */
int delete_FCB(int FCB_block_index)
{
    FCB* now_FCB = (FCB*)get_block_addr_from_index(FCB_block_index);    // get the address
    free_block(now_FCB->begin_block_index, now_FCB->file_size);  // release the memory
    free_block(FCB_block_index, 1); //释放FCB的空间
    return 0;
}

/* 创建FCB */
int create_FCB(int FCB_block_index, int block_index, int file_size)
{
    FCB* new_FCB = (FCB*) get_block_addr_from_index(FCB_block_index);   //FCB的存储位置
    new_FCB->begin_block_index = block_index;   // 文件数据起始位置
    new_FCB->file_size = file_size;   // 文件大小
    new_FCB->data_size = 0;  // 文件已写入的数据长度
    new_FCB->readptr = 0;   // 文件读指针
    new_FCB->reader_count = 0;   
    new_FCB->reader_mutex = 0;
    new_FCB->writer_mutex = 0;
    return 1;
}

/* 删除目录 */
int delete_dir(Index_Table* T, int inode_index)
{
    Inode node = T->nodes[inode_index];

    if(node.file_type == 0) //目录
    {
        //找到目录位置
        int Table_block_index = node.start_block_index;
        Index_Table* table = (Index_Table*)get_block_addr_from_index(Table_block_index);

        // Recursive Delete 
        int count = table->inode_number;
        for(int i=1; i<count; i++) 
        {
            
            delete_dir(table, i);  
        }
        // 释放数据块
        free_block(Table_block_index, 1);
    }
    else    //文件
    {
        // 释放内存
        printf("delete %s .....\n", node.file_name);
        int FCB_block_index = node.start_block_index;
        delete_FCB(FCB_block_index);
    }
}



/*********************************************/
// 指令
/*
 * ls 查看目录当前文件和目录
 * mkdir 在当前目录下创建新目录
 * rmdir 当前目录下删除指定目录
 * cd 切换到该目录
 * touch 在当前目录下创建指定大小文件
 * rename 重命名文件/目录
 * rm 在当前目录下删除指定文件
 * read 读取该文件
 * write 写数据到该文件
 */

/* ls 查看目录当前文件和目录*/
int LS()
{
    int inode_number = curr_dir->inode_number;  
    for(int i=0; i<inode_number; i++)   // 输出所有节点的信息
    {
        Inode temp_inode = curr_dir->nodes[i]; 
        printf("%s\t",temp_inode.file_name);    // 输出文件名

        /* 输出文件信息 */
		if(temp_inode.file_type==0) // 目录信息
        {
            printf("\t<目录>\t\n");
            // int dir_block_index = temp_inode.start_block_index; 
            // Index_Table* T = (Index_Table*)get_block_addr_from_index(dir_block_index);  // 获取物理地址
            // printf("文件数量: %d\n", T->inode_number);
        }
			
		else // 文件信息
        {
            printf("\t<文件>\t\n");
            // int FCB_block_index = temp_inode.start_block_index; 
            // FCB* file_FCB = (FCB*)get_block_addr_from_index(FCB_block_index);
            // printf("文件大小: %d\n",file_FCB->file_size);
        }
    }
}

/* mkdir 在当前目录下创建新目录*/
int MKDIR(char dir_name[])
{
    int dir_block = malloc_block(1); 
    if(dir_block == -1)
        return 0;

    if(add_Inode(curr_dir, dir_name, 0, dir_block) == -1)
        return -1;

    //创建父inode
    Index_Table* new_table = (Index_Table*)get_block_addr_from_index(dir_block);
    new_table->inode_number = 0;
    char parent[] = "..";
    int curr_block = get_block_index_from_address((char*)curr_dir);

    if(add_Inode(new_table, parent, 0, curr_block) == -1)   
        return -1;
    return 1;
}

/* cd 切换到该目录*/
int CD(char dir_name[])
{
    int inode_index = find_inode(curr_dir, dir_name); // find the target file's block index
    if(inode_index == -1)
    {
        printf("Error：目录不存在！\n");
        return -1;
    }
    if(curr_dir->nodes[inode_index].file_type == 1)
    {
        printf("Error：该文件不是目录！\n");
        return -1;
    }

    // 改变目录
    int dir_block_index = curr_dir->nodes[inode_index].start_block_index;
    curr_dir = (Index_Table*)get_block_addr_from_index(dir_block_index);

    // 改变路径
    if(strcmp(dir_name, "..") == 0)
    {
        // 返回
        int len = strlen(path);
        for(int i=len-2;i>=0;i--)
            if(path[i] == '/')
            {
                path[i]='\0';
                break;
            }
    }
    else 
    {
        strcat(path, "/");
        strcat(path, dir_name);
    }
    return 0;
}

/* rmdir 当前目录下删除指定目录*/
int RMDIR(char dir_name[])
{
    if(strcmp(dir_name, "..") == 0)
    {
        printf("Error：该目录里有子目录，请先删除子目录!\n");
        return -1;
    }

    // 查找目标目录
    int dir_index = find_inode(curr_dir, dir_name);
    if(dir_index == -1)
    {
        printf("Error：该目录没有找到！\n");
        return -1;
    }

    Inode target = curr_dir->nodes[dir_index];

    // 确认类型
    if(target.file_type == 0)//目录
    {
        delete_dir(curr_dir, dir_index);
    }
    else 
    {
        printf("Error：这不是个目录！\n");
        return -1;
    }
    
    // 删除iNode
    delete_inode(curr_dir, dir_index);
    return 0;
}

/* touch 在当前目录下创建指定大小文件*/
int TOUCH(char file_name[], int file_size)
{
    // 给控制块分配数据块
    int FCB_block_index = malloc_block(1);
    if(FCB_block_index == -1)
        return -1;
    // 获取文件大小
    int File_block_index = malloc_block(file_size);
    if(File_block_index == -1)
        return -1;

    // 创建一个控制块
    if(create_FCB(FCB_block_index, File_block_index, file_size) == -1)
        return -1;

    // 创建新节点
    if(add_Inode(curr_dir, file_name, 1, FCB_block_index) == -1)
        return -1;

    return 0;
}

/* rename 重命名文件/目录*/
int RENAME(char old_file_name[], char new_file_name[])
{
    int file_Index = find_inode(curr_dir, old_file_name);
    if(file_Index == -1) 
    {
        printf("Error：文件不存在！\n");
        return -1;
    }
    // 修改文件名称
    strcpy(curr_dir->nodes[file_Index].file_name, new_file_name);
    return 1;
}

/* rm 在当前目录下删除指定文件*/
int RM(char file_name[])
{
    if(strcmp(file_name, "..") == 0)
    {
        printf("Error：父文件不能被删除！\n");
        return -1;
    }
    // 查找
    int inode_index = find_inode(curr_dir, file_name);
    if(inode_index == -1)
    {
        printf("Error：文件不存在！\n");
        return -1;
    }
    Inode node = curr_dir->nodes[inode_index];

    // 确定类型
    if(node.file_type == 0)  // 目录
    {
        printf("Error：这不是个文件！\n");
        return -1;
    }
    int FBC_block_index = node.start_block_index;

    // 释放内存
    delete_FCB(FBC_block_index);
    delete_inode(curr_dir, inode_index);
    return 0;
}

/* read 读取该文件*/
int READ(char file_name[])
{
    int file_index = find_inode(curr_dir,file_name);    // 查找文件
    if(file_index == -1)  
    {
        printf("Error：文件不存在！\n");
        return -1;
    }

    // 获取FCB
    int FCB_block_index = curr_dir->nodes[file_index].start_block_index;   
    FCB* file_FCB = (FCB*)get_block_addr_from_index(FCB_block_index);   // 获取物理地址
    file_FCB->readptr=0; 
    
    // 读取数据
    char* data = (char*)get_block_addr_from_index(file_FCB->begin_block_index);

    while(1)
    {
        if(file_FCB->reader_mutex == 0)
            break;
    }
    file_FCB->reader_mutex++;   // 读者上锁

    if(file_FCB->reader_count == 0)
    {
        while(1)    
        {
            if(file_FCB->writer_mutex == 0) // 没有写者
                break;
        }
        file_FCB->writer_mutex = 1;    // 有人读就锁写
    }
    file_FCB->reader_count++;  
    file_FCB->reader_mutex--;

    int data_size = file_FCB->data_size;
    printf("CONTENT:\n");
    for(int i = 0; file_FCB->readptr < data_size; i++, file_FCB->readptr++)
        printf("%c", *(data+file_FCB->readptr));
    if(file_FCB->readptr == data_size)  // 写满
        printf(" ");
    
    printf("\n输入回车键以继续...\n");
    getchar();
    
    while(1)
    {
        if(file_FCB->reader_mutex == 0)
            break;
    }
    file_FCB->reader_mutex++;      // 锁读
    file_FCB->reader_count--; 
    if(file_FCB->reader_count == 0)
        file_FCB->writer_mutex--;   // 没有人读释放写

    file_FCB->reader_mutex--;   // 释放读

    return 0;
}

/* write 写数据到该文件*/
int WRITE(char file_name[], char content[])
{
    int file_index = find_inode(curr_dir, file_name);   // 查找文件
    if(file_index == -1)   
    {
        printf("Error：文件不存在！\n");
        return -1;
    }

    // 获取FCB
    int FCB_block_index = curr_dir->nodes[file_index].start_block_index;    
    FCB* file_FCB = (FCB*)get_block_addr_from_index(FCB_block_index);   // 获取物理地址
    int contentLen = strlen(content);  
    int file_size = file_FCB->file_size * BLOCK_SIZE;   // 文件大小(block->byte)
    char* data = (char*)get_block_addr_from_index(file_FCB->begin_block_index);
    file_FCB->data_size = 0;

    while(1)
    {
        if(file_FCB->writer_mutex == 0) // 没有在写
            break;
    }
    file_FCB->writer_mutex++;

    for(int i=0; i < contentLen && file_FCB->data_size < file_size; i++)
    {
        *(data+file_FCB->data_size) = content[i];
        file_FCB->data_size++;
    }
    
    printf("\n输入回车键以继续...\n");
    getchar();

    file_FCB->writer_mutex--;

    return 0;
}

/* 文件系统初始化 */
void init()
{
    shm_id = create_shared_memory();    // 创建共享内存
    void *shared_memory = shmat(shm_id,(void *)0, 0);    // 将共享内存区映射到本进程的进程空间
    address = (char *) shared_memory;

    // 初始化节点信息
    int start_index = 100; 
    curr_dir = (Index_Table*)get_block_addr_from_index(start_index); // 得到地址
    printf("%d\n", curr_dir->inode_number);
    
    strcat(path, "[COMMAND]->");
}



/* 打印文件系统信息 */
void help()
{
    printf("**********************文件系统设计*******************\n");
	printf("* \t命令格式\t\t说明\n");
    printf("* mkdir 目录名\t\t在当前目录下创建目录\n");
    printf("* rmdir 目录名\t\t在当前目录下删除指定目录\n");
    printf("* rename 旧名 新名\t重命名文件/目录\n");
    printf("* cd 目录名\t\t切换到该目录\n");
    printf("* touch 文件名 大小\t在当前目录下创建指定大小文件\n");
    printf("* read 文件名\t\t读取该文件\n");
    printf("* write 文件名\t\t写数据到该文件\n");
    printf("* rm 文件名\t\t在当前目录下删除指定文件\n");
    printf("* ls  \t\t\t查看目录当前文件和目录\n");
    printf("* exit  \t\t退出系统\n");
    printf("*****************************************************\n\n");
}

int main()
{
    init();
    help();
    while(1)
    {
        char prompt[256];
        strcpy(prompt, path);
        strcat(prompt, "$");
        printf("%s ", prompt);
        char cmds[10][128]; // 输入的命令
        int line = 0;   // 参数个数
        int row = 0;    // 每个参数的长度
        while(1)
        {
            char ch = getchar();    // 每次读取一个字符
            if(ch == '\n')  // 回车则结束输入
            {
                if(row != 0)    // 前面有新的字符串才可以
                {
                    cmds[line][row] = '\0';
                    line++;
                }
                break;
            }
            else if(ch == ' ')  // 空格则开始下一个参数
            {
                if(row != 0)    // 避免多个空格
                {
                    cmds[line][row] = '\0';   // 结束符
                    line++; // 下一个参数的输入
                    row = 0; 
                }
            }
            else
            {
                cmds[line][row] = ch;
                row++;  // 下一个字符
            }  
        }

        if(line == 0)
            continue;

        if(strcmp(cmds[0], "exit") == 0)    // "exit"
            break;

        else if(strcmp(cmds[0], "ls") == 0) // "ls"
        {
            LS();
        }

        else if(strcmp(cmds[0], "mkdir") == 0)  // "mkdir"
        {
            if(line == 1)  
                printf("[Error]correct usage:\t mkdir <file_name>\n");
            else
                MKDIR(cmds[1]);
        }

        else if(strcmp(cmds[0], "rmdir") == 0)  // "rmdir"
        {
            if(line == 1)   
                printf("[Error]correct usage:\t rmdir <file_name>\n");
            else
                RMDIR(cmds[1]);
        }

        else if(strcmp(cmds[0], "cd") == 0) //  "cd"
        {
            if(line == 1)   
                printf("[Error]correct usage:\t cd <dir_name>\n");
            else
                CD(cmds[1]);
        }

        else if(strcmp(cmds[0], "touch") == 0)  // "touch" 
        {
            if(line < 3)   
                printf("[Error]correct usage:\t touch <file_name> <file_size>\n");
            else
            {
                int file_size = 0;
                for(int i=0; i<strlen(cmds[2]); i++)
                {
                    file_size = file_size * 10 + cmds[2][i] - '0';
                }
                TOUCH(cmds[1], file_size);
            }
            
        }

        else if(strcmp(cmds[0], "rename") == 0) // "rename"
        {
            if(line < 3)
                printf("[Error]correct usage:\t rename <old_file_name> <new_file_name>\n");
            else
                RENAME(cmds[1], cmds[2]);
        }

        else if(strcmp(cmds[0], "rm") == 0) // "rm"
        {
            if(line == 1)
                printf("[Error]correct usage:\t rm <file_name>\n");
            else
                RM(cmds[1]);
        }

        else if(strcmp(cmds[0], "read") == 0)   // "read"
        {
            if(line == 1)
                printf("[Error]correct usage:\t read <file_name>\n");
            else
                READ(cmds[1]);
        }

        else if(strcmp(cmds[0], "write") == 0)  // "write"
        {
            if(line < 3)
                printf("[Error]correct usage:\t write <file_name> <content>\n");
            else
                WRITE(cmds[1], cmds[2]);
        }
        else
        {
            printf("Error：该命令不存在！\n");
        }
    }
    delete_shared_menory(shm_id);
}
