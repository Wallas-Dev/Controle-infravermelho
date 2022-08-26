#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t kIrLed = 27;
const uint16_t kRecvPin = 14;

IRsend irsend(kIrLed);
IRrecv irrecv(kRecvPin);

#define button 26
#define button1 25

byte flag = 0;
byte flag1 = 0; 

decode_results results;

void setup() {
  irsend.begin();
  irrecv.enableIRIn();  // Start the receiver
  Serial.begin(115200, SERIAL_8N1);
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  pinMode(button, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);


}

void loop() {
  if (!digitalRead(button)) {
    flag = 1;

  }
  if (digitalRead(button) && flag == 1) {
    irsend.sendNEC(0xF7C03F, 32);
    flag = 0;

  }
  if (!digitalRead(button1)) {
    flag1 = 1;

  }
  if (digitalRead(button1) && flag1 == 1) {
    irsend.sendNEC(0xF740BF, 32);
    flag1 = 0;

  }
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
  delay(100);

  

}
