#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    char *args[64];

    while (1) {
        printf("shellforge$ ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        int i = 0;

        char *token = strtok(line, " \t");

        while (token != NULL && i < 63) {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }

        args[i] = NULL;

        if (i == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {

            if (args[1] == NULL) {
                fprintf(stderr, "shellforge: missing path parameter\n");
            }
            else {
                if (chdir(args[1]) != 0) {
                    perror("Directory change failed");
                }
            }

            continue;
        }

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);

            perror("Execution error");
            exit(1);
        }
        else if (pid > 0) {
            waitpid(pid, NULL, 0);
        }
        else {
            perror("Fork error");
        }
    }

    free(line);

    return 0;
}
