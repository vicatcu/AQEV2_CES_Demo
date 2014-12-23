#include <LiquidCrystal.h>
#include "AQEV2_Constants.h"
#include <avr/pgmspace.h>
#include <stdlib.h>

LiquidCrystal lcd(A3, A2, 4, 5, 6, 8);

extern PGM_P sensor_names[NUM_SENSORS] PROGMEM;
extern PGM_P sensor_units[NUM_SENSORS] PROGMEM;
void initializeLCD(){
  byte upArrow[8] = {
          B00100,
          B01110,
          B11111,
          B00100,
          B00100,
          B00100,
          B00100,
          B00100
  };  
  
  byte downArrow[8] = {
          B00100,
          B00100,
          B00100,
          B00100,
          B00100,
          B11111,
          B01110,
          B00100
  };  
  
  pinMode(A6, OUTPUT);
  digitalWrite(A6, HIGH);
  
  lcd.createChar(0, upArrow);  
  lcd.createChar(1, downArrow); 
  
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print(F("Air Quality Egg"));
  lcd.setCursor(3, 1);
  lcd.print(F("Version 2"));
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("by: Wicked"));
  lcd.setCursor(7, 1);
  lcd.print(F("Device"));  
  delay(1000);
}

// this task gets updates the display periodically
// to cycle through showing the sensor values
void lcdUpdateTask(){
  static uint8_t sensor_to_display = 0;
  static float last_sensor_value[NUM_SENSORS] = {0};
  static uint8_t not_first[NUM_SENSORS] = {0};
 
  uint8_t len = 0;
  char buf[32];
  PGM_P p;
  
  // copy the name into ram
  memcpy_P(&p, &sensor_names[sensor_to_display], sizeof(PGM_P));
  strcpy_P(buf, p);
  len = strlen(buf);
  
  // center the text, as well as possible (biased to the left)
  lcd.clear();
  lcd.setCursor((16 - len)/2, 0); 
  lcd.print(buf);
  
  // get the value and write it into buff, left aligned and trimmed
  float sensor_value = getWindowedAverageSensorReading(sensor_to_display);
  dtostrf(sensor_value, -16, 2, buf);
  len = strlen(buf);
  // trim white space off the right side
  for(uint8_t ii = 0; ii < len; ii++){
    if(buf[ii] == ' '){
      buf[ii] = '\0';      
      break;
    }
  }
  
  // tack on the units string
  memcpy_P(&p, &sensor_units[sensor_to_display], sizeof(PGM_P));
  strcat_P(buf, p);
  len = strlen(buf);
  
  
  if(not_first[sensor_to_display]){
    // after the first sample, include the arrow symbols
    lcd.setCursor((16 - len)/2 - 2, 1); // center and leave space for arrow
    
    if(sensor_value > last_sensor_value[sensor_to_display]){
      lcd.write((uint8_t) 0);    
    }
    else if(sensor_value < last_sensor_value[sensor_to_display]){
      lcd.write((uint8_t) 1);
    }
    else{
      lcd.print(F("="));
    }   
    
    lcd.print(F(" "));    
    lcd.print(buf);     
  }
  else{    
    lcd.setCursor((16 - len)/2, 1); // center
    lcd.print(buf);
  }
  
  
  not_first[sensor_to_display] = true;
  // get ready to display the next sensor value
  sensor_to_display++;
  if(sensor_to_display >= NUM_SENSORS){
    sensor_to_display = 0; 
  }
}
