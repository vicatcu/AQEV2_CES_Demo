#include "DHT.h"

DHT dht(A1, DHT22);

void initializeTempHumidity(){
  dht.begin();   
}

float getTemperature(){
  return dht.readHumidity();
}

float getHumidity(){
  return dht.readTemperature();
}
