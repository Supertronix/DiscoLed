#define USE_HSV

#include <DiscoLed.h>

#include <WS2812.h>
#define PIN 9
#define LED_NOMBRE 40
cRGB couleur;
cRGB couleurRouge;
uint8_t masque;
const volatile uint8_t * port;
volatile uint8_t * port_reg;

struct led
{ 
  uint8_t vert;
  uint8_t rouge;
  uint8_t bleu;
};

led * preparerBandeVide(int taille);
led creerCouleur(int rouge, int vert, int bleue);
void initialiserBandeCouleur(led * bandeCouleur, led couleur);

led * pixels;

led * bandeRouge;
led * bandeBleue;
led * bandeVerte;
led * bandeRougeFramboise;

/*led couleurRouge;
led couleurBleu;
led couleurVert;
led couleurJaune;*/
led couleurRougeFramboise;

WS2812 anneau(LED_NOMBRE);

void setup() {
  Serial.begin(9600);
  masque = digitalPinToBitMask(PIN);
  port = portOutputRegister(digitalPinToPort(PIN));
  port_reg = portModeRegister(digitalPinToPort(PIN));
  anneau.setOutput(PIN);

  couleurRougeFramboise = creerCouleur(242, 39, 144);
  bandeRougeFramboise = preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position++){
    bandeRougeFramboise[position] = couleurRougeFramboise;
  }
  //initialiserBandeCouleur(bandeRougeFramboise, couleurRougeFramboise);
}

/*
 * Initialise la couleur du led : 
 * Paramètre : couleur du led, niveau de rouge, niveau de vert, niveau de bleu
 */
led creerCouleur(int rouge, int vert, int bleue)
{
    led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleue;
    return couleur;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : Bande de couleur, couleur du led
 */
led * initialiserBandeCouleur(led couleur)
{
  led * bandeCouleur = preparerBandeVide(LED_NOMBRE);
  for(int position = 0; position < LED_NOMBRE; position++){
    bandeCouleur[position] = couleur;
  }
  return bandeCouleur;
}

void loop() {
  delay(1000);
  pixels = bandeRougeFramboise;
  Serial.println("Allo de Nadine");
  //anneau.set_crgb_at(2, couleur);
  *port_reg |= masque;
  anneau.ws2812_sendarray_mask((uint8_t*)pixels,3*LED_NOMBRE, masque,(uint8_t*) port,(uint8_t*) port_reg); 
  //anneau.sync();
}

led * preparerBandeVide(int taille)
{
  return (led*)malloc(taille*3*sizeof(uint8_t));
}


