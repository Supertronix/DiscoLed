void initialiserAlternance()
{
  bandeBleuBlanc = discoled.creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC); 
  bandeBlancBleu = discoled.creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec); 
}

bool animerAlternance()
{
  moment = millis() >> 4;
  if(moment%40 > 20)
    pixels = bandeBlancBleu;
  else 
    pixels = bandeBleuBlanc;
  discoled.afficher(pixels);
  //if(positionDansAnimation%2 == 0) 
}

