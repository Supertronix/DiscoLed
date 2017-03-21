#include <Scheduler.h>

void initialiserBonjourMonde()
{
  Serial.println("Initialiser Bonjour Monde");  
}

void bouclerBonjourMonde()
{
  Serial.println("Boucle Bonjour Monde");  
  delay(10);
}

void initialiserPaysDesMerveilles()
{
  Serial.println("Initialiser Pays Des Merveilles");  
}

void bouclerPaysDesMerveilles()
{
  Serial.println("Boucle Pays Des Merveilles");  
  delay(10);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialiser");  
  Scheduler.start(initialiserBonjourMonde, bouclerBonjourMonde);
  Scheduler.start(initialiserPaysDesMerveilles, bouclerPaysDesMerveilles);  
}

void loop() {
  delay(10);
  Serial.println("boucle principale");  

}
