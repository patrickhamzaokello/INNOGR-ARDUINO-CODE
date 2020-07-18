#include <WaziDev.h>
#include <DHT.h>
#define DHTPIN 2        // what pin on the arduino is the DHT data line connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
// new WaziDev with node address = 8
WaziDev wazidev("INNOGRDEVICEPK", 8);

int yellowled = 4;
int ledon = 6;

int wlvalue = 0;  // holds the value water level
int wlpin = A5; // sensor pin used water level

int moisturesensorval = 0;
int moisturesensor =  A4; //moisture sensor

int lightpin = A2;
int lightvalue = 0; // variable to hold light  intensity

void setup() {
  wazidev.setup();

  pinMode(ledon, OUTPUT);
  digitalWrite(ledon, HIGH);

  //  pinMode(3, OUTPUT);
  //  digitalWrite(3, HIGH);

  pinMode(yellowled, OUTPUT);
  
  dht.begin();
  delay(2000);
  
  Serial.begin(38400);
}

void loop() {

  //water level
  wlvalue = analogRead(wlpin); //Read data from analog pin and store it to resval variable
  moisturesensorval = analogRead(moisturesensor);
  lightvalue = analogRead(lightpin);

  if (lightvalue < 40){
    digitalWrite(yellowled, HIGH);
  }
  else{
    digitalWrite(yellowled, LOW);
  }

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("Tem: ");
  Serial.print(t);
  Serial.print(" hum: ");
  Serial.print(h);
  Serial.print(" WL: ");
  Serial.print(wlvalue);
  Serial.print(" WM: ");
  Serial.print(moisturesensorval);
  Serial.print(" LDR: ");
  Serial.println(lightvalue);


  WaziDev::SensorVal fields[5] = {{"InnogrTC", t}, {"InnogrHUM", h},{"InnogrLI", lightvalue}, {"InnogrWM", moisturesensorval},{"InnogrWL",wlvalue}};
  //Send temperature as sensor "TC"
  wazidev.sendSensorValues(fields, 5);

  Serial.flush();
  delay(3000);

}
