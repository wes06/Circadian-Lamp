
/*
Title: Lesson 3a. Improved parsing and reduced SRAM consumption - "Case" Statements
 
Description:  Reading a line of text from the Serial Port and sending to a command process function.
the processing function only echos back to the console for this lesson
This sketch also demonstrates the use of compiler directives to turn on and off blocks of functionality
Date created: 5th June 2014
Created By: Peter Oakes
Additional Comments:
Feel free to use and abuse as you wish, I imply NO Warranty
NOTE: defines take no program space untill used so use instead of ints etc when it will never change
Lessons Available
lesson 0. How big is an Empty Sketch anyway
Lesson 1. Reading the Serial input a line at time
Lesson 2. Parsing the line using  "if else if" statements and == or strcmp
Lesson 3a. Preperation for Improved parsing and reduced SRAM consumption - "Case" Statements
*/
/* Include needed Lbraries */

/* End include libraries */

// Bunch of constants in the form of definitions
// 1 = output debug to serial port, 0 = no debug
#define debug 1 
// define the buffer size... 
#define serialbufferSize 50 
#define cmdDel "|,.- "


// End of Constants


char inputBuffer[serialbufferSize]; 
int serialIndex = 0; // keep track of where we are in the buffer


void setup() 
{    
  Serial.begin(115200);

  Serial.println("type \"Hello\"" );

}

void loop() 
{
  if (CheckSerial()) DoCommand(inputBuffer); 
}



// Enhanced Command Processor using strtok to strip out command from multi parameter string
boolean DoCommand(char * cmdBuf)
{

  // COMMAND-1024-1024-1024-1024
  char* Command;
  char* Param[4];

  // Get the command from the input string
  Command = strtok(cmdBuf, cmdDel);
  for(int i = 0;i<4;i++){
      Param[i] = strtok(NULL, cmdDel);
  }

  //if (strcmp(Command, "A")==0){}


  for(int i = 0; i<4;i++){
    tarVal[i] = atoi(Param[i]); //atoi() = ascii to intger
  //  int outparam[i]= isNumeric (Param[i]);
  }

  //if it is a number then convert it
  //if (!outparam[i]) 
  //{
      

      //if (tarVal[i]< 0 || tarVal[i] > 1023) outparameter = false;

  //}
  if (strcmp(Command, "WRITE")==0){
      Serial.print("WRITE: ");
      for(int i = 0; i<4;i++){
        Serial.print("val ");
        Serial.print(i);
        Serial.print(":  ")
        Serial.println(tarVal[i]); //atoi() = ascii to intger
  //  int outparam[i]= isNumeric (Param[i]);
      }
  }
  else if (strcmp(Command, "WRITE_FAST")==0  && outparameter ){
      Serial.print("pwm 1 = ");
      Serial.println(analogVal2);    // read the input pin "A1" is already defined
  } 
  else {
    Serial.print("I dont understand you \nYou said: ");
    Serial.println(commandBuffer);
  }




    
  // debug code after here
  #if debug  
  if (Parameter1 != '\0'){
    Serial.print((outparameter)? "Remaining Param1 is numeric and = " : "Remaining Param1 is non numeric and = " );
    Serial.println(Parameter1);  
  }

    if (Parameter2 != '\0'){
    Serial.print((outparameter)? "Remaining Param2 is numeric and = " : "Remaining Param2 is non numeric and = " );
    Serial.println(Parameter2);  
  }

    if (Parameter3 != '\0'){
    Serial.print((outparameter)? "Remaining Param3 is numeric and = " : "Remaining Param3 is non numeric and = " );
    Serial.println(Parameter3);  
  }

    if (Parameter4 != '\0'){
    Serial.print((outparameter)? "Remaining Param4 is numeric and = " : "Remaining Param4 is non numeric and = " );
    Serial.println(Parameter4);  
  }

    Serial.print("Free Ram = "); Serial.println(freeRam(), DEC);
  #endif  
  return true;
}












/*
Checks the serial input for a string, returns true once a '\n' is seen
users can always look at the global variable "serialIndex" to see if characters have been received already
*/
boolean CheckSerial()
{
  boolean lineFound = false;
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    //Read a character as it comes in:
    //currently this will throw away anything after the buffer is full or the \n is detected
    char charBuffer = Serial.read(); 
      if (charBuffer == '\n') {
           inputBuffer[serialIndex] = 0; // terminate the string
           lineFound = (serialIndex > 0); // only good if we sent more than an empty line
           serialIndex=0; // reset for next line of data
         }
         else if(charBuffer == '\r') {
           // Just ignore the Carrage return, were only interested in new line
         }
         else if(serialIndex < serialbufferSize && lineFound == false) {
           /*Place the character in the string buffer:*/
           inputBuffer[serialIndex++] = charBuffer; // auto increment index
         }
  }// End of While
  return lineFound;
}// End of CheckSerial()

int isNumeric (const char * s)
{
  while(*s)
  {
    if(!isdigit(*s)) return 0;
    s++;
  }
  return 1;
}

#if debug
// check free ram
int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
#endif
