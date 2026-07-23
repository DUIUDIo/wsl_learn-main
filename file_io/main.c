#include <stdio.h>

int main()
    {
    char *filename = "example.txt";
    FILE *fp = fopen(filename, "w+");
    if (fp == NULL)
        {
        perror("错误，无法打开文件");
        return -1;
        }
    fputc('H', fp);
    int result = fputs("ello, World!", fp);
    if (result == EOF)
        {
        perror("错误，无法写入文件");
        fclose(fp);
        return -1;
        }
    
    // 将文件指针重置到文件开头，以便读取刚才写入的内容
    rewind(fp);
    char buffer[100];

    printf("%c\n", fgetc(fp)); // 读取第一个字符 'H'
    buffer[0] = fgetc(fp); // 初始化缓冲区
    fclose(fp);
    return 0;
}