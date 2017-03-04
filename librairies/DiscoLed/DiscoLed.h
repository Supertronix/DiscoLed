#include <WS2812.h>

struct Led
{ 
  uint8_t vert;
  uint8_t rouge;
  uint8_t bleu;
};

const Led COULEUR_BLANC = {255, 255, 255};

	
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
		Led * preparerBandeVide(int taille);
		Led * creerBandeCouleurUnie(Led couleur);
		void afficher(Led* pixels);
		Led creerCouleur(int rouge, int vert, int bleu);
};

