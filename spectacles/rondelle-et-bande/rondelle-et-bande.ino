#include <Scheduler.h>
#include <DiscoLed.h>

Led couleurBleuPale = {.vert = 190, .rouge = 36, .bleu = 240};
Led couleurBleuQuebec = {.vert = 92, .rouge = 0, .bleu = 22};
Led couleurJaune = {.vert = 252, .rouge = 250, .bleu = 104};
Led couleurRougeFramboise = {.vert = 39, .rouge = 242, .bleu = 144};

int positionActuelle = 0;
int positionPrecedente = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Initialiser");  
  Scheduler.start(initialiserRondelle, bouclerRondelle);
  //Scheduler.start(initialiserBande, bouclerBande);  
}

void loop() {
  delay(10);
  Serial.println("boucle principale");  

}



