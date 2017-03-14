#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

#define MODE_ROTATION_ALTERNEE 0
#define MODE_CLIGNOTE_ROUGE 1
#define MODE_PROMENADE_ROUGE 2
#define MODE_TROIS_TOURS 3
int tour = 0;
int mode = 0;

int positionActuelle = 0;
int positionPrecedente = 0;

int LONGUEUR_PROGRAMME_ROTATION_ALTERNEE = 14;
int LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE = 6;
int LONGUEUR_PROGRAMME_PROMENAGE_ROUGE = 24;
int LONGUEUR_PROGRAMME_TROIS_TOURS = 3 * 24;

int LONGUEUR_PROGRAMME = LONGUEUR_PROGRAMME_ROTATION_ALTERNEE + LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE + LONGUEUR_PROGRAMME_PROMENAGE_ROUGE + LONGUEUR_PROGRAMME_TROIS_TOURS;


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
//Spectacle * spectacle;

Led * animerRotationAlternee()
{
    delay(300);
    Serial.println("Mode ROTATION_ALTERNEE");
    if (tour % 2 == 0) pixels = bandeBlancBleu;
    else pixels = bandeBleuBlanc;
    return pixels;
}

Led * animerClignotementRouge()
{
    delay(300);
    Serial.println("Mode CLIGNOTE_ROUGE");
    if (tour % 2 == 0) pixels = bandeRougeFramboise;
    else pixels = bandeBlanche;  
    return pixels;
}

Led * animerPromenadeRouge()
{
    delay(50);
    positionActuelle = (tour % LONGUEUR_PROGRAMME) - LONGUEUR_PROGRAMME_ROTATION_ALTERNEE - LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE;
    positionPrecedente = positionActuelle - 1;
    if (positionPrecedente < 0) positionPrecedente = 24 - 1;

    Serial.print("Position precedente = ");
    Serial.println(positionPrecedente);
    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode PROMENADE");

    bandeBlanchePixelRouge[positionPrecedente] = COULEUR_BLANC;
    bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
    pixels = bandeBlanchePixelRouge;  
    return pixels;
}

Led * animerTroisTours()
{
   delay(50);
    int positionDansMode = tour % LONGUEUR_PROGRAMME - LONGUEUR_PROGRAMME_ROTATION_ALTERNEE - LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE - LONGUEUR_PROGRAMME_PROMENAGE_ROUGE;
    positionActuelle = positionDansMode % 24;

    Serial.print("Position actuelle = ");
    Serial.println(positionActuelle);
    Serial.println("Mode TROIS TOURS");

    if (positionDansMode < 24)
    {
      bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
      pixels = bandeBlanchePixelRouge;
    }
    else if (positionDansMode < 2 * 24)
    {
      bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLANC;
      pixels = bandeBlanchePixelRouge;
    }
    else
    {
      bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLEU;
      pixels = bandeBlanchePixelRouge;
    }
   return pixels;
}


int listeModes[4];

int listeDurees[4];
void setup()
{
listeModes[0] = MODE_ROTATION_ALTERNEE;
listeModes[1] = MODE_CLIGNOTE_ROUGE;
listeModes[2] = MODE_PROMENADE_ROUGE;
listeModes[3] = MODE_TROIS_TOURS;
listeDurees[0] = LONGUEUR_PROGRAMME_ROTATION_ALTERNEE;
listeDurees[1] = LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE;
listeDurees[2] = LONGUEUR_PROGRAMME_PROMENAGE_ROUGE;
listeDurees[3] = LONGUEUR_PROGRAMME_TROIS_TOURS;

  //spectacle = new Spectacle();
  Serial.begin(9600);
  bandeRougeFramboise = discoled.creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = discoled.creerBandeCouleurUnie(COULEUR_BLANC);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC);
  bandeBlancBleu = creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec);
  bandeBlanchePixelRouge = discoled.creerBandeCouleurUnie(COULEUR_BLANC);
  pixels = bandeRougeFramboise;
}

/*
   Initialise la couleur des bandes
   Paramètres : couleurs des led
*/
Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2)
{
  Led * bandeCouleur = discoled.preparerBandeVide();
  for (int position = 0; position < LED_NOMBRE; position += 2) // possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position + 1] = couleur2;

  }
  return bandeCouleur;
}


int positionDansProgramme;
int positionDansAnimation = 0;
int numeroAnimation = 0;

int duree;

void loop()
{
  tour++;

  positionDansProgramme = tour % LONGUEUR_PROGRAMME;

  positionDansAnimation++;
  
  mode = listeModes[numeroAnimation];
  duree = listeDurees[numeroAnimation]; 

  if(positionDansAnimation == duree) 
  {
    positionDansAnimation = 0;  
    numeroAnimation++;
    if(numeroAnimation > 3) numeroAnimation = 0;
  }
  
  //if (positionDansProgramme < LONGUEUR_PROGRAMME_ROTATION_ALTERNEE) mode = MODE_ROTATION_ALTERNEE;  
  //else if ((positionDansProgramme - LONGUEUR_PROGRAMME_ROTATION_ALTERNEE) < LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE) mode = MODE_CLIGNOTE_ROUGE;
  //else if ((positionDansProgramme - LONGUEUR_PROGRAMME_ROTATION_ALTERNEE - LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE) < LONGUEUR_PROGRAMME_PROMENAGE_ROUGE) mode = MODE_PROMENADE_ROUGE;
  //else if ((positionDansProgramme - LONGUEUR_PROGRAMME_ROTATION_ALTERNEE - LONGUEUR_PROGRAMME_CLIGNOTE_ROUGE - LONGUEUR_PROGRAMME_PROMENAGE_ROUGE) < LONGUEUR_PROGRAMME_TROIS_TOURS) mode = MODE_TROIS_TOURS;

  if(mode == MODE_ROTATION_ALTERNEE)
  {
    pixels = animerRotationAlternee();
  }
  else if(mode == MODE_CLIGNOTE_ROUGE)
  {
    pixels = animerClignotementRouge();
  }
  else if(mode == MODE_PROMENADE_ROUGE)
  {
    pixels = animerPromenadeRouge();
  }
  else if(mode == MODE_TROIS_TOURS)
  {
    pixels = animerTroisTours();
  }
 
  discoled.afficher(pixels);
}



