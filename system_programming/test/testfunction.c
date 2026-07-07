#include <stdio.h>
#include <time.h>
#include <unistd.h> 

void print_time_for_five_seconds() 
{
    int i = 0;
    for (i = 0; i < 5; ++i) 
    {
        time_t raw_time;
        struct tm *time_info;

        time(&raw_time);
        
        time_info = localtime(&raw_time);

        printf("Current time: %02d:%02d:%02d\n", 
               time_info->tm_hour, 
               time_info->tm_min, 
               time_info->tm_sec);
        
        fflush(stdout); 

        if (i < 4) 
        {
            sleep(1); 
        }
    }
}

int main() {
    printf("Starting 5-second timer:\n");
    print_time_for_five_seconds();
    printf("Done!\n");
    return 0;
}