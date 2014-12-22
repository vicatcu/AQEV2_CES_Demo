#include <LiquidCrystal.h>

LiquidCrystal lcd(A3, A2, 4, 5, 6, 8);

void initializeLCD(){
  pinMode(A6, OUTPUT);
  digitalWrite(A6, HIGH);
  
  lcd.begin(16, 2);
}
