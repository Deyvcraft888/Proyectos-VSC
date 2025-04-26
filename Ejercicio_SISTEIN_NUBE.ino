// code

/*
 P5 ESP32 Punto de luz conmutado
con tres pulsadores SerialPort
1)
A- Diseñar el programa para que un ESP32 haga encender o apagar un led verde de tal forma que
funcione como un punto de luz conmutado con trés pulsadores. Además otro led rojo se encenderá
cuando el verde se apague y se apagará cuando el verde se encienda.
Además cuando el led verde esté apagado pondrá por el puerto serie Led Verde Apagado y cuando
esté encendido pondrá por el puerto serie Led Verde Encendido

2)
A- Diseñar el programa para que un ESP32 haga encender o apagar un led verde de tal forma que
funcione como un punto de luz conmutado con trés pulsadores. Además otro led rojo se encenderá
cuando el verde se apague y se apagará cuando el verde se encienda.
Además cuando el led verde esté apagado pondrá por el puerto serie Led Verde Apagado x veces
encendido y cuando esté encendido pondrá por el puerto serie Led Verde Encendido x veces
encendido (siendo x el número de veces que se encendió el led verde desde que se inicia el ESP32,
pudiendo retornar el valor de x a 0 cuando se pulse un cuarto pulsador.

*/

//RECUERDA CAMBIAR LOS PINES

const byte ledVerde = 27; //27 ESP32
const byte ledRoja = 26; //26 ESP32
//const byte puls[3] = {4, 5, 6} ; //Pines thinkercad
const byte puls[3] = {13, 14, 15} ; //Pines esp32
bool estadoVerde = false;
byte repeticiones = 0;

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

//Sumamos una repeticion para la siguiente secuencia
    byte repeticiones = repeticiones + 1;

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
    Serial.print(estadoVerde ? "Encendido" : "Apagado");
Serial.println(repeticiones);
    Serial.println(" veces");
    Serial.print("LED Rojo: ");
    Serial.print(!estadoVerde ? "Encendido" : "Apagado");
Serial.println(repeticiones);
    Serial.println(" veces");
    Serial.println("------------------------------------------");

    // Esperar hasta que se suelten todos los pulsadores (para evitar rebotes)
    while (digitalRead(puls[0]) || digitalRead(puls[1]) || digitalRead(puls[2])) {
      delay(3000);  // Pequeño delay para estabilidad
    }
    
    delay(1000);  // Pequeño delay para evitar rebotes
  }
}