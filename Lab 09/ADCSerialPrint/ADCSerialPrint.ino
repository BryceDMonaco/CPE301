/*
    ArduinoPrintADC.ino

    Original Author: Seb Madgwick
    Modified By: Bryce Monaco
    Version 2.0 //2.0 since I consider 1.0 to be the original program

    Original File: https://github.com/xioTechnologies/Serial-Oscilloscope/blob/master/ArduinoPrintADC/ArduinoPrintADC.ino

 */

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
void InitializeADC ();

void setup() 
{
  // initialize the serial port on USART0:
  U0init(9600);
  
}

void loop() 
{
    InitializeADC ();
    PrintInt(MyAnalogRead());
    
    U0putchar('\r');
    
}

// Fast int to ASCII conversion, used for serial output
void PrintInt(int i) 
{
    static const char asciiDigits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int n;
    int print = 0;
    
    if(i < 0) 
    {
        U0putchar('-');
        i = -i;
        
    }

    if(i >= 10000) 
    {
        n = i/10000;
        U0putchar(asciiDigits[n]);
        i = i % 10000;
        print = 1;
        
    }
    
    if(i >= 1000 || print) 
    {
        n = i / 1000;
        U0putchar(asciiDigits[n]);
        i = i % 1000;
        print = 1;
        
    }
    
    if(i >= 100 || print) 
    {
        n = i / 100;
        U0putchar(asciiDigits[n]);
        i = i % 100;
        print = 1;
        
    }
    
    if(i >= 10 || print) 
    {
        n = i / 10;
        U0putchar(asciiDigits[n]);
        i = i % 10;
        
    }
    
    U0putchar(asciiDigits[i]);

    return;
    
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

//Has the ADC record a value
void InitializeADC ()
{
  *myADCSRA = (unsigned char) 0x84;
  *myADCSRB = (unsigned char) 0x00;
  *myADMUX = (unsigned char) 0x40;
  *myDIDR0 = (unsigned char) 0x00;

  *myADCSRA |= 0x40; //Start conversion

  while ((*myADCSRA & 0x40) == 0x40); //Wait for conversion to finish
  
  return;
  
}

unsigned int MyAnalogRead ()
{
  return *myADCData;
  
}

