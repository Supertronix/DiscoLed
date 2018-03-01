Led * bandeVague;

int momentVagues = 0;
int deltaVagues = 5;

void initialiserVagues()
{
  bandeVague = discoled.creerBandeRayeeDouce(COULEUR_ROUGE, COULEUR_BLANC, 5); 
  pixels = bandeVague;
}


bool animerVagues()
{
  if(momentVagues == 0)   pixels = bandeVague;
  momentVagues++;
  
  if(momentVagues%deltaVagues == 0)
  {
    pixels = DiscoLed::decalerBande(pixels, NOMBRE);
  }
  pixels = bandeVague;
  discoled.afficher(pixels);  
}



