/*
 NOTE: THIS CODE IS MEANT FOR THE IO MCU ON THE ARDUINO.
 To upload code to the IO MCU, you have to put the arduino
 in bootloader mode by shorting the two 16u2 reset pins.

 This part of the code handles taking input from the IO pins
 and sending it to the USB MCU over Serial.
*/

// Number of buttons
#define BUTTON_COUNT 8

// Array linking IO pins to button numbers.
// The index in the array dictates the button number (index 0 is button 1, etc)
const int BUTTON_ARRAY[BUTTON_COUNT] = {
  9,
  7,
  5,
  3,
  8,
  6,
  4,
  2
};

void setup() {
  // Configure IO pins to input mode
  for(int i = 0; i < BUTTON_COUNT; i++){
    pinMode(BUTTON_ARRAY[i], INPUT_PULLUP);
  }
  
  // Start the Serial which is connected with the USB MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission. 
  Serial.begin(115200);
}

void loop() {
  // Only send data if the Serial is empty
  if(Serial.available() == 0){

    /* 
     * Data is sent as an 8 bit number, with each bit representing a button. 
     * 1 means pressed, 0 means unpressed.
     */
    
    // Value to be outputed over Serial
    int output = 0;
    
    int bitCounter = 1; // Tracking binary decimal place
    for(int i = 0; i < BUTTON_COUNT; i++){
      if(digitalRead(BUTTON_ARRAY[i]) == HIGH){
        output += bitCounter; // Set digit to 1
      }
      bitCounter *= 2; // Move to next decimal place (binary equivalent of * 10)
    }

    Serial.write(output);
  }

  // Debouncing
  delay(10);
}
