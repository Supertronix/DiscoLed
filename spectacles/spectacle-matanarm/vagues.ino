Led * bandeVague;

int momentVagues = 0;
int deltaVagues = 2;

void initialiserVagues(DiscoLed* discoled)
{
  bandeVague = discoled->creerBandeRayeeDouce(COULEUR_ROUGE, COULEUR_BLANC, 5); 
  discoled->pixels = bandeVague;
}


bool animerVagues(DiscoLed* discoled)
{
  if(momentVagues == 0) discoled->pixels = bandeVague;
  momentVagues++;
  
  if(momentVagues%deltaVagues == 0)
  {
    discoled->pixels = DiscoLed::decalerBande(discoled->pixels, NOMBRE);
  }
  discoled->pixels = bandeVague;
  discoled->afficher(discoled->pixels);  
}



