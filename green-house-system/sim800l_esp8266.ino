//#include <SoftwareSerial.h>
//#include "ghs.h"
//
//SoftwareSerial sim800l(13, 12); // RX, TX
//String phone_number = PHONE_NUMBER; 
//
//void sendSMS();
//
//void setup() {
//  pinMode(15, INPUT);
//  sim800l.begin(9600);
//  Serial.begin(9600);
//  delay(1000);
//}
//
//void loop() {
//  if (digitalRead(15)) {
//    Serial.println("Button pressed...");
//    delay(200);
//    sendSMS();
//  }
//
//  if (sim800l.available()) {
//    Serial.write(sim800l.read());
//  }
//}
//
//void sendSMS() {
//  String message = "Hello World !";
//  Serial.println("Sending SMS...");
//  sim800l.print("AT+CMGF=1\r"); // sets the module to SMS mode
//  delay(100);
//  sim800l.print("AT+CMGS=\"" + phone_number + "\"\r");
//  delay(500);
//  sim800l.print(message);
//  delay(500);
//  sim800l.print((char)26);
//  delay(500);
//  Serial.println("Text Sent.");
//  delay(500);
//}
