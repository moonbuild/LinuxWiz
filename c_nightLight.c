#include <stdio.h> /* print */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* system */
#include <time.h> /* time */

int main(){
    time_t time_now;
    time(&time_now);

    struct tm *localTime = localtime(&time_now);

    int hour_now = localTime->tm_hour;
    // printf("%d\n",hour_now);

    const char *redshift = "redshift -O 2500";
    int result = 1;

    if(hour_now > 12){
        result = system(redshift);
    }
    if (result == 0){
        const char *message = "notify-send 'NightLight is on'";
        system(message);
    }
    else{
        const char *message = "notify-send 'NightLight has failed to turn on!'";
        system(message);
    }

sleep(2);
    redshift = "redshift -x && redshift -O 3000";
    system(redshift);
}