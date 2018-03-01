#include <APA102.h>
#ifndef DISCOLED_H
#define DISCOLED_H

struct Led
{ 
	uint8_t rouge;
	uint8_t vert;
	uint8_t bleu;  
};

const Led COULEUR_BLANC = {100, 100, 100};
const Led COULEUR_ROUGE = {100, 0, 0};
const Led COULEUR_VERT = {0, 100, 0};
const Led COULEUR_BLEU = {0, 0, 100};

class FabriqueLed
{
	public:
	static Led convertirHSV(uint16_t h, uint8_t s, uint8_t v);
	static Led creerCouleur(int rouge, int vert, int bleu);
    static Led trouverCouleurMilieu(Led couleur1, Led couleur2);
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
		Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2);
        Led * creerBandeRayee(Led couleur1, Led couleur2, int epaisseur);
        Led * creerBandeRayeeDouce(Led couleur1, Led couleur2, int epaisseur);        
        static Led * decalerBande(Led * bande, int nombre);
};

class Animation
{
	public:
		int duree;
		int curseur = 0;
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
