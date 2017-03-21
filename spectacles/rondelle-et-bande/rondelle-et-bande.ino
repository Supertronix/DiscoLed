#include <Scheduler.h>
#include <DiscoLed.h>

Led couleurBleuPale = {.vert = 190, .rouge = 36, .bleu = 240};
Led couleurBleuQuebec = {.vert = 92, .rouge = 0, .bleu = 22};
Led couleurJaune = {.vert = 252, .rouge = 250, .bleu = 104};
Led couleurVerte = {.vert = 255, .rouge = 0, .bleu = 0};
Led couleurRougeFramboise = {.vert = 39, .rouge = 242, .bleu = 144};


void setup() {
  Serial.begin(9600);
  Serial.println("Initialiser");  
  //Scheduler.start(initialiserBande, bouclerBande);  
  Scheduler.start(initialiserRondelle, bouclerRondelle);
}

void loop() {
  delay(10);
  Serial.println("boucle principale");  
}



