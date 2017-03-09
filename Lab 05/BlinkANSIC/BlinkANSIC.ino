/*
  Bryce Monaco
  CPE 301
  Lab 05 - Question 1 (Book 3.3)

  This modified version of the Blink example blinks the LED a variable amount of times,
  starting once and going all the way to ten times.

  Because the MyDelay function in this program does not actually use the timers the cycles
  take significantly longer.

  The LED is connected to PB7
  
*/

//Port B Pointers
volatile unsigned char* thisDDRB = (unsigned char) 0x24;
volatile unsigned char* thisPortB = (unsigned char) 0x25;

void MyDelay (unsigned long mSeconds);

// the setup function runs once when you press reset or power the board
void setup() 
{
  *thisDDRB |= 0x80; //Sets pin 7 to write
  
}

// the loop function runs over and over again forever
void loop() 
{
  for (int i = 0; i < 10; i++)
  {
    for (int ii = 0; ii <= i; ii++)
    {
      *thisPortB |= 0x80;
      MyDelay (500);                   
      *thisPortB &= 0x7F;
      MyDelay (500);                       
          
    }

    MyDelay (2000);
    
  }
  
}

void MyDelay (unsigned long mSeconds)
{
  volatile unsigned long i;
  unsigned long endTime = 1000 * mSeconds;

  for (i = 0; i < endTime; i++);

  return;
  
} 
