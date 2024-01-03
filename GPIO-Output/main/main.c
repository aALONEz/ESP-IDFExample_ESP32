#include "Task.c"

void app_main(void)
{
    xTaskCreatePinnedToCore(LED0Task, "LED0Task", LED0Task_StackSize, NULL, LED0Task_Priority, &LED0TaskHandler, 1);//创建LED0任务
    xTaskCreatePinnedToCore(LED1Task, "LED1Task", LED1Task_StackSize, NULL, LED1Task_Priority, &LED1TaskHandler, 1);//创建LED1任务
    //vTaskStartScheduler();ESP-IDF禁止调用此函数,因为默认app_main函数最后会执行此函数
}
