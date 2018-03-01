#include <Scheduler.h>

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



