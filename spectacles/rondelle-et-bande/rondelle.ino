#include <DiscoLed.h>
#define PIN 2
#define LED_NOMBRE 40

Led * pixels;
Led * bandeVerte;

DiscoLed rondelle(LED_NOMBRE, PIN);
//Spectacle spectacle(&rondelle); // peut-etre plutot memoire dynamique

void initialiserRondelle() 
{  
  Serial.begin(9600);
  bandeVerte = rondelle.creerBandeCouleurUnie(couleurVerte);
  pixels = bandeVerte;
}

unsigned long tempsRondelle = 0;
void bouclerRondelle() 
{  
  tempsRondelle = millis();
  if(tempsRondelle%200 == 0)
    rondelle.afficher(bandeVerte);
}



