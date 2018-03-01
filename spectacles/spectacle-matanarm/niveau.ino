void preparerNiveau(DiscoLed* discoled)
{
  discoled->blanchir();
}
int niveau = 5;
bool animerNiveau(DiscoLed* discoled)
{  
  niveau = convertirChariotNiveau(chariot);
  //Serial.print("Niveau "); Serial.println(niveau);

  for(int position = 0; position < niveau; position++) // on pourrait optimiser et juste dessiner la derniere sauf que si le niveau monte trop vite
  {
    discoled->pixels[position] = couleurAlliance;
  }
  discoled->afficher(discoled->pixels);
}

void libererNiveau(DiscoLed* discoled)
{
  
}

#define FACTEUR_NIVEAU 0.5

int convertirChariotNiveau(int chariot)
{
  niveau = (int)(FACTEUR_NIVEAU*chariot);
  if(niveau >= NOMBRE) niveau = NOMBRE - 1;
  return niveau;
}
