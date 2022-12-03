void FuncNPaletes() {

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


  //*************levanta mesa*************************
  if (Etapa1 == true && Etapa2 == false && SensorMesa == false && LigaEsteira == false && dseg1 >= 5) {


    MotorMesa.move(PassosGarraCheia);
    MotorMesa.runToPosition();

    Serial.print("POS Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("SobeMesaCheia");
  }

  if (Etapa1 == true && Etapa2 == false && MotorMesa.currentPosition() == PassosGarraCheia) {

    dseg2 = 0;

    Etapa2 = true;

    Serial.println("Finaliza Movimento Mesa linha 56");
  }

  //*************Abre Garra**************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {

    Serial.println("FuncAbreGarras Linha 62");

    MotorGarraE.move(-PassosGarra);
    MotorGarraE.runToPosition();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());

    MotorGarraD.move(PassosGarra);
    MotorGarraD.runToPosition();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());
  }

  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == -PassosGarra && Etapa3 == false) {

    Serial.println("FuncAbreGarra Linha 79");

    dseg3 = 0;

    Etapa3 = true;
  }


  //********************* sobe restante da mesa ************************

  if (Etapa3 == true && Etapa4 == false && dseg3 >= 5) {


    MotorMesa.move(PassosGarraVazia - PassosGarraCheia);
    MotorMesa.runToPosition();

    Serial.print("POS Mesa ");
    Serial.println(MotorMesa.currentPosition());


    Serial.println("SobeMesaCheia Para Npalete Linha 101");
  }

  if (Etapa3 == true && MotorMesa.currentPosition() == PassosGarraVazia & Etapa4 == false) {

    Serial.println("Linha 104");

    dseg4 = 0;

    Etapa4 = true;


    MotorGarraD.setCurrentPosition(0);
    MotorGarraE.setCurrentPosition(0);

    MotorMesa.setCurrentPosition(0);
  }

  //*********************fecha garra *********************

  if (Etapa4 == true && Etapa5 == false && dseg4 >= 5) {


    MotorGarraD.move(-PassosGarra);
    MotorGarraD.runToPosition();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraE.move(PassosGarra);
    MotorGarraE.runToPosition();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());

    Serial.println("Fechando Garras Linha 131");
  }

  if (Etapa4 == true && Etapa5 == false && MotorGarraD.currentPosition() == -PassosGarra && MotorGarraE.currentPosition() == PassosGarra) {


    Serial.println("Garras fechadas - Linha 138");

    dseg5 = 0;

    Etapa5 = true;
  }




  //**************** abaixa mesa ***************************
  if (Etapa5 == true && dseg5 >= 5) {


    MotorMesa.move(-PassosGarraVazia);
    MotorMesa.runToPosition();


    Serial.print("POS Motor Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("Desce Mesa Linha 164");
  }

  if (MotorMesa.currentPosition() == -PassosGarraVazia && Etapa5 == true) {

    ContPaletes++;

    Etapa1 = false;
    Etapa2 = false;
    Etapa3 = false;
    Etapa4 = false;
    Etapa5 = false;

    Serial.println("Finaliza N palete");


    MotorMesa.setCurrentPosition(0);
    MotorGarraD.setCurrentPosition(0);
    MotorGarraE.setCurrentPosition(0);
    
  }
}