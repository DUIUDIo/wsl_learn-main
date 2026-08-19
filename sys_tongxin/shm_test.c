#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
//共享内存的案例
int main(int argc, char const *argv[])
{
    char* share_ptr;
    // 1.创建共享内存对象
    char shm_name [100] = "/my_shm";
    sprintf(shm_name, "/my_shm_%d", getpid());
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
   
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    
    //2.设置共享内存对象的大小
    ftruncate(shm_fd, 1024);

    //3.将共享内存对象映射到进程的地址空间
    void *shm_ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }   

    //4.映射完成后，关闭共享内存对象的文件描述符
    close(shm_fd);

    //5.向父子进程共享内存中写入数据,实现进程间通讯
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE); 
    } 
    else if (pid == 0) {
        //子进程
        strcpy((char*)shm_ptr, "Hello from child process!");
        printf("子进程写入共享内存完成\n");
            }
    else {
        waitpid(pid, NULL, 0); //父进程等待子进程写入完成
        printf("父进程读取共享内存内容: %s\n", (char*)shm_ptr);
        //父进程
       
    }

    //6.释放映射区
    int result = munmap(shm_ptr, 1024);
    if (result == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    //7.释放共享内存对象
    shm_unlink(shm_name);
    return 0;
}