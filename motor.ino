#include <SoftwareSerial.h>

char state;
int motorPin1 = 8;  //pin8----1N4
int motorPin2 = 9;  //pin8----1N3
int motorPin3 = 10; //pin8----1N2
int motorPin4 = 11; //pin8----1N1

//Creamos un metodo para girar en sentido anti horario
void gira_antihorario(int delayTime)
{
digitalWrite(motorPin1, HIGH); // Los pines se activan en secuencia
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, LOW);
delay(delayTime);
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin4, LOW);
delay(delayTime);
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin4, HIGH);
delay(delayTime);
digitalWrite(motorPin1, HIGH);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, HIGH);
delay(delayTime);  
}
//Definimos la función que provocará el giro horario
void gira_horario(int delayTime)
{
digitalWrite(motorPin1, HIGH);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, HIGH);
delay(delayTime); 
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin4, HIGH);
delay(delayTime);
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin4, LOW);
delay(delayTime);
digitalWrite(motorPin1, HIGH); // Los pines se activan en secuencia
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, LOW);
delay(delayTime);
}

void setup() { 
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT); // Configuración de los PINes como salida digital
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

}

void loop() { 
  char caracter;
  String comando;
      while (Serial.available() >0){
        caracter = Serial.read();
        comando =String(comando + caracter);
        Serial.println("GIRO MOTOR: "+comando+" ");
        if (comando.equals("I")){
          //Serial.println("IZQUIERDA");
           for (int i=0; i <= 1; i++){
            gira_antihorario(3);
       } 
     } 
    else if (comando.equals("D")){
      //Serial.println("DERECHA");
           for (int i=0; i <= 1; i++){
                gira_horario(3); 
             } 
      }
        comando="";
        caracter= ' ';
        delay(100);
    }
  }
