#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"

xQueueHandle IREventQueue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(IREventQueue, &gpio_num, NULL);
}

void IRTask(void* arg)
{
    uint32_t IoNum;
    uint32_t Count = 0;
    while(1)
    {
        ESP_LOGD("IRTask", "IRTask执行中");
        if(xQueueReceive(IREventQueue, &IoNum, portMAX_DELAY))//一直等待就已经让他进入阻塞状态了
        {
            if(IoNum == GPIO_NUM_2)
            {
                ESP_LOGD("IR", "Count: %d", Count);
                Count++;
            }
        }
    }
}

void app_main(void)
{
    //ESP32每组GPIO只可以有一个边沿中断,如果一组GPIO没有一个边沿中断就可以有很多个电平中断
    //1.首先重置GPIO引脚状态
    gpio_reset_pin(GPIO_NUM_2);
    //2.配置GPIO,配置为输入模式,开启低电平中断,关闭上拉下拉电阻
    gpio_config_t IRremote;
    IRremote.intr_type = GPIO_INTR_HIGH_LEVEL;//低电平触发
    IRremote.mode = GPIO_MODE_INPUT;//输入模式
    IRremote.pin_bit_mask = (1ULL << GPIO_NUM_2);//引脚掩码
    IRremote.pull_down_en = GPIO_PULLDOWN_DISABLE;//关闭下拉电阻
    IRremote.pull_up_en = GPIO_PULLUP_DISABLE;//关闭上拉电阻

    gpio_config(&IRremote);
    //3.创建一个队列
    IREventQueue = xQueueCreate(10, sizeof(uint32_t));
    //4.创建IRTask任务
    xTaskCreatePinnedToCore(IRTask, "IR_ISR_Task", 4096, NULL, 2, NULL, 1);
    //5.GPIO引脚安装中断服务
    gpio_install_isr_service(0);
    //6.注册添加对应引脚中断函数
    gpio_isr_handler_add(GPIO_NUM_2, gpio_isr_handler, (void*)GPIO_NUM_2);
    //7.使能对应GPIO的中断
    gpio_intr_enable(GPIO_NUM_2);
    while(1)
    {
        ESP_LOGD("System", "运行中...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}
