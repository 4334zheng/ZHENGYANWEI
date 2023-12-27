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
    sem_t *reader_mutex;
    sem_t *writer_mutex;
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

int main()
{
    shm_id = create_shared_memory();                   // 创建共享内存
    void *shared_memory = shmat(shm_id, (void *)0, 0); 
    address = (char *)shared_memory;                   // 共享内存的开始地址

    // 将所有块的位图初始化为 0
    for (int i = 0; i < BLOCK_NUM; i++)
        address[i] = '0';

    /* 位图的第一部分，前100个块用于位图 */
    for (int i = 0; i < BLOCK_NUM / BLOCK_SIZE; i++)
        address[i] = '1';

    int start_index = malloc_block(1); //分配1块用于根表
    curr_dir = (Index_Table *)get_block_addr_from_index(start_index); //得到地址
    curr_dir->inode_number = 0;
}