#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#define READ 0
#define WRITE 1

int main(){
    int piped1[2]; // 子进程写1，父进程读0
    int piped2[2]; // 父进程写1，子进程读0

    pipe(piped1);
    pipe(piped2); 

    int pid = fork();

    if(pid < 0){
        printf("fork error...\n");
    }
    else if(pid == 0){
        //read bytes from parent
        close(piped2[WRITE]);
        char buf[10];
        read(piped2[READ], buf, sizeof(buf));
        printf("%d: received ping\n", getpid(), buf);
        close(piped2[READ]);

        //send bytes to parent
        close(piped1[READ]);
        write(piped1[WRITE], "pong", 4);
        close(piped1[WRITE]);

    }else{
        //send bytes to child
        close(piped2[READ]);
        write(piped2[WRITE], "ping", 4);
        close(piped2[WRITE]);

        //read bytes from child
        close(piped1[WRITE]);
        char buf[10];
        read(piped1[READ], buf, sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);
        close(piped1[READ]);
    }
    exit(0);
}