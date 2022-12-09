void FuncFinaliza() {



  //*************levanta mesa*************************
  if (Etapa1 == false && ContPaletes == EmpilhamentoMaximo) {

    Serial.println("Finalizacao");

    Serial.println("LEVANTANDO MESA");


    MotorMesa.set(Horario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();
    }
  }


  if (i == PassosGarraVazia && Etapa1 == false) {

    Etapa1 = true;

    dseg1 = 0;
  }

  //*************Abre Garra**************************
  if (Etapa1 == true && Etapa2 == false && dseg1 >= 5) {

    Serial.println("ABRINDO GARRA");

    MotorGarraE.set(Antihorario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Horario, RPMGarras, PassosPorVolta);

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();
    }
  }

  if (i == PassosGarra && Etapa2 == false) {

    dseg2 = 0;

    Etapa2 = true;
  }


  //**************** abaixa mesa ***************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {

    Serial.println("ABAIXANDO MESA");

    MotorMesa.set(Antihorario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();
    }
  }


  if (i == PassosGarraVazia && Etapa2 == true && Etapa3 == false) {

    dseg3 = 0;

    Etapa3 = true;
  }


  //**************** liga esteira *******************

  if (Etapa3 == true && LigaEsteira == false && dseg3 >= 5) {

    Serial.println("LIGANDO ESTEIRA");

    LigaEsteira = true;
  }

  if (LigaEsteira = true && Etapa3 == true) {


    MotorEsteira.set(Horario, RPMEsteira, PassosPorVolta);

    while (SensorFim == false && LigaEsteira == true) {

      MotorEsteira.run();

      SensorFim = digitalRead(Fim);
    }
  }

  if (SensorFim == true && LigaEsteira == true) {


    LigaEsteira = false;

    MotorGarraE.set(Horario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Antihorario, RPMGarras, PassosPorVolta);

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();
    }

    Etapa1 = false;
    Etapa2 = false;
    Etapa3 = false;
    Etapa4 = false;
    Etapa5 = false;

    i = 0;

    ContPaletes = 0;

    Serial.println("FINALIZA PROCESSO");
  }
}