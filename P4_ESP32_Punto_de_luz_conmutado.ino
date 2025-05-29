//C++

/*
P4 ESP32 Punto de luz conmutado
con tres pulsadores
A- Diseñar el programa para que un ESP32 haga encender o apagar un led verde de tal forma que
funcione como un punto de luz conmutado con trés pulsadores. Además otro led rojo se encenderá
cuando el verde se apague y se apagará cuando el verde se encienda.
B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.
*/

//RECUERDA CAMBIAR LOS PINES

const byte ledVerde = 2; //27
const byte ledRoja = 3; //26
//const byte puls[3] = {4, 5, 6} ; //Pines thinkercad
const byte puls[3] = {13, 12, 14} ; //Pines esp32
bool estadoVerde = false;


void setup(){
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRoja, OUTPUT);
  for(int repet = 0;repet < 3;repet++){
    pinMode(puls[repet], INPUT);
  }
}

void loop(){

  bool pulsadores[3] = {digitalRead(puls[0]), digitalRead(puls[1]), digitalRead(puls[2])};

  // Si se presiona cualquier pulsador
  if (pulsadores[0] || pulsadores[1] || pulsadores[2]) {
    // Invertir el estado del LED verde
    estadoVerde = !estadoVerde;
    // Leer estado actual del LED verde

    // Invertir el estado del LED verde
    digitalWrite(ledVerde, !estadoVerde);

    // El LED rojo toma el estado opuesto al LED verde
    digitalWrite(ledRoja, estadoVerde);

    // Mostrar en Serial Monitor
    Serial.print("LED Verde: ");
    Serial.println(estadoVerde ? "Encendido" : "Apagado");
    Serial.print("LED Rojo: ");
    Serial.println(!estadoVerde ? "Encendido" : "Apagado");
    Serial.println("------------------------------------------");

    // Esperar hasta que se suelten todos los pulsadores (para evitar rebotes)
    while (digitalRead(puls[0]) || digitalRead(puls[1]) || digitalRead(puls[2])) {
      delay(3000);  // Pequeño delay para estabilidad
    }

    delay(1000);  // Pequeño delay para evitar rebotes
  }
}