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

void setup() 
{
  Serial.begin(9600);
  pixels = new Led[NOMBRE];

  Animation * animationArcEnCiel = new Animation();
  animationArcEnCiel->animer = animerArcEnCiel;
  animationArcEnCiel->duree = 30000;
  spectacle.ajouterAnimation(animationArcEnCiel);
}


void loop() 
{  
  spectacle.jouerAnimation();
}



