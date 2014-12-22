#include "WildFire.h"
WildFire wf;

void setup(){
  wf.begin();
  Serial.begin(115200);
  
  initializeGasSensors();
  initializeTempHumidity();  
  initializeLight();
  
}

void loop(){
  
}
