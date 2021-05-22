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

unsigned fact(unsigned n);


    


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "delay.h"

int main() {
    
    volatile unsigned x;
    x = fact(0U);
    x = 2U + 3U*fact(1U);
    (void)fact(5U);
    
    SYSCTL_RCGCGPIO_R |= (1U << 5);   /* enable clock for GPIOF */
    SYSCTL_GPIOHBCTL_R |= (1U << 5);   /* enable AHB for GPIOF */
    GPIO_PORTF_AHB_DIR_R |= (LED_RED|LED_BLUE|LED_GREEN); // set pins 1,2, and 3 as outputs
    GPIO_PORTF_AHB_DEN_R  |= (LED_RED|LED_BLUE|LED_GREEN); 

    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    while(1){
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
        delay(1000000);
        //counter = 0;
        GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
        delay(500000);
    }
    return 0;
}

unsigned fact(unsigned n) {
    // 0! = 1
    // n! = n*(n-1)! for n> 0
    
    if (n == 0U){
        return 1U;
    } else {
        return n*fact(n - 1U); 
    }
    
}