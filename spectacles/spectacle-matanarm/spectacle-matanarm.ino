#include <DiscoLed.h>
#include <Wire.h>

#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); 
Spectacle spectacleNiveau(&discoled); 
uint8_t moment = 0;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(recevoirCommandeRio);

  Animation * animationNiveau = new Animation();
  animationNiveau->preparer = preparerNiveau;
  animationNiveau->animer = animerNiveau;
  animationNiveau->liberer = libererNiveau;
  animationNiveau->duree = 400;
  spectacleNiveau.ajouterAnimation(animationNiveau);

/*
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
  */
 }

#define MODE_NORMAL 0
#define MODE_NIVEAU 1
#define MODE_FLASH 2

int mode = MODE_NIVEAU;
int chariot = 0;

void loop() 
{
  //Serial.println("loop()");
  moment++; 
  //if(moment%2 == 0) 
  chariot++;  // simulation de reception
  //Serial.print("chariot "); Serial.println(chariot);
  
  switch(mode)
  {
    case MODE_NORMAL : spectacle.jouerAnimation(); break;
    case MODE_NIVEAU : spectacleNiveau.jouerAnimation(); break;
    //case MODE_FLASH : spectacleFlash.jouerAnimation(); break;
    default: spectacle.jouerAnimation(); break;
  }
  
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


