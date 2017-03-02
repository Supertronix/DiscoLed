#define USE_HSV

#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

led * pixels;

led * bandeRougeFramboise;
led * bandeBlanche;
led * bandeBleuBlanc;
led * bandeBlancBleu;
led * bandeBlanchePixelRouge;

led couleurBlanc = {255, 255, 255};
led couleurBleuPale = {.vert = 190, .rouge = 36, .bleu = 240};
led couleurBleuQuebec = {.vert = 92, .rouge = 0, .bleu = 22};
led couleurRouge = {0, 255, 0};
led couleurBleu = {0, 0, 255};
led couleurVert = {255, 0, 0};
led couleurJaune = {.vert = 252, .rouge = 250, .bleu = 104};
led couleurRougeFramboise = {.vert = 39, .rouge = 242, .bleu = 144};

DiscoLed discoled(LED_NOMBRE, PIN);

void setup() 
{
  Serial.begin(9600);
  bandeRougeFramboise = creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = creerBandeCouleurUnie(couleurBlanc);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, couleurBlanc); 
  bandeBlancBleu = creerBandeCouleurAlternee(couleurBlanc, couleurBleuQuebec); 
  bandeBlanchePixelRouge = creerBandeCouleurUnie(couleurBlanc);
  pixels = bandeRougeFramboise;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleur du led
 */
led * creerBandeCouleurUnie(led couleur)
{
  led * bandeCouleur = discoled.preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position++)
  {
    bandeCouleur[position] = couleur;
  }
  return bandeCouleur;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
led * creerBandeCouleurAlternee(led couleur1, led couleur2)
{
  led * bandeCouleur = discoled.preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position+=2)// possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position+1] = couleur2;
    
  }
  return bandeCouleur;
}

int tour = 0;
int mode = 0;

int positionActuelle = 0;
int positionPrecedente = 0;
int limiteProgrammeClignote = 24;
int limiteProgrammePromenade = 48;

void loop() 
{  
  delay(50);    
 
  Serial.print("tour = ");
  Serial.println(tour);
  if(tour%48 < limiteProgrammeClignote) mode = 0;
  else mode = 1; 
    
  Serial.print("mode = ");
  Serial.println(mode);
  
  if(mode == 0) 
  {
    positionActuelle = tour%24;
    
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");
      
    bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
    pixels = bandeBlanchePixelRouge;
  }
  if(mode == 1)
  {
    positionActuelle = tour%24;
    
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");
      
    bandeBlanchePixelRouge[positionActuelle] = couleurBlanc;
    pixels = bandeBlanchePixelRouge;
  }
  
  discoled.afficher(pixels);
  tour++;

}



