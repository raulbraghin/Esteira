void FuncPrimeiroPalete(){

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