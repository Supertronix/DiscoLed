void initialiserArcEnCiel(DiscoLed * discoled)
{
  
}

bool animerArcEnCiel(DiscoLed * discoled)
{
  Serial.print("animerArcEnCiel() ");
  moment = millis() >> 4;
  for(int position = 0; position < NOMBRE; position++)
  {
    uint8_t p = moment-position*8;
    discoled->pixels[position] = FabriqueLed::convertirHSV( (uint32_t)p * 359 / 256, 255, 255);
  }
  discoled->afficher(discoled->pixels);
}

