
#include "base.h"
#include "gpio.h"
#include "adc.h"
#include "filter.h"
#include "pwm.h"

#define TOTAL_SAMPLES 144		///< total samples until the end of program
#define SAMPLING_PERIOD 1000		///< sampling period in miliseconds

#define SAMPLING_PRIO 1			///< sampling thread priority
#define FILTERING_PRIO 1		///< filtering thread priority
#define ACTUATING_PRIO 1		///< actuating thread priority

#define SAMPLING_STACK_SIZE 256
#define FILTERING_STACK_SIZE 256
#define ACTUATING_STACK_SIZE 256

K_THREAD_STACK_DEFINE(sampling_stack,SAMPLING_STACK_SIZE);
K_THREAD_STACK_DEFINE(filtering_stack,FILTERING_STACK_SIZE);
K_THREAD_STACK_DEFINE(actuating_stack,ACTUATING_STACK_SIZE);

struct k_thread sampling_data;
struct k_thread filtering_data;
struct k_thread actuating_data;

k_tid_t sampling_tid;
k_tid_t filtering_tid;
k_tid_t actuating_tid;

struct k_sem sem_sample;
struct k_sem sem_filtsample;

void sampling(void* A,void* B,void* C)
{
	
}

void filtering(void* A,void* B,void* C)
{
	
}

void actuating(void* A,void* B,void* C)
{
	
}

void main()
{
	printk("\n\n\nStart\n");

	adc_init();
	filter_init();
	pwm_init();

	sampling_tid=k_thread_create(&sampling_data,sampling_stack,K_THREAD_STACK_SIZEOF(sampling_stack),
		sampling,NULL,NULL,NULL,SAMPLING_PRIO,0,K_NO_WAIT);

	filtering_tid=k_thread_create(&filtering_data,filtering_stack,K_THREAD_STACK_SIZEOF(filtering_stack),
		filtering,NULL,NULL,NULL,FILTERING_PRIO,0,K_NO_WAIT);

	actuating_tid=k_thread_create(&actuating_data,actuating_stack,K_THREAD_STACK_SIZEOF(actuating_stack),
		actuating,NULL,NULL,NULL,ACTUATING_PRIO,0,K_NO_WAIT);
}
