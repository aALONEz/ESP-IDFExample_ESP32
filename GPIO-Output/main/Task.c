#include "LED.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//LED0相关
TaskHandle_t LED0TaskHandler;//LED0任务句柄
#define LED0Task_GPIO       GPIO_NUM_2
#define LED0Task_StackSize  512 * 4//注意ESP-IDF的FreeRTOS的堆栈大小是按照字节为单位,不是传统的字为单位
#define LED0Task_Priority   2 | portPRIVILEGE_BIT//要设置的优先级需要或上portPRIVILEGE_BIT,ESP-IDF优先级的值越高,优先级越大

//LED1相关
TaskHandle_t LED1TaskHandler;//LED1任务句柄
#define LED1Task_GPIO       GPIO_NUM_4
#define LED1Task_StackSize  512 * 4//注意ESP-IDF的FreeRTOS的堆栈大小是按照字节为单位,不是传统的字为单位
#define LED1Task_Priority   2 | portPRIVILEGE_BIT//要设置的优先级需要或上portPRIVILEGE_BIT,ESP-IDF优先级的值越高,优先级越大

/// @brief LED0任务函数,让LED0按照每500ms亮灭一次.循环亮灭
/// @param parameter FreeRTOS任务函数固定参数,本函数没有使用到
void LED0Task(void* parameter)//任务函数的,函数头必须要是void 函数名(void* 变量名)
{
    esp_err_t err;
    err = LED_Init(LED0Task_GPIO);//引脚2连接LED 初始化
    if(err != ESP_OK)
    {
        vTaskDelete(NULL);//如果LED_Init返回值不是ESP_OK就说明GPIO初始化出错那么就删除当前任务,然后返回
        ESP_LOGD("LED0Task", "LED0任务LED初始化出错,错误代码: %d", err);
        return;
    }
    for(;;)//死循环
    {
        LED_Switch(LED0Task_GPIO, LED_ON);
        vTaskDelay(500 / portTICK_PERIOD_MS);//延时500ms
        LED_Switch(LED0Task_GPIO, LED_OFF);
        vTaskDelay(500 / portTICK_PERIOD_MS);//延时500ms
    }
}

/// @brief LED1任务函数,让LED1按照每300ms亮灭一次.循环亮灭
/// @param parameter FreeRTOS任务函数固定参数,本函数没有使用到
void LED1Task(void* parameter)//任务函数的,函数头必须要是void 函数名(void* 变量名)
{
    esp_err_t err;
    err = LED_Init(LED1Task_GPIO);//引脚2连接LED 初始化
    if(err != ESP_OK)
    {
        vTaskDelete(NULL);//如果LED_Init返回值不是ESP_OK就说明GPIO初始化出错那么就删除当前任务,然后返回
        ESP_LOGD("LED1Task", "LED1任务LED初始化出错,错误代码: %d", err);
        return;
    }
    for(;;)//死循环
    {
        LED_Switch(LED1Task_GPIO, LED_ON);
        vTaskDelay(300 / portTICK_PERIOD_MS);//延时500ms
        LED_Switch(LED1Task_GPIO, LED_OFF);
        vTaskDelay(300 / portTICK_PERIOD_MS);//延时500ms
    }
}