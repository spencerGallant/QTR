#include <Wire.h>
#define SLAVE_ADDRESS 4

byte calibrationValues[16];

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
}

byte x = 1; //Master command to slave

void loop() {
  if (Serial.available()) {
    char c = Serial.read(); {
      Serial.print("Command: ");
      Serial.println(c);
      send_command_to_slave(c);
      get_data_from_slave(); //tell the slave to execute the command and return data to master
    }
  }
}

void send_command_to_slave(char a) {
  //Send a command to the slave
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(a);              // sends one byte
  Wire.endTransmission();    // stop transmitting
}

void get_data_from_slave() {
  //    byte i;
  //    byte j;
  Wire.requestFrom(SLAVE_ADDRESS, 16);    // request 2 bytes from slave device #4
  //    while (Wire.available()) {  // slave may send less than requested
  //      i = Wire.read();
  //      j = Wire.read();
  //    }
  //    int integer = word(i, j);
  for (int i = 0; i < 16; i++) {
    calibrationValues[i] = Wire.read();  //alternatively:  Serial.println(word(i,j));
    Serial.println(calibrationValues[i]);
  }
  
}

