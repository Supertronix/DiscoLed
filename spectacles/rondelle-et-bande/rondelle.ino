#define RONDELLE_PIN 3
#define RONDELLE_LED 60
DiscoLed rondelle(RONDELLE_LED, RONDELLE_PIN);
Spectacle spectacleRondelle(&rondelle); // peut-etre plutot memoire dynamique
Led * pixelsRondelle;

// BANDE de la rondelle
Led * rondelleRougeFramboise;
Led * rondelleBlanche;
Led * rondelleBleuBlanc;
Led * rondelleBlancBleu;
Led * rondelleBlanchePixelRouge;

void initialiserRondelle()
{
  Serial.begin(9600);
  Serial.println("Initialiser Rondelle");

  Animation * animationRotationAlternee = new Animation();
  animationRotationAlternee->animer = animerRondelleRotationAlternee;
  spectacleRondelle.ajouterAnimation(animationRotationAlternee);
  
  Animation * animationClignotementRouge = new Animation();
  animationClignotementRouge->animer = animerRondelleClignotementRouge;
  spectacleRondelle.ajouterAnimation(animationClignotementRouge);
 
  Animation * animationPromenadeRouge = new Animation();
  animationPromenadeRouge->animer = animerRondellePromenadeRouge;
  spectacleRondelle.ajouterAnimation(animationPromenadeRouge);
  
  Animation * animationTroisTours = new Animation();
  animationTroisTours->animer = animerRondelleTroisTours;
  spectacleRondelle.ajouterAnimation(animationTroisTours);
  
  rondelleRougeFramboise = rondelle.creerBandeCouleurUnie(couleurRougeFramboise);
  rondelleBlanche = rondelle.creerBandeCouleurUnie(COULEUR_BLANC);
  rondelleBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC, RONDELLE_LED); 
  rondelleBlancBleu = creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec, RONDELLE_LED); 
  rondelleBlanchePixelRouge = rondelle.creerBandeCouleurUnie(COULEUR_BLANC);
  pixelsRondelle = rondelleRougeFramboise;
  
}

void bouclerRondelle()
{
  Serial.println("Boucle Rondelle");  
  spectacleRondelle.jouerAnimation();
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
      positionPrecedente = positionDansAnimation - 1;
      if(positionPrecedente < 0) positionPrecedente = 24 - 1;
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelle);
      Serial.println("Mode PROMENADE");
      
      rondelleBlanchePixelRouge[positionPrecedente] = COULEUR_BLANC;    
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
      positionActuelle = positionDansAnimation%24;
        
      Serial.print("Position actuelle = ");
      Serial.println(positionActuelle);
      Serial.println("Mode TROIS TOURS");
    
      if(positionDansAnimation < 24)
      {        
        rondelleBlanchePixelRouge[positionActuelle] = couleurRougeFramboise;
        pixelsRondelle = rondelleBlanchePixelRouge;
      }
      else if(positionDansAnimation < 2*24)
      {       
        rondelleBlanchePixelRouge[positionActuelle] = COULEUR_BLANC;
        pixelsRondelle = rondelleBlanchePixelRouge;
      }
      else
      {       
        rondelleBlanchePixelRouge[positionActuelle] = COULEUR_BLEU;
        pixelsRondelle = rondelleBlanchePixelRouge;
      }
      rondelle.afficher(pixelsRondelle);
    }
}

/*
 * Initialise la couleur des bandes
 * Paramètres : couleurs des led
 */
Led * creerBandeCouleurAlternee(Led couleur1, Led couleur2, int nombre)
{
  Led * bandeRondelleCouleur = rondelle.preparerBandeVide();
  for(int position = 0; position < nombre; position+=2)// possible car le nombre est pair
  {
    bandeRondelleCouleur[position] = couleur1;
    bandeRondelleCouleur[position+1] = couleur2;
    
  }
  return bandeRondelleCouleur;
}

