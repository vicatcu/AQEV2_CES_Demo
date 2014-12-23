#include <LiquidCrystal.h>

LiquidCrystal lcd(A3, A2, 4, 5, 6, 8);

void initializeLCD(){
  pinMode(A6, OUTPUT);
  digitalWrite(A6, HIGH);
  
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Egg");
  lcd.setCursor(3, 1);
  lcd.print("Version 2");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("by: Wicked");
  lcd.setCursor(7, 1);
  lcd.print("Device");  
}
