/*
 * Bryce Monaco
 * CPE 301 (Lab Section 1102)
 * Lab 07
 * 
 */

//Clock Pointers, See Mega Datasheet PDF Chapter 17.11 for Reg Summary
volatile unsigned char* thisTCCR1A = (unsigned char *) 0x80; //Contains WGM10 (bit 0) and WGN11 (bit 1)
volatile unsigned char* thisTCCR1B = (unsigned char *) 0x81; //Contains WGM12 (bit 3) and WGN13 (bit 4)
volatile unsigned char* thisTCCR1C = (unsigned char *) 0x82; //Contains FOC1A through C (bits 5 to 7)
volatile unsigned char* thisTIMSK1 = (unsigned char *) 0x6F; //Interrupt Mask Register
volatile unsigned int*  thisTCNT1  = (unsigned  int *) 0x84; //Timer1 Counter, 16b, H byte at 0x85
volatile unsigned char* thisTIFR1  = (unsigned char *) 0x36; //Contains TOV1 (overflow flag) (bit 0)

//GPIO Pointers for Port B, See Mega Datasheet PDF Chapter 33 pg 403
volatile unsigned char *portDDRB = (unsigned char *) 0x24; 
volatile unsigned char *portB =    (unsigned char *) 0x25;

//Status Register
volatile unsigned char *thisSREG = (unsigned char *) 0x5F;

//Serial Pointers
volatile unsigned char *myUCSR0A = (unsigned char *) 0xC0;
volatile unsigned char *myUCSR0B = (unsigned char *) 0xC1;
volatile unsigned char *myUCSR0C = (unsigned char *) 0xC2;
volatile unsigned int  *myUBRR0  = (unsigned int *)  0xC4;
volatile unsigned char *myUDR0   = (unsigned char *) 0xC6;

unsigned char byteRead;
bool shouldPlay = false; //Gets marked as false when q is input, stays true after first note until q
bool hasStarted = false;
int value;

void U0init (int rate);
unsigned char U0kbhit ();
unsigned char U0getchar ();
void U0putchar (unsigned char U0pdata);

void setup() 
{
  *portDDRB |= 0x40; //Speaker connected to PB6, pin 12

  //Set the timer to Normal mode
  *thisTCCR1A = 0;
  *thisTCCR1B = 0;
  *thisTCCR1C = 0;
  *thisTIMSK1 = 0x01; //Enable interrupt

  *thisSREG |= 0x80; //Enable global interrupts

  //Serial.begin(9600);
  U0init(9600);
    
}

void loop() 
{
  if (U0kbhit() == 0x01)
  {
    byteRead = U0getchar();

    U0putchar(byteRead);
    
  }

  if (byteRead == 'q')
  {
    shouldPlay = false; 

    //Serial.write("Stopping!\n");
    
  }


  if (byteRead == 'a') //A
  {
    shouldPlay = true;
    value = 18182;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;  
    
  } else if (byteRead == 'b') //B
  {
     shouldPlay = true;
    value = 16194; 

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'c') //C
  {
    shouldPlay = true;
    value = 15296;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'd') //D
  {
    shouldPlay = true;
    value = 13628;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'e') //E
  {
    shouldPlay = true;
    value = 12139;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'f') //F
  {
    shouldPlay = true;
    value = 11461;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'g') //G
  {
    shouldPlay = true;
    value = 10204;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'A') //A#
  {
    shouldPlay = true;
    value = 17167;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'C') //C#
  {
    shouldPlay = true;
    value = 14440;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'D') //D#
  {
    shouldPlay = true;
    value = 12820;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'F') //F#
  {
    shouldPlay = true;
    value = 10811;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'G') //G#
  {
    shouldPlay = true;
    value = 9627;

    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536

    byteRead = 't'; //Note 't' is just a value which the program doesn't recognize as a note

    *thisTCCR1B |= 0b00000001;
    
  } else if (byteRead == 'q')
  {
    shouldPlay == false;

    *portB &= 0xBF; //Set the output low
    *thisTCCR1B &= 0xF8; //Disable the timer to stop any possible interrupts

    //This if statement does not set byteRead to 't' because on the off chance that an interrupt fires and starts the timer again
    //while this function is running then the next time the loop() function goes it will be immediately stopped
    
  }
  
}

ISR(TIMER1_OVF_vect)
{  
  if ((*portB & 0x40) == 0x40) //Output is on
  {
    *portB &= 0xBF; //Disable the output
    
  } else
  {
    *portB |= 0x40; //Enable the output
     
  }

  hasStarted = false;
    
  *thisTCCR1B &= 0xF8;              //Disable Timer
  *thisTCNT1 = (unsigned int) (65536 - value); //The timer will count up from the value to the max 65536
  *thisTCCR1B |= 0b00000001; //Run the timer at PS1
  
}

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

unsigned char U0kbhit()
{
  return (*myUCSR0A >> 7); //Shifted to the 0th bit

}

unsigned char U0getchar()
{
  return *myUDR0;
  
}

void U0putchar(unsigned char U0pdata)
{  
  while ((*myUCSR0A & 0x20) != 0x20); //Wait for data register to be empty
  
  *myUDR0 = U0pdata;

  return;
  
}
