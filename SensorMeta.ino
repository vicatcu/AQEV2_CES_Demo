#include "AQEV2_Constants.h"

// these names must be less than 16 characters long
// in order to fit on a 16x2 character LCD display
const char Sensor_Display_Name_NO2[] PROGMEM = "NO2";
const char Sensor_Display_Name_CO[] PROGMEM = "CO";
const char Sensor_Display_Name_O3[] PROGMEM = "O3";
const char Sensor_Display_Name_TEMP[] PROGMEM = "Temperature";
const char Sensor_Display_Name_HUM[] PROGMEM = "Humidity";
const char Sensor_Display_Name_LIGHT[] PROGMEM = "Ambient Light";

// the order here must be kept consistent with 
// the index order in AQEV2_Constants
PGM_P sensor_names[NUM_SENSORS] PROGMEM = {
  Sensor_Display_Name_NO2,
  Sensor_Display_Name_CO,
  Sensor_Display_Name_O3,
  Sensor_Display_Name_TEMP,
  Sensor_Display_Name_HUM,
  Sensor_Display_Name_LIGHT
};

const char Sensor_Display_Units_NO2[] PROGMEM = " ppb";
const char Sensor_Display_Units_CO[] PROGMEM = " ppm";
const char Sensor_Display_Units_O3[] PROGMEM = " ppb";
const char Sensor_Display_Units_TEMP[] PROGMEM = {' ', 223, 'C', '\0'};
const char Sensor_Display_Units_HUM[] PROGMEM = " %";
const char Sensor_Display_Units_LIGHT[] PROGMEM = " V";

// the order here must be kept consistent with 
// the index order in AQEV2_Constants
PGM_P sensor_units[NUM_SENSORS] PROGMEM = {
  Sensor_Display_Units_NO2,
  Sensor_Display_Units_CO,
  Sensor_Display_Units_O3,
  Sensor_Display_Units_TEMP,
  Sensor_Display_Units_HUM,
  Sensor_Display_Units_LIGHT
};
