void FuncInicializaLCD() {

  //Mostra a versão do software
  lcd.setCursor(0, 0);
  lcd.print("     ESTEIRA    ");
  lcd.setCursor(5, 1);
  lcd.print("V. 1.00");

  delay(1000);

  lcd.clear();
}

void FuncLCD() {

  if (EmergAtiva == false && ResetProcesso == false) {

    lcd.setCursor(0, 0);
    lcd.print("    CONTAGEM    ");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(ContPaletes);
    lcd.print(" PALETES  ");
  }


  if (EmergAtiva == true) {

    lcd.setCursor(0, 0);
    lcd.print("   EMERGENCIA   ");
  }

  if (ResetProcesso == true) {

    lcd.setCursor(0, 0);
    lcd.print("      RESET     ");
  }
}