#define BANDE_PIN 3
#define BANDE_LED 60

DiscoLed bande(BANDE_LED, BANDE_PIN);
Spectacle spectacleBande(&bande); // peut-etre plutot memoire dynamique
Led * pixelsBande;

int positionActuelleBande = 0;
int positionPrecedenteBande = 0;


// BANDE de la bande
Led * bandeRougeFramboise;
Led * bandeBlanche;
Led * bandeBleuBlanc;
Led * bandeBlancBleu;
Led * bandeBlanchePixelRouge;


void initialiserBande()
{
  Serial.println("Initialiser Bande");

  Serial.begin(9600);
  Serial.println("Initialiser Rondelle");

  Animation * animationRotationAlternee = new Animation();
  animationRotationAlternee->animer = animerBandeRotationAlternee;
  spectacleBande.ajouterAnimation(animationRotationAlternee);
  
  Animation * animationClignotementRouge = new Animation();
  animationClignotementRouge->animer = animerBandeClignotementRouge;
  spectacleBande.ajouterAnimation(animationClignotementRouge);
 
  Animation * animationPromenadeRouge = new Animation();
  animationPromenadeRouge->animer = animerBandePromenadeRouge;
  spectacleBande.ajouterAnimation(animationPromenadeRouge);
  
  Animation * animationTroisTours = new Animation();
  animationTroisTours->animer = animerBandeTroisTours;
  spectacleBande.ajouterAnimation(animationTroisTours);
  
  bandeRougeFramboise = bande.creerBandeCouleurUnie(couleurRougeFramboise);
  bandeBlanche = bande.creerBandeCouleurUnie(COULEUR_BLANC);
  bandeBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC, BANDE_LED); 
  bandeBlancBleu = creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec, BANDE_LED); 
  bandeBlanchePixelRouge = bande.creerBandeCouleurUnie(COULEUR_BLANC);
  pixelsBande = bandeRougeFramboise;
  
}

void bouclerBande()
{
  Serial.println("Spectacle Bande - Nouvelle animation");  
  spectacleBande.jouerAnimation();
}




////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void animerBandeRotationAlternee()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 14; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode ROTATION_ALTERNEE");
      Serial.println(positionDansAnimation);
      if(positionDansAnimation%2 == 0) pixelsBande = bandeBlancBleu;
      else pixelsBande = bandeBleuBlanc;
      bande.afficher(pixelsBande);
    } 
}

void animerBandeClignotementRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 6; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode CLIGNOTE_ROUGE");
      if(positionDansAnimation%2 == 0) pixelsBande = bandeRougeFramboise;
      else pixelsBande = bandeBlanche;
      bande.afficher(pixelsBande);
    }
}

void animerBandePromenadeRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < BANDE_LED; positionDansAnimation++)
    {
      delay(50);    
      positionPrecedenteBande = positionDansAnimation - 1;
      if(positionPrecedenteBande < 0) positionPrecedenteBande = 24 - 1;
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelleBande);
      Serial.println("Mode PROMENADE");
      
      bandeBlanchePixelRouge[positionPrecedenteBande] = COULEUR_BLANC;    
      bandeBlanchePixelRouge[positionDansAnimation] = couleurRougeFramboise;
      pixelsBande = bandeBlanchePixelRouge;
      bande.afficher(pixelsBande);
    }
}

void animerBandeTroisTours()
{   
    for(int positionDansAnimation = 0; positionDansAnimation < 3*BANDE_LED; positionDansAnimation++)
    {
      delay(50);
      positionActuelleBande = positionDansAnimation%24;
        
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelleBande);
      Serial.println("Mode TROIS TOURS");
    
      if(positionDansAnimation < 24)
      {        
        bandeBlanchePixelRouge[positionActuelleBande] = couleurRougeFramboise;
        pixelsBande = bandeBlanchePixelRouge;
      }
      else if(positionDansAnimation < 2*24)
      {       
        bandeBlanchePixelRouge[positionActuelleBande] = COULEUR_BLANC;
        pixelsBande = bandeBlanchePixelRouge;
      }
      else
      {       
        bandeBlanchePixelRouge[positionActuelleBande] = COULEUR_BLEU;
        pixelsBande = bandeBlanchePixelRouge;
      }
      bande.afficher(pixelsBande);
    }
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2, int nombre)
{
  Led * bandeRondelleCouleur = bande.preparerBandeVide();
  for(int position = 0; position < nombre; position+=2)// possible car le nombre est pair
  {
    bandeRondelleCouleur[position] = couleur1;
    bandeRondelleCouleur[position+1] = couleur2;
    
  }
  return bandeRondelleCouleur;
}

