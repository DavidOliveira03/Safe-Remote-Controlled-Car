#include<SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // tx e rx

struct PacketData 
{
  byte lxAxisValue;
  byte lyAxisValue;
  byte rxAxisValue;
  byte ryAxisValue;
};
PacketData data;

void setup()
{
  btSerial.begin(38400);   
}

int joystick(int value, bool reverse)
{
  if (value >= 530)
  {
    value = map(value, 530, 1023, 127, 254);
  }
  else if (value <= 500)
  {
    value = map(value, 500, 0, 127, 0);  
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  return value;
}

void loop()
{
  data.lxAxisValue = joystick(analogRead(A0), false);
  data.lyAxisValue = joystick(analogRead(A1), false);
  data.rxAxisValue = joystick(analogRead(A2), false);
  data.ryAxisValue = joystick(analogRead(A3), false);

  String dataString;
  dataString = dataString 
  + data.lxAxisValue + "," 
  + data.lyAxisValue + ","  
  + data.rxAxisValue + ","  
  + data.ryAxisValue + "\n";
  
  btSerial.print(dataString);
  delay(10);
}
