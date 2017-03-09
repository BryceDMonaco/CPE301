/*
  Bryce Monaco
  CPE 301
  Lab 05 - Question 1 (Book 3.1)

  This modified version of the Blink example blinks the LED a variable amount of times,
  starting once and going all the way to ten times.

  The LED is connected to PB7
  
*/

// the setup function runs once when you press reset or power the board
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() 
{
  for (int i = 0; i < 10; i++)
  {
    for (int ii = 0; ii <= i; ii++)
    {
      digitalWrite (LED_BUILTIN, HIGH);   
      delay (500); 
      digitalWrite (LED_BUILTIN, LOW); 
      delay (500);                    
          
    }

    delay (2000);
    
  }
  
}
