/**
* \file filter.h
* \brief Smart Filter module
*
* This module contains functions to implement the smart filter required
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 2.7
* \bug No bugs detected
*/

#include "base.h"

#define MAX_SAMPLE_VALUE 1023			///< max sample value
#define FILTER_BUFFER_SIZE 11			///< number of samples in each average plus the excluded old sample
#define FILTER_THRESHOLD 120			///< range of values centered in the sample average allowed for a sample value

typedef struct filter_buffer
{
	float array[FILTER_BUFFER_SIZE];
	uint8_t pointer;
	uint8_t count;
	float samples_avg;
}filter_buffer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

//uint16_t read_avg();
//void insert_sample(uint16_t sample);
//void avg_samples();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions

/**
* \brief Filter initialisation function
*
* Initialises the filter buffer necessary for its operation
*
* \bug No bugs detected
*/
void filter_init();

/**
* \brief Filter operation function
*
* Inserts a new sample in the filter buffer, calculates the average of the samples in the filter buffer except the oldest and returns the last average calculated
*
* \param [IN] sample to be inserted
* \return last average calculated
* \bug No bugs detected
*/
uint16_t filter(uint16_t in);