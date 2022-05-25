
#include "base.h"
#include "gpio.h"
#include "buttons.h"
#include ".h"

#define SAMPLING_STACK_SIZE 256
#define FILTERING_STACK_SIZE 256
#define ACTUATING_STACK_SIZE 256W

K_THREAD_STACK_DEFINE(thread_sampling_stack,SAMPLING_STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_filtering_stack,FILTERING_STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_actuating_stack,ACTUATING_STACK_SIZE);

void main()
{
	printk("\n\n\nStart\n");

	adc_init();
	filter_init();
	pwm_init();
}
