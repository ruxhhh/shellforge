#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
//declares a pointer variable named line that points to a char data type and initializes //it to a NULL pointer value.
char *line = NULL;
//initializes an unsigned integer variable named len to zero
size_t len = 0;
//declares an array of 64 pointers to characters
char *args[64];
while (1) {
// displaying prompt
printf("shellforge$ ");
// to avoid buffer delay
fflush(stdout);
//user inputs ctrl+d
if (getline(&line, &len, stdin) == -1) break;
//removes newline with NULL (Line termination)

line[strcspn(line, "\n")] = '\0';
int i = 0;
// splits the line into words delimited by  space or tab
char *token = strtok(line, " \t");
// all word in line are stored in args[] array 
while (token != NULL && i < 63) {
args[i++] = token;
token = strtok(NULL, " \t");
}
// args[] terminated by NULL
args[i] = NULL;
// if no input from user loop continues and prints prompt 
if (i == 0) continue;
// if user inputs exit process ends
if (strcmp(args[0], "exit") == 0) break;
// FORK CHILD GENERATION ENGINE ---
pid_t pid = fork();
if (pid == 0) {
// Child PROCESS
(execvp(args[0], args);
// if exec fails the below code runs
perror("Command execution error");
exit(1); 
}

else if (pid > 0) {
// Parent branch: Wait synchronously for child target execution to finish
waitpid(pid, NULL, 0);
}
else 
{
// if child unable to create 
perror("Fork creation error");
}
}
free(line);
return 0;
}
