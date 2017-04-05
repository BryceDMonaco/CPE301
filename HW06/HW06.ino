/*
  Bryce Monaco
  CPE 301
  HW06 - Question 2/3
  Version 1.0
  
*/

#define FCPU 16000000 //Used in U0init for Baud calculation

#define RDA 0x80  
#define TBE 0x20  

//Pointers
volatile unsigned char *thisUCSR0A = (unsigned char *) 0x00C0;  
volatile unsigned char *thisUCSR0B = (unsigned char *) 0x00C1;  
volatile unsigned char *thisUCSR0C = (unsigned char *) 0x00C2;  
volatile unsigned int  *thisUBRR0  = (unsigned int *)  0x00C4;  
volatile unsigned char *thisUDR0   = (unsigned char *) 0x00C6;

void U0init (int rate);
unsigned char U0kbhit ();
unsigned char U0getchar ();
void U0putchar (unsigned char U0pdata);

// the setup function runs once when you press reset or power the board
void setup () 
{
  U0init(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() 
{   
  /* //Just a simple test program to use the functions to echo the input back out
  digitalWrite (LED_BUILTIN, LOW);
   *thisUCSR0A = 0x20;  

  unsigned char cs1;   
  while (U0kbhit()==0x00); // wait for RDA = true   
  cs1 = U0getchar(); // read character   
  U0putchar(cs1); // echo character
  */
}

void U0init (int rate) 
{ 
  unsigned int newBaud = (FCPU / 16 / rate - 1); //FCPU/(16*rate) - 1 (Old function) 

  *thisUCSR0A = 0x20;
  *thisUCSR0B = 0x18;
  *thisUCSR0C = 0x06;
  *thisUBRR0 = newBaud; 
/*
   unsigned long tFCPU = 16000000;  
   unsigned int tbaud;  
   tbaud = (tFCPU / 16 / rate - 1);  
   *thisUCSR0A = 0x20;  
   *thisUCSR0B = 0x18;  
   *thisUCSR0C = 0x06;  
   *thisUBRR0  = tbaud;
*/
  return;
  
}

//U0kbhit(void) – will examine the RDA status bit and return a true (non-zero value) if RDA is true otherwise it will return a false (0 value) in ACC
//RDA is the Recieve Status Bit in UCSRA (bit 7)
unsigned char U0kbhit ()
{ 
  return (*thisUCSR0A >> 7); //Shifted to the 0th bit
  
}

//U0getchar(void) – will read one character from the serial port and return it.
unsigned char U0getchar ()
{
  return *thisUDR0;
  
}

//U0putchar(unsigned char U0pdata) – will wait until the serial port TBE status bit is high and then will take the character U0pdata and send the character out to the serial port.
void U0putchar (unsigned char U0pdata)
{
  //while ((*thisUCSR0A >> 6) != 0x00); //wait until the bit 6 goes high

  *thisUDR0 = U0pdata;

  return;
  
}

