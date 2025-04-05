#define RCC_BASE       0x40021000 //page no 50 in register

#define GPIOC_BASE     0x40011000 //page no 51 in register

#define RCC_APB2ENR    (*(volatile unsigned int *)(RCC_BASE + 0x18))

#define GPIOC_CRH      (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR      (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

#define RCC_IOPCEN     0x10
#define GPIOC13_MASK   0x2000

void delay(volatile unsigned int time)
{
    while (time--)
        for (volatile int i = 0; i < 800; i++);
}

int main(void)
{
    // 1. Enable GPIOC clock
    RCC_APB2ENR |= RCC_IOPCEN;

    // 2. Configure PC13 as push-pull output, 2MHz
    GPIOC_CRH &= ~(0xF << 20);        // Clear CNF13[1:0] and MODE13[1:0]
    GPIOC_CRH |=  (0x3 << 20);        // MODE13 = 10 (Output mode, max speed 2 MHz)
                                      // CNF13 = 00 (General purpose output push-pull)

    // 3. Toggle LED
    while (1)
    {
        GPIOC_ODR ^= GPIOC13_MASK;   // Toggle PC13
        delay(1000);
    }

    return 0;
}
