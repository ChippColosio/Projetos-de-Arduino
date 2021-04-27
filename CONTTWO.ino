#include <TimerOne.h>

//Fernando Luiz Colosio - Contador com 2 displays de 7 segmentos, utilizando potenciometros com timers para controlar a frequencia numeros sucessores e frequencia de desligamento do display na transição de numeros.

int sensorPino1 = A0;
int sensorPino2 = A1;
int sensorValor1 = 0;
int sensorValor2 = 0;


void setup()
{
  for (int i = 0; i <= 13; i++)
    pinMode(i, OUTPUT); //Seta todos os pinos de 1 a 13 como saida
}
//A linha abaixo contem o vetor com os numeros de 0 a 9 no display de 7 segmentos
const int number[11] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};

void loop()
{ 
  
  Timer1.initialize(100000);

  for (int tens = 0; tens < 10; tens++)

  {
     
    display_tens(tens);
   
   
  }
   
   sensorValor1 = analogRead(sensorPino1); //Potenciometro 1 que le a velocidade que o contador sobe
   sensorValor2 = analogRead(sensorPino2); //Potenciometro 2 que le a frequencia que a tela apaga 
   
}

void display_tens(const int tens)
{
  int pin1, a, ones;     
  //aqui é usado o pin1 para lidar com o primeiro digito no display de 7 segmentos na interação com os decimos

  for (pin1 = 0, a = 0; pin1 < 7; pin1++, a++)
  {
    digitalWrite(pin1, bitRead(number[tens], a));
    Timer1.detachInterrupt();
  }
  for (ones = 0; ones < 10; ones++)
  {
    display_ones(ones);
    delay(sensorValor1); 
    Timer1.attachInterrupt(lightsout);
    //Valor lido do potenciometro para o contador
  }
  
}

void display_ones(const int x)
{ int pin2, b;             
//pin2 é utilizado para lidar com os pinos do segundo display que são as casas unitarias

  for (pin2 = 7, b = 0; pin2 <= 13; pin2++, b++)
  {
    digitalWrite(pin2, bitRead(number[x], b));
    

  }

}

void lightsout(){
  for (int i = 0; i <= 13; i++)
    digitalWrite(i,HIGH);
    delay(sensorValor2+200); // valor lido do potenciometro para a frequencia que o display apaga
    Timer1.initialize(100000);
   
}
