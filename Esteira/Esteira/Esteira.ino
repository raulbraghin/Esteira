#include "AccelStepper.h"       //Motor de Passo
#include "EEPROM.h"             //EEPROM
#include "Wire.h"               //biblioteca I2C
#include "LiquidCrystal_I2C.h"  //LCD I2C

//************************** MOTORES DE PASSO *************************
AccelStepper MotorEsteira(2, 3, 4);  //EN-ENABLE  CW-STEPS  CLK-DIRECTION
AccelStepper MotorMesa(5, 6, 7);
AccelStepper MotorGarra1(8, 9, 10);
AccelStepper MotorGarra2(11, 12, 13);


//Valores devem ser definidos para posicionamento, exceto da esteria que deve ser em excesso
#define PassosEsteira 1000  //Se precisa de 900 passos para o palete chegar até o sensor, colocar 1000 ara ter certeza
#define PassosMesaVazia 500
#define PassosMesaCheia 300
#define PassosGarra 100


//************************** SENSORES DE POSIÇÃO ************************
#define Inicio 23
#define Mesa 25
#define Fim 27

bool SensorInicio;
bool SensorMesa;
bool SensorFim;

//************************** BOTÕES *************************************
#define Start 29
#define Reset 31
#define Emergencia 33

bool BtStart;
bool BtReset;
bool BtEmergencia;


//************************** IHM LCD ************************************
LiquidCrystal_I2C lcd(0x27, 16, 2);  //endereço, colunas, linhas


//************************** VARIÁVEIS DE PROCESSO **********************
int ContPaletes = 0;

bool EmergAtiva = false;
bool ResetProcesso = false;

unsigned long millisec;
unsigned long dsec1;
unsigned long dsec2;
unsigned long dsec3;
unsigned long dsec4;
unsigned long dsec5;

long TPIntProc1;
long TPIntProc2;
long TPIntProc3;
long TPIntProc4;
long TPIntProc5;




void setup() {

  Serial.begin(115200);

  lcd.init();       //Inicializa LCD
  lcd.backlight();  //Liga luz de fundo do LCD
  FuncInicializaLCD();

  pinMode(Start, INPUT_PULLUP);
  pinMode(Reset, INPUT_PULLUP);
  pinMode(Emergencia, INPUT_PULLUP);

  pinMode(Inicio, INPUT_PULLUP);
  pinMode(Mesa, INPUT_PULLUP);
  pinMode(Fim, INPUT_PULLUP);

  //Velocidade de rotação do motor
  MotorEsteira.setMaxSpeed(500);
  MotorMesa.setMaxSpeed(500);
  MotorGarra1.setMaxSpeed(500);
  MotorGarra2.setMaxSpeed(500);

  //A Aceleração e a desaceleração levam 100 passos
  MotorEsteira.setAcceleration(100);
  MotorMesa.setAcceleration(100);
  MotorGarra1.setAcceleration(100);
  MotorGarra2.setAcceleration(100);

  millisec = millis();

  Serial.println("Fim do Setup");
}

void loop() {

  FuncBotoes();

  FuncSensores();

  FuncLCD();

  FuncEsteira();
}


void FuncTempo() {

  if ((millis() - millisec) >= 100) {
    dsec1++;
    dsec2++;
    dsec3++;
  }


  if (millis() < millisec) {
    millisec = millis();
  }
}