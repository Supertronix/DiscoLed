#define USE_HSV

#include <DiscoLed.h>

#include <WS2812.h>
#define PIN 9
#define LED_NOMBRE 40
//cRGB couleur;
uint8_t masque;
const volatile uint8_t * port;
volatile uint8_t * port_reg;

struct led
{ 
  uint8_t vert;
  uint8_t rouge;
  uint8_t bleu;
};

led * pixels;

led * bandeRougeFramboise;
led * bandeBlanche;

led * bandeBleuBlanc;
led * bandeBlancBleu;

led couleurBlanc = {255, 255, 255};
led couleurBleuPale = {.vert = 190, .rouge = 36, .bleu = 240};
led couleurBleuQuebec = {.vert = 92, .rouge = 0, .bleu = 22};

led couleurRouge = {0, 255, 0};
led couleurBleu = {0, 0, 255};
led couleurVert = {255, 0, 0};
led couleurJaune = {.vert = 252, .rouge = 250, .bleu = 104};
led couleurRougeFramboise = {.vert = 39, .rouge = 242, .bleu = 144};

WS2812 anneau(LED_NOMBRE);

void setup() {
  Serial.begin(9600);
  masque = digitalPinToBitMask(PIN);
  port = portOutputRegister(digitalPinToPort(PIN));
  port_reg = portModeRegister(digitalPinToPort(PIN));
  anneau.setOutput(PIN);

  bandeRougeFramboise = creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = creerBandeCouleurUnie(couleurBlanc);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, couleurBlanc); 
  bandeBlancBleu = creerBandeCouleurAlternee(couleurBlanc, couleurBleuQuebec); 

  pixels = bandeRougeFramboise;
}

/*
 * Initialise la couleur du led : 
 * Paramètre : couleur du led, niveau de rouge, niveau de vert, niveau de bleu
 */
led creerCouleur(int vert, int rouge, int bleu)
{
    led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleu;
    return couleur;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : Bande de couleur, couleur du led
 */
led * creerBandeCouleurUnie(led couleur)
{
  led * bandeCouleur = preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position++)
  {
    bandeCouleur[position] = couleur;
  }
  return bandeCouleur;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : Bande de couleur, couleur du led
 */
led * creerBandeCouleurAlternee(led couleur1, led couleur2)
{
  led * bandeCouleur = preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position+=2)// possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position+1] = couleur2;
    
  }
  return bandeCouleur;
}

int tour = 0;



void loop() {
  tour++;
  delay(300);
  if(tour%20 < 15)
  {
    Serial.println("Mode ROTATION_ALTERNEE");
    if(tour%2 == 0) pixels = bandeBlancBleu;
    else pixels = bandeBleuBlanc;
  }
  else
  {
    Serial.println("Mode CLIGNOTE");
    if(tour%2 == 0) pixels = bandeRougeFramboise;
    else pixels = bandeBlanche;
    
  }
  //anneau.set_crgb_at(2, couleur);
  *port_reg |= masque;
  anneau.ws2812_sendarray_mask((uint8_t*)pixels,3*LED_NOMBRE, masque,(uint8_t*) port,(uint8_t*) port_reg); 
  //anneau.sync();
}

led * preparerBandeVide(int taille)
{
  return (led*)malloc(taille*3*sizeof(uint8_t));
}


