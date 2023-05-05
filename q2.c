//Aybike Zeynep Taskin
//150190004

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void left_right_tree(int N, int M){
    /*each fork cretaes: 
        (P)
        / \
       C   P
    for the left child, create child for M times and recurse this for N rigth child (recurse)
         Pclear

        / \
      (C)  (P)
      / \   / \
     C   P C   P
    */

   
    pid_t pid, pid1, pid2;

    pid = fork();

    if(pid<0){
        fprintf(stderr, "Fork Failed");
        exit(1);
    }
    //child process (left child)
    else if(pid==0){
        //wait(NULL);
        printf("Left child %d with parent %d is created\n", getpid(), getppid());
        for(int i=1; i<M; i++){
            pid1 = fork();
            if(pid1 == 0){
                printf("Left child %d with parent %d is created\n", getpid(), getppid());
                //exit(0);
            }
            
            //parent
            else{
                wait(NULL);
                exit(0);
            }

        }
        exit(0);
    }
    
    //parent process
    else{
        wait(NULL);
        if(N>0){
            pid2 = fork();
            
            if(pid2 < 0){
                fprintf(stderr, "Fork Failed");
                exit(1);
            }
            //right child
            if(pid2 == 0){
                printf("Right child %d with parent %d is created N=%d\n", getpid(), getppid(), N);
                N--;
                left_right_tree(N, M);
                exit(0);
            }
            
            //parent
            else{
                wait(NULL);
                exit(0);
            }
        }
    }
    
    return;
}


int main(){
    //N and M positive integer. call the fork recursively and create right children N times. 
    int N, M;
    printf("Enter positive integer N and M values separated by space: ");
    scanf("%d %d", &N, &M);
    left_right_tree(N, M);

    return 0;
}

