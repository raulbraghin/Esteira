void FuncFinaliza() {

  //*************levanta mesa*************************
  if (Etapa1 == false && ContPaletes == EmpilhamentoMaximo) {

    MotorMesa.move(PassosGarraVazia);
    MotorMesa.runToPosition();


    Serial.print("POS Motor Mesa");
    Serial.println(MotorMesa.currentPosition());
  }


  if (MotorMesa.currentPosition() == PassosGarraVazia && Etapa1 == false) {

    Etapa1 = true;

    dseg1 = 0;

    Serial.println("Sobe Mesa linha 21");
  }

  //*************Abre Garra**************************
  if (Etapa1 == true && Etapa2 == false && dseg1 >= 5) {

    Serial.println("FuncAbreGarras Linha 28");

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

    Serial.println("FuncAbreGarra Linha 45");

    dseg2 = 0;

    Etapa2 = true;

    MotorMesa.setCurrentPosition(0);
  }


  //**************** abaixa mesa ***************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {


    MotorMesa.move(-PassosGarraVazia);
    MotorMesa.runToPosition();


    Serial.print("POS Motor Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("Desce Mesa Linha 67");
  }


  if (MotorMesa.currentPosition() == -PassosGarraVazia && Etapa2 == true && Etapa3 == false) {

    dseg3 = 0;

    Etapa3 = true;

    Serial.println("Finaliza Descer Mesa");
  }


  //**************** liga esteira *******************

  if (Etapa3 == true && LigaEsteira == false && dseg3 >= 5) {

    LigaEsteira = true;

    MotorEsteira.setCurrentPosition(0);

    Serial.println("Liga Esteira Lnha 85 Finaliza");
  }

  if (LigaEsteira = true && Etapa3 == true) {


    MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();

    Serial.print("POS Motor Esteira Linha 94");
    Serial.println(MotorEsteira.currentPosition());
  }

  if (SensorFim == false && LigaEsteira == true) {

    MotorEsteira.stop();

    LigaEsteira = false;

    Etapa1 = false;
    Etapa2 = false;
    Etapa3 = false;
    Etapa4 = false;
    Etapa5 = false;

    Serial.println("Finaliza N palete");


    MotorMesa.setCurrentPosition(0);
    MotorGarraD.setCurrentPosition(0);
    MotorGarraE.setCurrentPosition(0);

    ContPaletes = 0;

  }
}