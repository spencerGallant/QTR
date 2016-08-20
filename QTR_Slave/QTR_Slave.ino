//type in 1 on master and will calibrate
#include <Wire.h>
#include <QTRSensors.h>

#define SLAVE_ADDRESS 4
#define NUM_SENSORS             4  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // emitter is controlled by digital pin 2

char master_command = '0';
int data = 1023;
byte integer[2];

  QTRSensorsAnalog qtra((unsigned char[]) {
    0, 1, 2, 3
  },
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup() {
  Wire.begin(SLAVE_ADDRESS);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(sendData);
  Serial.begin(115200);           // start serial for output

  pinMode(6, OUTPUT);
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
    callibrate();
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

void callibrate() {
  digitalWrite(6, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 500; i++) { // make the calibration take about 10 seconds
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(6, LOW);     // turn off Arduino's LED to indicate we are through with calibration

}

