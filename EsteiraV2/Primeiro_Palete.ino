void FuncPrimeiroPalete() {

  //INICIO DO PROCESSO

  if (SensorInicio == false && BtStart == false && LigaEsteira == false && Etapa1 == false) {
    LigaEsteira = true;
  }

  if (LigaEsteira == true) {  //LIGA MOTOR DA ESTEIRA
    MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();

    Serial.print("POS Motor Esteira");
    Serial.println(MotorEsteira.currentPosition());
  }

  //FINALIZA PROCESSO

  if (SensorMesa == false && LigaEsteira == true /*&& FinalizaProcesso == false*/) {  //PARA MOTOR DA ESTEIRA

    LigaEsteira = false;

    MotorEsteira.stop();
    MotorEsteira.setCurrentPosition(0);

    dseg1 = 0;

    Serial.println("FuncEsteira Para esteira");

    Etapa1 = true;
  }


  //*************Abre Garra**************************
  if (Etapa1 == true && Etapa2 == false && SensorMesa == false && LigaEsteira == false && dseg1 >= 5) {

    Serial.println("FuncAbreGarras Linha 38");

    MotorGarraE.move(-PassosGarra);
    MotorGarraE.runToPosition();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());

    MotorGarraD.move(PassosGarra);
    MotorGarraD.runToPosition();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());
  }

  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == -PassosGarra && Etapa2 == false) {

    Serial.println("FuncAbreGarra Linha 55");

    dseg2 = 0;

    Etapa2 = true;
  }


  //*************levanta mesa*************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {


    MotorMesa.move(PassosGarraVazia);
    MotorMesa.runToPosition();

    Serial.print("POS Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("SobeMesaVazia");
    
    
  }

  if (Etapa2 == true && Etapa3 == false && MotorMesa.currentPosition() == PassosGarraVazia){

        
MotorMesa.setCurrentPosition(0);

MotorGarraD.setCurrentPosition(0);

MotorGarraE.setCurrentPosition(0);

dseg3 = 0;

    Etapa3 = true;

    Serial.println("Finaliza Movimento Mesa linha 86");
    
  }

  //**************** Fecha Garra *******************

  if (Etapa3 == true && Etapa4 == false && dseg3 >= 5){


    MotorGarraD.move(-PassosGarra);
    MotorGarraD.runToPosition();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraE.move(PassosGarra);
    MotorGarraE.runToPosition();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());

    Serial.println("Fechando Garras Linha 107");
    
  }

  if (Etapa3 == true && Etapa4 == false && MotorGarraD.currentPosition() == -PassosGarra && MotorGarraE.currentPosition() == PassosGarra){


    Serial.println("Garras fechadas - Linha 114");

    dseg4 = 0;

    Etapa4 = true;

    

    
  }

//**************** abaixa mesa ***************************

if (Etapa4 == true && dseg4 >= 5){


    MotorMesa.move(-PassosGarraVazia);
    MotorMesa.runToPosition();


    Serial.print("POS Motor Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("Desce Mesa Linha 137");

  
}

if (MotorMesa.currentPosition() == -PassosGarraVazia && Etapa4 == true && ContPaletes == 0){

ContPaletes++;

Etapa1 = false;
Etapa2 = false;
Etapa3 = false;
Etapa4 = false;

Serial.println("Finaliza primeiro palete");

MotorMesa.setCurrentPosition(0);
MotorGarraD.setCurrentPosition(0);
MotorGarraE.setCurrentPosition(0);
  
}


}