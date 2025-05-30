P4_ESP32_Punto_de_luz_conmutadoconst byte ledVerde = 2;
const byte ledRoja = 3;
const byte puls[3] = {13, 12, 14}; // Pines pulsadores

bool estadoVerde = false;
bool estadoAnterior[3] = {false, false, false}; // Guarda estados anteriores

void setup() {
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRoja, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(puls[i], INPUT);
  }

  digitalWrite(ledVerde, estadoVerde);
  digitalWrite(ledRoja, !estadoVerde);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    bool estadoActual = digitalRead(puls[i]);

    // Detectar flanco ascendente
    if (estadoActual == HIGH && estadoAnterior[i] == LOW) {
      estadoVerde = !estadoVerde; // Invertir LED verde
      digitalWrite(ledVerde, estadoVerde);
      digitalWrite(ledRoja, !estadoVerde);

      Serial.print("LED Verde: ");
      Serial.println(estadoVerde ? "Encendido" : "Apagado");
      Serial.print("LED Rojo: ");
      Serial.println(!estadoVerde ? "Encendido" : "Apagado");
      Serial.println("------------------------------------------");

      delay(50); // Antirrebote cavernícola
    }

    estadoAnterior[i] = estadoActual; // Actualizar estado
  }
}
