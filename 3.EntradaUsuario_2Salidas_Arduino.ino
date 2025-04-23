// C++ code
//
const int pinLEDS[5] = {2, 3, 4, 5, 6}; 
const int pinBombilla = 7;
String userInput;
String userYN;
String opciones = 
  "-------------------------------------\n"
  "----------___________----------------\n"
  "----------ARDUINO UNO----------------\n"
  "----------___________----------------\n"
  "------------------------------------\n"
  "-----------------------------\n"
  "________OPCIONES_____________\n"
  "\n"
  "1.LEDS SECUENCIALES\n"
  "2.ENCENDER BOMBILLA\n"
  "\n"
  "> Responde con 1 o 2:\n";

void setup(){
  Serial.begin(9600);
  pinMode(pinLEDS[5], OUTPUT);
  pinMode(pinBombilla, OUTPUT);
}

void menu(){
  Serial.println(opciones);
  respuestaUsuario();
}
//------------------------------------//------------------------------------------//
void procesoTerminado(){
  	userYN = ""; //Limpia el anterior SI/NO para uno nuevo
    Serial.println("> Proceso Terminado!\n");
    Serial.println("> Quieres volver a repetir el proceso?\n");
    Serial.println("> Responde con un SI/NO: \n");

// Condicional para reedirijir
  while(true){// Si hay datos en el buffer serial
    if (Serial.available() > 0) {  // Si hay datos en el buffer serial
         userYN = Serial.readString();  // Leer entrada del usuario
         userYN.trim();  // Elimina espacios y saltos de línea
      
       if (userYN.length() == 0) {  // Si el usuario solo presionó Enter
         
         Serial.println("> Responde con SI/NO\n");
         break;
            }
         if (userYN.equalsIgnoreCase("SI")) {  // Hace otra vez el codigo LEDS
            Serial.println("> Entendido!\n");
            respuestaUsuario();
           break;
         } else if(userYN.equalsIgnoreCase("NO")){ //Vuelve al Menú
           Serial.println("> Volviendo al Menu\n");
           menu();
           break;
         }else { // Respuesta Invalida
           Serial.println("> Respuesta Incorrecta >( \n");
           break;
         }
    }
  }
}
//------------------------------------//------------------------------------------//
void respuestaUsuario(){
  if (userYN.equalsIgnoreCase("SI")) {  // Si el usuario quiere repetir
    Serial.println("> Repitiendo la ultima opcion...\n");
    return;  // Sale del void y deja que loop() se ejecute nuevamente
   }
  
  userInput = ""; //Limpia el anterior INPUT para uno nuevo
  
  while (true) {  // Si hay datos en el buffer serial
    if (Serial.available() > 0) {  // Si hay datos en el buffer serial
         userInput = Serial.readString();  // Leer entrada del usuario
         userInput.trim();  // Elimina espacios y saltos de línea
      
       if (userInput.length() == 0) {  // Si el usuario solo presionó Enter
         Serial.println("Entrada incorrecta. Elige una de las opciones para continuar: \n");
         break;
            }
         if (userInput.equalsIgnoreCase("1")||userInput.equalsIgnoreCase("2")) {  // Verifica si escribió "start"
          Serial.println(">...Iniciando del programa \n");
          break;  // Sale del while y continúa con el código
         } else{
             Serial.println(">... Esperando Respuesta :( \n");
           break;
            }
        }
    }
}
//------------------------------------//----------------------------------//
void limpiarBufferSerial() { //Limpia Serial.avaliable();
    while (Serial.available() > 0) {
        Serial.read();  // Elimina cualquier dato pendiente
    }
}
//------------------------------------//----------------------------------//
void loop(){
  switch(userInput.charAt(0)){
    case '1':
    Serial.println("> Ejectunado Programa!\n");
    delay(500);
    for(int BRILLOinc = 0;BRILLOinc < 6;BRILLOinc++){
      digitalWrite(pinLEDS[BRILLOinc], HIGH);
      delay(500);
      digitalWrite(pinLEDS[BRILLOinc], LOW);
    }
    for(int BRILLOdec = 6;BRILLOdec > 6;BRILLOdec--){
      digitalWrite(pinLEDS[BRILLOdec], HIGH);
      delay(500);
      digitalWrite(pinLEDS[BRILLOdec], LOW);
    }
    procesoTerminado();
    break;
    
    case '2':
    digitalWrite(pinBombilla, HIGH);
    Serial.println("punto 2...");
    delay(4000);
    digitalWrite(pinBombilla, LOW);
    procesoTerminado();
    break;
    
    default:
    menu();
    break;
  }
}
