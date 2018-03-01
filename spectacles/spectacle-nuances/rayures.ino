Led * bandeBlancRouge;

//int momentRayures = 0;
//int deltaRayures = 10;

void initialiserRayures()
{
  bandeBlancRouge = discoled.creerBandeRayee(COULEUR_ROUGE, COULEUR_BLANC, 5); 
  pixels = bandeBlancRouge;
}


bool animerRayures()
{
  //if(momentRayures == 0)   pixels = bandeBlancRouge;
  //momentRayures++;
  
  //if(momentRayures%deltaRayures == 0)
  //{
    pixels = DiscoLed::decalerBande(pixels, NOMBRE);
  //}
  pixels = bandeBlancRouge;
  discoled.afficher(pixels);  
}


Led * decalerBande(Led * bande)
{
  Led temporaire = bande[0];
  for(int position; position < NOMBRE-1; position++)
  {
    bande[position] = bande[position+1];
  }
  bande[NOMBRE-1] = temporaire;
  return bande;
}

