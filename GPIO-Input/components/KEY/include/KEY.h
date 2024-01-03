#ifndef __KEY_H_
#define __KEY_H_

//引入相关头文件
#include <stdio.h>
#include "driver/gpio.h"


//枚举按键状态
typedef enum
{
    KEY_Conduction      = 0,//按键导通电平状态
    KEY_Disconnected    = 1,//按键断开电平状态
}KEY_State;

/// @brief 按键初始化,输入模式上拉电阻开启,下拉电阻关闭
/// @param GPIO_NUM_x 连接按键的引脚编号,其中x表示引脚编号.举例:引脚编号:2 ,那么参数就填写GPIO_NUM_2.
/// @return 成功初始化返回ESP_OK,发生错误会返回对应错误码
esp_err_t KEY_Init(gpio_num_t GPIO_NUM_x);

/// @brief 返回按键当前状态
/// @param GPIO_NUM_x 连接按键的引脚编号,其中x表示引脚编号.举例:引脚编号:2 ,那么参数就填写GPIO_NUM_2.
/// @return 返回连接按键的引脚状态
KEY_State KEY_Get_State(gpio_num_t GPIO_NUM_x);

#endif
