void FuncBotoes() {
  //Leitura das entradas digitais
  BtStart = digitalRead(Start);
/*  BtReset = digitalRead(Reset);
  BtEmergencia = digitalRead(Emergencia);


  if (BtEmergencia == false && EmergAtiva == false) {
    EmergAtiva = true;
    Serial.println("Botão Emergencia Pressionado");
    lcd.clear();
  }


  if (BtReset == false && ResetProcesso == false) {
    ResetProcesso = true;
    Serial.println("Botão Reset Pressionado");
    lcd.clear();
  }*/


}

void FuncSensores(){

//Leitura dos Sensores
SensorInicio = digitalRead(Inicio);
SensorMesa = digitalRead(Mesa);
SensorFim = digitalRead(Fim);



}