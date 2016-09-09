// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 100;
// the maximum length of paramters we accept
const int MAX_PARAM = 30;

#define cmdDelimiter "|,.- "        // command delimiter

int paramVal[4];

// Example GET line: GET /?foo=bar HTTP/1.1
void processGet (const char * data)
  {
  // find where the parameters start
  const char * paramsPos = strchr (data, '?');
  if (paramsPos == NULL)
    return;  // no parameters
  // find the trailing space
  const char * spacePos = strchr (paramsPos, ' ');
  if (spacePos == NULL)
    return;  // no space found
  // work out how long the parameters are
  int paramLength = spacePos - paramsPos - 1;
  // see if too long
  if (paramLength >= MAX_PARAM)
    return;  // too long for us
  // copy parameters into a buffer
  char param [MAX_PARAM];
  memcpy (param, paramsPos + 1, paramLength);  // skip the "?"
  param [paramLength] = 0;  // null terminator

  // do things depending on argument (GET parameters)


  char* Command;
  char* Vals[4];

  //Split message
  Command = strtok(param, cmdDelimiter);
 
  for(int i = 0;i<4;i++){
      Vals[i] = strtok(NULL, cmdDelimiter);
  }


  for(int i = 0; i<4;i++){
    if(isNumeric(Vals[i])){
      paramVal[i] = atoi(Vals[i]); //atoi() = ascii to intger
      if(paramVal[i]<0) paramVal[i] = 0;
      else if(paramVal[i]>4095) paramVal[i] = 4095;
    }
    //Serial.print(i);
    //Serial.println(paramVal[i]);
  }
    swSer.print("WR-");
    swSer.print(paramVal[0]);
    swSer.print("-");
    swSer.print(paramVal[1]);
    swSer.print("-");
    swSer.print(paramVal[2]);
    swSer.print("-");
    swSer.print(paramVal[3]);
    swSer.print("\r\n");

  }  // end of processGet


bool isNumeric (const char * s)
{
  while(*s)
  {
    if(!isdigit(*s)) return 0;
    s++;
  }
  return 1;
}



// here to process incoming serial data after a terminator received
void processData (const char * data)
  {
  Serial.println (data);
  if (strlen (data) < 4)
    return;

  if (memcmp (data, "GET ", 4) == 0)
    processGet (&data [4]);
  }  // end of processData





bool processIncomingByte (const byte inByte)
  {
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;
  switch (inByte)
    {
    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      if (input_pos == 0)
        return true;   // got blank line
      // terminator reached! process input_line here ...
      processData (input_line);
      // reset buffer for next time
      input_pos = 0;  
      break;

    case '\r':   // discard carriage return
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1))
        input_line [input_pos++] = inByte;
      break;
    }  // end of switch
  return false;    // don't have a blank line yet
  } // end of processIncomingByte  



