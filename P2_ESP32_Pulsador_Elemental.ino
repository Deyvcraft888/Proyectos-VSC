// C++ code
/*
P2 ESP32 Pulsador Elemental
A- Diseñar el programa para que un ESP32 haga encender un led mientras se pulsa el pulsador, si se
suelta el pulsador se apagará.
B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.
*/

//¡Recuerda cambiar el pin en arduino esp32!
const byte led = 11;
const byte pulsador = 10;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pulsador, INPUT);
}

void loop()
{
  byte entrada = digitalRead(pulsador);
  
  if(entrada == HIGH){
    digitalWrite(led, HIGH);
    delay(2000);
  } else {
    digitalWrite(led, LOW);
  }
}