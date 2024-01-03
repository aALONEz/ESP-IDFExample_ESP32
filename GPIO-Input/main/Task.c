#include "LED.h"
#include "KEY.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

//LED0相关
TaskHandle_t LED0TaskHandler = NULL;//LED0任务句柄
#define LED0Task_GPIO       GPIO_NUM_2
#define LED0Task_StackSize  512 * 4//注意ESP-IDF的FreeRTOS的堆栈大小是按照字节为单位,不是传统的字为单位
#define LED0Task_Priority   2 | portPRIVILEGE_BIT//要设置的优先级需要或上portPRIVILEGE_BIT,ESP-IDF优先级的值越高,优先级越大

//LED1相关
TaskHandle_t LED1TaskHandler = NULL;//LED1任务句柄
#define LED1Task_GPIO       GPIO_NUM_4
#define LED1Task_StackSize  512 * 4//注意ESP-IDF的FreeRTOS的堆栈大小是按照字节为单位,不是传统的字为单位
#define LED1Task_Priority   2 | portPRIVILEGE_BIT//要设置的优先级需要或上portPRIVILEGE_BIT,ESP-IDF优先级的值越高,优先级越大

//KEY0相关
TaskHandle_t KEY0TaskHandler = NULL;//LED1任务句柄
#define KEY0Task_GPIO       GPIO_NUM_16
#define KEY0Task_StackSize  512 * 4//注意ESP-IDF的FreeRTOS的堆栈大小是按照字节为单位,不是传统的字为单位
#define KEY0Task_Priority   2 | portPRIVILEGE_BIT//要设置的优先级需要或上portPRIVILEGE_BIT,ESP-IDF优先级的值越高,优先级越大

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

/// @brief KEY0任务函数,按照KEY0就创建LED0Task任务,如果LED0Task任务已存在就删除LED0Task任务
/// @param parameter FreeRTOS任务函数固定参数,本函数没有使用到
void KEY0Task(void* parameter)//任务函数的,函数头必须要是void 函数名(void* 变量名)
{
    // 初始化KEY
    KEY_Init(KEY0Task_GPIO);
    while (1)
    {
        if(KEY_Get_State(KEY0Task_GPIO) == KEY_Conduction)
        {
            if (LED0TaskHandler == NULL)
            {
                xTaskCreatePinnedToCore(LED0Task, "LED0Task", LED0Task_StackSize, NULL, LED0Task_Priority, &LED0TaskHandler, 1);
            }
            else
            {
                vTaskDelete(LED0TaskHandler);
                LED_Switch(LED0Task_GPIO, LED_OFF);
                LED0TaskHandler = NULL;
            }
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}
