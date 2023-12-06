void setup(){
}

void loop(){
}

SLAVE:

In serial monitor put BOTH NL & CR and put BAUD RATE = 38400.
Putting in Serial Monitor those commands:
AT
AT+RMAAD
AT+ROLE=0
AT+ UART = 38400,0,0
AT+ADDR?