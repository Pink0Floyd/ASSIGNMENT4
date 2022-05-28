
#include "adc.h"

void adc_init()
{

      int err=0;

      /* ADC setup: bind and initialize */
      adc_dev = device_get_binding(DT_LABEL(ADC_NID));
      if (!adc_dev) 
      {
	    printk("ADC device_get_binding() failed\n");
      } 

      err = adc_channel_setup(adc_dev, &adc_conf);
      if (err) 
      {
	    printk("adc_channel_setup() failed with error code %d\n", err);
      }
      
      /* It is recommended to calibrate the SAADC at least once before use, and whenever the ambient temperature has changed by more than 10 °C */
      NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;
}

/* Takes one sample */
uint16_t adc_sample()
{
	int ret;
	const struct adc_sequence sequence = {
		.channels=BIT(ADC_CHANNEL_ID),
		.buffer=adc_sample_buffer,
		.buffer_size=sizeof(adc_sample_buffer),
		.resolution=ADC_RESOLUTION,
	};

	ret = adc_read(adc_dev, &sequence);
	if (ret) {
            printk("adc_read() failed with code %d\n", ret);
	}	

	return adc_sample_buffer[0]; 
}