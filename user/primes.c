#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define READ 0
#define WRITE 1
#define MAXSIZE 100


void child(int *fd){
    close(fd[WRITE]);
    int number;
    // if(read(fd[READ], &number, sizeof(number)) == 0){
    //     //31往后没有读入了，读入了一个空值0，后续会爆掉
    //     exit(0);
    // }
    read(fd[READ], &number, sizeof(number));
    printf("prime %d\n", number);

    int send;
    //先判断后续有没有读入值了，避免空值，后面do while判断
    if(read(fd[READ], &send, sizeof(send))){
        int pipedl[2];
        pipe(pipedl);
            int pid = fork();
        if(pid < 0){
            printf("fork error..\n");
        }
        else if(pid == 0){
            child(pipedl);
        }
        else{
            close(pipedl[READ]);
            do{
                if(send % number != 0){
                    write(pipedl[WRITE], &send, sizeof(send));
                }
            }while(read(fd[READ], &send, sizeof(number)));
            close(pipedl[WRITE]);
            close(fd[READ]);
            wait((int*)0);
        }
    }
    else{
        close(fd[READ]); //donot forget
    }
    exit(0);
}

int main(){
    //双通道，进程间通信，一个读，一个写
    //主进程发送2-35，子进程接着发送，知道打印35
    int pipedr[2];
    pipe(pipedr);

    int pid = fork();

    if(pid < 0){
        printf("fork error...\n");
    }
    else if(pid == 0){
        child(pipedr);
    }else {
        close(pipedr[READ]);
        
        for(int i = 2; i <= 35; i++){
            write(pipedr[WRITE], &i, sizeof(int));
        }
        close(pipedr[WRITE]);
        wait((int *) 0);
    }
    exit(0);
}
