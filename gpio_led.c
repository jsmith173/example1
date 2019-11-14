#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define ENABLE_LED_MSG	
#define GPIOPIN gpio68

void sig_handler(int signo)
{
    if (signo == SIGINT)
        printf("\nreceived SIGINT\n");
    exit(1);
}

int main(void) {

    int status;
    unsigned int cnt=0;
    
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIG Handler\n");
        exit(1);
    }

    status = access("/sys/class/gpio/GPIOPIN/value", F_OK );

    if (status == -1) {
        // file doesn't exist
        printf("GPIOPIN file doesn't exist\n");
        exit(1);
    }

    //Set GPIOPIN as output
    system("echo out > /sys/class/gpio/GPIOPIN/direction"); 
    sleep(1);    

    while(1) {
        if (cnt % 2 == 0) {
		   #ifdef ENABLE_LED_MSG	
           printf("%u) LED --- ON\n", cnt);
           printf("Echo ON for GPIOPIN\n");
		   #endif
           system("echo 1 > /sys/class/gpio/GPIOPIN/value");
        }
        else {
		   #ifdef ENABLE_LED_MSG	
           printf("%u) LED --- OFF\n", cnt);
		   #endif
           system("echo 0 > /sys/class/gpio/GPIOPIN/value");
        }

        cnt += 1;
        sleep(1);
    }

    return 0;
}

