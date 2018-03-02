//Led couleurBleuQuebec = {.rouge = 0, .vert = 92, .bleu = 22};
Led * bandeBleuBlanc;
Led * bandeBlancBleu;

void preparerAlternance(DiscoLed * discoled)
{
  //delete discoled->pixels;
  bandeBleuBlanc = discoled->dessinerBandeCouleurAlternee(discoled->pixels, couleurAlliance, COULEUR_BLANC); 
  bandeBlancBleu = discoled->dessinerBandeCouleurAlternee(discoled->pixels2, COULEUR_BLANC, couleurAlliance); 
}

bool animerAlternance(DiscoLed * discoled)
{
  moment = millis() >> 4;
  if(moment%40 > 20)
    discoled->pixels = bandeBlancBleu;
  else 
    discoled->pixels = bandeBleuBlanc;
  discoled->afficher(discoled->pixels);
  //if(positionDansAnimation%2 == 0) 
}

void libererAlternance(DiscoLed * discoled)
{
  //delete bandeBleuBlanc;
  //discoled->pixels = bandeBlancBleu;
}
