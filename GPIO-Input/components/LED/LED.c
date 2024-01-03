#include "LED.h"//引入LED.h头文件

esp_err_t LED_Init(gpio_num_t GPIO_NUM_x)
{
    esp_err_t err = 0;
    //1.重置GPIO
    err = gpio_reset_pin(GPIO_NUM_x);
    if(err != ESP_OK)//判断是否引脚重置成功
    {
        return err;
    }
    //2.配置GPIO
    gpio_config_t LED0_Config;//定义配置结构体

    LED0_Config.intr_type = GPIO_INTR_DISABLE;//关闭中断
    LED0_Config.mode = GPIO_MODE_INPUT_OUTPUT;//输入和输出模式,输出模式为了驱动LED,输入模式为了检测LED当前状态
    LED0_Config.pin_bit_mask = (1ULL << GPIO_NUM_x);//这里1左移引脚编号位正好.1是选择这个引脚,0是不选择。1ULL表示这个1是unsigned long long 类型的
    LED0_Config.pull_down_en = GPIO_PULLDOWN_DISABLE;//关闭下拉电阻
    LED0_Config.pull_up_en = GPIO_PULLUP_DISABLE;//关闭上拉电阻
    err = gpio_config(&LED0_Config);
    if(err != ESP_OK)//判断配置GPIO是否成功
    {
        return err;
    }
    //3.让GPIO输出低电平.由于是高电平点亮,所以此时默认不点亮
    err = gpio_set_level(GPIO_NUM_x, LED_OFF);
    if(err != ESP_OK)//判断配置GPIO是否成功
    {
        return err;
    }
    return ESP_OK;
}

esp_err_t LED_Switch(gpio_num_t GPIO_NUM_x, LED_State LEDx_State)
{
    return gpio_set_level(GPIO_NUM_x, LEDx_State);
}

LED_State LED_Get_State(gpio_num_t GPIO_NUM_x)
{
    if(gpio_get_level(GPIO_NUM_x) == LED_ON)//判断电平状态是不是等于LED_ON
    {
        return LED_ON;//等于就直接返回LED_ON
    }
    return LED_OFF;//否则就返回LED_OFF
}
