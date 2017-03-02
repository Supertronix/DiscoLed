#define USE_HSV

#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

led * pixels;

led * bandeRougeFramboise;
led * bandeBlanche;
led * bandeBleuBlanc;
led * bandeBlancBleu;

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

  pixels = bandeRougeFramboise;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleur du led
 */
led * creerBandeCouleurUnie(led couleur)
{
  led * bandeCouleur = preparerBandeVide(LED_NOMBRE);
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
  led * bandeCouleur = preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position+=2)// possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position+1] = couleur2;
    
  }
  return bandeCouleur;
}

int tour = 0;



void loop() 
{
  tour++;
  delay(300);
  if(tour%20 < 14)
  {
    Serial.println("Mode ROTATION_ALTERNEE");
    if(tour%2 == 0) pixels = bandeBlancBleu;
    else pixels = bandeBleuBlanc;
  }
  else
  {
    Serial.println("Mode CLIGNOTE");
    if(tour%2 == 0) pixels = bandeRougeFramboise;
    else pixels = bandeBlanche;
  }
  discoled.afficher(pixels);
}

led * preparerBandeVide(int taille)
{
  return (led*)malloc(taille*3*sizeof(uint8_t));
}

/*
 * Initialise la couleur du led : 
 * Paramètre : niveau de rouge, niveau de vert, niveau de bleu
 */
led creerCouleur(int vert, int rouge, int bleu)
{
    led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleu;
    return couleur;
}

