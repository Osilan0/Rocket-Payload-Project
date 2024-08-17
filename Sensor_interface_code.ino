// GPS
#define GPSSerial Serial1
// Accelerometer
#include <Wire.h>                
#include "SparkFun_MMA8452Q.h"    

MMA8452Q accel;

// flex sensor
// declare variables
int sensorpin = A14;  // sensor pin
float flex;          // sensor readings
// Altimeter
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro;
int vib_slow; //hard to trigger
int vib_med;
int vib_fast; //easy to trigger


void setup() {
  // put your setup code here, to run once:
  // GPS

  Serial.begin(115200);
  while (!Serial) delay(10);
  GPSSerial.begin(115200);
  // initialize serial communication
  Serial.begin(9600);
  // Accelerometer
  Serial.begin(115200);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  // Altimeter
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Adafruit_MPL3115A2 test!");
  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }
  // use to set sea level pressure for current location this is needed for accurate altitude measurement STD SLP = 1013.26 hPa
  baro.setSeaPressure(1013.26);
  pinMode(25, INPUT);
  pinMode(26,INPUT);
  pinMode(27, INPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  // GPS
  if (Serial.available()) {
    char c = Serial.read();
    GPSSerial.write(c);
  }
  if (GPSSerial.available()) {
    char c = GPSSerial.read();
    Serial.write(c);
  }
  // flex sensor
  flex = analogRead(sensorpin);
  // print sensor value
  Serial.println(flex);
  // accelerometer
  if (accel.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    Serial.print(accel.getCalculatedX() , 3);
    Serial.print("\t");
    Serial.print(accel.getCalculatedY(), 3);
    Serial.print("\t");
    Serial.print(accel.getCalculatedZ(), 3);
    Serial.println();
  vib_fast= digitalRead(25);
  vib_med= digitalRead(26);
  vib_slow= digitalRead(27);


  }
  // altimeter
  float pressure = baro.getPressure();
  float altitude = baro.getAltitude();
  float temperature = baro.getTemperature();


  Serial.print("pressure = "); Serial.print(pressure); Serial.println(" hPa");
  Serial.print("altitude = "); Serial.print(altitude); Serial.println(" m");
  Serial.print("temperature = "); Serial.print(temperature); Serial.println(" C");


  Serial.print(vib_fast);
  Serial.print(vib_med);
  Serial.print(vib_slow);
  //Serial.print(vib_high);
  Serial.print("\n");
  //delay(100);
  Serial.println("-----------------");
}
