#include <DiscoLed.h>
#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

Led * pixels;
DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique

uint8_t moment;

Led couleurBleuQuebec = {.rouge = 0, .vert = 92, .bleu = 22};
Led * bandeBleuBlanc;
Led * bandeBlancBleu;


void setup() 
{
  Serial.begin(9600);
  pixels = new Led[NOMBRE];

  initialiserAlternance();

  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 300;
  spectacle.ajouterAnimation(animationArcEnCiel);
  
  Animation * animationAlternance = new Animation();
  animationAlternance->animer = animerAlternance;
  animationAlternance->duree = 400;
  spectacle.ajouterAnimation(animationAlternance);
}


void loop() 
{  
  spectacle.jouerAnimation();
}



