#include <DiscoLed.h>
#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

Led * pixels;
DiscoLed discoled(NOMBRE, PIN, HORLOGE);
Spectacle spectacle(&discoled); // peut-etre plutot memoire dynamique

uint8_t moment;
bool animerArcEnCiel()
{
  Serial.print("animerArcEnCiel() ");
  moment = millis() >> 4;
  for(int position = 0; position < NOMBRE; position++)
  {
    uint8_t p = moment-position*8;
    pixels[position] = FabriqueLed::convertirHSV( (uint32_t)p * 359 / 256, 255, 255);
  }
  discoled.afficher(pixels);
}

Led couleurBleuQuebec = {.rouge = 0, .vert = 92, .bleu = 22};
Led * bandeBleuBlanc;
Led * bandeBlancBleu;
bool animerAlternance()
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

void setup() 
{
  Serial.begin(9600);
  pixels = new Led[NOMBRE];

  bandeBleuBlanc = discoled.creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC); 
  bandeBlancBleu = discoled.creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec); 

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



