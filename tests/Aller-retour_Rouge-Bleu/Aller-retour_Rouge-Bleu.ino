#include <DiscoLed.h>
#define PIN 3
#define LED_NOMBRE 60

Led * pixels;

Led * bandeCouleur;

Led rouge = {.vert = 0, .rouge = 255, .bleu = 0};
Led bleu = {.vert = 0, .rouge = 0, .bleu = 255};

DiscoLed discoled(LED_NOMBRE, PIN);

void setup() {  
  Serial.begin(9600);
  bandeCouleur = discoled.creerBandeCouleurUnie(bleu);
  pixels = bandeCouleur;
}

int tour = 1;

void loop() {
  if(tour==1)
  {     
    for(int i=0; i<LED_NOMBRE; i++)
    {
      delay(10);     
      bandeCouleur[i-1] = rouge;
      pixels = bandeCouleur;      
      discoled.afficher(pixels);  
    }
    tour++;
  }
  else
  {     
    for(int i=LED_NOMBRE; i>0; i--)
    {
      delay(10);
      bandeCouleur[i] = bleu;
      pixels = bandeCouleur;      
      discoled.afficher(pixels);  
    } 
    tour=1;
  }
}
