#include "MCP342x.h"
#include "LMP91000.h"
#include <Wire.h>

MCP342x adc; // default address is 0x68
LMP91000 lmp91000;

boolean no2_is_present = false;
boolean co_is_present = false;
boolean o3_is_present = false;

void selectNoSlot(void){
        digitalWrite(7, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);  
}

void selectSlot1(void){
        selectNoSlot();
        digitalWrite(10, HIGH);    
}

void selectSlot2(void){
        selectNoSlot();
        digitalWrite(9, HIGH);  
}

void selectSlot3(void){
        selectNoSlot();
        digitalWrite(7, HIGH);
}

void initializeGasSensors(){  
  uint8_t res = 0;
  
  // initialize the slot select pins to "not selected"
  pinMode(7, OUTPUT);  digitalWrite(7, LOW);
  pinMode(9, OUTPUT);  digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);        
  
  // fire up the i2c bus
  Wire.begin();  
  
  Serial.print(F("Initializing O3..."));
  selectSlot1(); //O3
  res = lmp91000.configure( 
      LMP91000_TIA_GAIN_350K | LMP91000_RLOAD_10OHM,
      LMP91000_REF_SOURCE_EXT | LMP91000_INT_Z_67PCT 
            | LMP91000_BIAS_SIGN_NEG | LMP91000_BIAS_1PCT,
      LMP91000_FET_SHORT_DISABLED | LMP91000_OP_MODE_AMPEROMETRIC                  
  );
  
  if(res == 0 ){
    Serial.println(F("Failed!"));
  }
  else{
    o3_is_present = true;
    Serial.println(F("Complete!"));
  }

  Serial.print(F("Initializing NO2..."));
  selectSlot2(); //NO2
  res = lmp91000.configure( 
      LMP91000_TIA_GAIN_350K | LMP91000_RLOAD_10OHM,
      LMP91000_REF_SOURCE_EXT | LMP91000_INT_Z_67PCT 
            | LMP91000_BIAS_SIGN_NEG | LMP91000_BIAS_8PCT,
      LMP91000_FET_SHORT_DISABLED | LMP91000_OP_MODE_AMPEROMETRIC                  
  );
  
  if(res == 0 ){
    Serial.println(F("Failed!"));
  }
  else{
    no2_is_present = true;
    Serial.println(F("Complete!"));
  }


  Serial.print(F("Initializing CO..."));
  selectSlot3(); //CO
  res = lmp91000.configure( 
      LMP91000_TIA_GAIN_350K | LMP91000_RLOAD_10OHM,
      LMP91000_REF_SOURCE_EXT | LMP91000_INT_Z_20PCT 
            | LMP91000_BIAS_SIGN_POS | LMP91000_BIAS_1PCT,
      LMP91000_FET_SHORT_DISABLED | LMP91000_OP_MODE_AMPEROMETRIC                  
  );
  
  if(res == 0 ){
    Serial.println(F("Failed!"));
  }
  else{
    co_is_present = true;
    Serial.println(F("Complete!"));
  }

}

float burstSampleADC(void){
  const uint8_t NUM_SAMPLES_PER_BURST = 16;
  MCP342x::Config status;
  int32_t burst_sample_total = 0;
  int32_t value = 0;
  
  for(uint8_t ii = 0; ii < NUM_SAMPLES_PER_BURST; ii++){
    adc.convertAndRead(MCP342x::channel1, MCP342x::oneShot, 
      MCP342x::resolution16, MCP342x::gain1, 1000000, value, status);   
    burst_sample_total += value;
  }
  
  return (1.0f * burst_sample_total) / NUM_SAMPLES_PER_BURST;
}


//Cx = (Vout - Vzero) / ( nA/ppm * V/nA )  
float getO3Sample(){
  selectSlot1(); //O3  
  float voltage = burstSampleADC() * 62.5e-6; //62.5 microvolts
  float sensor_value = -1.0f * (voltage - 0.0f) / 0.00640; // M = 0.00640 V/ppm for 051514B-07
  sensor_value /= 1000.0f;
  return sensor_value;
}

float getNO2Sample(){
  selectSlot2(); //NO2  
  float voltage = burstSampleADC() * 62.5e-6; //microvolts
  float sensor_value = -1.0f * (voltage - 0.0f) / 0.0188; // M = 0.0188 V/ppm for 051514B-11
  sensor_value /= 1000.0f;
  return sensor_value;
}

float getCOSample(){
  selectSlot3(); //CO  
  float voltage = burstSampleADC() * 62.5e-6; //microvolts
  float sensor_value = -1.0f * (voltage - 0.0f) / 0.0002; // M = 0.0002 V/ppm for 032114A-35 
  sensor_value /= 1000.0f;  
  return sensor_value;
}




