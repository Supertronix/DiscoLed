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

/*
 * Initialise la couleur du led : 
 * Parametre : niveau de rouge, niveau de vert, niveau de bleu
 */
/*
Led DiscoLed::creerCouleur(int rouge, int vert, int bleu)
{
    Led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleu;
    return couleur;
	return (Led)NULL;
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
*/

/*
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
	if(nombreAnimations < 1) return;
	
	this->listeAnimations[animationCourante]->animer();		
	this->sauterAnimation();
}
bool Spectacle::jouerAnimationSansSauter()
{
	if(nombreAnimations < 1) return;
	return this->listeAnimations[animationCourante]->animer();		
}

void Spectacle::sauterAnimation()
{
	animationCourante++;
	if(animationCourante > nombreAnimations) animationCourante = 0;
}*/
