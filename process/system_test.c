#include <stdio.h>
#include <stdlib.h>
int main( int argc, char *argv[] )
    {
    int result = system("ping -c 4 www.baidu.com");
    if (result == -1)
        {
        perror("错误，无法执行命令");
        return -1;
        }
    printf("命令执行结果: %d\n", result);
    return 0;
    }