/*
 NOTE: THIS CODE IS MEANT FOR THE USB MCU ON THE ARDUINO.
 This should be the default MCU when you upload code.

 This part of the code handles taking the data sent over
 Serial1 and sending it to the driver station as button presses.
*/

#include "HID-Project.h"

// Number of buttons
#define BUTTON_COUNT 8

void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);
  
  // Start the USB Serial for debugging
  Serial.begin(115200);

  // Begin sending data to the DriverStation
  Gamepad.begin();
}

void loop() {
  // Check if any Serial data from the IO MCU was received
  if(Serial1.available() >= 1){
    
    // Get rid of old data
    while(Serial1.available() > 1){
      Serial.println("More than 1 byte was sent"); // DEBUG
      Serial1.read();
    }

    // Read data (this also removes it from the serial cache)
    int data = Serial1.read();
    
    Serial.println(data); // DEBUG

    // Iterate over each bit in the byte for the number of buttons
    for(int i = 1; i <= BUTTON_COUNT; i++){
      // Get the first binary digit (binary equivalent of % 10)
      int firstBit = data % 2; 

      // 1 indicates pressed
      if(firstBit == 1){
        Gamepad.press(i);
      }
      // 0 indicates not pressed
      else{
        Gamepad.release(i);
      }

      // Move digits to the right by 1 (binary equivalent of / 10)
      data /= 2;
    }

    // Send data to DriverStation
    Gamepad.write();
  }
}
