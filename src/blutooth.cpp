
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int ledPin =  25;

String message = "";
char incomingChar;
//String temperatureString = "";

// Timer: auxiliar variables
unsigned long previousMillis = 0;    // Stores last time temperature was published
const long interval = 10000;         // interval at which to publish sensor readings

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // Bluetooth device name
  SerialBT.begin("ESP32_Bluetooth");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
   if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  if (message =="led_on"){
    digitalWrite(ledPin, HIGH);
  }
  else if (message =="led_off"){
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}