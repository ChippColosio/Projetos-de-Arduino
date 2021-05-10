#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <HCSR04.h>
 
#define pin1 D4
#define pin2 D3
#define pin3 D8
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int trigPin = D5; 
const int echoPin = D6; 

double temp_amb;
double temp_obj;
double calibration = 2.36;

int resval = 0;
int respin = A0; // sensor pin used

long duration;
int distance;
 
char auth[] = "WNJST-DTf9ntZEL_8P70Vobc1GEEjo6I";    // You should get Auth Token in the Blynk App.
char ssid[] = "NewLife_PANDORA";                       // Your WiFi credentials.
char pass[] = "12345678";


 
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode (pin1, OUTPUT);
  pinMode (pin2, OUTPUT);
  pinMode (pin3, OUTPUT);
  
  mlx.begin();         //Initialize MLX90614
  Blynk.begin(auth, ssid, pass);
  
  Serial.println("Temperature Sensor MLX90614");

 // delay(2500);
  
}
 
void loop(){
 
  Blynk.run();
  // Clears the trigPin
  
  //digitalWrite(pin1, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  //delay(500);
  

  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  resval = analogRead(respin);
  //Serial Monitor
  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj);
  
  
  Serial.println("---");
  if (resval<=100){ Serial.println("Water Level: Empty"); } else if (resval>100 && resval<=300){ Serial.println("Water Level: Low"); } else if (resval>300 && resval<=330){ Serial.println("Water Level: Medium"); } else if (resval>330){ 
    Serial.println("Water Level: High");
  
  }
  if (temp_obj + calibration >= 36.600) {
  digitalWrite(pin3, HIGH);  
  digitalWrite(pin2, LOW);
  }else{
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,LOW);
  }
  
  Blynk.virtualWrite(V1, temp_amb);
  Blynk.virtualWrite(V2, (temp_obj + calibration));
  
  if (distance <= 12) (digitalWrite( pin1, LOW));
 
 
 delay(1000);
 digitalWrite( pin1, HIGH);
 delay(1000);

 


}  
