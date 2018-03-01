
void initialiserBandeDroite()
{
  //Serial.begin(9600);
  //Serial.println("initialiserBandeDroite()");

  Animation * animationVagues = new Animation();
  animationVagues->preparer = preparerVagues;
  animationVagues->animer = animerVagues;
  animationVagues->liberer = libererVagues;
  animationVagues->duree = 400;
  spectacleDroit.ajouterAnimation(animationVagues);
  
/*
  initialiserArcEnCiel(&discoledDroit);
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleDroit.ajouterAnimation(animationArcEnCiel);

  initialiserCollision(&discoledDroit);
  Animation * animationCollision = new Animation();
  animationCollision->animer = animerCollision;
  animationCollision->duree = 400;
  spectacleDroit.ajouterAnimation(animationCollision);
  */
}

void bouclerBandeDroite()
{
  //Serial.println("bouclerBandeDroite()");
  spectacleDroit.jouerAnimation();
  delay(1);
}
