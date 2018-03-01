#define DELTA_VAGUE 2
Led * bandeVague;

int momentVagues = 0;

void preparerVagues(DiscoLed* discoled)
{
  bandeVague = discoled->dessinerBandeRayeeDouce(discoled->pixels, COULEUR_ROUGE, COULEUR_BLANC, 5); 
  discoled->pixels = bandeVague;
}


bool animerVagues(DiscoLed* discoled)
{
  if(momentVagues == 0) discoled->pixels = bandeVague;
  momentVagues++;
  
  if(momentVagues%DELTA_VAGUE == 0)
  {
    discoled->pixels = DiscoLed::decalerBande(discoled->pixels, NOMBRE);
  }
  discoled->pixels = bandeVague;
  discoled->afficher(discoled->pixels);
}

void libererVagues(DiscoLed * discoled)
{
  //delete bandeVague;
}

