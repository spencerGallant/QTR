#include <Wire.h>
#define SLAVE_ADDRESS 4

char master_command = '0';
int data = 1023;
byte integer[2];

void setup()
{
  Wire.begin(SLAVE_ADDRESS);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(sendData);
  Serial.begin(115200);           // start serial for output
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while (Wire.available()) // loop through all but the last
  {
    master_command = Wire.read(); // receive byte as a character
  }
  //  Serial.println(master_command);       // print the integer
}

void sendData() {
  if (master_command == '1') {
    integer[0] = highByte(data);
    integer[1] = lowByte(data);
    Wire.write(integer, 2);
  }
  else {
    integer[0] = highByte(0);
    integer[1] = lowByte(0);
    Wire.write(integer, 2);
  }
}

