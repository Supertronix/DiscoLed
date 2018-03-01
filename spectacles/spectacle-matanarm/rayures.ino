Led * bandeBlancRouge;
#define DELTA_RAYURES 2
int momentRayures = 0;

void preparerRayures(DiscoLed * discoled)
{
  discoled->pixels = discoled->dessinerBandeRayee(discoled->pixels, COULEUR_ROUGE, COULEUR_BLANC, 5); 
}


bool animerRayures(DiscoLed * discoled)
{
  momentRayures++;
  
  if(momentRayures%DELTA_RAYURES == 0)
    discoled->pixels = DiscoLed::decalerBande(discoled->pixels, NOMBRE);
  
  discoled->afficher(discoled->pixels);  
}

void libererRayures(DiscoLed * discoled)
{
  //delete bandeBlancRouge;
}

Led * decalerBande(Led * bande)
{
  Led temporaire = bande[0];
  for(int position; position < NOMBRE-1; position++)
  {
    bande[position] = bande[position+1];
  }
  bande[NOMBRE-1] = temporaire;
  return bande;
}

