#include <DiscoLed.h>
#include <Wire.h>

#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique
uint8_t moment;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(recevoirCommandeRio);
  

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

  Animation * animationCollision = new Animation();
  animationCollision->preparer = preparerCollision;
  animationCollision->animer = animerCollision;
  animationCollision->liberer = libererCollision;
  animationCollision->duree = 400;
  //spectacle.ajouterAnimation(animationCollision);
  
  Animation * animationRayures = new Animation();
  animationRayures->preparer = preparerRayures;
  animationRayures->animer = animerRayures;
  animationRayures->liberer = libererRayures;
  animationRayures->duree = 400;
  spectacle.ajouterAnimation(animationRayures);
 }

void loop() 
{
  //Serial.println("bouclerBandeDroite()");
  spectacle.jouerAnimation();
  delay(1);
}

void recevoirCommandeRio(int nombre)
{
  Serial.println("recevoirCommandeRio()");
  if(Wire.available())
  {
    char lettre = Wire.read();
    Serial.println(lettre);
  }
}



