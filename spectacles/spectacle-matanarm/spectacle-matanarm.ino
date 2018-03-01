#include <DiscoLed.h>
#include <Scheduler.h>

#define PIN 3
#define HORLOGE 4
#define NOMBRE 67
DiscoLed discoledDroit(NOMBRE, PIN, HORLOGE);
Spectacle spectacleDroit(&discoledDroit); // peut-etre plutot memoire dynamique
uint8_t moment;


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



