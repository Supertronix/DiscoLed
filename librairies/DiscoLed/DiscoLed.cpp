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

void DiscoLed::afficher(led* pixels)
{
	//anneau->set_crgb_at(2, couleur);
	*portMode |= masque;
	anneau->ws2812_sendarray_mask((uint8_t*)pixels,3*this->nombre, masque,(uint8_t*) port,(uint8_t*) portMode); 
	//anneau->sync();

}