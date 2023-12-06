#include <LiquidCrystal.h>
#include <TFT.h>
#include <SPI.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
unsigned long update;
int contador = 0;
bool info = false;

//tft:
#define cs 10
#define dc 8
#define rst 9
TFT TFTscreen = TFT(cs, dc, rst);

int xPos = 0;

const int ldr = A0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Safe Remote     ");
  lcd.setCursor(1, 1);
  lcd.print("Controlled Car  ");
  update = millis();

  //tft:
  pinMode(ldr, INPUT);

  Serial.begin(9600);

  TFTscreen.begin();
}

void loop() {
  //TFT:
  int valor = analogRead(ldr);
  int limite = 600;


  if (valor > limite) {     // Quando está de noite ou seja é necessário ligar os faróis do carro
    TFTscreen.background(0, 0, 0);

    int x1 = 40;
    int y1 = 60;
    int radius1 = 30;

    int x2 = 120;
    int y2 = 60;
    int radius2 = 30;

    for (int i = 0; i < 10; i++) {
      TFTscreen.circle(x1, y1, radius1 + i);
      TFTscreen.circle(x2, y2, radius2 + i);
    }

    TFTscreen.fill(255, 255, 255);

    TFTscreen.circle(x1, y1, radius1);
    TFTscreen.circle(x2, y2, radius2);
  } else {
    TFTscreen.background(0, 0, 0);
    delay(1000);  // Quando está de dia ou seja tft fica com o background preto
  }


  if (!info) {
    if (millis() - update > 100) {
      lcd.scrollDisplayRight();
      update = millis();
      contador++;

      if (contador > 16) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Projeto 1");
        lcd.setCursor(2, 1);
        lcd.print("DAVID & PEDRO");
        info = true;
        delay(500);
        contador = 0;
      }
    }
  } else {
    if (millis() - update > 100) {
      lcd.scrollDisplayLeft();
      update = millis();
      contador++;

      if (contador > 13) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Safe Remote     ");
        lcd.setCursor(1, 1);
        lcd.print("Controlled Car  ");
        info = false;
        delay(500);
        contador = 0;
      }
    }
  }

}
