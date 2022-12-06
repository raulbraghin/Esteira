void FuncPrimeiroPalete() {

  //INICIO DO PROCESSO



  if (SensorInicio == false && BtStart == false && LigaEsteira == false && Etapa1 == false) {
    LigaEsteira = true;

    Serial.println("Inicia Primeiro Palete");
  }

  if (LigaEsteira == true) {  //LIGA MOTOR DA ESTEIRA

    MotorEsteira.set(Horario, RPMEsteira, PassosPorVolta);

    while (SensorMesa == true) {

      MotorEsteira.run();

      SensorMesa = digitalRead(Mesa);
    }
  }


  //FINALIZA PROCESSO

  if (SensorMesa == false && LigaEsteira == true) {  //PARA MOTOR DA ESTEIRA

    LigaEsteira = false;

    dseg1 = 0;

    Serial.println("FuncEsteira Para esteira");

    Etapa1 = true;
  }


  //*************Abre Garra**************************
  if (Etapa1 == true && Etapa2 == false && SensorMesa == false && LigaEsteira == false && dseg1 >= 5) {

    Serial.println("FuncAbreGarras Linha 39");

    MotorGarraE.set(Antihorario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Horario, RPMGarras, PassosPorVolta);

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();

      Serial.println(" Garra D Horário");
      Serial.println(" Garra E AntiHorário");
      Serial.print(i);
    }
  }

  if (i == PassosGarra && Etapa1 == true && Etapa2 == false) {

    Serial.println("FuncAbreGarra Linha 59");

    dseg2 = 0;

    Etapa2 = true;
  }


  //*************levanta mesa*************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {


    MotorMesa.set(Horario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();

      Serial.println("Levanta Mesa Horário");
      Serial.print(i);
    }

    Serial.println("SobeMesaVazia");
  }

  if (Etapa2 == true && Etapa3 == false && i == PassosGarraVazia) {


    dseg3 = 0;

    Etapa3 = true;

    Serial.println("Finaliza Movimento Mesa linha 91");
  }

  //**************** Fecha Garra *******************

  if (Etapa3 == true && Etapa4 == false && dseg3 >= 5) {


    MotorGarraE.set(Horario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Antihorario, RPMGarras, PassosPorVolta);

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();

      Serial.println("Horário");
      Serial.print(i);
    }

    Serial.println("Fechando Garras Linha 113");
  }

  if (Etapa3 == true && Etapa4 == false && i == PassosGarra) {


    Serial.println("Garras fechadas - Linha 114");

    dseg4 = 0;

    Etapa4 = true;
  }

  //**************** abaixa mesa ***************************

  if (Etapa4 == true && dseg4 >= 5) {


    MotorMesa.set(Antihorario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();

      Serial.println("Horário");
      Serial.print(i);
    }
    Serial.println("Desce Mesa Linha 140");
  }

  if (i == PassosGarraVazia && Etapa4 == true && ContPaletes == 0) {

    ContPaletes++;

    Etapa1 = false;
    Etapa2 = false;
    Etapa3 = false;
    Etapa4 = false;

    Serial.println("Finaliza primeiro palete");
  }
}