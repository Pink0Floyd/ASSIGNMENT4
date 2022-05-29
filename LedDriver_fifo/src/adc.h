/**
* \file adc.h
* \brief Analog-Digital Converter module
*
* This module contains functions to implement an AD converter
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 2.7
* \bug No bugs detected
*/

#ifndef ADC_H
#define ADC_H

#include "base.h"

#define ADC_MIN_VALUE 0		///< minimum value to be interpreted by the ADC
#define ADC_MAX_VALUE 1023	///< maximum value to be interpreted by the ADC

#define ADC_NID DT_NODELABEL(adc) 
#define ADC_RESOLUTION 10

// Parameters for adc Struct Configuration
#define ADC_GAIN ADC_GAIN_1_4
#define ADC_REFERENCE ADC_REF_VDD_1_4
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40)
#define ADC_CHANNEL_ID 1
#define ADC_CHANNEL_INPUT NRF_SAADC_INPUT_AIN1 

// ADC channel struct Configuration:
static struct adc_channel_cfg adc_conf = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_CHANNEL_ID,
	.input_positive = ADC_CHANNEL_INPUT
};

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief ADC initialization function
*
* Initializes the ADC in order to use it 
*
* \bug No bugs detected
*/
void adc_init();


/**
* \brief ADC read function
*
* Read a sample from ADC previosly configurated and return it
*
* \return Return the read value from adc
* \bug No bugs detected
*/
uint16_t adc_sample();

#endif