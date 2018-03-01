void initialiserBandeGauche()
{
  Serial.begin(9600);
  Serial.println("initialiserBandeGauche()");
/*
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->preparer = preparerArcEnCiel;
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->liberer = libererArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleGauche.ajouterAnimation(animationArcEnCiel);
  */
  Animation * animationAlternance = new Animation();
  animationAlternance->preparer = preparerAlternance;
  animationAlternance->animer = animerAlternance;
  animationAlternance->liberer = libererAlternance;
  animationAlternance->duree = 400;
  spectacleGauche.ajouterAnimation(animationAlternance);  
}

void bouclerBandeGauche()
{
  Serial.println("bouclerBandeGauche()");  
  spectacleGauche.jouerAnimation();
  delay(1);   
}
