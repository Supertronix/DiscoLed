#include <DiscoLed.h>
#define PIN 2
#define LED_NOMBRE 40

Led * pixels;

Led * bandeVerte;

Led couleurVerte = {.vert = 255, .rouge = 0, .bleu = 0};

DiscoLed rondelle(LED_NOMBRE, PIN);
//Spectacle spectacle(&rondelle); // peut-etre plutot memoire dynamique

void setup() 
{  
  Serial.begin(9600);
  bandeVerte = rondelle.creerBandeCouleurUnie(couleurVerte);
  pixels = bandeVerte;
}

void loop() 
{  
  rondelle.afficher(bandeVerte);
  delay(200);
}



