#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Define los pines GPIO para el control del motor
const int motor1A = 12; // Conectado a IN1 del L293D
const int motor1B = 13; // Conectado a IN2 del L293D
const int enable1 = 14; // Conectado a ENA del L293D

const int motor2A = 25; // Conectado a IN1 del L293D
const int motor2B = 26; // Conectado a IN2 del L293D
const int enable2 = 27; // Conectado a ENA del L293D

void setup() {
  // Inicializar los pines GPIO para el motor como salidas
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(enable1, OUTPUT);

  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(enable2, OUTPUT);

  // Inicializar el puerto serie Bluetooth
  SerialBT.begin("ESP32_BT_Motor_Control");
  Serial.begin(115200);
  Serial.println("Bluetooth iniciado, conecta tu dispositivo móvil.");
}

void loop() {
  // Verificar si hay datos disponibles para leer desde Bluetooth
  if (SerialBT.available()) {
    char command = SerialBT.read();

    // Interpretar el comando recibido y controlar el motor en consecuencia
    switch (command) {
      case 'U': // Avanzar
        digitalWrite(motor1A, HIGH);
        digitalWrite(motor1B, LOW);
       
        digitalWrite(motor2A, HIGH);
        digitalWrite(motor2B, LOW);
        analogWrite(enable2, 210); // Control de velocidad
        analogWrite(enable1, 210); // Control de velocidad

        delay(10);

        Serial.println("ADELANTE");
       // paro();
        break;

      case 'D': // Atras
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, HIGH);
        
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, HIGH);
        analogWrite(enable2, 210); // Control de velocidad
        analogWrite(enable1, 210); // Control de velocidad

        delay(10);
        Serial.println("ATRAS");
       // paro();
        break;

      case 'L': // izquierda
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, HIGH);
        
        digitalWrite(motor2A, HIGH);
        digitalWrite(motor2B, LOW);
        analogWrite(enable2, 210); // Control de velocidad
        analogWrite(enable1, 210); // Apagar el motor

        delay(10);
        Serial.println("IZQUIERDA");
        //paro();
        break;

      case 'R': // derecha
        digitalWrite(motor1A, HIGH);
        digitalWrite(motor1B, LOW);
       
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, HIGH);
        analogWrite(enable2, 210); // Apagar el motor
        analogWrite(enable1, 210); // Control de velocidad


        delay(10);
        Serial.println("DERECHA");
        //paro();
        break;

        case 'X': // DETENER
        Serial.println("STOP");
        paro();

        delay(10);
        Serial.println("STOP");
        //paro();
        break;
    }
  }
}

void paro() { // Detener los motores
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(enable2, 0); // Apagar el motor
  analogWrite(enable1, 0); // Control de velocidad

}
