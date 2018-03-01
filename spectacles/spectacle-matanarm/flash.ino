void preparerFlash(DiscoLed* discoled)
{
}

bool animerFlash(DiscoLed* discoled)
{  
  //Serial.print("Niveau "); Serial.println(niveau);

  for(int position = 0; position < NOMBRE; position++) 
  {
    discoled->pixels[position] = COULEUR_BLANC;
  }
  discoled->afficher(discoled->pixels);
  delay(100);
  for(int position = 0; position < NOMBRE; position++) 
  {
    discoled->pixels[position] = couleurAlliance;
  }
  discoled->afficher(discoled->pixels);
  delay(100);
}

void libererFlash(DiscoLed* discoled)
{
  
}

