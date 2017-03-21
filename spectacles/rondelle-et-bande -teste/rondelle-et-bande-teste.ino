#include <Scheduler.h>
#include <DiscoLed.h>

#define RONDELLE_PIN 8
#define RONDELLE_LED 40
#define BANDE_PIN 3
#define BANDE_LED 60

DiscoLed discoled(RONDELLE_LED, RONDELLE_PIN);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique

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


void initialiserRondelle()
{
  Serial.begin(9600);
  Serial.println("Initialiser Rondelle");

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
  
  bandeRougeFramboise = discoled.creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = discoled.creerBandeCouleurUnie(COULEUR_BLANC);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC, RONDELLE_LED); 
  bandeBlancBleu = creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec, RONDELLE_LED); 
  bandeBlanchePixelRouge = discoled.creerBandeCouleurUnie(COULEUR_BLANC);
  pixels = bandeRougeFramboise;
  
}

void bouclerRondelle()
{
  Serial.println("Boucle Rondelle");  
  spectacle.jouerAnimation();
}

void initialiserBande()
{
  Serial.println("Initialiser Bande");  
}

void bouclerBande()
{
  Serial.println("Boucle Bande");  
  delay(10);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialiser");  
  Scheduler.start(initialiserRondelle, bouclerRondelle);
  Scheduler.start(initialiserBande, bouclerBande);  
}

void loop() {
  delay(10);
  Serial.println("boucle principale");  

}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

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

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2, int nombre)
{
  Led * bandeCouleur = discoled.preparerBandeVide();
  for(int position = 0; position < nombre; position+=2)// possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position+1] = couleur2;
    
  }
  return bandeCouleur;
}

