
#include "TeensyROMControl.h"

//TeensyROMControl::TeensyROMControl()
//{
//   //Constructor
//
//}

bool TeensyROMControl::begin(Stream &port) 
{
   _port = &port;

#ifdef DbgChannel
   DbgChannel.begin(115200);
#endif
   DbgPrintf("Debug channel enabled\n");

   return true;
}

bool TeensyROMControl::MenuReset()
{
   SendToken(ResetC64Token);
   DbgPrintf("*Sent Reset\n");
   if (!FlushRx()) return false;
   DbgPrintf("*Success\n");   
   return true;
}

bool TeensyROMControl::LaunchFile(enDriveSel DriveSel, const char* PathFileName)
{
   SendToken(LaunchFileToken);
   DbgPrintf("*Sent Launch\n");
   if (!GetAckToken()) return false;  //retry/abort if minimal
   _port->write(DriveSel);
   _port->write(PathFileName, strlen(PathFileName)+1); //include term
   if (!GetAckToken()) return false; 
   if (!FlushRx()) return false;
   DbgPrintf("*Success\n");   
   return true;
}



//   ***** Private *****

void TeensyROMControl::SendToken(uint16_t TokToSend)
{
   _port->write((TokToSend >> 8) & 0xFF);
   _port->write(TokToSend & 0xFF);
}

bool TeensyROMControl::GetAckToken()
{
   uint8_t LastVal = 0xFF;
   
   while (SerialAvailabeTimeout()) 
   {
      uint8_t Val = _port->read();
      DbgWrite(Val);
      if (Val == ((AckToken >> 8) & 0xFF) && LastVal == (AckToken & 0xFF)) return true;
      LastVal = Val;
   }
   DbgPrintf("No Ack\n");   
   return false;
}

bool TeensyROMControl::FlushRx()
{
   if (!SerialAvailabeTimeout(1000)) 
   {
      DbgPrintf("Nothing to flush\n");   
      return false; //wait up to 1 sec for initial response
   }
   do
   {
      uint8_t val = _port->read();
      DbgWrite(val);
   } while(SerialAvailabeTimeout());
   
   return true;
}

bool TeensyROMControl::SerialAvailabeTimeout(uint32_t MaxTime)
{
  uint32_t StartMillis = millis();
  
  while(!_port->available() && millis() - StartMillis < MaxTime); // timeout loop
  
  return(_port->available());
}

//bool TeensyROMControl::GetSerialString(char * cpBuf, int iMaxLength)
//{
//  int iCharNum = 0;
//  
//  iMaxLength--; //always leave room for term char
//  while (iCharNum < iMaxLength) 
//  {
//    if (!SerialAvailabeTimeout()) 
//    {
//      //Serial.println("Serial Timeout!");  
//      return(false);
//    }
//    cpBuf[iCharNum] = _port->read();
//    if (cpBuf[iCharNum] == '\r') break; 
//    iCharNum++;
//  } 
//  cpBuf[iCharNum] = 0; //terminate (or force if at max len)
//  return(iCharNum < iMaxLength);  
//}
//

