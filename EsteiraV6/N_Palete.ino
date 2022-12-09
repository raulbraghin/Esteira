void FuncNPaletes() {

  //INICIO DO PROCESSO




  if (SensorInicio == true && BtStart == false && LigaEsteira == false && Etapa1 == false) {

    LigaEsteira = true;

    Serial.println("Inicia N Palete");
  }

  if (LigaEsteira == true) {  //LIGA MOTOR DA ESTEIRA

    MotorEsteira.set(Horario, RPMEsteira, PassosPorVolta);

    while (SensorMesa == false) {

      MotorEsteira.run();

      SensorMesa = digitalRead(Mesa);
    }
  }

  //FINALIZA PROCESSO

  if (SensorMesa == true && LigaEsteira == true /*&& FinalizaProcesso == false*/) {  //PARA MOTOR DA ESTEIRA

    LigaEsteira = false;

    dseg1 = 0;

    Serial.println("FuncEsteira Para esteira");

    Etapa1 = true;
  }


  //*************levanta mesa*************************
  if (Etapa1 == true && Etapa2 == false && SensorMesa == true && LigaEsteira == false && dseg1 >= 5) {

    MotorMesa.set(Horario, RPMMesa, PassosPorVolta);

    

    for (i = 0; i < PassosGarraCheia; i++) {
      MotorMesa.run();

      //Serial.println("Horário");
      //Serial.print(i);
    }

    Serial.println("SobeMesaCheia");
  }

  if (Etapa1 == true && Etapa2 == false && i == PassosGarraCheia) {

    dseg2 = 0;

    Etapa2 = true;

    Serial.println("Finaliza Movimento Mesa linha 57");
  }

  //*************Abre Garra**************************
  if (Etapa2 == true && Etapa3 == false && dseg2 >= 5) {

    Serial.println("FuncAbreGarras Linha 62");

    MotorGarraE.set(Antihorario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Horario, RPMGarras, PassosPorVolta);

    

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();

      //Serial.println("Horário");
      //Serial.print(i);
    }
  }

  if (i == PassosGarra && Etapa3 == false) {

    Serial.println("FuncAbreGarra Linha 79");

    dseg3 = 0;

    Etapa3 = true;
  }


  //********************* sobe restante da mesa ************************

  if (Etapa3 == true && Etapa4 == false && dseg3 >= 5) {


    PassosRestantes = PassosGarraVazia - PassosGarraCheia;

    MotorMesa.set(Horario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosRestantes; i++) {
      MotorMesa.run();

      //Serial.println("Horário");
      //Serial.print(i);
    }


    Serial.println("SobeMesaCheia Para Npalete Linha 108");
  }

  if (Etapa3 == true && i == PassosRestantes && Etapa4 == false) {

    Serial.println("Linha 104");

    dseg4 = 0;

    Etapa4 = true;
  }

  //*********************fecha garra *********************

  if (Etapa4 == true && Etapa5 == false && dseg4 >= 5) {


    MotorGarraE.set(Horario, RPMGarras, PassosPorVolta);

    MotorGarraD.set(Antihorario, RPMGarras, PassosPorVolta);

    for (i = 0; i < PassosGarra; i++) {
      MotorGarraE.run();

      MotorGarraD.run();

      //Serial.println("Horário");
      //Serial.print(i);
    }

    Serial.println("Fechando Garras Linha 135");
  }

  if (Etapa4 == true && Etapa5 == false && i == PassosGarra) {


    Serial.println("Garras fechadas - Linha 141");

    dseg5 = 0;

    Etapa5 = true;
  }




  //**************** abaixa mesa ***************************
  if (Etapa5 == true && dseg5 >= 5) {


    MotorMesa.set(Antihorario, RPMMesa, PassosPorVolta);

    for (i = 0; i < PassosGarraVazia; i++) {
      MotorMesa.run();

      //Serial.println("Horário");
      //Serial.print(i);
    }
    Serial.println("Desce Mesa Linha 164");
  }

  if (i == PassosGarraVazia && Etapa5 == true) {

    ContPaletes++;

    Etapa1 = false;
    Etapa2 = false;
    Etapa3 = false;
    Etapa4 = false;
    Etapa5 = false;

    Serial.println("Finaliza N palete");
  }
}