#define BANDE_PIN 3
#define BANDE_LED 60

DiscoLed bande(BANDE_LED, BANDE_PIN);
Spectacle spectacleBande(&bande); // peut-etre plutot memoire dynamique
Led * pixelsBande;


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
/*
  Animation * animationRotationAlternee = new Animation();
  animationRotationAlternee->animer = animerBandeRotationAlternee;
  spectacleRondelle.ajouterAnimation(animationRotationAlternee);
  
  Animation * animationClignotementRouge = new Animation();
  animationClignotementRouge->animer = animerBandeClignotementRouge;
  spectacleRondelle.ajouterAnimation(animationClignotementRouge);
 
  Animation * animationPromenadeRouge = new Animation();
  animationPromenadeRouge->animer = animerBandePromenadeRouge;
  spectacleRondelle.ajouterAnimation(animationPromenadeRouge);
  
  Animation * animationTroisTours = new Animation();
  animationTroisTours->animer = animerBandeTroisTours;
  spectacleRondelle.ajouterAnimation(animationTroisTours);
  
  rondelleRougeFramboise = rondelle.creerBandeCouleurUnie(couleurRougeFramboise);
  rondelleBlanche = rondelle.creerBandeCouleurUnie(COULEUR_BLANC);
  rondelleBleuBlanc = creerBandeCouleurAlternee(couleurBleuQuebec, COULEUR_BLANC, RONDELLE_LED); 
  rondelleBlancBleu = creerBandeCouleurAlternee(COULEUR_BLANC, couleurBleuQuebec, RONDELLE_LED); 
  rondelleBlanchePixelRouge = rondelle.creerBandeCouleurUnie(COULEUR_BLANC);
  pixelsRondelle = rondelleRougeFramboise;
  */
}

void bouclerBande()
{
  Serial.println("Boucle Bande");  
  delay(10);
}
