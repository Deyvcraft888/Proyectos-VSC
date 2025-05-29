// C++ code
/*
A- Diseñar el programa para que un ESP32 controle un semáforo de la siguiente manera.
 El semáforo seguirá de forma repetitiva la siguiente secuencia
Luz verde encendida 10 segundos.
Luz ambar alumbra de forma intermitente generando cinco impulsos de On/Off, en los que
cada On dura 1 segundo y cada Off dura 1 segundo.
Luz roja encendida10 segundos.
B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.
*/

//¡Recuerda cambiarlo!Array de leds de salida en el esp32
const byte ledVerde = 2; 
const byte ledAmbar = 3; 
const byte ledRoja = 4;

void setup()
{
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmbar, OUTPUT);
  pinMode(ledRoja, OUTPUT);
}

void loop()
{
  digitalWrite(ledVerde, HIGH);
  delay(10000);
  digitalWrite(ledVerde, LOW);
  for(int brillo = 0; brillo < 5;brillo++){ //Repite 5 veces ambar
    digitalWrite(ledAmbar, HIGH);
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(ledAmbar, LOW);
    delay(1000); // Wait for 1000 millisecond(s)
  }
  digitalWrite(ledRoja, HIGH);
  delay(10000);
  digitalWrite(ledRoja, LOW);
}