#include <DiscoLed.h>
#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

Led * pixels;
DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique

uint8_t moment;

void setup() 
{
  Serial.begin(9600);
  pixels = new Led[NOMBRE];


  initialiserVagues();
  Animation * animationVagues = new Animation();
  animationVagues->animer = animerVagues;
  animationVagues->duree = 400;
  spectacle.ajouterAnimation(animationVagues);
  
  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 100;
  spectacle.ajouterAnimation(animationArcEnCiel);

/*
  initialiserRayures();
  Animation * animationRayures = new Animation();
  animationRayures->animer = animerRayures;
  animationRayures->duree = 200;
  spectacle.ajouterAnimation(animationRayures);
*/

/* 
  
  initialiserAlternance();
  Animation * animationAlternance = new Animation();
  animationAlternance->animer = animerAlternance;
  animationAlternance->duree = 100;
  spectacle.ajouterAnimation(animationAlternance);*/
}


void loop() 
{  
  spectacle.jouerAnimation();
}



