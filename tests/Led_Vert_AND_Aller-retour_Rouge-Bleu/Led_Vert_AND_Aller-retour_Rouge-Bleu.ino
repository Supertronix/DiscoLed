#include <DiscoLed.h>
#define PIN 3
#define LED_NOMBRE 60
#define PIN2 2
#define LED_NOMBRE40 40

Led * pixels;
Led * pixels2;

Led * bandeCouleur;
Led * bandeCouleur2;

Led rouge = {.vert = 0, .rouge = 255, .bleu = 0};
Led bleu = {.vert = 0, .rouge = 0, .bleu = 255};
Led vert = {.vert = 255, .rouge = 0, .bleu = 0};

DiscoLed discoled(LED_NOMBRE, PIN);
DiscoLed discoled2(LED_NOMBRE40, PIN2);

void setup() {  
  Serial.begin(9600);
  bandeCouleur = discoled.creerBandeCouleurUnie(bleu);
  pixels = bandeCouleur;
  bandeCouleur2 = discoled2.creerBandeCouleurUnie(vert);
  pixels2 = bandeCouleur2;
}

int tour = 0;

void loop() {
  if(tour==0)
  {
    for(int i=0; i<LED_NOMBRE40; i++)
    {     
      bandeCouleur2[i] = vert;      
    }
    pixels2 = bandeCouleur2;      
    discoled2.afficher(pixels2);  
    tour++;
  }
  else if(tour==1)
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
