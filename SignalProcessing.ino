#define NUM_SAMPLES_TO_AVERAGE (32)
#define NO2_INDEX   (0)
#define CO_INDEX    (1)
#define O3_INDEX    (2)
#define TEMP_INDEX  (3)
#define HUM_INDEX   (4)
#define LIGHT_INDEX (5)

float sensor_averaging_window[6][NUM_SAMPLES_TO_AVERAGE];
uint8_t sensor_averaging_window_index = 0;
uint8_t num_values_collected = 1; // so as not to average empty buffer space

void addValueToAveragingWindow(float value, uint8_t sensor_index){
  sensor_averaging_window[sensor_index][sensor_averaging_window_index] = value;
}

void advanceAveragingWindowIndex(void){
  sensor_averaging_window_index++;
  if(sensor_averaging_window_index >= NUM_SAMPLES_TO_AVERAGE){
    sensor_averaging_window_index = 0;
  }
  
  if(num_values_collected < NUM_SAMPLES_TO_AVERAGE){
    num_values_collected++;
  }
}

float getWindowedAverageSensorReading(uint8_t sensor_index){
  float sum = 0.0f;
  
  uint8_t upper_bound = NUM_SAMPLES_TO_AVERAGE;
  if(num_values_collected < upper_bound) {
      upper_bound = num_values_collected;
  }
  
  for(uint8_t ii = 0; ii < upper_bound; ii++){
     sum += sensor_averaging_window[sensor_index][ii];
  }
  
  return sum / upper_bound;
}



