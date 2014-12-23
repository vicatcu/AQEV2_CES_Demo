#include "AQEV2_Constants.h"

// this task collects samples from all the sensors
void sampleSensorsTask(){
  static uint8_t sensor_to_sample = 0;
  float sensor_value = 0;
   
  switch(sensor_to_sample){
  case TEMP_INDEX:
    sensor_value = getTemperature();
    addValueToAveragingWindow(sensor_value, TEMP_INDEX);
    break;
  case O3_INDEX:
    sensor_value = getO3Sample();
    addValueToAveragingWindow(sensor_value, O3_INDEX);
    break;
  case NO2_INDEX:
    sensor_value = getNO2Sample();
    addValueToAveragingWindow(sensor_value, NO2_INDEX);
    break;
  case CO_INDEX:
    sensor_value = getCOSample();
    addValueToAveragingWindow(sensor_value, CO_INDEX);
    break;
  case LIGHT_INDEX:
    sensor_value = getLight();
    addValueToAveragingWindow(sensor_value, LIGHT_INDEX);
    break;
  case HUM_INDEX:
    sensor_value = getHumidity();
    addValueToAveragingWindow(sensor_value, HUM_INDEX);  
    break;    
  }

  // get ready to sample the next sensor value
  sensor_to_sample++;
  if(sensor_to_sample >= NUM_SENSORS){
    advanceAveragingWindowIndex();         
    sensor_to_sample = 0; 
  }   
}
