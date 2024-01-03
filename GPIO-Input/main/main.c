#include "Task.c"

void app_main(void)
{
    xTaskCreatePinnedToCore(KEY0Task, "KEY0Task", KEY0Task_StackSize, NULL, KEY0Task_Priority, &KEY0TaskHandler, 1);//创建KEY0Task任务 
    xTaskCreatePinnedToCore(LED1Task, "LED1Task", LED1Task_StackSize, NULL, LED1Task_Priority, &LED1TaskHandler, 1);//创建LED1Task任务 
}
