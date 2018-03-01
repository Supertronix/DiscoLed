
void initialiserBandeDroite()
{
  //Serial.begin(9600);
  //Serial.println("initialiserBandeDroite()");

/*
  initialiserArcEnCiel();
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleDroit.ajouterAnimation(animationArcEnCiel);
  */

  initialiserCollision(&discoledDroit);
  Animation * animationCollision = new Animation();
  animationCollision->animer = animerCollision;
  animationCollision->duree = 400;
  spectacleDroit.ajouterAnimation(animationCollision);
  
}

void bouclerBandeDroite()
{
  //Serial.println("bouclerBandeDroite()");
  spectacleDroit.jouerAnimation();
  delay(10);

}
