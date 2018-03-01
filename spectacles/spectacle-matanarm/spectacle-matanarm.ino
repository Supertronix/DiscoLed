#include <DiscoLed.h>
#include <Scheduler.h>

#define DROIT 0
#define GAUCHE 1

#define PIN_DROITE 3
#define HORLOGE_DROITE 4
#define PIN_GAUCHE 2
#define HORLOGE_GAUCHE 5
#define NOMBRE 67

DiscoLed discoledDroit(NOMBRE, PIN_DROITE, HORLOGE_DROITE);
DiscoLed discoledGauche(NOMBRE, PIN_GAUCHE, HORLOGE_GAUCHE);
Spectacle spectacleDroit(&discoledDroit); // peut-etre plutot memoire dynamique
Spectacle spectacleGauche(&discoledGauche); // peut-etre plutot memoire dynamique

uint8_t moment;
DiscoLed& discoled = discoledGauche;

void setup() 
{
  //Serial.begin(9600);
  //Serial.println("initialisation principale");  

  Scheduler.start(initialiserBandeDroite, bouclerBandeDroite);  
  Scheduler.start(initialiserBandeGauche, bouclerBandeGauche);  
}


void loop() 
{
  delay(10);
  //Serial.println("boucle principale");  
}



