void FuncEsteira() {

  if (SensorInicio == false && BtStart == false && LigaEsteira == false) {
    LigaEsteira = true;
  }

  if (LigaEsteira == true) {  //LIGA MOTOR DA ESTEIRA
    MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();

    Serial.print("POS ");
    Serial.println(MotorEsteira.currentPosition());
  }


  if (SensorMesa == false && LigaEsteira == true && FinalizaProcesso == false) {  //PARA MOTOR DA ESTEIRA

    LigaEsteira = false;

    MotorEsteira.stop();
    MotorEsteira.setCurrentPosition(0);

    dseg1 = 0;

    Serial.println("FuncEsteira Para esteira");
    Serial.print("dseg1 ");
    Serial.println(dseg1);
  }
}



//************************************************************************
void FuncAbreGarra() {

  if (ContPaletes == 0 && SensorMesa == false && LigaEsteira == false && dseg1 >= 5) {  //SE FOR O PRIMEIRO PALETE

    AcioGarrasPrimPalete = true;
  }


  if (AcioGarrasPrimPalete == true) {

    MotorGarraD.move(PassosGarra);
    MotorGarraD.run();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraE.move(-PassosGarra);
    MotorGarraE.run();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());
  }


  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == PassosGarra) {

    LiberaMesaPrimeiroPalete = true;

    dseg2 = 0;
  }



  if (ContPaletes > 0 && SensorMesa == false && LigaEsteira == false && LiberaMesaNPalete == false && dseg1 >= 5) {  //SE NÃO FOR O PRIMEIRO PALETE

    LiberaMesaNPalete = true;  //Libera mesa para começar a subir

    dseg2 = 0;
  }


  if (MotorMesa.currentPosition() == PassosGarraCheia && LiberaMesaNPalete == true && SobeMesa == false) {


    MotorGarraD.move(PassosGarra);
    MotorGarraD.run();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraE.move(-PassosGarra);
    MotorGarraE.run();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());
  }

  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == PassosGarra) {

    SobeMesa2Estagio = true;
  }
}


//**********************************************************************************
void FuncSobeMesa() {

  if (LiberaMesaPrimeiroPalete == true && dseg2 >= 5) {  //Tempo entre a aberturada garra e o inicio do movimento da mesa em décimos de segundos
    SobeMesa = true;

    Serial.println("SobeMesa = true");
  }


  if (SobeMesa == true && LiberaMesaPrimeiroPalete == true) {  //ACIONA MOTOR DA MESA QUANDO NÃO TEM NENHUM PALETE NA GARRA

    MotorMesa.move(PassosGarraVazia);
    MotorMesa.run();

    Serial.print("POS ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("SobeMesaVazia");
  }


  if (MotorMesa.currentPosition() == PassosGarraVazia && LiberaMesaPrimeiroPalete == true) {  //FINALIZA MOVIMENTO DO MOTOR DA MESA
    SobeMesa = false;

    LiberaFecharGarras = true;

    dseg3 = 0;

    ContPaletes++;

    Serial.println("Para Mesa VAZIA");
  }


  if (LiberaMesaNPalete == true && dseg2 >= 5) {  //Tempo entre a aberturada garra e o inicio do movimento da mesa em décimos de segundos
    SobeMesa = true;

    Serial.println("SobeMesa = true");
  }


  if (SobeMesa == true && LiberaMesaNPalete == true) {  //ACIONA MOTOR DA MESA QUANDO JÁ TEM PALETE NA GARRA
    MotorMesa.move(PassosGarraCheia);
    MotorMesa.run();

    Serial.print("POS ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("SobeMesaCheia");
  }



  if (MotorMesa.currentPosition() == PassosGarraCheia && LiberaMesaNPalete == true) {  //FINALIZA PRIMEIRO MOVIMENTO DO MOTOR DA MESA
    SobeMesa = false;

    Serial.println("Para Mesa CHEIA");
  }

  if (SobeMesa2Estagio == true) {

    MotorMesa.move(PassosGarraVazia);
    MotorMesa.run();


    Serial.print("POS ");
    Serial.println(MotorMesa.currentPosition());
  }

  if (MotorMesa.currentPosition() == PassosGarraVazia && SobeMesa2Estagio == true) {


    LiberaFecharGarras = true;

    LiberaMesaNPalete = false;

    SobeMesa2Estagio = false;

    dseg3 = 0;
  }
}


//************************************************************************
void FuncFechaGarra() {

  if (LiberaFecharGarras == true && dseg3 >= 5) {

    MotorGarraD.move(0);
    MotorGarraD.run();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());



    MotorGarraE.move(0);
    MotorGarraE.run();


    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());
  }

  if (MotorGarraD.currentPosition() == 0 && MotorGarraE.currentPosition() == 0) {

    AcioGarrasPrimPalete = false;
    LiberaMesaPrimeiroPalete = false;
    LiberaFecharGarras = false;

    DesceMesa = true;

    dseg4++;
  }
}

//************************************************************************
void FuncDesceMesa() {

  if (DesceMesa == true && dseg4 >= 5) {

    MotorMesa.move(0);
    MotorMesa.run();


    Serial.print("POS Motor Mesa");
    Serial.println(MotorMesa.currentPosition());
  }

  if (DesceMesa == true && MotorMesa.currentPosition() == 0) {

    DesceMesa = false;
  }
}

//************************************************************************
void FuncFinaliza() {

  if (ContPaletes == EmpilhamentoMaximo && MotorMesa.currentPosition() == 0) {

    FinalizaProcesso = true;
  }

  if (FinalizaProcesso == true) {

    MotorMesa.move(PassosGarraVazia);
    MotorMesa.run();
  }

  if (FinalizaProcesso == true && MotorMesa.currentPosition() == PassosGarraVazia) {

    MotorGarraD.move(PassosGarra);
    MotorGarraD.run();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraE.move(-PassosGarra);
    MotorGarraE.run();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());
  }

  if (FinalizaProcesso == true && MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == -PassosGarra) {

    MotorMesa.move(0);
    MotorMesa.run();
  }


  if (FinalizaProcesso == true && MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == -PassosGarra && MotorMesa.currentPosition() == 0) {

        MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();

    Serial.print("POS ");
    Serial.println(MotorEsteira.currentPosition());
    
  }

  if (SensorFim == false) {

  MotorEsteira.stop();
    
  }
  

  
}