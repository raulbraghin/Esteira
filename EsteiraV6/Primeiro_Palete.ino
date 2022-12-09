void FuncPrimeiroPalete() {

  //INICIO DO PROCESSO



  if (SensorInicio == true && BtStart == false && LigaEsteira == false && Etapa1 == false) {
    LigaEsteira = true;

    Serial.println("Inicia Primeiro Palete");

    Serial.println("LIGA ESTEIRA");
  }

  if (LigaEsteira == true) {  //LIGA MOTOR DA ESTEIRA

    MotorEsteira.set(Horario, RPMEsteira, PassosPorVolta);

    while (SensorMesa == false) {

      MotorEsteira.run();

      SensorMesa = digitalRead(Mesa);
    }
  }


  //FINALIZA PROCESSO

  if (SensorMesa == true && LigaEsteira == true) {  //PARA MOTOR DA ESTEIRA

    LigaEsteira = false;

    dseg1 = 0;

    Etapa1 = true;
  }


  //*************Abre Garra**************************
  if (Etapa1 == true && Etapa2 == false && SensorMesa == true && LigaEsteira == false && dseg1 >= 5) {

    Serial.println("ABRINDO GARRA");

    MotorGarraE.set(Antihorario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Horario, RPMGarras, PassosPorVolta);



    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();
    }
  }

  if (i == PassosGarra && Etapa1 == true && Etapa2 == false) {


    dseg2 = 0;

    Etapa2 = true;
  }


  //*************levanta mesa*************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {

    Serial.println("LEVANTA MESA");

    MotorMesa.set(Horario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();
    }
  }

  if (Etapa2 == true && Etapa3 == false && i == PassosGarraVazia) {


    dseg3 = 0;

    Etapa3 = true;
  }

  //**************** Fecha Garra *******************

  if (Etapa3 == true && Etapa4 == false && dseg3 >= 5) {

    Serial.println("FECHANDO GARRA");


    MotorGarraE.set(Horario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Antihorario, RPMGarras, PassosPorVolta);

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();
    }
  }

  if (Etapa3 == true && Etapa4 == false && i == PassosGarra) {

    dseg4 = 0;

    Etapa4 = true;
  }

  //**************** abaixa mesa ***************************

  if (Etapa4 == true && dseg4 >= 5) {

    Serial.println("ABAIXANDO MESA");


    MotorMesa.set(Antihorario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();
    }
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