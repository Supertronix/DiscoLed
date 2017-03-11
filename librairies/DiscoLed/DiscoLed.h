#include <WS2812.h>

struct Led
{ 
  uint8_t vert;
  uint8_t rouge;
  uint8_t bleu;
};

const Led COULEUR_BLANC = {255, 255, 255};
const Led COULEUR_ROUGE = {0, 255, 0};
const Led COULEUR_BLEU = {0, 0, 255};
const Led COULEUR_VERT = {255, 0, 0};

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
		Led * preparerBandeVide();
		Led * creerBandeCouleurUnie(Led couleur);
		void afficher(Led* pixels);
		Led creerCouleur(int rouge, int vert, int bleu);
};

