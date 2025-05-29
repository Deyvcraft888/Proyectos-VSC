// C++ code
/*
P3 ESP32 Pulsador Conmutador
A- Diseñar el programa para que un ESP32 haga encender o apagar un led de tal forma que
funcione como un punto de luz simple que cambia el estado de encendido o apagado del led cada
vez que se acciona el único pulsador instalado
B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.
*/

//¡Recuerda cambiar el pin en arduino esp32!

//const byte led = 11;
const byte led = 13;
//const byte pulsador = 10;
const byte pulsador = 12;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pulsador, INPUT);
}

void loop()
{
  byte ESTADO = digitalRead(led); //Leo el estado del LED
  
  while(digitalRead(pulsador) == LOW){
 
  }
  digitalWrite(led, !ESTADO);
  while(digitalRead(pulsador) == HIGH){ // espera mientras pulsador este encendido
    delay(100);
  }
}