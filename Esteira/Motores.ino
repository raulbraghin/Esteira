void FuncEsteira() {

  //INICIO DO PROCESSO

  if (SensorInicio == false && BtStart == false && LigaEsteira == false) {
    LigaEsteira = true;
  }

  if (LigaEsteira == true) {  //LIGA MOTOR DA ESTEIRA
    MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();

    Serial.print("POS Motor Esteira");
    Serial.println(MotorEsteira.currentPosition());
  }

  //FINALIZA PROCESSO

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

  if (ContPaletes == 0 && SensorMesa == false && LigaEsteira == false && LiberaMesaPrimeiroPalete == false && dseg1 >= 5) {  //SE FOR O PRIMEIRO PALETE

    AcioGarrasPrimPalete = true;
  }


  if (AcioGarrasPrimPalete == true) {

    Serial.println("FuncAbreGarras Linha 47");

    MotorGarraE.move(-PassosGarra);
    MotorGarraE.runToPosition();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraD.move(PassosGarra);
    MotorGarraD.runToPosition();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());
  }


  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == -PassosGarra && LiberaMesaPrimeiroPalete == false && LiberaFecharGarras == false) {

    Serial.println("FuncAbreGarra Linha 66");

    LiberaMesaPrimeiroPalete = true;

    AcioGarrasPrimPalete = false;

    dseg2 = 0;
  }



  if (ContPaletes > 0 && SensorMesa == false && LigaEsteira == false && LiberaMesaNPalete == false && LiberaFecharGarras == false && dseg1 >= 5) {  //SE NÃO FOR O PRIMEIRO PALETE

    LiberaMesaNPalete = true;  //Libera mesa para começar a subir

    Serial.println("Libera N Palete Linha 81");

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

    Serial.println("MoveGarra Linha 102");
  }

  if (MotorGarraD.currentPosition() == PassosGarra && MotorGarraE.currentPosition() == -PassosGarra && LiberaMesaNPalete == true) {

    SobeMesa2Estagio = true;

    Serial.println("SobeMesa2Estagio Linha 109");
  }
}


//**********************************************************************************
void FuncSobeMesa() {

  if (LiberaMesaPrimeiroPalete == true && dseg2 >= 5) {  //Tempo entre a aberturada garra e o inicio do movimento da mesa em décimos de segundos
    SobeMesa = true;

    Serial.println("SobeMesa = true Linha 113");
  }


  if (SobeMesa == true && LiberaMesaPrimeiroPalete == true) {  //ACIONA MOTOR DA MESA QUANDO NÃO TEM NENHUM PALETE NA GARRA

    MotorMesa.move(PassosGarraVazia);
    MotorMesa.runToPosition();

    Serial.print("POS Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("SobeMesaVazia");
  }


  if (MotorMesa.currentPosition() == PassosGarraVazia && LiberaMesaPrimeiroPalete == true && LiberaFecharGarras == false) {  //FINALIZA MOVIMENTO DO MOTOR DA MESA
    SobeMesa = false;

    MotorMesa.setCurrentPosition(0);

    LiberaFecharGarras = true;

    LiberaMesaPrimeiroPalete = false;

    MotorGarraD.setCurrentPosition(0);

    MotorGarraE.setCurrentPosition(0);

    dseg3 = 0;

    Serial.println("Finaliza Movimento Mesa e Conta Palete - LINHA 145");

    ContPaletes++;
  }


  if (LiberaMesaNPalete == true && SobeMesa == false && dseg2 >= 5) {
    SobeMesa = true;

    Serial.println("SobeMesa = true Linha 160");
  }


  if (SobeMesa == true && LiberaMesaNPalete == true) {  //ACIONA MOTOR DA MESA QUANDO JÁ TEM PALETE NA GARRA
    MotorMesa.move(PassosGarraCheia);
    MotorMesa.runToPosition();

    Serial.print("POS Mesa ");
    Serial.println(MotorMesa.currentPosition());

    MotorGarraD.setCurrentPosition(0);
    MotorGarraE.setCurrentPosition(0);

    Serial.println("SobeMesaCheia Para Npalete Linha 171");
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

    MotorGarraD.move(-PassosGarra);
    MotorGarraD.runToPosition();

    Serial.print("POS Motor Garra D");
    Serial.println(MotorGarraD.currentPosition());

    MotorGarraE.move(PassosGarra);
    MotorGarraE.runToPosition();

    Serial.print("POS Motor Garra E");
    Serial.println(MotorGarraE.currentPosition());

    Serial.println("Fechando Garras Linha 212");
  }

  if (LiberaFecharGarras == true && MotorGarraD.currentPosition() == -PassosGarra && MotorGarraE.currentPosition() == PassosGarra) {

    AcioGarrasPrimPalete = false;
    LiberaMesaPrimeiroPalete = false;
    LiberaFecharGarras = false;

    DesceMesa = true;

    Serial.println("Garras fechadas - Linha 225");

    dseg4++;
  }
}

//************************************************************************
void FuncDesceMesa() {

  if (DesceMesa == true && dseg4 >= 5) {

    MotorMesa.move(-PassosGarraVazia);
    MotorMesa.runToPosition();


    Serial.print("POS Motor Mesa ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("Desce Mesa Linha 243");
  }

  if (DesceMesa == true && MotorMesa.currentPosition() == -PassosGarraVazia) {

    DesceMesa = false;

    MotorMesa.setCurrentPosition(0);

    Serial.println("Finaliza Desce Mesa Linha 252");

    Serial.print("BTStart ");
    Serial.println(BtStart);
    Serial.print("Entrada Start ");
    Serial.println(digitalRead(Start));
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


//************************************************************************
void FuncEmergencia() {

  MotorEsteira.stop();
  MotorGarraD.stop();
  MotorGarraE.stop();
  MotorMesa.stop();

  LigaEsteira = false;
  LiberaMesaPrimeiroPalete = false;
  LiberaMesaNPalete = false;
  LiberaFecharGarras = false;
  DesceMesa = false;
  SobeMesa = false;
  SobeMesa2Estagio = false;
  AcioGarrasNPalete = false;
  AcioGarrasPrimPalete = false;
  FinalizaProcesso = false;


  Serial.println("FuncEmergencia");
}