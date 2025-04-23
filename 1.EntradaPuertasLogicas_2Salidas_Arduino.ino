// C++ code
//
const int ledIN = 2;
const int motorIN = 3;
const int ledOUTA = 4;
const int ledOUTB = 5;
const int motorOUT =6;
int estado = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(ledIN, INPUT); // PIN DE ENTRADA PARA LEDS
  pinMode(motorIN, INPUT); // PIN DE ENTRADA PARA MOTOR CC
  pinMode(ledOUTA, OUTPUT); // PIN SALIDA LEDAZUL
  pinMode(ledOUTB, OUTPUT); // PIN SALIDA 
  pinMode(motorOUT, OUTPUT);
}
void entradasbajas(){
    while(digitalRead(ledIN) == estado && digitalRead(motorIN) == estado){
    Serial.println("Entradas Bajadas");
    Serial.println("_________________");
    digitalWrite(ledOUTA, !estado);
    delay(5000);
    digitalWrite(ledOUTA, estado);
    delay(500);
    digitalWrite(ledOUTA, !estado);
    delay(2000);
      if(digitalRead(ledIN) != estado || digitalRead(motorIN) == !estado){
        Serial.println("> Entrada Leida...");
        delay(1000);
        return;
    }
  }
}
void loop()
{
  int INLED = digitalRead(ledIN);
  int INMOTOR = digitalRead(motorIN);

  if(INLED == !estado && INMOTOR == !estado){
    Serial.println("Entrada doble!!!");
  }else if(INLED == estado && INMOTOR == estado){
    entradasbajas();
  }else if(INLED == !estado && INMOTOR == estado){
    digitalWrite(motorIN, estado);
    for(int Brillo = 0; Brillo < 5;Brillo++){
      digitalWrite(ledOUTA, !estado);
      digitalWrite(ledOUTB, estado);
      delay(1000);
      digitalWrite(ledOUTA, estado);
      digitalWrite(ledOUTB, !estado);
      delay(1000);
      digitalWrite(ledOUTA, !estado);
      digitalWrite(ledOUTB, estado);
    }
  }else if(INLED == estado && INMOTOR == !estado){
    digitalWrite(ledOUTA && ledOUTB, estado);
    digitalWrite(motorOUT, !estado);
    delay(1000);
    Serial.println("Mensaje enviado!");
  }
}