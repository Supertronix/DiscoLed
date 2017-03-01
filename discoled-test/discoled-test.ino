#define USE_HSV

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

led * pixels;
led * bandeRouge;
led * bandeBleue;
led * bandeVerte;

led rouge;
led bleu;
led vert;

WS2812 anneau(LED_NOMBRE);
void setup() {
  Serial.begin(9600);
  masque = digitalPinToBitMask(PIN);
  port = portOutputRegister(digitalPinToPort(PIN));
  port_reg = portModeRegister(digitalPinToPort(PIN));
  anneau.setOutput(PIN);

  rouge.rouge = 255;
  rouge.vert = 0;
  rouge.bleu = 0;
  bleu.rouge = 0;
  bleu.vert = 0;
  bleu.bleu = 255;
  vert.rouge = 0;
  vert.bleu = 0;
  vert.vert = 255;

  bandeRouge = (led*)malloc(LED_NOMBRE*3*sizeof(uint8_t));
  bandeBleue = (led*)malloc(LED_NOMBRE*3*sizeof(uint8_t));
  bandeVerte = (led*)malloc(LED_NOMBRE*3*sizeof(uint8_t));
  for(int position = 0; position < LED_NOMBRE; position++) bandeRouge[position] = rouge;
  for(int position = 0; position < LED_NOMBRE; position++) bandeBleue[position] = bleu;
  for(int position = 0; position < LED_NOMBRE; position++) bandeVerte[position] = vert;
}

void loop() {
  delay(1000);
  pixels = bandeVerte;
  Serial.println("Allo de Nadine");
  //anneau.set_crgb_at(2, couleur);
  *port_reg |= masque;
  anneau.ws2812_sendarray_mask((uint8_t*)pixels,3*LED_NOMBRE, masque,(uint8_t*) port,(uint8_t*) port_reg); 
  //anneau.sync();
}


