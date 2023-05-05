//Aybike Zeynep Taskin
//150190004

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void right_tree(int N){
    //at each fork call, create 1 left child. 
    //then call the function again recursively until N becomes zero to create N right children
    /*each fork cretaes: 
        (P)
        / \
       C   P
    we want to call the function again on the right child (parent)
         P
        / \
       C   (P)
           / \
          C   P
    */
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1<0){
        fprintf(stderr, "Fork Failed");
        exit(1);
    }
    //child process (left child)
    else if(pid1==0){
        printf("Left child %d with parent %d is created. N=%d\n", getpid(), getppid(), N);
        wait(NULL);
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
            else if(pid2 == 0){
                printf("Right child %d with parent %d is created. N=%d\n", getpid(), getppid(), N);
                N--;
                right_tree(N);
                //exit(0);
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
    //N positive integer. call the fork recursively and create right children N times. 
    int N;
    printf("Enter positive integer N value: ");
    scanf("%d", &N);
    right_tree(N);

    return 0;
}

