
#include "adc.h"

// Global Variables:
static const struct device *adc_dev = NULL;
static uint16_t adc_sample_buffer;

void adc_init()
{
      int err=0;

      /* ADC setup: bind and initialize */
      adc_dev = device_get_binding(DT_LABEL(ADC_NID));
      if (!adc_dev) 
      {
	    printk("\tADC device_get_binding() failed\n");
      } 

      err = adc_channel_setup(adc_dev, &adc_conf);
      if (err) 
      {
	    printk("\tadc_channel_setup() failed with error code %d\n", err);
      }
      
      /* It is recommended to calibrate the SAADC at least once before use, and whenever the ambient temperature has changed by more than 10 °C */
      NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;

	printk("\tInitialised ADC module\n");
}

/* Takes one sample */
uint16_t adc_sample()
{
	const struct adc_sequence sequence = {
		.channels=BIT(ADC_CHANNEL_ID),
		.buffer=&adc_sample_buffer,
		.buffer_size=sizeof(adc_sample_buffer),
		.resolution=ADC_RESOLUTION,
	};

	int ret = adc_read(adc_dev, &sequence);
	if (ret) {
            printk("\tadc_read() failed with code %d\n", ret);
	}

	if(adc_sample_buffer>ADC_MAX_VALUE)
	{
		adc_sample_buffer=ADC_MAX_VALUE;
	}
	else if(adc_sample_buffer<ADC_MIN_VALUE)
	{
		adc_sample_buffer=ADC_MIN_VALUE;
	}
	
	return adc_sample_buffer; 
}