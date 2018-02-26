#include "DiscoLed.h"

DiscoLed::DiscoLed(int nombre, const uint8_t pin, const uint8_t horloge)
{	
	bande = new APA102<3, 4>();
	//masque = digitalPinToBitMask(pin);
	//port = portOutputRegister(digitalPinToPort(pin));
	//portMode = portModeRegister(digitalPinToPort(pin));
	//anneau = new WS2812(pin);
	//anneau->setOutput(pin);
	this->pin = pin;
	this->horloge = horloge;
	this->nombre = nombre;
}

const uint8_t brillance = 1;
void DiscoLed::afficher(Led* pixels)
{
  bande->write((rgb_color*)pixels, nombre, brillance);
}

// https://cs.stackexchange.com/questions/64549/convert-hsv-to-rgb-colors
// https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
// https://gist.github.com/mjackson/5311256
// https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
// https://books.google.ca/books?id=hrcrDwAAQBAJ&pg=PT92&lpg=PT92
// h hue (teinte):0-360 - s saturation : 0-255 - v value : 0-255
Led FabriqueLed::convertirHSV(uint16_t h, uint8_t s, uint8_t v)
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


/*
 * Initialise la couleur du led : 
 * Parametre : niveau de rouge, niveau de vert, niveau de bleu
 */

Led FabriqueLed::creerCouleur(int rouge, int vert, int bleu)
{
    Led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleu;
    return couleur;
	//return (Led)NULL;
}

Led * DiscoLed::preparerBandeVide()
{
  return (Led*)malloc(this->nombre*3*sizeof(uint8_t));
}

Led * DiscoLed::creerBandeCouleurUnie(Led couleur)
{
  Led * bandeCouleur = this->preparerBandeVide();
  for(int position = 0; position < this->nombre; position++)
  {
    bandeCouleur[position] = couleur;
  }
  return bandeCouleur;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * DiscoLed::creerBandeCouleurAlternee(Led couleur1, Led couleur2)
{
  Led * bandeCouleur = this->preparerBandeVide();
  for(int position = 0; position < this->nombre; position+=2)// possible car le nombre est pair
  {
    bandeCouleur[position] = couleur1;
    bandeCouleur[position+1] = couleur2;
    
  }
  return bandeCouleur;
}



#define TAILLE_SPECTACLE 8

Spectacle::Spectacle()
{
	this->capaciteAnimations = TAILLE_SPECTACLE;
	this->listeAnimations = new Animation *[TAILLE_SPECTACLE]; 
	this->nombreAnimations = 0;
	this->animationCourante = 0;
}
Spectacle::Spectacle(DiscoLed * discoled)
{
	this->discoled = discoled;
	this->capaciteAnimations = TAILLE_SPECTACLE;
	this->listeAnimations = new Animation *[TAILLE_SPECTACLE]; 
	this->nombreAnimations = 0;
	this->animationCourante = 0;
}
void Spectacle::ajouterAnimation(Animation * animation)
{
	// TODO : gerer la croissance au-dela de TAILLE_SPECTACLE plus tard
	this->listeAnimations[nombreAnimations++] = animation;
}
void Spectacle::jouerAnimation()
{
	if(nombreAnimations < 1) return false;
	
	this->listeAnimations[animationCourante]->animer();		
	this->sauterAnimation();
}
bool Spectacle::jouerAnimationSansSauter()
{
	if(nombreAnimations < 1) return false;
	return this->listeAnimations[animationCourante]->animer();		
}

void Spectacle::sauterAnimation()
{
	animationCourante++;
	if(animationCourante > nombreAnimations) animationCourante = 0;
}
