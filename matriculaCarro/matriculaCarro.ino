#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
unsigned long lastUpdate;
int scrollCounter = 0;
bool showProjectInfo = false;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Safe Remote     "); 
  lcd.setCursor(1, 1);
  lcd.print("Controlled Car  "); 
  lastUpdate = millis();
}

void loop() {
  if (!showProjectInfo) {
    if (millis() - lastUpdate > 150) {
      lcd.scrollDisplayRight();
      lastUpdate = millis();
      scrollCounter++;
      
      if (scrollCounter > 16) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Projeto 1");
        lcd.setCursor(2, 1);
        lcd.print("DAVID & PEDRO");
        showProjectInfo = true;
        delay(1000);
        scrollCounter = 0;
      }
    }
  } else {
    if (millis() - lastUpdate > 150) {
      lcd.scrollDisplayLeft();
      lastUpdate = millis();
      scrollCounter++;
      
      if (scrollCounter > 16) { // Assuming 16 characters fit on the display
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Safe Remote     ");
        lcd.setCursor(2, 1);
        lcd.print("Controlled Car  ");
        showProjectInfo = false;
        delay(1000); // Wait for 2 seconds before switching back
        scrollCounter = 0; // Reset the scroll counter
      }
    }
  }
}