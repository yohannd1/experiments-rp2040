#include <stdio.h>

#include "pico/stdlib.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_A 11
#define LED_B 12

void task_1(void *_);
void task_2(void *_);

int main(void) {
	stdio_init_all();

	xTaskCreate(task_1, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(task_2, "Task 2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();
    panic_unsupported();

	return 0;
}

void task_1(void *_) {
	gpio_init(LED_A);
	gpio_set_dir(LED_A, GPIO_OUT);

	while (true) {
        gpio_put(LED_A, true);
        vTaskDelay(pdMS_TO_TICKS(250));
        gpio_put(LED_A, false);
        vTaskDelay(pdMS_TO_TICKS(250));
	}
}

void task_2(void *_) {
	gpio_init(LED_B);
	gpio_set_dir(LED_B, GPIO_OUT);

	while (true) {
        gpio_put(LED_B, true);
        vTaskDelay(pdMS_TO_TICKS(400));
        gpio_put(LED_B, false);
        vTaskDelay(pdMS_TO_TICKS(400));
	}
}
