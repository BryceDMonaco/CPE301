/*
 * Bryce Monaco
 * CPE 301
 * Lab 05 - Question 2
 */
void setup() 
{
  // put your setup code here, to run once:
  char message[80];

  snprintf (message, 80, "Hello, World!\n");

  Serial.begin(9600);
  Serial.write(message);

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
