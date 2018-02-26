#include <WS2812.h>
#ifndef DISCOLED_H
#define DISCOLED_H

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

class FabriqueLed
{
	public:
	static Led convertirHSV(uint16_t h, uint8_t s, uint8_t v);
	Led creerCouleur(int rouge, int vert, int bleu);
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
		Led * preparerBandeVide();
		Led * creerBandeCouleurUnie(Led couleur);
		void afficher(Led* pixels);
		Led creerCouleur(int rouge, int vert, int bleu);
};

class Animation
{
	public:
		int duree;
		bool (*animer)();
};

class Spectacle
{
  protected:
    Animation ** listeAnimations;
	DiscoLed * discoled;
    int nombreAnimations;
    int capaciteAnimations;
    int duree;
	int animationCourante;

  public:
    Spectacle();
    Spectacle(DiscoLed *);
    void ajouterAnimation(Animation *);
	void jouerAnimation();
	bool jouerAnimationSansSauter();
	void sauterAnimation();
};

#endif
