#include "stm32f4xx.h"

#define SAMPLE_COUNT 50  //50 samples per cycle
uint8_t sample_buffer[SAMPLE_COUNT];

void UART2_Init(void);
void UART2_SendChar(char c);
void UART2_SendString(const char* str);
void delay_ms(volatile uint32_t ms);

int main(void)
{
    UART2_Init();
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~(3<<(5*2));
    GPIOA->MODER |=  (1<<(5*2));
    GPIOA->MODER &= ~(3<<(0*2));

    while (1) // continuous capture
    {
        UART2_SendString("Starting capture...\r\n");
        for (int i=0; i<SAMPLE_COUNT; i++)
        {
            GPIOA->ODR ^= (1<<5);
            sample_buffer[i]=(GPIOA->IDR & 0x1)?1:0; // Read PA0 and store
            delay_ms(50);
        }

        UART2_SendString("Capture complete:\r\n");

        for (int i=0; i<SAMPLE_COUNT; i++)
        {
            UART2_SendChar(sample_buffer[i] ? '1' : '0');
            UART2_SendChar('\n');
        }

        UART2_SendString("Done\r\n");

        delay_ms(1000);
    }
}

void UART2_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // PA2 as TX (AF7)
    GPIOA->MODER &= ~(3<<(2*2));
    GPIOA->MODER |=  (2<<(2*2));
    GPIOA->AFR[0] &= ~(0xF<<(2*4));
    GPIOA->AFR[0] |=  (7<<(2*4));

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  // Enable USART2 clock

    USART2->BRR = 0x08B; // 115200 baud @ 16 MHz
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void UART2_SendChar(char c)
{
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = c;
}

void UART2_SendString(const char* str)
{
    while (*str)
    {
        UART2_SendChar(*str++);
    }
}

void delay_ms(volatile uint32_t ms)
{
    for (volatile uint32_t i = 0; i<(ms*4000); i++); // delay loop
}
//removesqwerty
