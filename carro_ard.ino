/* Carro com sensor ultrassonico Fernando Luiz Colosio 161151172
 Disciplina de microcontroladores Unipampa
 Professor Julio Saraçol
 */

#include <Ultrasonic.h>

// Define os pinos de utilização do Driver L298.
const int motorA1  = 9;    // preto
const int motorA2  = 12;    // amarelo.
const int motorB1  = 11;   // roxo.
const int motorB2  = 10;   // verde.

Ultrasonic ultrasonic(7,8);

int vSpeed = 200;   // Define velocidade padrão 0 < x < 255.
//int vSpeed2 = 80;

float distancia;

void setup() {
  // Inicializa as portas como entrada e saída.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  delay(5000);  // tempo pra colocar o carro na posição
}

void calculaDistancia(){
  long microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM);
  delay(50);
}


void loop() {

 calculaDistancia();
  
    if (distancia < 20) {  // anda para trás por 1 segundo
    analogWrite(motorB1, 0);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, vSpeed);
    delay(500);
//  olha para a esquerda
    analogWrite(motorB1, 0);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB2, vSpeed);
    delay(700);
    
// olha para a direita
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
    delay(1500);
  }
  else {
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB2, 0);
  }
}
