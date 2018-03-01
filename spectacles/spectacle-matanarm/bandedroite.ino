
void initialiserBandeDroite()
{
  //Serial.begin(9600);
  //Serial.println("initialiserBandeDroite()");

  initialiserArcEnCiel();
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleDroit.ajouterAnimation(animationArcEnCiel);
}

void bouclerBandeDroite()
{
  //Serial.println("bouclerBandeDroite()");
  spectacleDroit.jouerAnimation();
  delay(10);

}
