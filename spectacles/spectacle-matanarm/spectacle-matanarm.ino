#include <DiscoLed.h>

#define PIN_DROITE 3
#define HORLOGE_DROITE 4
#define NOMBRE 67

DiscoLed discoledDroit(NOMBRE, PIN_DROITE, HORLOGE_DROITE);
Spectacle spectacleDroit(&discoledDroit); // peut-etre plutot memoire dynamique

uint8_t moment;
DiscoLed& discoled = discoledDroit;

void setup() 
{
  Serial.begin(9600);
  //Serial.begin(9600);
  //Serial.println("initialiserBandeDroite()");

  Animation * animationVagues = new Animation();
  animationVagues->preparer = preparerVagues;
  animationVagues->animer = animerVagues;
  animationVagues->liberer = libererVagues;
  animationVagues->duree = 400;
  spectacleDroit.ajouterAnimation(animationVagues);
  
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->preparer = preparerArcEnCiel;
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->liberer = libererArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacleDroit.ajouterAnimation(animationArcEnCiel);
/*
  initialiserCollision(&discoledDroit);
  Animation * animationCollision = new Animation();
  animationCollision->animer = animerCollision;
  animationCollision->duree = 400;
  spectacleDroit.ajouterAnimation(animationCollision);
  */
}


void loop() 
{
  //Serial.println("bouclerBandeDroite()");
  spectacleDroit.jouerAnimation();
  delay(1);
}



