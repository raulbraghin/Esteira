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


  if (SensorMesa == false && LigaEsteira == true) {  //PARA MOTOR DA ESTEIRA

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

    MotorGarraE.move(PassosGarra);
    MotorGarraE.run();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());
  }


  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == PassosGarra) {

    LiberaMesaPrimeiroPalete = true;

    dseg2 = 0;
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


  } else if (SobeMesa == true && LiberaMesaNPalete == true) {  //ACIONA MOTOR DA MESA QUANDO JÁ TEM PALETE NA GARRA
    MotorMesa.move(PassosGarraCheia);
    MotorMesa.run();

    Serial.print("POS ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("SobeMesaCheia");
  }

  if (MotorMesa.currentPosition() == PassosGarraVazia && LiberaMesaPrimeiroPalete == true) {  //FINALIZA MOVIMENTO DO MOTOR DA MESA
    SobeMesa = false;

    //MotorMesa.setCurrentPosition(0);

    ContPaletes++;

    Serial.println("Para Mesa VAZIA");
  }


  if (MotorMesa.currentPosition() == PassosGarraCheia && ContPaletes != 0) {  //FINALIZA MOVIMENTO DO MOTOR DA MESA
    SobeMesa = false;

    //MotorMesa.setCurrentPosition(0);

    ContPaletes++;

    Serial.println("Para Mesa CHEIA");
  }
}


//************************************************************************
void FuncFechaGarra() {

  if (AcioGarrasPrimPalete == true && LiberaMesaPrimeiroPalete == true) {

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

    AcioGarrasPrimPalete == false;
    LiberaMesaPrimeiroPalete == false;

    DesceMesa = true;

    dseg3++;
  }
}

//************************************************************************
void FuncDesceMesa() {

  if (DesceMesa == true && dseg3 >= 5) {

    MotorMesa.move(0);
    MotorMesa.run();


    Serial.print("POS Motor Mesa");
    Serial.println(MotorMesa.currentPosition());
  }

  if (DesceMesa == true && MotorMesa.currentPosition() == 0) {

    DesceMesa = false;
    
  }
}