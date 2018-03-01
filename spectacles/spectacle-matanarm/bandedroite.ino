
void initialiserBandeDroite()
{
  //Serial.begin(9600);
  //Serial.println("initialiserBandeDroite()");

  initialiserVagues(&discoledDroit);
  Animation * animationVagues = new Animation();
  animationVagues->animer = animerVagues;
  animationVagues->duree = 400;
  spectacleDroit.ajouterAnimation(animationVagues);

/*
  initialiserCollision(&discoledDroit);
  Animation * animationCollision = new Animation();
  animationCollision->animer = animerCollision;
  animationCollision->duree = 400;
  spectacleDroit.ajouterAnimation(animationCollision);
  
  initialiserArcEnCiel(&discoledDroit);
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleDroit.ajouterAnimation(animationArcEnCiel);

  */
}

void bouclerBandeDroite()
{
  //Serial.println("bouclerBandeDroite()");
  spectacleDroit.jouerAnimation();
  delay(1);
}
