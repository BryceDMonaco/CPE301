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

unsigned char byteRead;
bool shouldPlay = false; //Gets marked as false when q is input, stays true after first note until q
int value;

void MyDelay (unsigned long mSeconds);

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  //*portDDRB |= 0x80; //LED is conected to PB7, used for debugging
  *portDDRB |= 0x40; //Speaker connected to PB6, pin 12

  //Set the timer to Normal mode
  *thisTCCR1A = 0;
  *thisTCCR1B = 0;
  *thisTCCR1C = 0;
  *thisTIMSK1 = 0;

  Serial.begin(9600);
    
}

void loop() 
{
  if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
    /*ECHO the value that was read, back to the serial port. */
    
    Serial.write(byteRead);
    
  }

  if (byteRead == 'q')
  {
    shouldPlay = false; 

    Serial.write("Stopping!\n");
    
  }


  if (byteRead == 'a') //A
  {
    shouldPlay = true;
    value = 18182;
    
  } else if (byteRead == 'b') //B
  {
     shouldPlay = true;
    value = 16194;
    
  } else if (byteRead == 'c') //C
  {
    shouldPlay = true;
    value = 15296;
    
  } else if (byteRead == 'd') //D
  {
    shouldPlay = true;
    value = 13628;
    
  } else if (byteRead == 'e') //E
  {
    shouldPlay = true;
    value = 12139;
    
  } else if (byteRead == 'f') //F
  {
    shouldPlay = true;
    value = 11461;
    
  } else if (byteRead == 'g') //G
  {
    shouldPlay = true;
    value = 10204;
    
  } else if (byteRead == 'A') //A#
  {
    shouldPlay = true;
    value = 17167;
    
  } else if (byteRead == 'C') //C#
  {
    shouldPlay = true;
    value = 14440;
    
  } else if (byteRead == 'D') //D#
  {
    shouldPlay = true;
    value = 12820;
    
  } else if (byteRead == 'F') //F#
  {
    shouldPlay = true;
    value = 10811;
    
  } else if (byteRead == 'G') //G#
  {
    shouldPlay = true;
    value = 9627;
    
  } else if (byteRead == 'q')
  {
    shouldPlay == false;
    
  }
  
  if (shouldPlay)
  {
    *portB |= 0x40; //Set output high
    
    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536
    *thisTCCR1B |= 0b00000001;        //Set pre-scalar 1024 and start Timer, I'm not sure if the function should choose what pre-scalar to use
                                      //...or if it's safest to just stick to one
    
    while ((*thisTIFR1 & 0x01) == 0);    //Wait for overflow flag 
    
    *thisTCCR1B &= 0xF8;              //Disable Timer                         
    *thisTIFR1 |= 0x01;               //Reset the flag

    *portB &= 0xBF; //Set output low
    
    *thisTCCR1B &= 0xF8;              //Disable Timer
    *thisTCNT1 = (unsigned int) 65536 - value; //The timer will count up from the value to the max 65536
    *thisTCCR1B |= 0b00000001;        //Set pre-scalar 1024 and start Timer, I'm not sure if the function should choose what pre-scalar to use
                                      //...or if it's safest to just stick to one
    
    while ((*thisTIFR1 & 0x01) == 0);    //Wait for overflow flag 
    
    *thisTCCR1B &= 0xF8;              //Disable Timer                         
    *thisTIFR1 |= 0x01;               //Reset the flag

  }  
}
