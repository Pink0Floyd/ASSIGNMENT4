
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
	if(buffer.count>=FILTER_BUFFER_SIZE)
	{
		if(sample<read_avg()-FILTER_THRESHOLD)			// smart filter threshold operation
		{									// smart filter threshold operation
			return -1;							// smart filter threshold operation
		}									// smart filter threshold operation
		else if(sample>read_avg()+FILTER_THRESHOLD)		// smart filter threshold operation
		{									// smart filter threshold operation
			return -1;							// smart filter threshold operation
		}									// smart filter threshold operation
	}
	else
	{
		buffer.count++;							// update count
	}

	buffer.pointer=(buffer.pointer+1)%FILTER_BUFFER_SIZE;			// update pointer
	buffer.array[buffer.pointer]=sample;				// insert accepted sample
	return 0;
}

void avg_samples()
{
	if(buffer.count>0&&buffer.count<FILTER_BUFFER_SIZE)					// buffer not full
	{													//
		buffer.samples_avg=buffer.samples_avg*(buffer.count-1)/buffer.count;	// resize past samples contribution
		buffer.samples_avg+=buffer.array[buffer.pointer]/buffer.count;		// add new sample contribution
	}													//

	else if(buffer.count>=FILTER_BUFFER_SIZE)												// buffer full
	{																		//
		buffer.samples_avg-=buffer.array[(buffer.pointer+1)%FILTER_BUFFER_SIZE]/(FILTER_BUFFER_SIZE-1);		// remove oldest sample contribution
		buffer.samples_avg+=buffer.array[buffer.pointer]/(FILTER_BUFFER_SIZE-1);					// add new sample contribution
	}																		//
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
	printk("\tInitialised filter operation\n");
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
