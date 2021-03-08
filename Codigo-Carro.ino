/*---------------------------------------------------------------
Com as ligações feitas dos motores com a ponte H, teremos:
Vendo o chassi com uma vista superior (com a frente do carro para cima), temos o 
motor A no lado direito  e   o motor B no lado esquerdo.

         frente    ré                       frente     ré
motorA1    1       0              motorB1      0       1
motorA2    0       1              motorB2      1       0

------------------------------------------------------------------*/


#include "SoftwareSerial.h"
#include <Ultrasonic.h>

char caracter = 'S';  
//começar parado, já que vai começar no modo manual
SoftwareSerial blu(12, 13); //TX,RX (do bluetooth)

const int motorA1 = 3,
          motorA2 = 5,
          motorB1 = 6,
          motorB2 = 9;
int vel = 150;
int modo = 0;      //começar no modo manual

long microsec = 0;
float distanciaCM = 0;

Ultrasonic ultra(7, 8);  
//o 7 é o trigger. O 8 é o echo

void modoAutomatico();
void modoManual();

void andar_frente();
void andar_atras();
void andar_direita();
void andar_esquerda();
void parar();

void setup() {

  blu.begin(9600);
  pinMode(motorA1, OUTPUT); 
  pinMode(motorA2, OUTPUT); 
  pinMode(motorB1, OUTPUT); 
  pinMode(motorB2, OUTPUT); 

}

void loop() {
  
  if (blu.available() > 0) {
  delay(10);//delay para deixar estável
  caracter = blu.read();
  }
  
 if(modo == 0){      
 //quando modo==0, modo manual. 
 //Quando modo==1, automatico
  
  if(caracter == 'W') modo=1;
  
  modoManual();
 
  delay(100);  //quem sabe...dá uma estabilidade
 }
 else {
  modoAutomatico();
  
  if(caracter =='w'){ 
    modo=0;
    parar();
  }
  
  delay(100);  //quem sabe...dá uma estabilidade
 }
}

void andar_frente(){
    analogWrite(motorA1, vel);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vel);
}
  
void andar_atras(){
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vel);
    analogWrite(motorB1, vel);
    analogWrite(motorB2, 0);
}
  
void andar_direita(){
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vel);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vel);
}
  
void andar_esquerda(){
    analogWrite(motorA1, vel);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vel);
    analogWrite(motorB2, 0);
}
  
void parar(){
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
}



void modoManual(){
  if (caracter == 'F') {
    
    microsec = ultra.timing();   //lendo o sensor
    delay(10);          //para estabilidade
    distanciaCM = ultra.convert(microsec, Ultrasonic::CM);
    
    if (distanciaCM >30) andar_frente();              
    else parar();
  }
  if (caracter == 'B')  andar_atras();
  if (caracter == 'R')  andar_direita(); 
  if (caracter == 'L')  andar_esquerda(); 
  if (caracter == 'S')  parar();  
  
  
  if(caracter == '1') vel = 160; 
  if(caracter == '2') vel = 170;
  if(caracter == '3') vel = 180;
  if(caracter == '4') vel = 190;
  if(caracter == '5') vel = 200;
  if(caracter == '6') vel = 210;
  if(caracter == '7') vel = 220;
  if(caracter == '8') vel = 230;
  if(caracter == '9') vel = 240;
  if(caracter == 'q') vel = 250;
}


void modoAutomatico(){
  vel=170;
  
  microsec = ultra.timing();  //lendo o sensor
  delay(10);        //para estabilidade
  distanciaCM = ultra.convert(microsec, Ultrasonic::CM);
  
  if (distanciaCM >30) andar_frente();
  else {
    parar(); delay(500);
    andar_atras(); delay(800);
    parar(); delay(500);
    andar_direita(); delay(400);
    parar(); delay(500);
  }
  
}
