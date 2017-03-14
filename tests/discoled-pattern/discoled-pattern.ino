#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

#define MODE_TOUR_ROUGE 0
#define MODE_TOUR_BLANC 1
#define MODE_TOUR_BLEU 2


Led * pixels;

Led * bandeBlanchePixelRouge;

Led couleurRougeFramboise = {.vert = 39, .rouge = 242, .bleu = 144};

DiscoLed discoled(LED_NOMBRE, PIN);

void setup() 
{
  Serial.begin(9600);
  bandeBlanchePixelRouge = discoled.creerBandeCouleurUnie(COULEUR_BLANC);

  bandeBlancBleu = discoled.preparerBandeVide();
  
  for( int position=0; position < LED_NOMBRE ; position++)
  {
        bandeBlancBleu[position] = COULEUR_BLANC;
        position++;
        bandeBlancBleu[position] = COULEUR_BLEU;
  }
  
  pixels = bandeBlanchePixelRouge;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2)
{
  Led * bandeCouleur = discoled.preparerBandeVide();
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
     
    bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLEU;
    pixels = bandeBlanchePixelRouge;
  }
  
  discoled.afficher(pixels);
  tour++;

}



