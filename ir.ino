// Include Libraries
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

// Setupt the IR reciever
const int IR = 11; // IR Receiver input pin (we receive data trough this pin)
IRrecv irrecv(IR); // Create a new instance of the IR
decode_results results;

const int LED = 9; // LED strip output pin (has to be a PWM digital pin)
int BRIGHTNESS = 255; // intial value for the brightness (should be between 0 and 255)
int BRIGHTNESS_COEF = 16; // The coefficient (with how much we want the value of the brightness to go up or down) 

void setup()
{
  pinMode(LED, OUTPUT); // Set the LED strip pin to OUTPUT mode
  analogWrite(LED, 255); // When device is started, LED strip should be on full brightness
  Serial.begin(9600); // Start Serial
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  // Only do something when we receive some data
  if (irrecv.decode(&results)) {

      // This will print on the screen what was received
      //Serial.println(results.value);

      // Now we do different stuff depending on the received data
      switch(results.value) {
        
        // In my case this is the "VOL+" button
        case 2155834005:
          BRIGHTNESS = BRIGHTNESS + BRIGHTNESS_COEF;

          // Make sure value never goes over 255 (or LED strip will just turn off)
          if(BRIGHTNESS > 255) {
            BRIGHTNESS = 255;
          }
          
          break;
          
        // In my case this is the "VOL-" button
        case 2155866645:
          BRIGHTNESS = BRIGHTNESS - BRIGHTNESS_COEF;

          // Make sure value doesn't go below 0
          if(BRIGHTNESS < 0) {
            BRIGHTNESS = 0;
          }

          break;

        // In my case this is the "TV IN" button
        case 2155813605:

          BRIGHTNESS = 255;
          break;

        // In my case this is the "SET" button
        case 2155846245:
        
          BRIGHTNESS = 0;
          break;
          
     }

      // Now we send our brightness data to the LED strip
      analogWrite(LED, BRIGHTNESS);

      // Display the brightness value in serial monitor window
      Serial.println(BRIGHTNESS);

      // Receive the next value
      irrecv.resume(); 
    }

    // THAT IS ALL FOLKS!
}
