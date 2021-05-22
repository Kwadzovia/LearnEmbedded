/* //Previous definitions replaced by header file
#define RCGCGPIO *((unsigned int *)0x400FE608U)

#define GPIOF_BASE 0x40025000U 

#define GPIO_DIR  (*((unsigned int *)(GPIOF_BASE + 0x400U)))
#define GPIO_DEN  (*((unsigned int *)(GPIOF_BASE + 0x51CU)))
#define GPIO_DATA  (*((unsigned int *)(GPIOF_BASE + 0x3FCU)))
*/

#include <stdint.h>
#include "tm4c123gh6pm.h"

int main() {
    SYSCTL_RCGCGPIO_R = 0x20U;   /* enable clock for GPIOF */
    GPIO_PORTF_DIR_R = 0x0EU; // set pins 1,2, and 3 as outputs
    GPIO_PORTF_DEN_R  = 0x0EU; 
    
    while(1){
        GPIO_PORTF_DATA_R = 0x02U;
        volatile int counter = 0;
        while (counter < 1000000){      // delay loop
            ++counter;//Do nothing
        }
        counter = 0;
        GPIO_PORTF_DATA_R = 0x00U;
        while (counter < 1000000){      // delay loop
            ++counter;//Do nothing
        }
    }
    return 0;
}
