//Control de Cargas con Arduino y Relé SPDT

int entradas[2] = {2,3};
int salidasLED[6] = {4,5,6,7,8,9};
int salidaMotor = 10;
int salidaBombilla = 11;


void setup()
{
  Serial.begin(9600);
  pinMode(entradas[2], INPUT);
  pinMode(salidasLED[6], OUTPUT);
  pinMode(salidaBombilla, OUTPUT);
  pinMode(salidaMotor, OUTPUT);
  
}

void bombillaON(){
  Serial.println(">Enciende una entrada");
  while(digitalRead(entradas[0]) == LOW &&  digitalRead(entradas[1]) == LOW){
      digitalWrite(salidaBombilla, HIGH);
      Serial.println("Comprobando...");
      delay(1000);
      if(digitalRead(entradas[0]) == HIGH ||  digitalRead(entradas[1]) == HIGH){
        Serial.println(">...Recibido!");
        digitalWrite(salidaBombilla, LOW);
        delay(500);
        digitalWrite(salidaBombilla, HIGH);
        delay(500);
        digitalWrite(salidaBombilla, LOW);
        break;
      }
  }
}

void loop()
{
  int entradaLED = digitalRead(entradas[0]);
  int entradaMOTOR = digitalRead(entradas[1]);
  
  Serial.println("> Comienzo:");
  delay(2000);
  if(entradaLED == LOW && entradaMOTOR == LOW){
    bombillaON();
  }
  if(entradaLED == HIGH && entradaMOTOR == LOW){
    Serial.println("_____________");
    Serial.println("> Lucecitass!!");
    digitalWrite(salidaBombilla, LOW);
    digitalWrite(salidaMotor, LOW);
    for(int BRILLO = 0; BRILLO < 6;BRILLO++){
      digitalWrite(salidasLED[BRILLO], HIGH);
      delay(1000);
      digitalWrite(salidasLED[BRILLO], LOW);
    }
    for(int BRILLOdec = 6; BRILLOdec > 6;BRILLOdec--){
      digitalWrite(salidasLED[BRILLOdec], LOW);
      delay(1000);
      digitalWrite(salidasLED[BRILLOdec], HIGH);
    }
  }else if (entradaLED == LOW && entradaMOTOR == HIGH){
    Serial.println("_____________");
    Serial.println("> Que Frio fae");
    digitalWrite(salidasLED[6], LOW);
    digitalWrite(salidaBombilla, LOW);
    digitalWrite(salidaMotor, HIGH);
    delay(1000);
  }
}