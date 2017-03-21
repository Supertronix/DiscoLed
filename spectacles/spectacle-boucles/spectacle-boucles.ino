#include <DiscoLed.h>
#define PIN 9
#define LED_NOMBRE 40

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

int positionActuelle = 0;
int positionPrecedente = 0;

int LONGUEUR_PROGRAMME_TROIS_TOURS = 3*24;

DiscoLed discoled(LED_NOMBRE, PIN);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique


void animerRotationAlternee()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 14; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode ROTATION_ALTERNEE");
      Serial.println(positionDansAnimation);
      if(positionDansAnimation%2 == 0) pixels = bandeBlancBleu;
      else pixels = bandeBleuBlanc;
      discoled.afficher(pixels);
    } 
}

void animerClignotementRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 6; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode CLIGNOTE_ROUGE");
      if(positionDansAnimation%2 == 0) pixels = bandeRougeFramboise;
      else pixels = bandeBlanche;
      discoled.afficher(pixels);
    }
}

void animerPromenadeRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 24; positionDansAnimation++)
    {
      delay(50);    
      positionPrecedente = positionDansAnimation - 1;
      if(positionPrecedente < 0) positionPrecedente = 24 - 1;
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelle);
      Serial.println("Mode PROMENADE");
      
      bandeBlanchePixelRouge[positionPrecedente] = COULEUR_BLANC;    
      bandeBlanchePixelRouge[positionDansAnimation] = couleurRougeFramboise;
      pixels = bandeBlanchePixelRouge;
      discoled.afficher(pixels);
    }
}

void animerTroisTours()
{   
    for(int positionDansAnimation = 0; positionDansAnimation < LONGUEUR_PROGRAMME_TROIS_TOURS; positionDansAnimation++)
    {
      delay(50);
      positionActuelle = positionDansAnimation%24;
        
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelle);
      Serial.println("Mode TROIS TOURS");
    
      if(positionDansAnimation < 24)
      {        
        bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
        pixels = bandeBlanchePixelRouge;
      }
      else if(positionDansAnimation < 2*24)
      {       
        bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLANC;
        pixels = bandeBlanchePixelRouge;
      }
      else
      {       
        bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLEU;
        pixels = bandeBlanchePixelRouge;
      }
      discoled.afficher(pixels);
    }
}







void setup() 
{
  Animation * animationRotationAlternee = new Animation();
  animationRotationAlternee->animer = animerRotationAlternee;
  spectacle.ajouterAnimation(animationRotationAlternee);
  
  Animation * animationClignotementRouge = new Animation();
  animationClignotementRouge->animer = animerClignotementRouge;
  spectacle.ajouterAnimation(animationClignotementRouge);
 
  Animation * animationPromenadeRouge = new Animation();
  animationPromenadeRouge->animer = animerPromenadeRouge;
  spectacle.ajouterAnimation(animationPromenadeRouge);
  
  Animation * animationTroisTours = new Animation();
  animationTroisTours->animer = animerTroisTours;
  spectacle.ajouterAnimation(animationTroisTours);
  
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
  Led * bandeCouleur = discoled.preparerBandeVide();
  for(int position = 0; position < LED_NOMBRE; position+=2)// possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position+1] = couleur2;
    
  }
  return bandeCouleur;
}

void loop() 
{  
  spectacle.jouerAnimation();
}



