
#include "filter.h"

static filter_buffer buffer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

uint16_t read_avg()
{
	return (uint16_t)buffer.samples_avg;		// return last calculated average
}

int insert_sample(uint16_t sample)
{
	sample=sample%(MAX_SAMPLE_VALUE+1);
	printk("\tentered %i sample\n",(int16_t)sample);
	if(buffer.count>=FILTER_BUFFER_SIZE)
	{
		if(sample<read_avg()-FILTER_THRESHOLD)			// smart filter threshold operation
		{									// smart filter threshold operation
			printk("\tLow Spike sample rejected\n");		// smart filter threshold operation
			return -1;							// smart filter threshold operation
		}									// smart filter threshold operation
		else if(sample>read_avg()+FILTER_THRESHOLD)		// smart filter threshold operation
		{									// smart filter threshold operation
			printk("\tHigh Spike sample rejected\n");		// smart filter threshold operation
			return -1;							// smart filter threshold operation
		}									// smart filter threshold operation
	}
	else
	{
		buffer.count++;							// update count
	}

	buffer.pointer=(buffer.pointer+1)%FILTER_BUFFER_SIZE;			// update pointer
	buffer.array[buffer.pointer]=sample;					// insert accepted sample
	printk("\tinserted sample in position %u\n",buffer.pointer);
	printk("\tbuffer has %u samples\n",buffer.count);
	return 0;
}

void avg_samples()
{
	if(buffer.count==0)
	{
		buffer.samples_avg=buffer.array[buffer.pointer];
	}
	else if(buffer.count>0&&buffer.count<FILTER_BUFFER_SIZE)
	{
		printk("\tavg resized from %i",(int16_t)buffer.samples_avg);
		buffer.samples_avg=buffer.samples_avg*(buffer.count-1)/buffer.count;
		printk(" to %i\n",(int16_t)buffer.samples_avg);

		printk("\tadded %i to the avg %i",(int16_t)buffer.array[buffer.pointer],(int16_t)buffer.samples_avg);
		buffer.samples_avg+=buffer.array[buffer.pointer]/buffer.count;
		printk(" becoming avg %i\n",(int16_t)buffer.samples_avg);
	}
	else if(buffer.count>=FILTER_BUFFER_SIZE)
	{
		printk("\tremoved %i contribution to %i",(int16_t)buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE],(int16_t)buffer.samples_avg);
		buffer.samples_avg-=buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE]/(FILTER_BUFFER_SIZE-1);
		printk(" becoming %i\n",(int16_t)buffer.samples_avg);

		printk("\tadded %i to the avg %i",(int16_t)buffer.array[buffer.pointer],(int16_t)buffer.samples_avg);
		buffer.samples_avg+=buffer.array[buffer.pointer]/(FILTER_BUFFER_SIZE-1);
		printk(" becoming avg %i\n",(int16_t)buffer.samples_avg);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

void filter_init()
{
	uint8_t k=0;
	while(k<FILTER_BUFFER_SIZE)
	{
		buffer.array[k]=0;
		k++;
	}
	buffer.pointer=FILTER_BUFFER_SIZE-1;
	buffer.count=0;
	buffer.samples_avg=0;
	printk("Initialised filter operation\n");
}

uint16_t filter(uint16_t in)
{
	int err=insert_sample(in);
	if(err==0)
	{
		avg_samples();
	}
	return read_avg();
}
