//C++

/*
 P6 ESP32 Jugador rápido
1)
A- Diseñar el programa para que un ESP32 realice el control de un concurso. El funcionamiento
será el siguiente:
El sistema está pensado para un concurso de trés concursantes y un moderador.
A cada concursante se le asigna un aviso luminoso (led) y un pulsador.
Al moderador se le asignan dos pulsadores un pulsador de activación y desactivación Pact y y un
pulsador de respuesta correcta Pcorrect, además de una luminaria de activación (led) Lact
El funcionamiento es el siguiente.
El moderador activa un turno de pregunta pulsando Pact entonces el primer concursante que cree
saber la respuesta pulsa su pulsador, a partir de ahí se enciende el led correspondiente a ese
concursante y la pulsación de los demás concursantes no tendrá ningún efecto. Después cuando el
moderador pulse de nuevo el botón de finalización Pact se apagará el led de concursante que estaba
encendido. Y el sistema esperará a que el moderador vuelva a pulsar de nuevo Pact para repetir otra
secuencia. Una vez que se enciende el led de algún concursante si el moderador pulsa Pcorrect se
considera respuesta correcta
Lact se activará al pulsar Pact originando activación y se desactivará al pulsar Pact originando
deactivación.

B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.

*/

//RECUERDA CAMBIAR LOS PINES

//const byte LEDS[5] = {2,3, 4, 5, 6};
const byte LEDS[5] = {2,3, 4, 5, 6};  
//Tinkercad -- POSICION: LED Verde = 0, LED Blanca = 1, LED Azul = 2, LED Roja = 3, LED Amarillo = 4
//const byte puls[3] = {4, 5, 6} ; //Pines ESP32
const byte pulsMOD[2] = {7, 8}; 
//Thinkercad -- POSICION PULSMODERADOR : PACT = 0, PCORRECT = 1
const byte pulsCONC[3] = {9, 10, 11} ; 
//Tinkercad -- POSICION : CONCURSANTE 1 = 0, CONCURSANTE 2 = 1, CONCURSANTE 3 = 2 


//---------------------------------------//
bool pulsadorOnOff = false;
bool estadoLED = false;
//------------------------------------------//
unsigned long ultimoMensaje = 0;
unsigned long intervalo = 1500;


void setup(){
  Serial.begin(9600);
  for(int ledsR = 0;ledsR < 5;ledsR++){
    pinMode(LEDS[ledsR], OUTPUT);
  }
  for(int MOD = 0;MOD < 2;MOD++){
    pinMode(pulsMOD[MOD], INPUT);
  }
    for(int CONC = 0;CONC < 3;CONC++){
    pinMode(pulsCONC[CONC], INPUT);
  }
}

void pulsMODOFF(){
  unsigned long ahora = millis(); //intervalo que actualiza

  while(pulsadorOnOff == false){
      
    //En Un intervalo envía un mensaje
    if (ahora - ultimoMensaje >= intervalo) {
      Serial.println("> Pulsadores Desactivados....");
      ultimoMensaje = ahora;
    }
    //Apaga todas las LEDS
    for(int apagarL = 0;apagarL <5;apagarL++){
      digitalWrite(LEDS[apagarL], LOW);
    }

    //Sal del while
    if(digitalRead(pulsMOD[0])){
      Serial.println("Activando Concurso..");
      delay(500);
      pulsadorOnOff = true;
      return;
    } //if
  } //while
}

void pulsCONC123() {
  int concursanteActivo = -1;
  bool respuestaRegistrada = false;

  while (true) {
    // Solo aceptar al primero que pulsa
    if (concursanteActivo == -1) {
      if (digitalRead(pulsCONC[0])) {
        concursanteActivo = 0;
        digitalWrite(LEDS[2], HIGH); // Azul
        Serial.println("Concursante 1 ha pulsado.");
      } else if (digitalRead(pulsCONC[1])) {
        concursanteActivo = 1;
        digitalWrite(LEDS[3], HIGH); // Roja
        Serial.println("Concursante 2 ha pulsado.");
      } else if (digitalRead(pulsCONC[2])) {
        concursanteActivo = 2;
        digitalWrite(LEDS[4], HIGH); // Amarilla
        Serial.println("Concursante 3 ha pulsado.");
      }
    } else {
      // Ya hay concursante activo
      if (!respuestaRegistrada && digitalRead(pulsMOD[1])) {
        // Switch para identificar quién fue y dar feedback
        switch (concursanteActivo) {
          case 0:
            Serial.println("✅ Concursante 1 ha respondido correctamente.");
            break;
          case 1:
            Serial.println("✅ Concursante 2 ha respondido correctamente.");
            break;
          case 2:
            Serial.println("✅ Concursante 3 ha respondido correctamente.");
            break;
        }
        digitalWrite(LEDS[0], HIGH); // Verde = Respuesta correcta
        respuestaRegistrada = true;
      }

      // Salida del modo concurso si el moderador pulsa Pact
      if (digitalRead(pulsMOD[0])) {
        Serial.println("🔴 Finalizando ronda...");
        delay(300); // Debounce
        return;
      }
    }
  }
}


void loop(){
  unsigned long ahora = millis(); //intervalo que actualiza

    //Envia un mensaje en un intervalo
    if (ahora - ultimoMensaje >= intervalo) {
      Serial.println("> Entrando en el Loop");
      ultimoMensaje = ahora;
    }
  // Condiciona si 1. Desactivamos Pact 2.  
  if(pulsadorOnOff == false ){
    Serial.println("> Entramos en Anuncios...");
    pulsMODOFF();
    return;
  } else {

    if(digitalRead(pulsMOD[0])){
    digitalWrite(LEDS[1], HIGH);
    pulsadorOnOff = !pulsadorOnOff;
    delay(10);
    } else if(digitalRead(pulsCONC[0]) || digitalRead(pulsCONC[1]) || digitalRead(pulsCONC[2])){
      Serial.println("> Comienza el Concurso...");
      pulsCONC123();
      return;
    }
  }
}