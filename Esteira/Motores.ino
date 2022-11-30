void FuncEsteira() {

  if (SensorInicio == false && BtStart == false && LigaEsteira == false) {
    LigaEsteira = true;
  }

  if (LigaEsteira == true) {
    MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();

    Serial.print("POS ");
    Serial.println(MotorEsteira.currentPosition());
  }


  if (SensorMesa == false && LigaEsteira == true) {

    LigaEsteira = false;

    MotorEsteira.stop();
    MotorEsteira.setCurrentPosition(0);

    dseg1 = 0;

    Serial.println("FuncEsteira Para esteira");
    Serial.print("dseg1 ");
    Serial.println(dseg1);
  }
}

void FuncMesa() {

  if (SensorMesa == false && LigaEsteira == false && dseg1 >= 5) {  //Tempo entre a parada da esteira e o inicio do movimento da mesa em décimos de segundos
    LigaMesa = true;

    Serial.println("LigaMesa = true");
  }

  if (LigaMesa == true && ContPaletes == 0) {

    MotorMesa.move(PassosMesaVazia);
    MotorMesa.run();

    Serial.print("POS ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("LigaMesaVazia");


  } else if (LigaMesa == true && ContPaletes != 0) {
    MotorMesa.move(PassosMesaCheia);
    MotorMesa.run();

    Serial.print("POS ");
    Serial.println(MotorMesa.currentPosition());

    Serial.println("LigaMesaCheia");
  }

  if (MotorMesa.currentPosition() == PassosMesaVazia && ContPaletes == 0){
    LigaMesa = false;

    MotorMesa.setCurrentPosition(0);

    Serial.println("Para Mesa");
  }


  if (MotorMesa.currentPosition() == PassosMesaCheia && ContPaletes != 0){
    LigaMesa = false;

    MotorMesa.setCurrentPosition(0);
    
    Serial.println("Para Mesa");
  }

  ContPaletes++;

}