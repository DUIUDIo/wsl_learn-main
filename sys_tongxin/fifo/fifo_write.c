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
    unlink(fifo_path);
    if(mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    //对有名管道进行读写操作
    int fd_write = open(fifo_path, O_WRONLY);

    if(fd_write == -1) {
        perror("open for write");
        exit(EXIT_FAILURE);
    }

    char message[100];
    ssize_t read_num;
    while( (read_num = read(STDIN_FILENO, message, sizeof(message))) > 0) {
        write(fd_write, message, read_num);
    }

    if( read_num == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
   
    printf("写入完成，关闭管道\n");
    close(fd_write);
    return 0;
 }