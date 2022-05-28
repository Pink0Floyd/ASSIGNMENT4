
#include "filter.h"

static filter_buffer buffer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

void insert_sample(uint16_t sample)
{
	sample=sample%(MAX_SAMPLE_VALUE+1);
//	printk("entered %u sample\n",sample);
	if(buffer.count>1)
	{
		if(sample<read_avg()-FILTER_THRESHOLD||sample>read_avg()+FILTER_THRESHOLD)
		{
			printk("sample rejected\n");
			return;
		}
	}
	buffer.pointer=(buffer.pointer+1)%FILTER_BUFFER_SIZE;
	buffer.array[buffer.pointer]=sample;
//	printk("inserted sample in position %u \n",buffer.pointer);
	if(buffer.count<FILTER_BUFFER_SIZE)
	{
		buffer.count++;
	}
	printk("buffer has %u samples\n",buffer.count);
}

void avg_samples()
{
	if(buffer.count==0)
	{
		buffer.samples_avg=buffer.array[buffer.pointer];
	}
	else if(buffer.count>0&&buffer.count<FILTER_BUFFER_SIZE)
	{
		printk("avg resized from %u",buffer.samples_avg);
		buffer.samples_avg=buffer.samples_avg*(buffer.count-1)/buffer.count;
		printk(" to %u \n",buffer.samples_avg);

		printk("added %u to the avg %u ",buffer.array[buffer.pointer],buffer.samples_avg);
		buffer.samples_avg+=buffer.array[buffer.pointer]/buffer.count;
		printk("becoming avg %u \n",buffer.samples_avg);
	}
	else if(buffer.count>=FILTER_BUFFER_SIZE)
	{
		printk("removed %u contribution to %u",buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE],buffer.samples_avg);
		buffer.samples_avg-=buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE]/(FILTER_BUFFER_SIZE-1);
		printk(" becoming %u \n",buffer.samples_avg);

		printk("added %u to the avg %u ",buffer.array[buffer.pointer],buffer.samples_avg);
		buffer.samples_avg+=buffer.array[buffer.pointer]/(FILTER_BUFFER_SIZE-1);
		printk("becoming avg %u \n",buffer.samples_avg);
	}
}

uint16_t read_avg()
{
	return buffer.samples_avg;
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
	printk("Initialized filter operation\n");
}

uint16_t filter(uint16_t in)
{
	insert_sample(in);
	avg_samples();
	return read_avg();
}