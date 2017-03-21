#include <Scheduler.h>

void initialiserRondelle()
{
  Serial.println("Initialiser Rondelle");  
}

void bouclerRondelle()
{
  Serial.println("Boucle Rondelle");  
  delay(10);
}

void initialiserBande()
{
  Serial.println("Initialiser Bande");  
}

void bouclerBande()
{
  Serial.println("Boucle Bande");  
  delay(10);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialiser");  
  Scheduler.start(initialiserRondelle, bouclerRondelle);
  Scheduler.start(initialiserBande, bouclerBande);  
}

void loop() {
  delay(10);
  Serial.println("boucle principale");  

}
