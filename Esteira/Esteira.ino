#include "AccelStepper.h"       //Motor de Passo
#include "Wire.h"               //biblioteca I2C
#include "LiquidCrystal_I2C.h"  //LCD I2C

//************************** MOTORES DE PASSO *************************
AccelStepper MotorEsteira(1, 3, 4);  //EN-ENABLE  CW-STEPS  CLK-DIRECTION
AccelStepper MotorMesa(2, 8, 9);
AccelStepper MotorGarraD(3, 10, 11);
AccelStepper MotorGarraE(4, 12, 13);


//Valores devem ser definidos para posicionamento, exceto da esteria que deve ser em excesso
#define PassosEsteira 1000  //Se precisa de 900 passos para o palete chegar até o sensor, colocar 1000 ara ter certeza
#define PassosGarraVazia 500
#define PassosGarraCheia 300
#define PassosGarra 100


//************************** SENSORES DE POSIÇÃO ************************
//#define Inicio 23
//#define Mesa 25
//#define Fim 27

#define Inicio 6
#define Mesa 7
#define Fim 8

bool SensorInicio;
bool SensorMesa;
bool SensorFim;

//************************** BOTÕES *************************************
#define Start 5
/*
#define Start 29
#define Reset 31
#define Emergencia 33
*/
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
bool SobeMesa = false;
bool SobeMesa2Estagio = false;
bool DesceMesa = false;

bool AcioGarrasPrimPalete = false;
bool AcioGarrasNPalete = false;
bool LiberaFecharGarras = false;

bool LiberaMesaPrimeiroPalete = false;
bool LiberaMesaNPalete = false;

int EmpilhamentoMaximo = 5;
bool FinalizaProcesso;

unsigned long tempoins;
long dseg1;
long dseg2;
long dseg3;
long dseg4;


void setup() {

  Serial.begin(115200);

  lcd.init();       //Inicializa LCD
  lcd.backlight();  //Liga luz de fundo do LCD
  FuncInicializaLCD();

  pinMode(Start, INPUT_PULLUP);
  /* pinMode(Reset, INPUT_PULLUP);
  pinMode(Emergencia, INPUT_PULLUP);
*/
  pinMode(Inicio, INPUT_PULLUP);
  pinMode(Mesa, INPUT_PULLUP);
  pinMode(Fim, INPUT_PULLUP);

  //Velocidade de rotação do motor
  MotorEsteira.setMaxSpeed(2000);
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

  FuncEsteira();

  FuncSobeMesa();

  FuncDesceMesa();

  FuncAbreGarra();

  FuncFechaGarra();

  FuncFinaliza();


  FuncTempo();
}



//**************************************************************
void FuncTempo() {

  if ((millis() - tempoins) >= 100) {  //CONTADOR DE SEGUNDOS

    dseg1++;
    dseg2++;
    dseg3++;
    dseg4++;
    tempoins = millis();
  }


  if (millis() < tempoins) {
    tempoins = millis();
  }

}  //FIM DO temporizador