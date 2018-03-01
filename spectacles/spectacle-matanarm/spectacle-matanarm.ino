#include <DiscoLed.h>

#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique
uint8_t moment;

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
  spectacle.ajouterAnimation(animationVagues);
  
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->preparer = preparerArcEnCiel;
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->liberer = libererArcEnCiel;
  animationArcEnCiel->duree = 400;
  spectacle.ajouterAnimation(animationArcEnCiel);

  Animation * animationAlternance = new Animation();  
  animationAlternance->preparer = preparerAlternance;  
  animationAlternance->animer = animerAlternance;  
  animationAlternance->liberer = libererAlternance;  
  animationAlternance->duree = 400;  
  spectacle.ajouterAnimation(animationAlternance);  

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
  spectacle.jouerAnimation();
  delay(1);
}



