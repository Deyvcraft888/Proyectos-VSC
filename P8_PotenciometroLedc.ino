/*
P8 Potenciometro Ledc
1)
A- Realizar con un ESP32 la automatización siguiente:
Regulación iluminación led mediante potenciómetro
Regulación iluminación led mediante potenciómetro
Ademas se indica por puerto serie el porcentaje de 0 a 100%
A mayores del led regulado se encenderán:
3 leds más si regulación > 90%
2 leds más si regulación > 60%
1 leds más si regulación > 30%
0 leds si regulación <= 30%
Además un led se iluminará proporcionalmente a la posición del potenciometro
Por el puerto Serie se indicará la posición del potenciometro con el siguiente texto:
Potenciometro al X % (Donde x es un valor del 0 al 100)
Solamente escribirá por el puerto Serial cuando se cambia la posición del potenciometro y nunca
con un intervalo inferior a 1 segundo.
B- Realizar el montaje en un simulador , introducir el código y simular comprobando el correcto
funcionamiento.

*/

const byte Poten1 = 32;
const byte ledsPin[3] = {13, 14, 27};

int ultimoPorcentaje = -1;
unsigned long ultimoTiempo = 0;

void setup(){
    Serial.begin(9600);
    for(int x = 0; x < 3; x++){
        pinMode(ledsPin[x], OUTPUT);
    }
}

void loop(){
  int  lecturaP = analogRead(Poten1);
  int  conversionP = (lecturaP * 100) / 1023;
  //------------------------------------------------------------------//
  // Mapeamos el valor que salga cada repeticion del Potenciometro y la pasamos por el comando constrain que crea unos limites ante map
  // para evitar ruidos y mala colocación del Potenciometro
  int  porcentaje = map(lecturaP, 0, 1023, 0, 100);
  int  porcentajeLimitado = constrain(porcentaje, 0, 100);

  // Solo imprimir si el valor cambió y pasó más de 1 segundo
  if (abs(porcentajeLimitado - ultimoPorcentaje) > 1 && millis() - ultimoTiempo >= 1000) {
      Serial.print("Porcentaje Mapeado: ");
      Serial.print(porcentaje);
      Serial.println("%");
      Serial.println("------------------------------------");
      Serial.print("Porcentaje Limitado: ");
      Serial.print(porcentajeLimitado);
      Serial.println("%");
    ultimoPorcentaje = porcentajeLimitado;
    ultimoTiempo = millis();
  }

  // Apagar todos antes de encender
  for(int i = 0; i < 3; i++){
    digitalWrite(ledsPin[i], LOW);
  }

  if(porcentajeLimitado > 0 && porcentajeLimitado <= 30){
    for(int brilloL = 0; brilloL < 3; brilloL++){
        digitalWrite(ledsPin[brilloL], LOW);
    }
  }else if(porcentajeLimitado > 30 && porcentajeLimitado < 60){
    digitalWrite(ledsPin[0], HIGH);
  }else if(porcentajeLimitado > 60 && porcentajeLimitado < 90){
    for(int a = 0; a < 2; a++){
    digitalWrite(ledsPin[a], HIGH);
    }
  }else if(porcentajeLimitado > 90 && porcentajeLimitado <= 100){
    for(int b = 0; b < 3; b++){
    digitalWrite(ledsPin[b], HIGH);
    }
  }
  delay(500);
}