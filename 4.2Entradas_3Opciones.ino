// C++ code
//
byte entrada1 = 2; //ESP32 es 13
byte entrada2 = 3; //ESP32 es 12
byte salidaLEDS[6] = {4, 5, 6, 7, 8, 9};
//byte salidaLEDS[6] = {14, 27, 26, 25, 33, 32}; Entradas ESP32
String userInput;
byte numero;

void setup()
{
  Serial.begin(9600);
  pinMode(entrada1, INPUT);
  pinMode(entrada2, INPUT);
  for(int ledsalida = 0; ledsalida < 6;ledsalida++){
    pinMode(salidaLEDS[ledsalida], OUTPUT);
  }
}
void estadoBajado(){
  while(digitalRead(entrada1) == LOW && digitalRead(entrada2) == LOW ){
    digitalWrite(salidaLEDS[0], HIGH);
    delay(800);
    Serial.println("> Entradas Bajadas, sube alguna entrada");
    Serial.println("------------------------------------------");
    if(digitalRead(entrada1) != LOW && digitalRead(2) != LOW){
      digitalWrite(salidaLEDS[0], LOW);
      return;
    }
  }
}
void loop()
{
  Serial.println("> Void Loop...");
  if(digitalRead(entrada1) == LOW && digitalRead(entrada2) == LOW){
    estadoBajado();
    return;
  }else if(digitalRead(entrada1) == HIGH && digitalRead(entrada2) == HIGH){
    Serial.println("----------------------------");
    return;
  }else if(digitalRead(entrada1) == HIGH && digitalRead(entrada2) == LOW){
    Serial.println("> Cuantas Repeticiones deseas?");
    Serial.println("> Ponlo en cantidad numerica");
    
    while(true){
      if(Serial.available() > 0){
        userInput = Serial.readString(); // le la entrada como string
        userInput.trim(); // Quita espacios innecesarios
        
        numero = userInput.toInt(); //Convierte el dato en numero
        
        if(userInput.length() == 0 || numero == 0){
          Serial.println("Entrada Invalida");
        }
        if(numero == numero){
          Serial.println("Numero Ingreado:" + String(numero));
          for(int i = 0;i < numero;i++){
            digitalWrite(salidaLEDS[1], HIGH);
            digitalWrite(salidaLEDS[2], LOW);
            delay(500);
            digitalWrite(salidaLEDS[1], LOW);
            digitalWrite(salidaLEDS[2], HIGH);
            delay(500);
          } // for
          digitalWrite(salidaLEDS[2], LOW);
          break;
        } //if numero
      }//if serial available
    } //while
  } /*else if*/ else if(digitalRead(entrada1) == LOW && digitalRead(entrada2) == HIGH){
    
    //Desactivo las otras  LEDS del programa
    for (int ledsobrante = 0;ledsobrante < 5;ledsobrante++){
    digitalWrite(salidaLEDS[ledsobrante], LOW);
    }
    
    //Función del IF
    digitalWrite(salidaLEDS[3], HIGH);
    delay(10000);
    digitalWrite(salidaLEDS[3], LOW);
    
    for(int BRILLO = 0; BRILLO < 5;BRILLO++){
      digitalWrite(salidaLEDS[4], HIGH);
      delay(500);
      digitalWrite(salidaLEDS[4], LOW);
      delay(500);
    }//for
    digitalWrite(salidaLEDS[5], HIGH);
    delay(10000);
    digitalWrite(salidaLEDS[5], LOW);
  }/*else  if*/
}//loop