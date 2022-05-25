/**
* \file filter.h
* \brief Smart Filter module
*
* This module contains functions to implement the smart filter required
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 2.2
* \bug No bugs detected
*/

#include "adc.h"

#define MAX_SAMPLE_VALUE 1024
#define FILTER_BUFFER_SIZE 11		///< number of samples in each average plus the excluded old sample
#define FILTER_THRESHOLD 12		///< range of values centered in the sample average allowed for a sample value

typedef struct filter_buffer
{
	uint16_t array[FILTER_BUFFER_SIZE];
	uint8_t pointer;
	uint8_t count;
	uint16_t samples_avg;
}filter_buffer;

void filter_init();

void insert_sample(uint16_t sample);

void avg_samples();

uint16_t read_avg();