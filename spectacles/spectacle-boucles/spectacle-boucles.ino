#include <DiscoLed.h>
#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

Led * pixels;

Led * bandeRougeFramboise;
Led * bandeBlanche;
Led * bandeBleuBlanc;
Led * bandeBlancBleu;
Led * bandeBlanchePixelRouge;

Led couleurBleuPale = { .rouge = 36,.vert = 190, .bleu = 240};
Led couleurBleuQuebec = {.rouge = 0, .vert = 92, .bleu = 22};
Led couleurJaune = {.rouge = 250, .vert = 252, .bleu = 104};
Led couleurRougeFramboise = {.rouge = 242, .vert = 39, .bleu = 144};

int positionActuelle = 0;
int positionPrecedente = 0;

DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique


bool animerRotationAlternee()
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

bool animerClignotementRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 6; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode CLIGNOTE_ROUGE");
      if(positionDansAnimation%2 == 0) discoled.afficher(bandeRougeFramboise);
      else discoled.afficher(bandeBlanche);
    }
}

bool animerPromenadeRouge()
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
      discoled.afficher(bandeBlanchePixelRouge);
    }
}

bool animerTroisTours()
{   
    for(int positionDansAnimation = 0; positionDansAnimation < 3*24; positionDansAnimation++)
    {
      delay(50);
      positionActuelle = positionDansAnimation%24;
        
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelle);
      Serial.println("Mode TROIS TOURS");
    
      if(positionDansAnimation < 24)
      {        
        bandeBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
        discoled.afficher(bandeBlanchePixelRouge);
      }
      else if(positionDansAnimation < 2*24)
      {       
        bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLANC;
        discoled.afficher(bandeBlanchePixelRouge);
      }
      else
      {       
        bandeBlanchePixelRouge[positionActuelle] = COULEUR_BLEU;
        discoled.afficher(bandeBlanchePixelRouge);
      }
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
  for(int position = 0; position < NOMBRE; position+=2)// possible car le nombre est pair
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



