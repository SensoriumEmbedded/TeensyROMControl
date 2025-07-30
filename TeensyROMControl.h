
#ifndef TeensyROMControl_h
#define TeensyROMControl_h

#include <Arduino.h>

#define DbgChannel   Serial   //define to select stream for debug data

//synch with TeensyROM\Source\Teensy\MinimalBoot\Common\Common_Defs.h
#define SetColorToken     0x6422
#define LaunchFileToken   0x6444
#define PingToken         0x6455
#define PauseSIDToken     0x6466
#define SetSIDSongToken   0x6488
#define SIDSpeedLinToken  0x6499
#define SIDSpeedLogToken  0x649A
#define SIDVoiceMuteToken 0x6433
#define C64PauseOnToken   0x6431
#define C64PauseOffToken  0x6430
#define DebugToken        0x6467
#define SendFileToken     0x64AA
#define PostFileToken     0x64BB
#define CopyFileToken     0x64FF
#define GetFileToken      0x64B0
#define DeleteFileToken   0x64CF
#define AckToken          0x64CC
#define GetDirectoryToken 0x64DD
#define ResetC64Token     0x64EE
#define RetryToken        0x9B7E
#define FailToken         0x9B7F
#define BadSIDToken       0x9B80
#define GoodSIDToken      0x9B81

enum enDriveSel
{
   DriveUSB,  // 0
   DriveSD,   // 1
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
   private:
      Stream *_port;
      void SendToken(uint16_t TokToSend);
      bool SerialAvailabeTimeout(uint32_t MaxTime = DEFAULT_TIMEOUT_MS);
      bool FlushRx();
      bool GetAckToken();
};

#endif
