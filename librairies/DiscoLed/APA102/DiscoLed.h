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
	// https://cs.stackexchange.com/questions/64549/convert-hsv-to-rgb-colors
	// https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
	// https://gist.github.com/mjackson/5311256
	// https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
	// https://books.google.ca/books?id=hrcrDwAAQBAJ&pg=PT92&lpg=PT92
	// h hue (teinte):0-360 - s saturation : 0-255 - v value : 0-255
	static Led convertirHSV(uint16_t h, uint8_t s, uint8_t v)
	{
		uint8_t rouge = 0, vert = 0, bleu = 0;
		
		float saturation = s/255;
		float valeur = v/255;
		
		uint8_t teinte = (h % 60) * 255 / 60; // teinte normalisee ou aplatie (flat)
		uint8_t p = 255*(1 - saturation) * valeur;
		uint8_t q = (255 - teinte * saturation) * valeur; // 
		uint8_t t = (255 - (255 - teinte) * saturation) * valeur; // teinte inverse
		switch((h / 60) % 6){
			case 0: rouge = v; vert = t; bleu = p; break;
			case 1: rouge = q; vert = v; bleu = p; break;
			case 2: rouge = p; vert = v; bleu = t; break;
			case 3: rouge = p; vert = q; bleu = v; break;
			case 4: rouge = t; vert = p; bleu = v; break;
			case 5: rouge = v; vert = p; bleu = q; break;
		}
		Led led;
		led.rouge = rouge;
		led.vert = vert;
		led.bleu = bleu;
		return led;
	}
	Led creerCouleur(int rouge, int vert, int bleu);
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
		//Led * preparerBandeVide();
		//Led * creerBandeCouleurUnie(Led couleur);
};

/*
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
*/
#endif
