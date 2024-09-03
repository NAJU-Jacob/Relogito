// professor tentamos usar o pré scaler, mas não deu certo conosco, quando implementavmos o pré scaler ao código nada 
//funcionava e a tela de lcd ficava em branco acesa mas em branco então optamos por faer sem
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int startButtonPin = 6;
const int stopButtonPin = 7;

unsigned long startTime = 0; // armazena o tempo de início
unsigned long elapsedTime = 0; // armazena o tempo decorrido
bool running = false;
bool lastStartButtonState = LOW;
bool lastStopButtonState = LOW;

void setup() {
  lcd.begin(16, 2);
  pinMode(startButtonPin, INPUT_PULLUP); 
  pinMode(stopButtonPin, INPUT_PULLUP);

  // Defina o contraste do display
  analogWrite(A0, 100);
}

void loop() {
  
  bool currentStartButtonState = digitalRead(startButtonPin);

  bool currentStopButtonState = digitalRead(stopButtonPin);  

  if (currentStartButtonState == HIGH && lastStartButtonState == LOW) {
    if (!running) {
      startTime = millis();
      running = true; 
    } else {
      elapsedTime = millis() - startTime;
      running = false;
    }
  }

  if (currentStopButtonState == HIGH && lastStopButtonState == LOW && running) {
    running = false;
  }

  lastStartButtonState = currentStartButtonState;
  lastStopButtonState = currentStopButtonState;

  updateLCD();
}

void updateLCD() {
  lcd.clear();
  
  // Mostra "Aula 2 time" na primeira linha
  lcd.setCursor(0, 0);
  lcd.print("Aula 2 time");

  unsigned long seconds = (elapsedTime / 1000) % 60;
  unsigned long minutes = (elapsedTime / 60000) % 100;
  lcd.setCursor(0, 1);
  lcd.print(minutes < 10 ? "0" : ""); // Adiciona um zero à esquerda se necessário
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds < 10 ? "0" : ""); // Adiciona um zero à esquerda se necessário
  lcd.print(seconds);
  
  delay(100);
}
