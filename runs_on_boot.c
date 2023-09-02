#include <stdio.h> /* print perror fopen fclose */
#include <stdlib.h> /* system exit */
#include <unistd.h> /* dup2 fileno */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <time.h> /* time */

int main(){
    FILE *logFile = fopen("log.txt", "a");
    if(!logFile){
        perror("Error opening log File");
        exit(1);
    }
    const char *programs[] = {
        "./c_nightLight",
        "./normalCode"
    };

    int numPrograms = sizeof(programs) / sizeof(programs[0]);

    time_t time_now;
    struct tm *info;
        time(&time_now);
        info = localtime(&time_now);

        char timestamp[80];
        strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", info);
        fprintf(logFile, "Time-Now: %s\n",timestamp);

    for (int i=0; i<numPrograms; i++){

        pid_t pid = fork();

        if (pid == -1){
            perror("Error creating child process");
            exit(1);
        }
        else if (pid == 0){
            dup2(fileno(logFile), STDOUT_FILENO);
            dup2(fileno(logFile), STDERR_FILENO);

            const char *fileName = programs[i] + 2;
            printf("Executing file: %s\n", fileName);
            fflush(stdout);


            execl(programs[i], programs[i], NULL);

            fprintf(stderr, "Error executing file %s", programs[i]);
            exit(1);
        }
        int status;
        wait(&status);

    }

    fprintf(logFile, "~~~~~~~~~\n");

    fclose(logFile);
    printf("All programs have been executed\n");
    return 0;

}