void FuncEsteira(){

if (SensorInicio == false && BtStart == false){
  MotorEsteira.move(PassosEsteira);
  MotorEsteira.run();
}

if (SensorMesa == false){

MotorEsteira.stop();


}





}