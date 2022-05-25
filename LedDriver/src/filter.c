
#include "filter.h"

static filter_buffer buffer;

void filter_init()
{
	uint8_t k=0;
	while(k<FILTER_BUFFER_SIZE)
	{
		buffer.array[k]=0;
		k++;
	}
	buffer.pointer=0;
	buffer.count=0;
	buffer.samples_avg=0;
}

void insert_sample(uint16_t sample)
{
	sample=sample%MAX_SAMPLE_VALUE;
	if(buffer.count>1)
	{
		if(sample<read_avg()-FILTER_THRESHOLD||sample>read_avg()+FILTER_THRESHOLD)
		{
			return;
		}
	}
	buffer.array[buffer.pointer]=sample;
	buffer.pointer=(buffer.pointer+1)%FILTER_BUFFER_SIZE;
	if(buffer.count<FILTER_BUFFER_SIZE)
	{
		buffer.count++;
	}
}

void avg_samples()
{
	// if buffer is full, remove the last sample contribution
	if(buffer.count==FILTER_BUFFER_SIZE)
	{
		buffer.samples_avg-=buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE]/buffer.count;
	}
	// if buffer is not full, resize the old samples contribution
	else if(buffer.count>0)
	{
		buffer.samples_avg=buffer.samples_avg*(buffer.count-1)/buffer.count;
	}
	// add the new sample contribution
	if(buffer.count>0)
	{
		buffer.samples_avg+=buffer.array[buffer.pointer]/buffer.count;
	}
}

uint16_t read_avg()
{
	return buffer.samples_avg;
}