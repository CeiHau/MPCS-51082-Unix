
#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>
#include<stdio.h>

int redirect(char * filename){

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return EXIT_SUCCESS;
}
extern char **environ;

int main(int argc, char * argv[]) {
    pid_t pid[100], wpid;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int index = 0, child_status;

    // If the user forgets to include the command-line argument
    if (argc == 1) {
        printf("File argument not provided.\n");
        exit(EXIT_FAILURE);
    }

    while((read = getline(&line, &len, stdin)) != -1) {
        // Remove the "\n" in the end of line, if exist
        int ln = strlen(line) - 1;
        if (*line && line[ln] == '\n') 
            line[ln] = '\0';
        // printf("%s\n", line);
        char * myargv[] = {"../p1/du", "user", line, NULL};
        if ((pid[index] = fork()) == 0) {   // child            
            redirect(argv[1]);
            if (execve(myargv[0], myargv, environ) < 0) {
                printf("%s: Command not found.\n", myargv[0]);  
                exit(1); 
            }
            exit(100 + index);
        }
        
        index++;
    }

    // wait all child finished
    while((wpid = wait(&child_status)) != -1) {

    }
    printf("done\n");
}