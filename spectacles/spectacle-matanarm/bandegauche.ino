void initialiserBandeGauche()
{
  Serial.begin(9600);
  Serial.println("initialiserBandeGauche()");

  initialiserArcEnCiel(&discoledDroit);
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleGauche.ajouterAnimation(animationArcEnCiel);
}

void bouclerBandeGauche()
{
  Serial.println("bouclerBandeGauche()");  
  spectacleGauche.jouerAnimation();
  delay(1);   
}
