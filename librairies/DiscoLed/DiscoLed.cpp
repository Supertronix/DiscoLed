#include "DiscoLed.h"

DiscoLed::DiscoLed(int nombre, int pin)
{	
	masque = digitalPinToBitMask(pin);
	port = portOutputRegister(digitalPinToPort(pin));
	portMode = portModeRegister(digitalPinToPort(pin));
	anneau = new WS2812(pin);
	anneau->setOutput(pin);
	this->pin = pin;
	this->nombre = nombre;
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

void DiscoLed::afficher(Led* pixels)
{
	//anneau->set_crgb_at(2, couleur);
	*portMode |= masque;
	anneau->ws2812_sendarray_mask((uint8_t*)pixels,3*this->nombre, masque,(uint8_t*) port,(uint8_t*) portMode); 
	//anneau->sync();

}

/*
 * Initialise la couleur du led : 
 * Parametre : niveau de rouge, niveau de vert, niveau de bleu
 */
Led DiscoLed::creerCouleur(int rouge, int vert, int bleu)
{
    Led couleur;
    couleur.rouge = rouge;
    couleur.vert = vert;
    couleur.bleu = bleu;
    return couleur;
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
	if(nombreAnimations < 1) return;
	
	this->listeAnimations[animationCourante]->animer();		
	this->sauterAnimation();
}

void Spectacle::sauterAnimation()
{
	animationCourante++;
	if(animationCourante > nombreAnimations) animationCourante = 0;
}
