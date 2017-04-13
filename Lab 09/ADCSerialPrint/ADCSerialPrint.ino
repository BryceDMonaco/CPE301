/*
    ArduinoPrintADC.ino

    Original Author: Seb Madgwick
    Modified By: Bryce Monaco

    Sends up to all 6 analogue inputs values in ASCII as comma separated values
    over serial.  Each line is terminated with a carriage return character ('\r').
    The number of channels is sent by sending a character value of '1' to '6' to 
    the Arduino.

    Original File: https://github.com/xioTechnologies/Serial-Oscilloscope/blob/master/ArduinoPrintADC/ArduinoPrintADC.ino

 */

#include <stdlib.h> // div, div_t

//Serial Pointers
volatile unsigned char *myUCSR0A = (unsigned char *) 0xC0;
volatile unsigned char *myUCSR0B = (unsigned char *) 0xC1;
volatile unsigned char *myUCSR0C = (unsigned char *) 0xC2;
volatile unsigned int  *myUBRR0  = (unsigned int *)  0xC4;
volatile unsigned char *myUDR0   = (unsigned char *) 0xC6;

//ADC Pointers
volatile unsigned char *myADCSRA = (unsigned char *) 0x7A;
volatile unsigned char *myADCSRB = (unsigned char *) 0x7B;
volatile unsigned char *myADMUX =  (unsigned char *) 0x7C;
volatile unsigned char *myDIDR0 =  (unsigned char *) 0x7E;
volatile unsigned int *myADCData = (unsigned int *) 0x78; //0x78 is the low byte

void U0init (int rate);
unsigned char U0kbhit ();
unsigned char U0getchar ();
void U0putchar (unsigned char U0pdata);
void InitializeADC (int doStart);

void setup() 
{
  // initialize the serial port on USART0:
  U0init(9600);
  //Serial.begin(9600);

  //InitializeADC (1);
  
}

void loop() 
{
    InitializeADC (1);
    PrintInt(MyAnalogRead());
    //PrintInt(analogRead(A0));

    
    //Serial.write('\r'); // print new line
    U0putchar('\r');
    
}

// Fast int to ASCII conversion
void PrintInt(int i) 
{
    static const char asciiDigits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    //div_t n;
    int n;
    int print = 0;
    
    if(i < 0) 
    {
        //Serial.write('-');
        U0putchar('-');
        i = -i;
        
    }
    
    if(i >= 10000) 
    {
        //n = div(i, 10000);
        n = i/10000;
        //Serial.write(asciiDigits[n.quot]);
        U0putchar(asciiDigits[n]);
        //i = n.rem;
        i = i % 10000;
        print = 1;
        
    }
    
    if(i >= 1000 || print) 
    {
        //n = div(i, 1000);
        n = i / 1000;
        //Serial.write(asciiDigits[n.quot]);
        U0putchar(asciiDigits[n]);
        //i = n.rem;
        i = i % 1000;
        print = 1;
        
    }
    
    if(i >= 100 || print) 
    {
        //n = div(i, 100);
        n = i / 100;
        //Serial.write(asciiDigits[n.quot]);
        U0putchar(asciiDigits[n]);
        //i = n.rem;
        i = i % 100;
        print = 1;
        
    }
    
    if(i >= 10 || print) 
    {
        //n = div(i, 10);
        n = i / 10;
        //Serial.write(asciiDigits[n.quot]);
        U0putchar(asciiDigits[n]);
        //i = n.rem;
        i = i % 10;
        
    }
    
    //Serial.write(asciiDigits[i]);
    U0putchar(asciiDigits[i]);
}

//
// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. Assume FCPU = 16MHz.
//
void U0init(int U0baud)
{
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20;
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0  = tbaud;
 
}

//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//
void U0putchar(unsigned char U0pdata)
{  
  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty
  
  *myUDR0 = U0pdata;

  return;
  
}

void InitializeADC (int doStart)
{
  *myADCSRA = (unsigned char) 0x84;
  *myADCSRB = (unsigned char) 0x00;
  *myADMUX = (unsigned char) 0x40;
  *myDIDR0 = (unsigned char) 0x00;

  if (doStart == 1)
  {
    *myADCSRA |= 0x40; //Start conversion
    
  }

  while ((*myADCSRA & 0x40) == 0x40); //Wait for conversion to finish
  
  return;
  
}

unsigned int MyAnalogRead ()
{
  return *myADCData;
  
}

