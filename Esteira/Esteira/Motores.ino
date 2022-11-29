void FuncEsteira() {

  if (SensorInicio == false && BtStart == false) {
    MotorEsteira.move(PassosEsteira);
    MotorEsteira.run();
  }

  if (SensorMesa == false) {

    MotorEsteira.stop();
    dsec1 = 0;
  }

  if (SensorMesa == false && dsec1 >= TPIntProc1) {

    if (ContPaletes == 0) {
      MotorMesa.move(PassosMesaVazia);
    } else {
      MotorMesa.move(PassosMesaCheia);
    }

    MotorMesa.run();
  }
}