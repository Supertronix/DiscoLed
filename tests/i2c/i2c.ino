#include <Wire.h>
#include <DiscoLed.h>
#define PIN 3
#define HORLOGE 4
#define NOMBRE 67

DiscoLed* discoLed;
Led pixels[NOMBRE];
//Led** arcenciel;

void setup()
{
  Serial.begin(9600);
  discoLed = new DiscoLed(NOMBRE, PIN, HORLOGE);
  Wire.begin(4);
  Wire.onReceive(recevoirCommandeRio);
}

void recevoirCommandeRio(int nombre)
{
  Serial.println("recevoirCommandeRio()");
  if(Wire.available())
  {
    char lettre = Wire.read();
    Serial.println(lettre);
  }

}



Led construireArcEnCielDecale(Led * liste, int total)
{
  
} 
int ADXLAddress = 4;//0x53;
int commande;
uint8_t moment;
//int iteration = 0;
void loop()
{
  Wire.requestFrom(ADXLAddress,1);
  commande = Wire.read();
  Serial.print("commande ");
  Serial.println(commande);
  //discoLed->afficher(arcenciel[0]);

    moment = millis() >> 4;
    for(int position = 0; position < NOMBRE; position++)
    {
      uint8_t p = moment-position*8;
      pixels[position] = FabriqueLed::convertirHSV( (uint32_t)p * 359 / 256, 255, 255);
    }
  discoLed->afficher(pixels);
  delay(10);
}


