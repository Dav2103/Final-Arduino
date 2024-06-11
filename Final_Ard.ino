const int buttonPin1 = 2; // Pin del primer pulsador (encender)
const int buttonPin2 = 3; // Pin del segundo pulsador (apagar)
const int motorPin = 9;   // Pin del motor (PWM)
const int potPin = A0;    // Pin del potenciómetro
const int ledGreenPin = 10; // Pin del LED verde (motor encendido)
const int ledRedPin = 11;   // Pin del LED rojo (motor apagado)

int buttonState1 = 0;
int buttonState2 = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int potValue = 0;
int motorSpeed = 0;
bool motorOn = false;
char command;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledRedPin, LOW);
}

void loop() {
  // Leemos el estado de los pulsadores
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // Si el primer pulsador es presionado (detección de flanco ascendente)
  if (buttonState1 == HIGH && lastButtonState1 == LOW) {
    motorOn = true; // Enciende el motor
  }

  // Si el segundo pulsador es presionado (detección de flanco ascendente)
  if (buttonState2 == HIGH && lastButtonState2 == LOW) {
    motorOn = false; // Apaga el motor
  }

  // Actualiza el último estado de los pulsadores
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;

  // Si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    command = Serial.read();
    if (command == 'E') {
      motorOn = true; // Enciende el motor
    } else if (command == 'A') {
      motorOn = false; // Apaga el motor
    }
  }

  // Control del motor y LEDs según el estado del motor
  if (motorOn) {
    potValue = analogRead(potPin);
    motorSpeed = map(potValue, 0, 1023, 0, 255);
    analogWrite(motorPin, motorSpeed);
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledRedPin, LOW);
  } else {
    analogWrite(motorPin, 0);
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledRedPin, HIGH);
  }

  // Pequeño retardo para evitar rebotes
  delay(50);
}

