
#include "base.h"
#include "gpio.h"
#include "adc.h"
#include "filter.h"
#include "pwm.h"

#define PRINT_INIT 1		///< enable for thread initialisation prints
#define PRINT_LOOP 0		///< enable for thread loop prints

#define SAMPLING_PERIOD 1000

#define SAMPLING_PRIO 1			///< sampling thread priority
#define FILTERING_PRIO 1		///< filtering thread priority
#define ACTUATING_PRIO 1		///< actuating thread priority

#define SAMPLING_STACK_SIZE 1024						///< sampling thread stack size
K_THREAD_STACK_DEFINE(sampling_stack,SAMPLING_STACK_SIZE);		///< sampling thread stack size
#define FILTERING_STACK_SIZE 512						///< filtering thread stack size
K_THREAD_STACK_DEFINE(filtering_stack,FILTERING_STACK_SIZE);	///< filtering thread stack size
#define ACTUATING_STACK_SIZE 512						///< actuating thread stack size
K_THREAD_STACK_DEFINE(actuating_stack,ACTUATING_STACK_SIZE);	///< actuating thread stack size

struct k_thread sampling_data;	///< sampling thread initialisation
k_tid_t sampling_tid;			///< sampling thread initialisation
struct k_thread filtering_data;	///< filtering thread initialisation
k_tid_t filtering_tid;			///< filtering thread initialisation
struct k_thread actuating_data;	///< actuating thread initialisation
k_tid_t actuating_tid;			///< actuating thread initialisation

struct k_fifo filt_in;			///< variable to carry a sample between sampling and filtering
struct k_fifo filt_out;			///< variable to carry a filtered sample between filtering and actuating

struct data_pack
{
    void *fifo_reserved;
    uint16_t data;
};

void sampling(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("Launched sampling thread\n");

	int64_t curr_time=k_uptime_get();
	int64_t end_time=k_uptime_get()+SAMPLING_PERIOD;

	struct data_pack sent_data;

	while(1)
	{
		sent_data.data=adc_sample();				// sample
		if(PRINT_LOOP)
		printk("sampling: sampled ADC for %u\n",sent_data.data);
		k_fifo_put(&filt_in,&sent_data);			// transmit sample
		if(PRINT_LOOP)
		printk("sampling: supplied a sample to filtering\n");

		curr_time=k_uptime_get();			// sleep until next sampling period
		if(curr_time<end_time)				// sleep until next sampling period
		{							// sleep until next sampling period
			k_msleep(end_time-curr_time);		// sleep until next sampling period
		}							// sleep until next sampling period
		end_time+=SAMPLING_PERIOD;			// sleep until next sampling period
	}
}

void filtering(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("Launched filtering thread\n");

	struct data_pack* received_data;
	struct data_pack sent_data;

	while(1)
	{
		if(PRINT_LOOP)
		printk("filtering: waiting for a sample from sampling\n");
		received_data=k_fifo_get(&filt_in,K_FOREVER);				// receive sample
		if(PRINT_LOOP)
		printk("filtering: got a sample from sampling\n");
		if(!PRINT_LOOP)
		printk("\t%u ->",received_data->data);
		sent_data.data=filter(received_data->data);				// filter
		if(!PRINT_LOOP)
		printk(" %u \n",sent_data.data);
		if(PRINT_LOOP)
		printk("filtering: filtered %u sample to %u\n",received_data->data,sent_data.data);
		k_fifo_put(&filt_out,&sent_data);						// transmit filtered sample
		if(PRINT_LOOP)
		printk("filtering: supplied a filtered sample to actuating\n");
	}
}

void actuating(void* A,void* B,void* C)
{
	if(PRINT_INIT)
	printk("Launched actuating thread\n");

	struct data_pack* received_data;

	while(1)
	{
		if(PRINT_LOOP)
		printk("actuating: waiting for a filtered sample from filtering\n");
		received_data=k_fifo_get(&filt_out,K_FOREVER);				// receive filtered sample
		if(PRINT_LOOP)
		printk("actuating: got a filtered sample from filtering\n");
		pwm_led_set(received_data->data*100/1023);				// act
		if(PRINT_LOOP)
		printk("actuating: led has been set to %u %%\n",received_data->data*100/1023);
	}
}

void main()
{
	printk("\n\n\nLed Driver (with fifo)\n");

	adc_init();
	filter_init();
	pwm_init();

	k_fifo_init(&filt_in);
	k_fifo_init(&filt_out);

	sampling_tid=k_thread_create(&sampling_data,sampling_stack,K_THREAD_STACK_SIZEOF(sampling_stack),	// create sampling thread
		sampling,NULL,NULL,NULL,SAMPLING_PRIO,0,K_NO_WAIT);								// create sampling thread

	filtering_tid=k_thread_create(&filtering_data,filtering_stack,K_THREAD_STACK_SIZEOF(filtering_stack),	// create filtering thread
		filtering,NULL,NULL,NULL,FILTERING_PRIO,0,K_NO_WAIT);								// create filtering thread

	actuating_tid=k_thread_create(&actuating_data,actuating_stack,K_THREAD_STACK_SIZEOF(actuating_stack),	// create actuating thread
		actuating,NULL,NULL,NULL,ACTUATING_PRIO,0,K_NO_WAIT);								// create actuating thread
}