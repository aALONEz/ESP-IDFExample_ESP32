#include "KEY.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

esp_err_t KEY_Init(gpio_num_t GPIO_NUM_x)
{
    esp_err_t err;
    //1.重置GPIO
    err = gpio_reset_pin(GPIO_NUM_x);
    if(err != ESP_OK)
    {
        return err;
    }
    //2.配置GPIO为输入模式,打开上拉电阻
    gpio_config_t Key_Config;
    Key_Config.intr_type = GPIO_INTR_DISABLE;//关闭中断
    Key_Config.mode = GPIO_MODE_INPUT;//输入模式
    Key_Config.pin_bit_mask = (1ULL << GPIO_NUM_x);//连接KEY的引脚
    Key_Config.pull_down_en = GPIO_PULLDOWN_DISABLE;//下拉电阻关闭
    Key_Config.pull_up_en = GPIO_PULLUP_ENABLE;//上拉电阻使能

    err = gpio_config(&Key_Config);
    if(err != ESP_OK)
    {
        return err;
    }
    return err;
}

KEY_State KEY_Get_State(gpio_num_t GPIO_NUM_x)
{
    if (gpio_get_level(GPIO_NUM_x) == KEY_Conduction)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS); // 消抖
        if (gpio_get_level(GPIO_NUM_x) == KEY_Conduction)
        {
            while (gpio_get_level(GPIO_NUM_x) == KEY_Conduction) // 松手停止循环
            {
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            return KEY_Conduction;
        }
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);//松手消抖
    return KEY_Disconnected;
}
