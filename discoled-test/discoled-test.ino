#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

#define MODE_ROTATION_ALTERNEE 0
#define MODE_CLIGNOTE 1
#define MODE_PROMENADE_ROUGE 2
//#define MODE_TOUR_ROUGE 3
//#define MODE_TOUR_BLANC 4
//#define MODE_TOUR_BLEU 5


Led * pixels;

Led * bandeRougeFramboise;
Led * bandeBlanche;
Led * bandeBleuBlanc;
Led * bandeBlancBleu;
Led * bandeBlanchePixelRouge;

Led couleurBleuPale = {.vert = 190, .rouge = 36, .bleu = 240};
Led couleurBleuQuebec = {.vert = 92, .rouge = 0, .bleu = 22};
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

int LONGUEUR_PROGRAMME_ROTATION_ALTERNEE = 14;
int LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE = 6;
int LONGUEUR_PROGRAMME_PROMENAGE_ROUGE = 24;

//int LONGUEUR_PROGRAMME_TOUR_ROUGE = 24;
//int LONGUEUR_PROGRAMME_TOUR_BLANC = 24;
//int LONGUEUR_PROGRAMME_TOUR_BLEU = 24;
//int LONGUEUR_PROGRAMME_TROIS_TOURS = 3*24;
int LONGUEUR_PROGRAMME_TROIS_TOURS = 0;

int LONGUEUR_PROGRAMME = LONGUEUR_PROGRAMME_ROTATION_ALTERNEE + LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE + LONGUEUR_PROGRAMME_PROMENAGE_ROUGE + LONGUEUR_PROGRAMME_TROIS_TOURS;

void loop() 
{  
  tour++;

  if(tour%LONGUEUR_PROGRAMME < LONGUEUR_PROGRAMME_ROTATION_ALTERNEE) mode = MODE_ROTATION_ALTERNEE;
  else if((tour%LONGUEUR_PROGRAMME - LONGUEUR_PROGRAMME_ROTATION_ALTERNEE) < LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE) mode = MODE_CLIGNOTE;
  else mode = MODE_PROMENADE_ROUGE;
  //else if(tour%limiteProgrammeTourBleu < limiteProgrammeTourRouge) mode = MODE_TOUR_ROUGE;
  //else if (tour%limiteProgrammeTourBleu < limiteProgrammeTourBlanc)mode = MODE_TOUR_BLANC; 
  //else mode = MODE_TOUR_BLEU;
  
  //PROGRAMME clignote + tourne
  if(mode == MODE_ROTATION_ALTERNEE)
  {
    delay(300);
    Serial.println("Mode ROTATION_ALTERNEE");
    if(tour%2 == 0) pixels = bandeBlancBleu;
    else pixels = bandeBleuBlanc;
  }
  else if(mode == MODE_CLIGNOTE)
  {
    delay(300);
    Serial.println("Mode CLIGNOTE");
    if(tour%2 == 0) pixels = bandeRougeFramboise;
    else pixels = bandeBlanche;
  }
  else
  {
    delay(50);    
    positionActuelle = (tour%LONGUEUR_PROGRAMME)-LONGUEUR_PROGRAMME_ROTATION_ALTERNEE - LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE;
    positionPrecedente = positionActuelle - 1;
    if(positionPrecedente < 0) positionPrecedente = 24 - 1;
    
    Serial.print("Position precedente = ");
    Serial.println(positionPrecedente);
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");
    
    bandeBlanchePixelRouge[positionPrecedente] = COULEUR_BLANC;    
    bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
    pixels = bandeBlanchePixelRouge;

  }

/*
else if(mode == MODE_TOUR_ROUGE) 
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
  }*/

  discoled.afficher(pixels);
}



