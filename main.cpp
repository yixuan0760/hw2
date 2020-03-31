#include "mbed.h"


Serial pc( USBTX, USBRX );

AnalogOut Aout(DAC0_OUT);

AnalogIn Ain(A0);

DigitalIn  Switch(SW3);

DigitalOut redLED(LED1);

DigitalOut greenLED(LED2);

BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};




int sample = 1000;

int i,j=0,fre,a,b,c;


float ADCdata[1000],fr[2],freq,k;


int main(){

  for (i = 0; i < sample; i++){
    //Aout = Ain;
    ADCdata[i] = Ain;

    wait(1./1000);

  }

  for (i = 0; i < sample; i++){

    pc.printf("%1.3f\r\n", ADCdata[i]);

    wait(0.05);
  }

  for(i=0; i<sample && j<2; i++){
    if(ADCdata[i]<0.01){
      fr[j]=i;
      j++;
    }
  }
  freq=1000.0/(fr[1]-fr[0]);
  fre=int(freq);
  while(1){
    if( Switch == 1 ){
      greenLED = 0;
      redLED = 1;
    }
    else{
      redLED = 0;
      greenLED = 1;
      a=fre/100;
      b=(fre-a*100)/10;
      c=fre%10;
      display = table[a];
      wait(1);
      display = table[b];
      wait(1);
      display = table[c];
      wait(1);
    }

    for( k=0; k<2; k+=0.05 ){

      Aout = 0.5 + 0.5*sin(k*3.14159);

      wait(1/(freq*40));

    }

  }
  


}