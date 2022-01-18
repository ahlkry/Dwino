
#include "Dwino.h"

Dwino* dwino;

Window AUTOMATIC;
Button Button;

void LoadData (){
  AUTOMATIC.idWindow   = 1;             //FROM DGUS II
  AUTOMATIC.AddressIN   = 0x1000;       //4096
  AUTOMATIC.AddressOUT  = 0x2000;       //8192
}
void setup() {  

  LoadData();
  // Initialize the hardware Serial1
  Serial1.begin(115200);
  delay(100);
   
  dwino = new Dwino((Stream *)&Serial1, 2);

  dwino->addWindow(AUTOMATIC);
  dwino->addButton(AUTOMATIC.idWindow, );

}
 
void loop() {
  
}
