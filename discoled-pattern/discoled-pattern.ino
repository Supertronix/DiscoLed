#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

#define MODE_TOUR_ROUGE 0
#define MODE_TOUR_BLANC 1
#define MODE_TOUR_BLEU 2


Led * pixels;

Led * bandeRougeFramboise;
Led * bandeBlanche;
Led * bandeBleuBlanc;
Led * bandeBlancBleu;
Led * bandeBlanchePixelRouge;
Led * bandeBleu;


Led couleurBlanc = {255, 255, 255};
Led couleurBleuPale = {.vert = 190, .rouge = 36, .bleu = 240};
Led couleurBleuQuebec = {.vert = 92, .rouge = 0, .bleu = 22};
Led couleurRouge = {0, 255, 0};
Led couleurBleu = {0, 0, 255};
Led couleurVert = {255, 0, 0};
Led couleurJaune = {.vert = 252, .rouge = 250, .bleu = 104};
Led couleurRougeFramboise = {.vert = 39, .rouge = 242, .bleu = 144};

DiscoLed discoled(LED_NOMBRE, PIN);

void setup() 
{
  Serial.begin(9600);
  bandeRougeFramboise = discoled.creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = discoled.creerBandeCouleurUnie(COULEUR_BLANC);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC); 
  bandeBlancBleu = creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec); 
  bandeBlanchePixelRouge = discoled.creerBandeCouleurUnie(COULEUR_BLANC);
  bandeBleu = discoled.creerBandeCouleurUnie(couleurBleu);

  pixels = bandeRougeFramboise;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2)
{
  Led * bandeCouleur = discoled.preparerBandeVide(LED_NOMBRE);
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
      
    bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLANC;
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



