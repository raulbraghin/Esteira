#include <mwc_stepper.h>        //Motor de passo
#include "Wire.h"               //biblioteca I2C
#include "LiquidCrystal_I2C.h"  //LCD I2C

//************************** MOTORES DE PASSO *************************
//MWCSTEPPER MotorEsteira(2, 3, 4);  //EN-ENABLE  CW-STEPS  CLK-DIRECTION
//MWCSTEPPER MotorMesa(5, 6, 7);
MWCSTEPPER MotorEsteira(23, 25, 27);  //EN-ENABLE   CLK-DIRECTION   CW-STEPS
MWCSTEPPER MotorMesa(22, 24, 26);
MWCSTEPPER MotorGarraD(31, 33, 35);
MWCSTEPPER MotorGarraE(30, 32, 34);

//Sentido de rotação dos motores
#define Horario 1
#define Antihorario 0

#define PassosPorVolta 1600  //Definir quantos passo por volta o motor tem que dar

size_t i = 0;

//RPM dos motores
#define RPMMesa 1
#define RPMGarras 1
#define RPMEsteira 1


//Valores devem ser definidos para posicionamento, exceto da esteria que deve ser em excesso
int PassosEsteira = 1000;  //Se precisa de 900 passos para o palete chegar até o sensor, colocar 1000 para ter certeza
int PassosGarraVazia = 500;
int PassosGarraCheia = 300;
int PassosGarra = 100;
int PassosRestantes;


//************************** SENSORES DE POSIÇÃO ************************
#define Inicio 5
#define Mesa 6
#define Fim 7

bool SensorInicio;
bool SensorMesa;
bool SensorFim;

//************************** BOTÕES *************************************
#define Start 2
#define Emergencia 3
#define Reset 4

bool BtStart;
bool BtReset;
bool BtEmergencia;


//************************** IHM LCD ************************************
LiquidCrystal_I2C lcd(0x27, 16, 2);  //endereço, colunas, linhas


//************************** VARIÁVEIS DE PROCESSO **********************
int ContPaletes = 0;

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

  attachInterrupt(3, FuncEmergencia, FALLING);

  pinMode(Inicio, INPUT_PULLUP);
  pinMode(Mesa, INPUT_PULLUP);
  pinMode(Fim, INPUT_PULLUP);


  //Inicializa motor
  MotorEsteira.init();

  MotorMesa.init();

  MotorGarraD.init();

  MotorGarraE.init();


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

  Serial.println("FuncEmergencia");
}