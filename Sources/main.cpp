#include <cstdio>
/*-------------FreeRTOS Includes--------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/********Tensorflow lite micro include *************/
#include "micro/micro_mutable_op_resolver.h"
#include "micro/tflite_bridge/micro_error_reporter.h"
#include "micro/micro_interpreter.h"
#include "schema/schema_generated.h"

// /*-------------Custom Driver Includes--------------*/
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "mpu6050.h"
#include "model.h"

// TensorFlow Lite Micro objects
tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter *error_reporter = &micro_error_reporter;

const tflite::Model *model = ::tflite::GetModel(model_tflite);

using GestureOpResolver = tflite::MicroMutableOpResolver<1>;

GestureOpResolver resolver;

TfLiteStatus RegisterOps(GestureOpResolver &op_resolver)
{
    TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected());
    return kTfLiteOk;
}

const int tensor_arena_size = 2 * 1024;
uint8_t tensor_arena[tensor_arena_size];

tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, tensor_arena_size);

TfLiteTensor *input = interpreter.input(0);

void USART2_Config(); // Configuring UART to send data to the computer

int main(void)
{
    UART2_GPIO_Init();
    USART2_Config();

    // Check TensorFlow Lite schema version
    if (model->version() != TFLITE_SCHEMA_VERSION)
    {
        TF_LITE_REPORT_ERROR(error_reporter,
                             "Model provided is schema version %d not equal "
                             "to supported version %d.\n",
                             model->version(), TFLITE_SCHEMA_VERSION);
    }
    else
    {
        UART_SendBuffer(USART2, (uint8_t *)"Version Matched\n", 20);
    }

    // Register operations
    RegisterOps(resolver);

    // Allocate tensors
    interpreter.AllocateTensors();

    while (1)
    {
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
    UARTConfig_t uart2;                       // Creating UART Instance
    uart2.pUARTx = USART2;                    // Adding USART peripheral to the instance
    uart2.Init.BaudRate = 115200U;            // Configuring Baud Rate
    uart2.Init.Mode = UART_MODE_TX_ONLY;      // Configuring Mode/Direction
    uart2.Init.Parity = UART_PARITY_NONE;     // Configuring Parity Control
    uart2.Init.WordLen = UART_WORD_LEN_8BITS; // Configuring Word length
    UART_Init(&uart2);
}

extern "C" int __io_putchar(int ch) // Overwriting for use printf via UART
{
    UART_SendChar(USART2, ch);
    return ch;
}
