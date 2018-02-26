#include <APA102.h>
#ifndef DISCOLED_H
#define DISCOLED_H

struct Led
{ 
	uint8_t rouge;
	uint8_t vert;
	uint8_t bleu;  
};

const Led COULEUR_BLANC = {255, 255, 255};
const Led COULEUR_ROUGE = {255, 0, 0};
const Led COULEUR_VERT = {0, 255, 0};
const Led COULEUR_BLEU = {0, 0, 255};

class FabriqueLed
{
	public:
	static Led convertirHSV(uint16_t h, uint8_t s, uint8_t v);
	static Led creerCouleur(int rouge, int vert, int bleu);
};

class DiscoLed
{
	
	protected:
		APA102<3,4> *bande;
		int nombre;
		int pin;
		int horloge;

	public:
		DiscoLed(int nombre, const uint8_t pin, const uint8_t horloge = 0);
		void afficher(Led* pixels);
		Led * preparerBandeVide();
		Led * creerBandeCouleurUnie(Led couleur);
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
