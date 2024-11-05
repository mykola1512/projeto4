// C++ code
#include <Wire.h>
#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

Servo servoCofre;
const byte LINHAS = 4;
const byte COLUNAS = 4;
char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte linhaPins[LINHAS] = {5, 6, 7, 8};
byte colunaPins[COLUNAS] = {9, 10, 11, 12};

Keypad teclado = Keypad(makeKeymap(teclas), linhaPins, colunaPins, LINHAS, COLUNAS);

Adafruit_LiquidCrystal lcd(0);

const int ledVerde = 4;
const int ledVermelho = 13;
const int buzzer = 3;

String codigoCorreto = "1234";
String codigoInserido = "";

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
  servoCofre.attach(2);
  servoCofre.write(0);
  
  lcd.begin(16, 2);
  lcd.print("Use 'A' para");
  lcd.setCursor(0,1);
  lcd.print("verificar.");
  delay(4000);
  lcd.clear();
  lcd.print("Insira o codigo:");
}

void loop() {
  char tecla = teclado.getKey();
  if (tecla) {
    if (tecla == 'A') {
      verificarCodigo();
    } else {
      codigoInserido += tecla;
      lcd.setCursor(codigoInserido.length() - 1, 1);
      lcd.print(tecla);
    }
  }
}

void verificarCodigo() {
  lcd.clear();
  if (codigoInserido == codigoCorreto) {
    digitalWrite(ledVerde, HIGH);
    tone(buzzer, 85);
    delay(1000);
    noTone(buzzer);
    lcd.print("Codigo Correto!");
    servoCofre.write(90);
  	delay(5000);
  	servoCofre.write(0);
    digitalWrite(ledVerde, LOW);
  } else {
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 85);
    delay(1000);
    noTone(buzzer);
    lcd.print("Codigo Incorreto!");
    delay(2000);
    digitalWrite(ledVermelho, LOW);
  }
  codigoInserido = "";
  lcd.clear();
  lcd.print("Insira o codigo:");
}
