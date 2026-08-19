#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo){
    if(signo == SIGINT){
        printf("收到 SIGINT: %d\n", signo);
        exit(signo);    
    }
}


int main (int arg, const char* agc[]){

    if (signal(SIGINT, sig_handler) == SIG_ERR){
        printf("无法捕捉 SIGINT\n");
        exit(1);
    }

    while(1){
        sleep(1);
        printf("hello\n");
    }
    return 0 ;
}