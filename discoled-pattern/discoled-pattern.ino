#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

#define MODE_TOUR_ROUGE 0
#define MODE_TOUR_BLANC 1
#define MODE_TOUR_BLEU 2


led * pixels;

led * bandeRougeFramboise;
led * bandeBlanche;
led * bandeBleuBlanc;
led * bandeBlancBleu;
led * bandeBlanchePixelRouge;
led * bandeBleu;


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
  bandeRougeFramboise = discoled.creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = discoled.creerBandeCouleurUnie(couleurBlanc);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, couleurBlanc); 
  bandeBlancBleu = creerBandeCouleurAlternee(couleurBlanc, couleurBleuQuebec); 
  bandeBlanchePixelRouge = discoled.creerBandeCouleurUnie(couleurBlanc);
  bandeBleu = discoled.creerBandeCouleurUnie(couleurBleu);

  pixels = bandeRougeFramboise;
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
int limiteProgrammeTourRouge = 24;
int limiteProgrammeTourBlanc = 48;
int limiteProgrammeTourBleu = 72;

void loop() 
{  
  delay(50);    
 
  Serial.print("tour = ");
  Serial.println(tour);
  if(tour%limiteProgrammeTourBleu < limiteProgrammeTourRouge) mode = MODE_TOUR_ROUGE;
  else if (tour%limiteProgrammeTourBleu < limiteProgrammeTourBlanc)mode = MODE_TOUR_BLANC; 
  else mode = MODE_TOUR_BLEU;
    
  Serial.print("mode = ");
  Serial.println(mode);
  
  if(mode == MODE_TOUR_ROUGE) 
  {
    positionActuelle = tour%24;
    
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");
      
    bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
    pixels = bandeBlanchePixelRouge;
  }
  if(mode == MODE_TOUR_BLANC)
  {
    positionActuelle = tour%24;
    
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");
      
    bandeBlanchePixelRouge[positionActuelle] = couleurBlanc;
    pixels = bandeBlanchePixelRouge;
  }
  if(mode == MODE_TOUR_BLEU){
    positionActuelle = tour%24;
    
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");
     
    bandeBlanchePixelRouge[positionActuelle] = couleurBleu;
    pixels = bandeBlanchePixelRouge;
  }
  
  discoled.afficher(pixels);
  tour++;

}



