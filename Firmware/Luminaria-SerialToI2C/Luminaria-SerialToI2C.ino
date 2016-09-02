#include <Wire.h>

#include <serialCom.h>

serialCom serCom;

/**
Description:    The pre-scaler and the timer count divide the timer-counter
                clock frequency to give a timer overflow interrupt rate:

                Interrupt rate =  16MHz / (prescaler * (255 - TCNT2))

        TCCR2B[b2:0]   Prescaler    Freq [KHz], Period [usec] after prescale
          0x0            (TC stopped)     0         0
          0x1                1        16000.        0.0625
          0x2                8         2000.        0.500
          0x3               32          500.        2.000
          0x4               64          250.        4.000
          0x5              128          125.        8.000
          0x6              256           62.5      16.000
          0x7             1024           15.625    64.000
          
**/

int tarVal[] = {3300,3300,3300,3300};
float currVal[] = {540,540,540,540};
int params[] = {  540,540,540,540,  //channels
                  0,        //Write Mode: linear, accel, instant, etc?
                  0,        //Speed
                  };

float valChange = 1;

byte channel[] = {
                
                0x09,   //  ADR1  gnd   ADR0    gnd
                0x0A,   // segundo
                0x4D,   //terceira
                0x4E,   //quarto (fontes)
                0x48    //  Broadcast
                };


boolean tick = false;

int frame;

void setup()
{
  cli();
  TCCR2B = 0x00;        // Disable Timer2 while we set it up
  TCNT2  = 0;         // Reset Timer Count  (255-100) = execute ev (255-tcnt2) 155-th T/C clock
  TIFR2  = 0x00;        // Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        // Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        // Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x07;        // Timer2 Control Reg B: Timer Prescaler set to 1024
  sei();
  
  
  Serial.begin(9600);
  
  Wire.begin();
  Wire.setClock(500000); //500kHz = 80 uS per DAC write
}


ISR(TIMER2_OVF_vect) {
    tick = true;
    TCNT2 = 250;     // reset timer ct to x out of 255
    TIFR2 = 0x00;    // timer2 int flag reg: clear timer overflow flag
};


void loop()
{
  if (serCom.checkSerial()) {
    serCom.getCommand(params, 6);
    for(int i = 0;i<4;i++){
      tarVal[i] = params[i];
      Serial.print("Param ");
      Serial.print(i);
      Serial.print(" :   ");
      Serial.println(params[i]);
    }
    if(params[4] != 0)    //params[4]
    if(params[5] != 0) valChange = params[5]/10;
    else valChange = 1;
  }

  
  if(tick == true){
    //animate();
    tick = false;
    frame++;
  }
  
  if(frame > 40){
    animate();
    frame=0;
  }

}

