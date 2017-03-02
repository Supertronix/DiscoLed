#include <WS2812.h>

struct led
{ 
  uint8_t vert;
  uint8_t rouge;
  uint8_t bleu;
};
	
class DiscoLed
{
	
	protected:
		uint8_t masque;
		const volatile uint8_t * port;
		volatile uint8_t * portMode;
		WS2812 * anneau;
		int nombre;
		int pin;


	public:
		DiscoLed(int nombre, int pin);
		void afficher(led* pixels);
		led creerCouleur(int rouge, int vert, int bleu);
};

