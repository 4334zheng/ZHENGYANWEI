#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "system_core.h"

void showHello();
void do_mkdir(struct FCB *dir_now, char order[], union SystemCore_union *system_core);
void printPath(struct FCB *dir_now, union SystemCore_union *system_core);
struct FCB* do_cd(struct FCB *dir_now, char order[], union SystemCore_union *system_core);
void do_touch(struct FCB *dir_now, char order[], union SystemCore_union *system_core);
void do_open(struct FCB *dir_now, char order[], union SystemCore_union *system_core);
void do_remove(struct FCB *dir_now, char order[], union SystemCore_union *system_core);
void do_rename(struct FCB *dir_now, char order[], union SystemCore_union *system_core);
void do_help();

int main()
{
    printf("Loading share memory...\n");
    int shm_id;
    void *share_mem = NULL;
    FILE *p = fopen("./shm_id", "r"); // 从文件中读取共享内存id
    fscanf(p, "%d", &shm_id);
    fclose(p);
    share_mem = shmat(shm_id, 0, 0); // 挂载共享内存
    union SystemCore_union *system_core = share_mem;
    struct FCB *dir_now = &system_core->core.FCB_array.fcb_array.FCB_array[0]; // shell的当前指针指在根目录
    sem_id = semget(0x8080, BLOCK_NUM, 0660); // 挂载信号量集
    printf("Finish!\n");
    showHello(); // 下面开始shell功能

    char order[100];
    while (1) {
        printPath(dir_now, system_core);
        fgets(order, 100, stdin);
        order[strlen(order) - 1] = 0;
        if (strncmp(order, "exit", 4) == 0) {
            printf("bye~\n");
            break;
        }
        else if (strncmp(order, "ls", 2) == 0)
            ls(dir_now, system_core);
        else if (strncmp(order, "mkdir", 5) == 0)
            do_mkdir(dir_now, order, system_core);
        else if (strncmp(order, "cd", 2) == 0)
            dir_now = do_cd(dir_now, order, system_core);
        else if (strncmp(order, "touch", 5) == 0)
            do_touch(dir_now, order, system_core);
        else if (strncmp(order, "open", 4) == 0)
            do_open(dir_now, order, system_core);
        else if (strncmp(order, "rm", 2) == 0)
            do_remove(dir_now, order, system_core);
        else if (strncmp(order, "rn", 2) == 0)
            do_rename(dir_now, order, system_core);
        else
            do_help();
    }
    shmdt(share_mem); // 卸载共享内存

    return 0;
}

void showHello() {
    printf("-------------------------------------------------------------------\n");
    printf("Welcome to my file system.\n");
    printf("You can use these orders: help, exit, ls, touch, mkdir, cd, open, rm, rn.\n");
    printf("-------------------------------------------------------------------\n\n");
}

void printPath(struct FCB *dir_now, union SystemCore_union *system_core) {
    char path[100] = { 0 };
    getPath(dir_now, system_core, path);
    printf("[%s]: ", path);
}

void do_help() {
    printf("\n\n");
    printf("ls ----------------------------- show folders and files in this folder.\n");
    printf("cd [../ or child folder name] -- get to target.\n");
    printf("mkdir [child folder name] ------ create folder.\n");
    printf("touch [filename] (filesize) ---- create file by size, dafault 0 bytes.\n");
    printf("open [r / w] [filename] -------- read / write the file.\n");
    printf("exit --------------------------- exit the file system.\n");
    printf("rm [-r] name ------------------- use -r to remove a folder.\n");
    printf("rn [f / d] old_name new_name --- f means file, d means dir, rename the target.\n");
    printf("\n\n");
}

void do_mkdir(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    if (strlen(p) >= 12) {
        printf("Folder name too long. Please reset it less than 12 characters.\n");
        return;
    }
    if (serachInodeByName(dir_now, p, 0, system_core) != NULL) {
        printf("Folder duplicate name!\n");
        return;
    }
    mkdir(dir_now, p, system_core);
}

struct FCB* do_cd(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return dir_now;
        }
        p++;
    }
    p++;
    if (strncmp(p, "../", 3) == 0) {
        int father_inode_number = system_core->core.inode_array.inode_array.inode_array[dir_now->inode].parent_inode_number;
        int father_FCB_number = system_core->core.inode_array.inode_array.inode_array[father_inode_number].FCB_number;
        return &system_core->core.FCB_array.fcb_array.FCB_array[father_FCB_number];
    }
    else {
        struct FCB* res = cd(dir_now, p, system_core);
        if (res == NULL) {
            printf("No such dir!\n");
            return dir_now;
        }
        return res;
    }
}

void do_touch(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    char *p1 = p;
    while (*p1 != ' ') {
        if (*p1 == 0)
            break;
        p1++;
    }
    int size = 0;
    if (*p1 == ' ') {
        *p1 = 0;
        p1++;
        size = atoi(p1);
    }
    if (strlen(p) >= 12) {
        printf("File name too long. Please reset it less than 12 characters.\n");
        return;
    }
    if (serachInodeByName(dir_now, p, 1, system_core) != NULL) {
        printf("File duplicate name!\n");
        return;
    }
    touch(dir_now, p, system_core, size);
}

void do_read(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;  // 获取指令参数
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    struct Inode *inode = serachInodeByName(dir_now, p, 1, system_core); // 获取该文件名对应inode
    if (inode == NULL) {
        printf("No such file!\n");
        return;
    }
    else {
        struct FCB *fcb = &system_core->core.FCB_array.fcb_array.FCB_array[inode->FCB_number];
        int inode_number = fcb->inode;
        wait(inode_number); // 等待信号量
        notify(inode_number); // 马上释放, 确保多个进程可以同时读取

        char* data = open_file_read(inode, system_core); // 读取内容并打印
        printf("-------------------------------------------------------------------\n");
        printf("%s", data);
        printf("-------------------------------------------------------------------\n");
        free(data);
    }
}

void do_write(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order; // 获取指令参数
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    struct Inode *inode = serachInodeByName(dir_now, p, 1, system_core); // 获取该文件名对应inode
    if (inode == NULL) {
        printf("No such file!\n");
        return;
    }
    struct FCB *fcb = &system_core->core.FCB_array.fcb_array.FCB_array[inode->FCB_number];
    int inode_number = fcb->inode;
    wait(inode_number); // 等待信号量

    printf("Please write the file. Write a blank line means finish:\n"); // 输入文件新内容
    char line[4096], data[1 << 20] = { 0 };
    while (1) {
        fgets(line, 4096, stdin);
        if (strncmp(line, "\n", 1) == 0)
            break;
        strncat(data, line, 4096);
    }
    printf("Writing finish.\n");
    writeFile(inode, system_core, data);
    notify(inode_number); // 释放信号量
}

void do_open(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    if (*p == 'r')
        do_read(dir_now, p, system_core);
    else if (*p == 'w')
        do_write(dir_now, p, system_core);
}

void do_remove_file(struct FCB *dir_now, char name[], union SystemCore_union *system_core) {
    struct Inode *inode = serachInodeByName(dir_now, name, 1, system_core);
    if (inode == NULL) {
        printf("No such file!\n");
        return;
    }
    remove_file(inode, system_core);
}

void do_remove_dir(struct FCB *dir_now, char name[], union SystemCore_union *system_core) {
    struct Inode *inode = serachInodeByName(dir_now, name, 0, system_core);
    if (inode == NULL) {
        printf("No such folder!\n");
        return;
    }
    remove_dir(inode, system_core);
}

void do_remove(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    char *p1 = p;
    while (*p1 != ' ') {
        if (*p1 == 0) {
            do_remove_file(dir_now, p, system_core);
            return;
        }
        p1++;
    }
    *p1 = 0;
    p1++;
    if (strncmp(p, "-r", 2) == 0)
        do_remove_dir(dir_now, p1, system_core);
    else 
        printf("Param error.\n");
}

void do_rename(struct FCB *dir_now, char order[], union SystemCore_union *system_core) {
    char *p = order;
    while (*p != ' ') {
        if (*p == 0) {
            printf("Param error.\n");
            return;
        }
        p++;
    }
    p++;
    char *p1 = p;
    while (*p1 != ' ') {
        if (*p1 == 0) {
            printf("Param error.\n");
            return;
        }
        p1++;
    }
    *p1 = 0;
    p1++;
    char *p2 = p1;
    while (*p2 != ' ') {
        if (*p2 == 0) {
            printf("Param error.\n");
            return;
        }
        p2++;
    }
    *p2 = 0;
    p2++;
    if (*p == 'f')
        rename_file(dir_now, p1, p2, system_core);
    else if (*p == 'd')
        rename_dir(dir_now, p1, p2, system_core);
    else
        printf("Param error.\n");
}
