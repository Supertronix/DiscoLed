#define RONDELLE_PIN 2
#define RONDELLE_LED 40
DiscoLed rondelle(RONDELLE_LED, RONDELLE_PIN);
Spectacle spectacleRondelle(&rondelle); // peut-etre plutot memoire dynamique
Led * pixelsRondelle;

int positionActuelleRondelle = 0;
int positionPrecedenteRondelle = 0;

// BANDE de la rondelle
Led * rondelleRougeFramboise;
Led * rondelleBlanche;
Led * rondelleVerte;
Led * rondelleBleuBlanc;
Led * rondelleBlancBleu;
Led * rondelleBlanchePixelRouge;

void initialiserRondelle()
{
  Serial.begin(9600);
  Serial.println("Initialiser Rondelle");

  Animation * animationRotationAlternee = new Animation();
  animationRotationAlternee->animer = animerRondelleRotationAlternee;
  //spectacleRondelle.ajouterAnimation(animationRotationAlternee);
  
  Animation * animationClignotementRouge = new Animation();
  animationClignotementRouge->animer = animerRondelleClignotementRouge;
  //spectacleRondelle.ajouterAnimation(animationClignotementRouge);
 
  Animation * animationPromenadeRouge = new Animation();
  animationPromenadeRouge->animer = animerRondellePromenadeRouge;
  //spectacleRondelle.ajouterAnimation(animationPromenadeRouge);
  
  Animation * animationTroisTours = new Animation();
  animationTroisTours->animer = animerRondelleTroisTours;
  //spectacleRondelle.ajouterAnimation(animationTroisTours);
  
  rondelleRougeFramboise = rondelle.creerBandeCouleurUnie(couleurRougeFramboise);
  rondelleVerte = rondelle.creerBandeCouleurUnie(couleurVerte);
  rondelleBlanche = rondelle.creerBandeCouleurUnie(COULEUR_BLANC);
  rondelleBleuBlanc = creerRondelleCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC, RONDELLE_LED); 
  rondelleBlancBleu = creerRondelleCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec, RONDELLE_LED); 
  rondelleBlanchePixelRouge = rondelle.creerBandeCouleurUnie(COULEUR_BLANC);
  pixelsRondelle = rondelleVerte;
  rondelle.afficher(pixelsRondelle);
}

void bouclerRondelle()
{
  Serial.println("Spectacle Rondelle - Nouvelle animation");  
  //spectacleRondelle.jouerAnimation();
  rondelle.afficher(pixelsRondelle);
}





////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void animerRondelleRotationAlternee()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 14; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode ROTATION_ALTERNEE");
      Serial.println(positionDansAnimation);
      if(positionDansAnimation%2 == 0) pixelsRondelle = rondelleBlancBleu;
      else pixelsRondelle = rondelleBleuBlanc;
      rondelle.afficher(pixelsRondelle);
    } 
}

void animerRondelleClignotementRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 6; positionDansAnimation++)
    {
      delay(300);
      Serial.println("Mode CLIGNOTE_ROUGE");
      if(positionDansAnimation%2 == 0) pixelsRondelle = rondelleRougeFramboise;
      else pixelsRondelle = rondelleBlanche;
      rondelle.afficher(pixelsRondelle);
    }
}

void animerRondellePromenadeRouge()
{
    for(int positionDansAnimation = 0; positionDansAnimation < 24; positionDansAnimation++)
    {
      delay(50);    
      positionPrecedenteRondelle = positionDansAnimation - 1;
      if(positionPrecedenteRondelle < 0) positionPrecedenteRondelle = 24 - 1;
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelleRondelle);
      Serial.println("Mode PROMENADE");
      
      rondelleBlanchePixelRouge[positionPrecedenteRondelle] = COULEUR_BLANC;    
      rondelleBlanchePixelRouge[positionDansAnimation] = couleurRougeFramboise;
      pixelsRondelle = rondelleBlanchePixelRouge;
      rondelle.afficher(pixelsRondelle);
    }
}

void animerRondelleTroisTours()
{   
    for(int positionDansAnimation = 0; positionDansAnimation < 3*24; positionDansAnimation++)
    {
      delay(50);
      positionActuelleRondelle = positionDansAnimation%24;
        
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelleRondelle);
      Serial.println("Mode TROIS TOURS");
    
      if(positionDansAnimation < 24)
      {        
        rondelleBlanchePixelRouge[positionActuelleRondelle] = couleurRougeFramboise;
        pixelsRondelle = rondelleBlanchePixelRouge;
      }
      else if(positionDansAnimation < 2*24)
      {       
        rondelleBlanchePixelRouge[positionActuelleRondelle] = COULEUR_BLANC;
        pixelsRondelle = rondelleBlanchePixelRouge;
      }
      else
      {       
        rondelleBlanchePixelRouge[positionActuelleRondelle] = COULEUR_BLEU;
        pixelsRondelle = rondelleBlanchePixelRouge;
      }
      rondelle.afficher(pixelsRondelle);
    }
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * creerRondelleCouleurAlternee(Led couleur1, Led couleur2, int nombre)
{
  Led * rondelleRondelleCouleur = rondelle.preparerBandeVide();
  for(int position = 0; position < nombre; position+=2)// possible car le nombre est pair
  {
    rondelleRondelleCouleur[position] = couleur1;
    rondelleRondelleCouleur[position+1] = couleur2;
    
  }
  return rondelleRondelleCouleur;
}

