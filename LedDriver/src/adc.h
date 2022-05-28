/**
* \file adc.h
* \brief Analog-Digital Converter module
*
* This module contains functions to implement an AD converter
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 1.1
* \bug No bugs detected
*/

#ifndef ADC_H
#define ADC_H

#include "base.h"

#define ADC_NID DT_NODELABEL(adc) 
#define ADC_RESOLUTION 10
#define BUFFER_SIZE 1
#define TIMER_INTERVAL_MSEC 1000

// Parameters for adc Struct Configuration
#define ADC_GAIN ADC_GAIN_1_4
#define ADC_REFERENCE ADC_REF_VDD_1_4
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40)
#define ADC_CHANNEL_ID 1
//#define ADC_CHANNEL_INPUT NRF_SAADC_INPUT_AIN1 

// ADC channel struct Configuration:
static const struct adc_channel_cfg adc_conf = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_CHANNEL_ID,
	//.input_positive = ADC_CHANNEL_INPUT
};

// Global Variables:
//const struct device *adc_dev = NULL;
static uint16_t adc_sample_buffer[BUFFER_SIZE];


///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief ADC initialization function
*
* Initializes the ADC in order to use it 
*
* \date 25/04/22
* \bug No bugs detected
*/
void adc_init();


/**
* \brief ADC read function
*
* Read a sample from ADC previosly configurated and return it
*
* \param [IN] struct device *adc  -> the pointer for adc struct
* \date 25/04/22
* \bug No bugs detected
*/
void adc_sample(struct device *adc_dev);

#endif