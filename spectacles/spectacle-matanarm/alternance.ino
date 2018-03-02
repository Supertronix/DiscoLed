Led * bandeCouleurBlanc;
Led * bandeBlancCouleur;

void preparerAlternance(DiscoLed * discoled)
{
  //delete discoled->pixels;
  bandeCouleurBlanc = discoled->dessinerBandeCouleurAlternee(discoled->pixels, couleurAlliance, COULEUR_BLANC); 
  bandeBlancCouleur = discoled->dessinerBandeCouleurAlternee(discoled->pixels2, COULEUR_BLANC, couleurAlliance); 
}

bool animerAlternance(DiscoLed * discoled)
{
  moment = millis() >> 4;
  if(moment%40 > 20)
    discoled->pixels = bandeBlancCouleur;
  else 
    discoled->pixels = bandeCouleurBlanc;
  discoled->afficher(discoled->pixels);
  //if(positionDansAnimation%2 == 0) 
}

void libererAlternance(DiscoLed * discoled)
{
  //delete bandeCouleurBlanc;
  //discoled->pixels = bandeBlancCouleur;
}
