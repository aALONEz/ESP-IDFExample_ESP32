#include "IRremote.h"


uint32_t Count = 0;
void IRremoteISR(void* arg)
{
    Count++;
}

esp_err_t IRremote_Init(gpio_num_t GPIO_NUM_x)
{
    esp_err_t err;
    //ESP32每组GPIO只可以有一个边沿中断,如果一组GPIO没有一个边沿中断就可以有很多个电平中断
    //1.首先重置GPIO引脚状态
    err = gpio_reset_pin(GPIO_NUM_x);
    if(err != ESP_OK) return err;
    //2.配置GPIO,配置为输入模式,开启低电平中断,关闭上拉下拉电阻
    gpio_config_t IRremote;
    IRremote.intr_type = GPIO_INTR_LOW_LEVEL;//低电平触发
    IRremote.mode = GPIO_MODE_INPUT;//输入模式
    IRremote.pin_bit_mask = (1ULL << GPIO_NUM_x);//引脚掩码
    IRremote.pull_down_en = GPIO_PULLDOWN_DISABLE;//关闭下拉电阻
    IRremote.pull_up_en = GPIO_PULLUP_DISABLE;//关闭上拉电阻

    err = gpio_config(&IRremote);
    if(err != ESP_OK) return err;
    //3.GPIO引脚安装中断服务
    err = gpio_install_isr_service(ESP_INTR_FLAG_EDGE);
    if(err != ESP_OK) return err;
    //4.注册添加对应引脚中断函数
    err = gpio_isr_handler_add(GPIO_NUM_x, IRremoteISR, NULL);
    if(err != ESP_OK) return err;
    //5.使能对应GPIO的中断
    err = gpio_intr_enable(GPIO_NUM_x);
    if(err != ESP_OK) return err;
    return err;
}

uint32_t IRremote_Get_Count(void)
{
    return Count;
}
