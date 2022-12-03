#include "AccelStepper.h"       //Motor de Passo
#include "Wire.h"               //biblioteca I2C
#include "LiquidCrystal_I2C.h"  //LCD I2C

//************************** MOTORES DE PASSO *************************
AccelStepper MotorEsteira(23, 25, 27);  //EN-ENABLE  CW-STEPS  CLK-DIRECTION
AccelStepper MotorMesa(22, 24, 26);
AccelStepper MotorGarraD(31, 33, 35);
AccelStepper MotorGarraE(30, 32, 34);


//Valores devem ser definidos para posicionamento, exceto da esteria que deve ser em excesso
int PassosEsteira = 1000;  //Se precisa de 900 passos para o palete chegar até o sensor, colocar 1000 para ter certeza
int PassosGarraVazia = 500;
int PassosGarraCheia = 300;
int PassosGarra = 100;


//************************** SENSORES DE POSIÇÃO ************************
#define Inicio 2
#define Mesa 3
#define Fim 4

bool SensorInicio;
bool SensorMesa;
bool SensorFim;

//************************** BOTÕES *************************************
#define Start 6
#define Reset 7
#define Emergencia 8

bool BtStart;
bool BtReset;
bool BtEmergencia;


//************************** IHM LCD ************************************
LiquidCrystal_I2C lcd(0x27, 16, 2);  //endereço, colunas, linhas


//************************** VARIÁVEIS DE PROCESSO **********************
int ContPaletes = 4;

bool EmergAtiva = false;
bool ResetProcesso = false;

bool LigaEsteira = false;

bool Etapa1 = false;
bool Etapa2 = false;
bool Etapa3 = false;
bool Etapa4 = false;
bool Etapa5 = false;

int EmpilhamentoMaximo = 5;
bool FinalizaProcesso;

unsigned long tempoins;
long dseg1;
long dseg2;
long dseg3;
long dseg4;
long dseg5;


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
  MotorEsteira.setAcceleration(100);

  MotorMesa.setMaxSpeed(500);
  MotorMesa.setAcceleration(100);

  MotorGarraD.setMaxSpeed(500);
  MotorGarraD.setAcceleration(10);

  MotorGarraE.setMaxSpeed(500);
  MotorGarraE.setAcceleration(10);





  tempoins = millis();

  Serial.println("Fim do Setup");
}

void loop() {

  FuncBotoes();

  FuncSensores();

  FuncLCD();

  if (EmergAtiva == false) {

    if (ContPaletes == 0) {

      FuncPrimeiroPalete();
    }

    if (ContPaletes > 0 && ContPaletes < EmpilhamentoMaximo) {

      FuncNPaletes();
    }

    if (ContPaletes == EmpilhamentoMaximo) {

      FuncFinaliza();
    }


  } else {
    FuncEmergencia();
  }

  if (ResetProcesso == true) {

    FuncReset();
  }

  FuncTempo();
}



//**************************************************************
void FuncTempo() {

  if ((millis() - tempoins) >= 100) {  //CONTADOR DE SEGUNDOS

    dseg1++;
    dseg2++;
    dseg3++;
    dseg4++;
    dseg5++;
    tempoins = millis();
  }


  if (millis() < tempoins) {
    tempoins = millis();
  }

}  //FIM DO temporizador



//************************************************************************
void FuncEmergencia() {

  MotorEsteira.stop();
  MotorGarraD.stop();
  MotorGarraE.stop();
  MotorMesa.stop();


  Serial.println("FuncEmergencia");
}

//************************************************************************
void FuncReset() {

  MotorEsteira.stop();
  MotorGarraD.stop();
  MotorGarraE.stop();
  MotorMesa.stop();

  ContPaletes = 0;


  MotorMesa.setCurrentPosition(0);
  MotorGarraD.setCurrentPosition(0);
  MotorGarraE.setCurrentPosition(0);
  MotorEsteira.setCurrentPosition(0);

  Serial.println("FuncReset");
}
