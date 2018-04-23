// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main()
{
    int p[2];
    char buf[16];

    if (pipe(p) < 0) {
        printf("Pipe failed.\n");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        printf("Fork failed.\n");
        exit(1);
    } else if (rc == 0) {
        write(p[1], msg1, 16);
        write(p[1], msg2, 16);
        write(p[1], msg3, 16);
    } else {
        // int wc = waitpid(rc, NULL, 0);

        for (int i = 0; i < 3; i++) {
            read(p[0], buf, 16);
            printf("%s\n", buf);
        }
    }
    
    return 0;
}
