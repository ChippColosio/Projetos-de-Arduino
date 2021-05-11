#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <HCSR04.h>
 
#define pin1 D4 //Pino responsavel pelo acionamento da bomba
#define pin2 D3 //Luz Verde
#define pin3 D8 //Luz Vermelha
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //Ativação do Infra
const int trigPin = D5; //Trigger Ultra
const int echoPin = D6; //Echo Ultra

double temp_amb; //temperatura ambiente
double temp_obj; //temperatura objeto
double calibration = 2.36; // calibração do infra

int resval = 0; // inicialização
int respin = A0; // leitura serial pra testes

long duration; //duração pulso
int distance; // medidor de distancia
 
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
  Blynk.begin(auth, ssid, pass); //Inicialização blynk
  
  Serial.println("Temperature Sensor MLX90614"); // teste via serial do infra

  
}
 
void loop(){
 
  Blynk.run(); //roda o blynk
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
  

  temp_amb = mlx.readAmbientTempC(); // le a temperatura ambiente em celsius
  temp_obj = mlx.readObjectTempC(); // le a temperatura no sensor infra do objeto
  resval = analogRead(respin);  //leitura do valor de reservatorio de alcool
 
 
  //Serial Monitor
  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj);
  
  
  Serial.println("---"); //leitura do sensor do reservatorio de alcool e comparações para teste na serial
  if (resval<=100){ Serial.println("Water Level: Empty"); } else if (resval>100 && resval<=300){ Serial.println("Water Level: Low"); } else if (resval>300 && resval<=330){ Serial.println("Water Level: Medium"); } else if (resval>330){ 
    Serial.println("Water Level: High");
  
  }
  if (temp_obj + calibration >= 36.600) { //logica de leitura do infra vermelho
  digitalWrite(pin3, HIGH);  
  digitalWrite(pin2, LOW);
  }else{
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,LOW);
  }
  
  Blynk.virtualWrite(V1, temp_amb); //blynk mostrando a temperatura ambiente
  Blynk.virtualWrite(V2, (temp_obj + calibration)); //blynk mostrando a temperatura lida pelo objeto
  
  if (distance <= 12) (digitalWrite( pin1, LOW)); //acionamento da bomba por um segundo enquanto tiver proximo do sensor
 
 
 delay(1000);
 digitalWrite( pin1, HIGH);
 delay(1000);

 


}  
