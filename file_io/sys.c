#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
    {
    
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        {
        perror("错误，无法打开文件");
        return -1;
        }
    close(fd);
    return 0;
}