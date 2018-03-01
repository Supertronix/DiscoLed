bool animerChromatisme()
{
  Serial.print("animerChromatisme() ");
  moment = millis() >> 4;
  for(int position = 0; position < NOMBRE; position++)
  {
    uint8_t p = moment-position*8;
    int h = (uint32_t)p * 359 / 256;
    //pixels[position] = FabriqueLed::convertirHSV( h, 128, 255);
  }
  //discoled.afficher(pixels);
}

