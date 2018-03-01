#include "DiscoLed.h"
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

Led FabriqueLed::trouverCouleurMilieu(Led couleur1, Led couleur2)
{
  Serial.print("Rouge de couleur1 = ");
  Serial.println(couleur1.rouge);
  Serial.print("Vert de couleur1 = ");
  Serial.println(couleur1.vert);
  Serial.print("Bleu de couleur1 = ");
  Serial.println(couleur1.bleu);
  Serial.print("Rouge de couleur2 = ");
  Serial.println(couleur2.rouge);
  Serial.print("Vert de couleur2 = ");
  Serial.println(couleur2.vert);
  Serial.print("Bleu de couleur2 = ");
  Serial.println(couleur2.bleu);
    
    
    Led nouvellecouleur;
    nouvellecouleur.rouge = (couleur1.rouge + couleur2.rouge)/2;
    nouvellecouleur.vert = (couleur1.vert + couleur2.vert)/2;
    nouvellecouleur.bleu = (couleur1.bleu + couleur2.bleu)/2;
    return nouvellecouleur;
}

Led& FabriqueLed::palirSelonDegre(Led& led, unsigned char degre)
{
	FabriqueLed::palirCouleurSelonDegre(&led.rouge, degre);
	FabriqueLed::palirCouleurSelonDegre(&led.vert, degre);
	FabriqueLed::palirCouleurSelonDegre(&led.bleu, degre);
	return led;
}

void FabriqueLed::palirCouleurSelonDegre(unsigned char *valeur, unsigned char degre)
{
  unsigned char palissement = *valeur >> degre;  // cree un ratio de la valeur
  *valeur -= palissement;  
}











DiscoLed::DiscoLed(int nombre, const uint8_t pin, const uint8_t horloge)
{	
	// hack du a la limitation de la lib qui requiert des constantes
	//if(pin == 3 && horloge == 4) bande = new APA102<3, 4>();
	//else if(pin == 2 && horloge == 5) bande = new APA102<2, 5>();
	this->bande = new APA102(pin, horloge);
	//masque = digitalPinToBitMask(pin);
	//port = portOutputRegister(digitalPinToPort(pin));
	//portMode = portModeRegister(digitalPinToPort(pin));
	//anneau = new WS2812(pin);
	//anneau->setOutput(pin);
	this->pin = pin;
	this->horloge = horloge;
	this->nombre = nombre;
	this->pixels = new Led[this->nombre];
}

const uint8_t brillance = 1;
void DiscoLed::afficher(Led* pixels)
{
  bande->write((rgb_color*)pixels, nombre, brillance);
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


/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * DiscoLed::creerBandeRayee(Led couleur1, Led couleur2, int epaisseur)
{
  Led * bandeCouleur = this->preparerBandeVide();
  for(int rayure = 0; rayure < this->nombre; rayure+=2*epaisseur)
  {
    for(int position = 0; position < epaisseur; position+=2)
    {
        if((rayure+position)<this->nombre) bandeCouleur[rayure+position] = couleur1;
        if((rayure+position+epaisseur)<this->nombre) bandeCouleur[rayure+position+epaisseur] = couleur2;
    }
  }
  return bandeCouleur;
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * DiscoLed::creerBandeRayeeDouce(Led couleur1, Led couleur2, int epaisseur)
{
  Led couleur12 = FabriqueLed::trouverCouleurMilieu(couleur1, couleur2);
  couleur12 = FabriqueLed::trouverCouleurMilieu(couleur1, couleur12);
  couleur12 = FabriqueLed::trouverCouleurMilieu(couleur1, couleur12);
  couleur12 = FabriqueLed::trouverCouleurMilieu(couleur1, couleur12);
  Serial.print("Rouge de couleur12 = ");
  Serial.println(couleur12.rouge);
  Serial.print("Vert de couleur12 = ");
  Serial.println(couleur12.vert);
  Serial.print("Bleu de couleur12 = ");
  Serial.println(couleur12.bleu);
  
  Led * bandeCouleur = this->preparerBandeVide();
  for(int rayure = 0; rayure < this->nombre; rayure+=2*epaisseur)
  {
    for(int position = 0; position < epaisseur; position++)
    {
        if((rayure+position)>=this->nombre) break;
        if((rayure+position+epaisseur)>=this->nombre) break;  // TODO
        
        if(position == 0)
        {
            bandeCouleur[rayure+position] = couleur12;
            bandeCouleur[rayure+position+epaisseur] = couleur12;            
        }
        else if(position == epaisseur - 1)
        {
            bandeCouleur[rayure+position] = couleur12;
            bandeCouleur[rayure+position+epaisseur] = couleur12;           
        }
        else
        {
            bandeCouleur[rayure+position] = couleur1;
            bandeCouleur[rayure+position+epaisseur] = couleur2;
        }
    }
  }
  return bandeCouleur;
}


Led * DiscoLed::decalerBande(Led * bande, int NOMBRE)
{
  Led temporaire = bande[0];
  for(int position; position < NOMBRE-1; position++)
  {
    bande[position] = bande[position+1];
  }
  bande[NOMBRE-1] = temporaire;
  return bande;
}

void DiscoLed::decalerBande()
{
	/*
  Led temporaire = (Led)bande[0];
  for(int position; position < this->nombre-1; position++)
  {
    bande[position] = bande[position+1];
  }
  bande[this->nombre-1] = temporaire;
  */
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
	Serial.println(this->listeAnimations[animationCourante]->curseur);
	if(this->listeAnimations[animationCourante]->curseur == 0) this->listeAnimations[animationCourante]->preparer(this->discoled);
	this->listeAnimations[animationCourante]->animer(this->discoled);	
	this->listeAnimations[animationCourante]->curseur++;
	if(this->listeAnimations[animationCourante]->curseur >= this->listeAnimations[animationCourante]->duree) this->sauterAnimation();
}
bool Spectacle::jouerAnimationSansSauter()
{
	if(nombreAnimations < 1) return false;
	return this->listeAnimations[animationCourante]->animer(this->discoled);		
}

void Spectacle::sauterAnimation()
{
	Serial.println("sauterAnimation()");
	animationCourante++;
	if(animationCourante > nombreAnimations) animationCourante = 0;
}
