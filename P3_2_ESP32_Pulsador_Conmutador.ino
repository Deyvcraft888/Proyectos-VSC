// C++ code
/*
P3 ESP32 Pulsador Conmutador
A- Diseñar el programa para que un ESP32 haga encender o apagar un led de tal forma que
funcione como un punto de luz simple que cambia el estado de encendido o apagado del led cada
vez que se acciona el único pulsador instalado
B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.

2 Realizar el programa empleando solo if()
*/

//¡Recuerda cambiar el pin en arduino esp32!
const byte led = 13
const byte pulsador = 14;

bool estadoLed = false;
bool estadoAnterior = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pulsador, INPUT);
  digitalWrite(led, estadoLed);
}

void loop() {
  bool estadoActual = digitalRead(pulsador);

  // Detectar flanco de subida (cuando se presiona el botón)
  if (estadoActual == HIGH && estadoAnterior == LOW) {
    estadoLed = !estadoLed; // Cambia el estado del LED
    digitalWrite(led, estadoLed);
    delay(50); // antirrebote cavernícola
  }

  estadoAnterior = estadoActual;
}