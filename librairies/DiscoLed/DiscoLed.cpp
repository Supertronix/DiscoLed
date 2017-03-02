#include "DiscoLed.h"

DiscoLed::DiscoLed(int nombre, int pin)
{	
	masque = digitalPinToBitMask(pin);
	port = portOutputRegister(digitalPinToPort(pin));
	portMode = portModeRegister(digitalPinToPort(pin));
	anneau = new WS2812(pin);
	anneau->setOutput(pin);
	this->pin = pin;
	this->nombre = nombre;

}

led * DiscoLed::preparerBandeVide(int taille)
{
  return (led*)malloc(taille*3*sizeof(uint8_t));
}

void DiscoLed::afficher(led* pixels)
{
	//anneau->set_crgb_at(2, couleur);
	*portMode |= masque;
	anneau->ws2812_sendarray_mask((uint8_t*)pixels,3*this->nombre, masque,(uint8_t*) port,(uint8_t*) portMode); 
	//anneau->sync();

}

/*
 * Initialise la couleur du led : 
 * Paramètre : niveau de rouge, niveau de vert, niveau de bleu
 */
led DiscoLed::creerCouleur(int rouge, int vert, int bleu)
{
    led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleu;
    return couleur;
}
