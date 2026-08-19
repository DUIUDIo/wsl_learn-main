#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 int main(int argc, char const *argv[])
 {
    char* fifo_path = "myfifo";
  

    //对有名管道进行读写操作
    int fd_read = open(fifo_path, O_RDONLY);

    if(fd_read == -1) {
        perror("open for read");
        exit(EXIT_FAILURE);
    }

    char message[100];
    ssize_t read_num;
    // 读取数据并输出到标准输出
    while( (read_num = read(fd_read, message, sizeof(message))) > 0) {
        write(STDOUT_FILENO, message, read_num);
    }

    if( read_num == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
   
    printf("读取完成，关闭管道\n");
    close(fd_read);
    
    return 0;
 }