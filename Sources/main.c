#include <stdio.h>
/*-------------FreeRTOS Includes--------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/*-------------Custom Driver Includes--------------*/
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "mpu6050.h"

void USART2_Config(); // Configuring UART to send data to the computer

int main(void)
{
    UART2_GPIO_Init();
    USART2_Config();

    while (1)
    {
        printf("Hello, World!\n");
        for (int i = 0; i < 100; i++)
            ;
    }

    return 0;
}
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) // Stack Overflow Hook
{
    /* Print or log stack overflow for task debugging */

    for (;;)
        ; // Halt system to debug
}

void USART2_Config()
{
    UARTConfig_t uart2;                      // Creating UART Instance
    uart2.pUARTx = USART2;                   // Adding USART peripheral to the instance
    uart2.Init.BaudRate = 115200U;           // Configuring Baud Rate
    uart2.Init.Mode = UART_MODE_TX_ONLY;     // Configuring Mode/Direction
    uart2.Init.Parity = UART_PARITY_NONE;    // Configuring Parity Control
    uart2.Init.Parity = UART_WORD_LEN_8BITS; // Configuring Word length
    UART_Init(&uart2);
}

int __io_putchar(int ch) // Overwriting for use printf via UART
{
    UART_SendChar(USART2, ch);
    return ch;
}
