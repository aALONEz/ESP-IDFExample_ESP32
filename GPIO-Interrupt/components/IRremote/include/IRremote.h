#ifndef __IR_REMOTE_H_
#define __IR_REMOTE_H_

//引入相关头文件
#include <stdio.h>
#include "driver/gpio.h"


//IR(对射式红外传感器)
#define IR_GPIO GPIO_NUM_2


esp_err_t IRremote_Init(gpio_num_t GPIO_NUM_x);
uint32_t IRremote_Get_Count(void);


#endif
