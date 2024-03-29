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
//Led orange = FabriqueLed::convertirHSV( 5, 255, 255); // RGB 255 21 0
//Led rouge = FabriqueLed::convertirHSV( 0, 255, 255);
//Led rose = FabriqueLed::convertirHSV( 350, 255, 255);
//Led mauve = FabriqueLed::convertirHSV( 300, 255, 255);
//Led vert = FabriqueLed::convertirHSV( 100, 255, 255);


class FabriqueLed
{
	public:
	static Led convertirHSV(uint16_t h, uint8_t s, uint8_t v);
	static Led creerCouleur(int rouge, int vert, int bleu);
    static Led trouverCouleurMilieu(Led couleur1, Led couleur2);
	static Led& palirSelonDegre(Led& led, unsigned char degre = 2);
	static void afficherLed(Led& led);
	
	private:
	static void palirCouleurSelonDegre(unsigned char *valeur, unsigned char degre = 2);	
};

class DiscoLed
{
	
	protected:
		APA102* bande;
		int nombre;
		int pin;
		int horloge;

	public:
		DiscoLed(int nombre, const uint8_t pin, const uint8_t horloge = 0);
		void afficher(Led* pixels);
		Led * preparerBandeVide();
		Led * creerBandeCouleurUnie(Led couleur);
		Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2);
		Led * dessinerBandeCouleurAlternee(Led * bandeCouleur, Led couleur1, Led couleur2);
        Led * creerBandeRayee(Led couleur1, Led couleur2, int epaisseur);
		Led * dessinerBandeRayee(Led* bandeCouleur, Led couleur1, Led couleur2, int epaisseur);
        Led * creerBandeRayeeDouce(Led couleur1, Led couleur2, int epaisseur);
		Led * dessinerBandeRayeeDouce(Led * bandeCouleur, Led couleur1, Led couleur2, int epaisseur);
		
		void decalerBande();
		void blanchir(Led * bande);
		void blanchir();
		
		Led * pixels;
		Led * pixels2;
		
        static Led * decalerBande(Led * bande, int nombre);
};

class Animation
{
	public:
		int duree;
		int curseur = 0;
		bool (*animer)(DiscoLed *);
		void (*preparer)(DiscoLed *);
		void (*liberer)(DiscoLed *);
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
