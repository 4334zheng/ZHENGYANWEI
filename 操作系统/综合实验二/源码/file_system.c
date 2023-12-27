#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "system_core.h"

const size_t MEM_SIZE = 100 << 20; // 100MB
int sem_id;

void init(union SystemCore_union *system_core);

int main()
{
    void *share_mem = NULL;
    int shm_id;

    shm_id = shmget(IPC_PRIVATE, MEM_SIZE, 0666); // 获取共享内存id
    share_mem = shmat(shm_id, 0, 0); // 挂载共享内存到这个进程

    union SystemCore_union *system_core = share_mem; // 文件系统管理核心
    init(system_core); // 初始化文件系统
    struct FCB *root = &system_core->core.FCB_array.fcb_array.FCB_array[0]; // 创建根目录
    FILE *p = fopen("./shm_id", "w"); // 把共享内存id写入文件, 供其他进程读取
    fprintf(p, "%d", shm_id);
    fclose(p);

    sem_id = semget(0x8080, BLOCK_NUM, 0660 | IPC_CREAT); // 创建信号量集
    union semun sem_union;
    sem_union.val = 1;
    for (int i = 0; i < BLOCK_NUM; i++) // 初始化信号量
        semctl(sem_id, i, SETVAL, sem_union);

    printf("startup finish.\n");

    char order[100];
    while (1) {
        scanf("%s", order);
        if (strncmp(order, "exit", 4) == 0) {
            printf("bye~\n");
            break;
        }
    }

    semctl(sem_id, BLOCK_NUM, IPC_RMID); // 删除信号量集
    shmdt(share_mem); // 卸载共享内存
    shmctl(shm_id, 0, NULL); // 删除共享内存
    return 0;
}

void init(union SystemCore_union *system_core) {
    char occupy_root = 1 << 7; // 占用第一位用于根目录

    struct Inode *inode = system_core->core.inode_array.inode_array.inode_array;
    system_core->core.inode_array.inode_array.inode_map[0] = occupy_root;
    for (int i = 0; i < BLOCK_NUM; i++) { // 初始化所有inode
        inode->brother_inode_number_left = inode->brother_inode_number_right = inode->child_inode_number = inode->parent_inode_number = -1;
        inode++;
    }
    struct FCB *fcb = system_core->core.FCB_array.fcb_array.FCB_array;
    strncpy(fcb->FileName, "root", 12);
    fcb->inode = 0;
    system_core->core.FCB_array.fcb_array.FCB_map[0] = occupy_root;
    fcb++;
    for (int i = 1; i < (BLOCK_NUM << 1); i++) { // 初始化所有FCB
        fcb->inode = -1;
        fcb++;
    }

    system_core->core.block_used = 0; // 初始化数据块使用信息
    system_core->core.block_rest = BLOCK_NUM;
}
