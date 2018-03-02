#include <DiscoLed.h>

#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacleTeleop(&discoled); 
Spectacle spectacleAutonome(&discoled); 
Spectacle spectacleNiveau(&discoled); 
Spectacle spectacleFlash(&discoled); 
Led couleurAlliance = COULEUR_ROUGE;
uint8_t moment = 0;

void setup() 
{
  Serial.begin(9600);
  
  ///////////////////////////////////////////////////
  //////////////////   NIVEAU   /////////////////////
  ///////////////////////////////////////////////////
  
  Animation * animationNiveau = new Animation();
  animationNiveau->preparer = preparerNiveau;
  animationNiveau->animer = animerNiveau;
  animationNiveau->liberer = libererNiveau;
  animationNiveau->duree = 400;
  spectacleNiveau.ajouterAnimation(animationNiveau);
  
  ///////////////////////////////////////////////////
  //////////////////   FLASH   //////////////////////
  ///////////////////////////////////////////////////

  Animation * animationFlash = new Animation();
  animationFlash->preparer = preparerFlash;
  animationFlash->animer = animerFlash;
  animationFlash->liberer = libererFlash;
  animationFlash->duree = 400;
  spectacleFlash.ajouterAnimation(animationFlash);

  ///////////////////////////////////////////////////
  ////////////////   AUTONOME   /////////////////////
  ///////////////////////////////////////////////////

  Animation * animationVagues = new Animation();
  animationVagues->preparer = preparerVagues;
  animationVagues->animer = animerVagues;
  animationVagues->liberer = libererVagues;
  animationVagues->duree = 100;
  spectacleAutonome.ajouterAnimation(animationVagues);
  
  Animation * animationCollision = new Animation();
  animationCollision->preparer = preparerCollision;
  animationCollision->animer = animerCollision;
  animationCollision->liberer = libererCollision;
  animationCollision->duree = 50;
  spectacleAutonome.ajouterAnimation(animationCollision);
  
  Animation * animationRayures = new Animation();
  animationRayures->preparer = preparerRayures;
  animationRayures->animer = animerRayures;
  animationRayures->liberer = libererRayures;
  animationRayures->duree = 100;
  spectacleAutonome.ajouterAnimation(animationRayures);

  //spectacleAutonome.ajouterAnimation(animationCollision);

  Animation * animationAlternance = new Animation();  
  animationAlternance->preparer = preparerAlternance;  
  animationAlternance->animer = animerAlternance;  
  animationAlternance->liberer = libererAlternance;  
  animationAlternance->duree = 100;  
  spectacleAutonome.ajouterAnimation(animationAlternance);  

  ///////////////////////////////////////////////////
  //////////////////   TELEOP   /////////////////////
  ///////////////////////////////////////////////////

  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->preparer = preparerArcEnCiel;
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->liberer = libererArcEnCiel;
  animationArcEnCiel->duree = 4000;
  spectacleTeleop.ajouterAnimation(animationArcEnCiel);

/*
  Animation * animationVide = new Animation();
  animationVide->preparer = preparerVide;
  animationVide->animer = animerVide;
  animationVide->liberer = libererVide;
  animationVide->duree = 400;
  spectacleTeleop.ajouterAnimation(animationVide);
*/
 }

#define MODE_TELEOP 0
#define MODE_AUTONOME 1
#define MODE_NIVEAU 2
#define MODE_FLASH 3

int mode = MODE_AUTONOME;
int chariot = 0;

#define INDICATEUR_ALLIANCE 5
#define INDICATEUR_FLASH 6
#define INDICATEUR_MODE 7

#define ALLIANCE_ROUGE 1
#define ALLIANCE_BLEUE 0
int valeurFlash = 0;
int valeurAlliance = 0;
int valeurMode = 0;

void loop() 
{
  pinMode(INDICATEUR_ALLIANCE, INPUT);  
  //pinMode(INDICATEUR_FLASH, INPUT);  
  
  //Serial.println("loop()");
  switch(mode)
  {
    case MODE_AUTONOME: spectacleAutonome.jouerAnimation();break;
    case MODE_TELEOP: spectacleTeleop.jouerAnimation();break;
    case MODE_NIVEAU: spectacleNiveau.jouerAnimation();break;
    case MODE_FLASH: spectacleFlash.jouerAnimation();break;
    default: spectacleTeleop.jouerAnimation(); break;
  }
  recevoirCommandeRio();
  delay(1);
}

void recevoirCommandeRio()
{
  Serial.println("recevoirCommandeRio()");

  valeurAlliance = digitalRead(INDICATEUR_ALLIANCE);
  Serial.print("valeur alliance "); Serial.println(valeurAlliance);
  if(valeurAlliance == ALLIANCE_ROUGE) couleurAlliance = COULEUR_ROUGE;
  else couleurAlliance = COULEUR_BLEU;

  valeurMode = digitalRead(INDICATEUR_MODE);
  Serial.print("valeur mode "); Serial.println(valeurMode);
  if(valeurMode) mode = MODE_TELEOP;
  else mode = MODE_AUTONOME;
  
  valeurFlash = digitalRead(INDICATEUR_FLASH);
  Serial.print("valeur flash "); Serial.println(valeurFlash);
  if(valeurFlash) mode = MODE_FLASH;

  switch(mode)
  {
    case MODE_AUTONOME : Serial.println("Mode autonome"); break;
    case MODE_TELEOP : Serial.println("Mode teleop"); break;
    case MODE_FLASH : Serial.println("Mode flash"); break;
    case MODE_NIVEAU : Serial.println("Mode niveau"); break;
  }
}


