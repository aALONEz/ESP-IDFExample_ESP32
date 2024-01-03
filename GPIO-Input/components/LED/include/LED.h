#ifndef __LED_H_
#define __LED_H_

//引入相关头文件
#include <stdio.h>
#include "driver/gpio.h"

//定义LED开关状态
typedef enum
{
    LED_OFF = 0,
    LED_ON  = 1,
}LED_State;


/// @brief LED初始化,配置为输入和输出模式,关闭上下拉电阻,关闭中断
/// @param GPIO_NUM_x 连接LED的引脚编号,其中x是引脚编号.举例:引脚编号是2,就是GPIO_NUM_2
/// @return 返回LED初始化过程中的状态,如果出现错误返回对应的错误代码.成功执行函数则返回ESP_OK
esp_err_t LED_Init(gpio_num_t GPIO_NUM_x);

/// @brief LED状态切换,亮灭切换
/// @param GPIO_NUM_x 要切换状态的引脚编号,其中x是引脚编号.举例:引脚编号是2,就是GPIO_NUM_2
/// @param LEDx_State 要设置的LED状态值,可以是LED_OFF LED_ON
/// @return 函数执行成功返回ESP_OK 函数执行错误返回对应错误码
esp_err_t LED_Switch(gpio_num_t GPIO_NUM_x, LED_State LEDx_State);

/// @brief 获取LED当前状态,是LED_OFF还是LED_ON
/// @param GPIO_NUM_x 连接LED的引脚编号,其中x是引脚编号.举例:引脚编号是2,就是GPIO_NUM_2
/// @return 返回LED当前状态.亮为LED_ON,灭为LED_OFF
LED_State LED_Get_State(gpio_num_t GPIO_NUM_x);

#endif
