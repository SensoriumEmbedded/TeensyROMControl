/*
  The MIT License (MIT)

  Copyright (c) 2025 Travis Smith, Sensorium Embedded, LLC

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TeensyROMControl_h
#define TeensyROMControl_h

#include <Arduino.h>

//#define DbgChannel   Serial1   //define to select stream for debug data


//synch with TeensyROM\Source\Teensy\MinimalBoot\Common\Common_Defs.h
#define SetColorToken     0x6422
#define LaunchFileToken   0x6444  // LaunchFile(enDriveSel DriveSel, const char* PathFileName)
#define PingToken         0x6455
#define PauseSIDToken     0x6466  // PauseSIDToggle()
#define SetSIDSongToken   0x6488  
#define SIDSpeedLinToken  0x6499  
#define SIDSpeedLogToken  0x649A  
#define SIDVoiceMuteToken 0x6433  // SIDVoiceMute(uint8_t EnableBits)
#define C64PauseOnToken   0x6431  // C64 Paused
#define C64PauseOffToken  0x6430  // C64 Unpaused
#define DebugToken        0x6467
#define SendFileToken     0x64AA
#define PostFileToken     0x64BB
#define CopyFileToken     0x64FF
#define GetFileToken      0x64B0
#define DeleteFileToken   0x64CF
#define AckToken          0x64CC  //    Comm
#define GetDirectoryToken 0x64DD
#define ResetC64Token     0x64EE  // MenuReset()
#define RetryToken        0x9B7E  //    Comm
#define FailToken         0x9B7F  //    Comm
#define BadSIDToken       0x9B80  //    Comm
#define GoodSIDToken      0x9B81  //    Comm

enum enDriveSel  //matches enum RegMenuTypes
{
   DriveUSB,    // 0
   DriveSD,     // 1
   DriveTeensy, // 2
};

#define DEFAULT_TIMEOUT_MS  50 //default mS to wait for each char when expecting data

#ifdef DbgChannel
   #define DbgPrintf DbgChannel.printf
   #define DbgWrite  DbgChannel.write
#else
   __attribute__((always_inline)) inline void DbgPrintf(...) {};
   __attribute__((always_inline)) inline void DbgWrite(...) {};
#endif

class TeensyROMControl
{
   public:
      //TeensyROMControl();
      bool begin(Stream &port);
      bool MenuReset();
      bool LaunchFile(enDriveSel DriveSel, const char* PathFileName);
      bool PauseSIDToggle();
      bool VoiceMuteToggle(uint8_t VoiceNum);
      bool C64PauseToggle();

   private:
      Stream *_port;
      uint8_t VoiceMuteBits = 0; //default to all unmuted
      bool C64PauseState = false; //default to unpaused

      void SendToken(uint16_t TokToSend);
      bool SerialAvailabeTimeout(uint32_t MaxTime = DEFAULT_TIMEOUT_MS);
      bool FlushRx();
      bool GetAckToken();
};

#endif
