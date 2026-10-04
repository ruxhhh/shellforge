#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

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

        if (strcmp(line, "exit") == 0) {
            break;
        }

        if (strlen(line) > 0) {
            printf("You typed: %s\n", line);
        }
    }

    free(line);

    return 0;
}
