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
    unsigned int a =  0x5A5A5A5A;
    unsigned int b = 0xDEADBEEF;
    unsigned int c;
    
    
    int x = 1024;
    int y = -1024;
    int z;
    z = x >> 3;
    z = y >> 3;
    
    c = a | b; // OR
    c = a & b; // AND
    c = a ^ b; // Exclusive OR
    c = ~b; // NOT
    c = b >> 1; // right-shift
    c = b << 1; // left-shift
    
    
    
    SYSCTL_RCGCGPIO_R |= 0x20U;   /* enable clock for GPIOF */
    GPIO_PORTF_DIR_R |= (LED_RED|LED_BLUE|LED_GREEN); // set pins 1,2, and 3 as outputs
    GPIO_PORTF_DEN_R  |= (LED_RED|LED_BLUE|LED_GREEN); 

    GPIO_PORTF_DATA_R |= LED_BLUE;
    while(1){
        GPIO_PORTF_DATA_R |= LED_RED;
        volatile int counter = 0;
        while (counter < 1000000){      // delay loop
            ++counter;//Do nothing
        }
        counter = 0;
        //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ LED_RED; //Not optimal it seems
        GPIO_PORTF_DATA_R &= ~LED_RED;  // bit clearing convention optimized by compiler
        while (counter < 1000000){      // delay loop
            ++counter;//Do nothing
        }
    }
    return 0;
}
