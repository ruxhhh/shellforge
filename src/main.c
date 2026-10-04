#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[64];

    while (1) {
        printf("shellforge$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);

        if (nread == -1) {
            printf("\nExiting cleanly...\n");
            break;
        }

        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        int i = 0;

        char *token = strtok(line, " \t");

        while (token != NULL && i < 63) {
            args[i] = token;
            i++;
            token = strtok(NULL, " \t");
        }

        args[i] = NULL;

        if (i == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        printf("Command detected: %s (Total args: %d)\n",
               args[0], i - 1);

        for (int j = 0; j < i; j++) {
            printf(" -> args[%d]: %s\n", j, args[j]);
        }
    }

    free(line);

    return 0;
}
