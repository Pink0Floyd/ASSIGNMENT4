
#include "base.h"
#include "gpio.h"
#include "adc.h"
#include "filter.h"
#include "pwm.h"

/*

void main()
{
	printk("\n\n\n\n\n\n");
	filter_init();

	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(0));
	printk("%u \n",filter(120));
	printk("%u \n",filter(240));
	printk("%u \n",filter(120));
	printk("%u \n",filter(120));
	printk("%u \n",filter(120));
	printk("%u \n",filter(120));
	printk("%u \n",filter(120));
	printk("%u \n",filter(240));
	
}

*/

#define TOTAL_SAMPLES 144		///< total samples until the end of program
#define SAMPLING_PERIOD 1000		///< sampling period in miliseconds

#define SAMPLING_PRIO 1			///< sampling thread priority
#define FILTERING_PRIO 1		///< filtering thread priority
#define ACTUATING_PRIO 1		///< actuating thread priority

#define SAMPLING_STACK_SIZE 256						///< sampling thread stack size
K_THREAD_STACK_DEFINE(sampling_stack,SAMPLING_STACK_SIZE);		///< sampling thread stack size
#define FILTERING_STACK_SIZE 256						///< filtering thread stack size
K_THREAD_STACK_DEFINE(filtering_stack,FILTERING_STACK_SIZE);	///< filtering thread stack size
#define ACTUATING_STACK_SIZE 256						///< actuating thread stack size
K_THREAD_STACK_DEFINE(actuating_stack,ACTUATING_STACK_SIZE);	///< actuating thread stack size

struct k_thread sampling_data;	///< sampling thread initialisation
k_tid_t sampling_tid;			///< sampling thread initialisation
struct k_thread filtering_data;	///< filtering thread initialisation
k_tid_t filtering_tid;			///< filtering thread initialisation
struct k_thread actuating_data;	///< actuating thread initialisation
k_tid_t actuating_tid;			///< actuating thread initialisation

const int64_t sampling_period=1000;		///< sampling thread period
struct k_sem sem_sample;			///< sample ready semafore
struct k_sem sem_filtsample;			///< filtered sample ready semafore

uint16_t filt_in;
uint16_t filt_out;

void sampling(void* A,void* B,void* C)
{
	int64_t curr_time=k_uptime_get();
	int64_t end_time=k_uptime_get()+sampling_period;
	while(1)
	{
		filt_in=adc_sample();
		k_sem_give(&sem_sample);

		curr_time=k_uptime_get();			// sleep until next sampling period
		if(curr_time<end_time)				// sleep until next sampling period
		{							// sleep until next sampling period
			k_msleep(end_time-curr_time);		// sleep until next sampling period
		}							// sleep until next sampling period
	}
}

void filtering(void* A,void* B,void* C)
{
	while(1)
	{
		k_sem_take(&sem_sample,K_FOREVER);
		filt_out=filter(filt_in);
		k_sem_give(&sem_filtsample);
	}
}

void actuating(void* A,void* B,void* C)
{
	while(1)
	{
		k_sem_take(&sem_filtsample,K_FOREVER);
		pwm_led_set(filt_out*100/1023);
	}
}

void main()
{
	printk("\n\n\nStart\n");

	adc_init();
	filter_init();
	pwm_init();

	k_sem_init(&sem_sample, 0, 1);
	k_sem_init(&sem_filtsample, 0, 1);

	sampling_tid=k_thread_create(&sampling_data,sampling_stack,K_THREAD_STACK_SIZEOF(sampling_stack),
		sampling,NULL,NULL,NULL,SAMPLING_PRIO,0,K_NO_WAIT);

	filtering_tid=k_thread_create(&filtering_data,filtering_stack,K_THREAD_STACK_SIZEOF(filtering_stack),
		filtering,NULL,NULL,NULL,FILTERING_PRIO,0,K_NO_WAIT);

	actuating_tid=k_thread_create(&actuating_data,actuating_stack,K_THREAD_STACK_SIZEOF(actuating_stack),
		actuating,NULL,NULL,NULL,ACTUATING_PRIO,0,K_NO_WAIT);
}