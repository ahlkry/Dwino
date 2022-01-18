#include "Dwino.h"


Dwino::Dwino(Stream* _stream) {

  stream = _stream;
 
}
/**
  * @brief  System_Reset of Display T5L chip
  * @param  None
  * @retval None
  */
void Dwino::resetDisplay() {
  uint8_t Buffer[10]={0x5A, 0xA5, 0x07, 0x82, 0x00, 0x04, 0x55, 0xAA, 0x5A, 0xA5};
  purgeSerial();
  stream->write(Buffer, 10);
  purgeSerial();
}
/**
  * @brief  Set the bit0 and bit1 of Addres 0x05 for Orientation of Display.
  * @param  uint16_t Angle 	Value of angle that we like set: 0°, 90°, 180° and 270°
  * @retval SUCCESSFULL if execute or Error Value
  */
void Dwino::setOrientation(uint16_t Angle) {
	uint16_t Ang;
	if (Angle == 0)
		Ang=0x04;
	if (Angle == 90)
		Ang=0x05;
	if (Angle == 180)
		Ang=0x06;
	if (Angle == 270)
		Ang=0x07;
	uint8_t Buffer[10]={0x5A, 0xA5, 0x07, 0x82, 0x00, 0x80, 0x5A, 0x00, 0x00, Ang};
	purgeSerial();
	stream->write(Buffer, 7);
	purgeSerial();
}
/**
  * @brief  Read the Num of Windows that is already showing
  * @param  TimeOut The time maximun that the CPU wait a response
  * @retval The num of Window that is the display (See the Dgus project for more details)
  */
uint8_t Dwino::readWindowNow(uint16_t TimeOut) {
  uint32_t TimeOutLCD;
	if (TimeOut < MIN_TIMEOUT)
		TimeOutLCD = millis() + MIN_TIMEOUT;
	else
		TimeOutLCD = millis() + TimeOut;
	uint8_t Buffer[10]={0x5A, 0xA5, 0x04, 0x83, 0x00, 0x14, 0x01};
	purgeSerial();
	stream->write(Buffer, 7);
	purgeSerial();
	//WAIT THE RESPONSE
	int8_t PicNow=-1;
	while (millis() < TimeOutLCD){
		if (stream->available() == 9){
			for (uint8_t i=0;i<8;i++){
				stream->read();
			}
			PicNow = stream->read();
		}
		if (PicNow >= 0)
			break;
	}
	return PicNow;
}
/**
  * @brief  Change Num of Windows for to show
  * @param  NumWindowChange The Number of the window that we like to change or show
  * @retval None
  */
void Dwino::changeWindowNow(uint8_t NumWindowChange) {
	uint8_t Buffer[10]={0x5A, 0xA5, 0x07, 0x82, 0x00, 0x84, 0x5A, 0x01, 0x00, NumWindowChange};
	purgeSerial();
	stream->write(Buffer, 10);
	purgeSerial();
}
/**
  * @brief  Read the percentage of the brightness of Led Display
  * @param  NumWindowChange The Number of the window that we like to change or show
  * @retval None
  */
uint8_t Dwino::readBrightnessNow(uint16_t TimeOut) {
	uint32_t TimeOutLCD;
	if (TimeOut < MIN_TIMEOUT)
		TimeOutLCD = millis() + MIN_TIMEOUT;
	else
		TimeOutLCD = millis() + TimeOut;
	uint8_t Buffer[10]={0x5A, 0xA5, 0x04, 0x83, 0x00, 0x31, 0x01};
	purgeSerial();
	stream->write(Buffer, 7);
	purgeSerial();
	//WAIT THE RESPONSE
	int8_t BrightnessNow=-1;
	while (millis() < TimeOutLCD){
		if (stream->available() == 9){
			for (uint8_t i=0;i<8;i++){
				stream->read();
			}
			BrightnessNow = stream->read();
		}
		if (BrightnessNow >= 0)
			break;
	}
	return BrightnessNow;
}
/**
  * @brief  Change 2 Brightnesses Min and Max and the maximun time for to change into the two Brigthnesses 
  * @param  Max	The percentage (0-100) of the maximun Brightness
  *			Min	The percentage (0-100) of the minimun Brightness
  *			TimSeconds	Number of Seconds that is into the two Brigthness
  * @retval None
  */
void Dwino::setBrightnesses(uint8_t Max, uint8_t Min, uint8_t TimSeconds) {
	uint16_t _Max, _Min, _Tim;
	_Max=Max;
	_Min=Min;
	_Tim=TimSeconds*100;
	uint8_t Buffer[10]={0x5A, 0xA5, 0x07, 0x82, 0x00, 0x82, _Max, _Min, 0x01, 0x2C};
	if (Max > 100)
		_Max=100;//100;
	if (Min > 100)
		_Min=20;//100;
	
	if (_Tim >= 1000){
		_Tim = 1000;
	}
	if (_Tim == 0){
		_Tim = 100;
	}
	Buffer[6] = _Max;
	Buffer[7] = _Min;
	Buffer[8]=_Tim>>8;
	Buffer[9]=_Tim;
	purgeSerial();
	stream->write(Buffer, 10);
	purgeSerial();
}
/**
  * @brief  Change 2 Brightnesses Min and Max and the maximun time for to change into the two Brigthnesses 
  * @param  Max	The percentage (0-100) of the maximun Brightness
  *			Min	The percentage (0-100) of the minimun Brightness
  *			TimSeconds	Number of Seconds that is into the two Brigthness
  * @retval None
  */
void Dwino::readVP(uint16_t* pData, uint16_t Add, uint8_t NumReg, uint16_t TimeOut) {
	
}
/**
  * @brief  Change 2 Brightnesses Min and Max and the maximun time for to change into the two Brigthnesses 
  * @param  Max	The percentage (0-100) of the maximun Brightness
  *			Min	The percentage (0-100) of the minimun Brightness
  *			TimSeconds	Number of Seconds that is into the two Brigthness
  * @retval None
  */
void Dwino::writeVP(uint16_t* pData, uint16_t Add, uint8_t NumReg) {
	
}
/**
  * @brief  Change 2 Brightnesses Min and Max and the maximun time for to change into the two Brigthnesses 
  * @param  Max	The percentage (0-100) of the maximun Brightness
  *			Min	The percentage (0-100) of the minimun Brightness
  *			TimSeconds	Number of Seconds that is into the two Brigthness
  * @retval None
  */
void Dwino::putTextVP(char* pData, uint16_t Add) {
	
}

/**
 * Purge the serial data
 */
void Dwino::purgeSerial() {
  stream->flush();
  while (stream->available()) {
    stream->read();
  }
  stream->flush();
}