bool animerArcEnCiel()
{
  Serial.print("animerArcEnCiel() ");
  moment = millis() >> 4;
  for(int position = 0; position < NOMBRE; position++)
  {
    uint8_t p = moment-position*8;
    pixels[position] = FabriqueLed::convertirHSV( (uint32_t)p * 359 / 256, 255, 255);
  }
  discoled.afficher(pixels);
}

