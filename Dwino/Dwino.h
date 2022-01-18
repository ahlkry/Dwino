
#ifndef _DWINO_H_
#define _DWINO_H_

#include <Arduino.h>
#include "Definitions.h"


#define DEFAULT_TIMEOUT 1000

typedef struct {
	uint8_t 	idWindow;
	uint32_t  	AddressIN;
	uint32_t 	AddressOUT;
} Window;
typedef struct {
	uint16_t  	BTN_IN1, BTN_IN2, BTN_OUT1, BTN_OUT2;
	uint16_t  	RAM_BTN_IN1, RAM_BTN_IN2, RAM_BTN_OUT1, RAM_BTN_OUT2;
} Window_RAM;

class Dwino {
  public:
    
    Dwino(Stream* _stream);
    ~Dwino();

    void resetDisplay();
    void setOrientation(uint16_t Angle);
	uint8_t readWindowNow(uint16_t TimeOut);
	void changeWindowNow(uint8_t NumWindowChange);
	uint8_t readBrightnessNow(uint16_t TimeOut);
	void setBrightnesses(uint8_t Max, uint8_t Min, uint8_t TimSeconds);
	uint8_t readVP (uint16_t* pData, uint16_t Add, uint8_t NumReg, uint16_t TimeOut);
    uint8_t writeVP (uint16_t* pData, uint16_t Add, uint8_t NumReg);
	uint8_t putTextVP (char* pData, uint16_t Add);
    // Purge the serial
    void purgeSerial();

   private:
    // Serial line with Dwino
    Stream* stream = NULL;

    // Internal memory for the shared buffer
    // Used for all reception of message from the module
    uint8_t Buffer[LengthBuffer];  
	Window _Window[MaxNumWindows];
	Window_RAM _Window_RAM[MaxNumWindows];
	uint8_t _NumWindows=0, cntWindows=0;
};

#endif // _Dwino_H_
