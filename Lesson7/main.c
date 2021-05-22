/* //Previous definitions replaced by header file
#define RCGCGPIO *((unsigned int *)0x400FE608U)

#define GPIOF_BASE 0x40025000U 

#define GPIO_DIR  (*((unsigned int *)(GPIOF_BASE + 0x400U)))
#define GPIO_DEN  (*((unsigned int *)(GPIOF_BASE + 0x51CU)))
#define GPIO_DATA  (*((unsigned int *)(GPIOF_BASE + 0x3FCU)))
*/

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

#include <stdint.h>
#include "tm4c123gh6pm.h"

int main() {
    SYSCTL_RCGCGPIO_R |= (1U << 5);   /* enable clock for GPIOF */
    SYSCTL_GPIOHBCTL_R |= (1U << 5);   /* enable AHB for GPIOF */
    GPIO_PORTF_AHB_DIR_R |= (LED_RED|LED_BLUE|LED_GREEN); // set pins 1,2, and 3 as outputs
    GPIO_PORTF_AHB_DEN_R  |= (LED_RED|LED_BLUE|LED_GREEN); 

    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    while(1){
        //GPIO_PORTF_AHB_DATA_R |= LED_RED;
        //*((unsigned long volatile *)(0x40025000 + (LED_RED << 2))) = LED_RED;
        //*(GPIO_PORTF_AHB_DATA_BITS_R + LED_RED) = LED_RED;
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
        volatile int counter[2] = {0,0};
        while (counter[0] < 1000000){      // delay loop
            ++counter[0];//Do nothing
        }
        //counter = 0;
        //GPIO_PORTF_AHB_DATA_R = GPIO_PORTF_AHB_DATA_R ^ LED_RED; //Not optimal it seems
        //GPIO_PORTF_AHB_DATA_R &= ~LED_RED;  // bit clearing convention optimized by compiler
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
        while (*(counter + 1) < 1000000){      // delay loop
            ++counter[1];//Do nothing
        }
    }
    return 0;
}
