#include <DiscoLed.h>
#define PIN 3
#define HORLOGE 4
#define NOMBRE 67
Led pixels[NOMBRE];

DiscoLed* discoLed;
void setup()
{
  discoLed = new DiscoLed(NOMBRE, PIN, HORLOGE);
}

void loop()
{
  uint8_t time = millis() >> 4;

  for(uint16_t i = 0; i < NOMBRE; i++)
  {
    uint8_t p = time - i * 8;
    pixels[i] = FabriqueLed::convertirHSV((uint32_t)p * 359 / 256, 255, 255);
    //pixels[i] = COULEUR_BLEU;
  }

  discoLed->afficher(pixels);

  delay(10);
}


