void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

MASTER:

In serial monitor put BOTH NL & CR and put BAUD RATE = 38400.
Putting in Serial Monitor those commands:
AT
AT+RMAAD
AT+ROLE=1
AT+UART=38400,0,0
AT+CMODE=0
AT+BIND=0022,04,01172B