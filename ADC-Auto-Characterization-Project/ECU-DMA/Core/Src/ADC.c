#include "ADC.h"

/**
  * @brief Take numSamples ADC values, average them, then return both raw and error adjusted values
  * @param adcValuesAveraged: Pointer to the averaged ADC value
  * @param adcValuesAdjusted: Pointer to the averaged ADC value, adjusted for error
  * @retval None
  */
void Get_Averaged_ADC_Values(int* adcValuesAveraged, int* adcValuesADCAdjusted, int* adcValuesCurrentAdjusted){
  *adcValuesAveraged = adcAveragedValue; // Set the pointer output

  // ADC Error Polynomial: -75.8 + 0.0222x
  // Current Sensor ADC Error Polynomial: 72 - 0.0325x + 19.6 - 8.82E-3x = 91.6 - 0.04132x

  int adcError = -75.8 + 0.0222 * (*adcValuesAveraged); // This is a predetermined error polynomial
  int currentSensorADCError = 91.6 - 0.04132 * (*adcValuesAveraged); // This is the predetermined erroy polynomial for the current sensor

  *adcValuesADCAdjusted = *adcValuesAveraged - adcError; // Set the other pointer output
  *adcValuesCurrentAdjusted = *adcValuesAveraged - adcError - currentSensorADCError; // Set the other pointer output
}

// adc dma half complete callback
// We can't sum in the Get_Averaged_ADC_Values function because DMA would to writing into some part of the buffer at the same time
// REMEMBER!!!! This function might not be allowed to be outside of main.c, so if you run into issues during testing, that's probably it
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc){
  int adcValuesSum = 0;
  for (int i = 0; i < ADC_BUFFER_LENGTH / 2; i++){
    adcValuesSum += adcBuffer[i];
  }
  adcAveragedValue = adcValuesSum / (ADC_BUFFER_LENGTH / 2);
}

// adc dma full complete callback
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  int adcValuesSum = 0;
  for (int i = ADC_BUFFER_LENGTH/2; i < ADC_BUFFER_LENGTH; i++){
    adcValuesSum += adcBuffer[i];
  }
  adcAveragedValue = adcValuesSum / (ADC_BUFFER_LENGTH / 2);
}