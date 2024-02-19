#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void writeOutput(const char *command, const char *output) {
    printf("The output of: %s : is\n", command);
    printf(">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
}

void removeExtraChar(char *str) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != '\r' && str[i] != '\n') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        return 1;
    }
    char **commands;
    commands = malloc(sizeof(char *) * 1000);
    size_t lineCount = 0;
    size_t charCount = 0;
    char c;

    do {
        c = fgetc(file);
        if (ferror(file)) {
            return 1;
        }
        if(c == '\n' && charCount == 0) {
            continue;
        }
        if (feof(file)) {
            if (charCount != 0) {
                commands[lineCount] = realloc(commands[lineCount], charCount + 1);
                commands[lineCount][charCount] = '\0';
                removeExtraChar(commands[lineCount]);
                lineCount++;
            }
            break;
        }
        if (charCount == 0)
            commands[lineCount] = malloc(1000);
        commands[lineCount][charCount] = c;
        charCount++;
        if (c == '\n') {
            commands[lineCount] = realloc(commands[lineCount], charCount + 1);
            commands[lineCount][charCount] = '\0';
            removeExtraChar(commands[lineCount]);  
            lineCount++;

            if (lineCount % 1000 == 0) {
                commands = realloc(commands, sizeof(char *) * (lineCount + 1000));
            }
            charCount = 0;
        } else if (charCount % 1000 == 0) {
            commands[lineCount] = realloc(commands[lineCount], (charCount + 1000));
        }

    } while (1);

    commands = realloc(commands, sizeof(char *) * lineCount);

    for (size_t i = 0; i < lineCount; ++i) {
        int fd[2];
        if (pipe(fd) == -1) {
            return 1;
        }

        pid_t pid;

        pid = fork();

        if (pid < 0) { 
            return 1;
        } else if (pid == 0) {
            close(fd[0]);  
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            execlp("/bin/sh", "/bin/sh", "-c", commands[i], (char *)NULL);
            exit(EXIT_FAILURE);
        } else { 
            wait(NULL);
            close(fd[1]);

            char buffer[3333];
            ssize_t stringRead;

            stringRead = read(fd[0], buffer, sizeof(buffer) - 1);
            if (stringRead > 0) {
                buffer[stringRead] = '\0';
                writeOutput(commands[i], buffer);
            }
            close(fd[0]);
            
        }
    }
    for(int i = 0; i < lineCount; i++) {
        free(commands[i]);
    }
    free(commands);
    return 0;
}
