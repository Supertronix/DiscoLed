#define BRILLANCE_MAX 180
unsigned int iterationCollision = 0;
bool encours = true;

void preparerCollision(DiscoLed* discoled)
{
  for (int i = 0; i < NOMBRE; i++)
  {
    discoled->pixels[i] = FabriqueLed::creerCouleur(0, 0, 0);
  }
}
void palir(unsigned char *valeur, unsigned char degre = 2)
{
  unsigned char palissement = *valeur >> degre;  // cree un ratio de la valeur
  *valeur -= palissement;  
}

bool animerCollision(DiscoLed* discoled)
{
  if (iterationCollision == 0)
  {
    discoled->pixels[NOMBRE - 1]= discoled->pixels[0] = FabriqueLed::creerCouleur(BRILLANCE_MAX, 0, 0);
    discoled->pixels[NOMBRE - 3] = discoled->pixels[NOMBRE - 2] = discoled->pixels[1] = discoled->pixels[2] = FabriqueLed::creerCouleur(255, 255, 255);
  }

  int compteFacteur = iterationCollision + 7;
  unsigned int debutTete = compteFacteur*(compteFacteur+1) >> 6;
  unsigned int dernierStart = compteFacteur*(compteFacteur-1) >> 6;
  unsigned int finTete = debutTete + (compteFacteur >> 5);
  //unsigned int finTete = debutTete*1.1;
  //Serial.print("start ");Serial.print(debutTete);
  //Serial.print(" stop ");Serial.println(finTete);
  
  if (debutTete > (NOMBRE+1)/2) return 0;  // arreter quand les flux se croisent
  if(finTete > (NOMBRE+1)/2) finTete = (NOMBRE+1)/2;
  
  rougirIntervalle(discoled->pixels, dernierStart, finTete + 1);
  palirIntervalle(discoled->pixels, 0, debutTete);
  blanchirIntervalle(discoled->pixels, finTete, (NOMBRE+1)/2 + 1);
  
  //if(finTete < (NOMBRE+1)/2 - 1) discoled->pixels[finTete + 2] = discoled->pixels[NOMBRE - finTete - 2] = FabriqueLed::creerCouleur(255, 255, 255);
  if(finTete < (NOMBRE+1)/2 - 2) discoled->pixels[finTete + 1] = discoled->pixels[NOMBRE - finTete - 1] = FabriqueLed::creerCouleur(255, 255, 255);
  
  discoled->afficher(discoled->pixels);
  iterationCollision++;  
  if(finTete >= (NOMBRE+1)/2 - 2) iterationCollision = 0;
}

void palirIntervalle(Led * pixels, int debut, int fin)
{
    for (int i = debut; i < fin-1; i++)
    {
      // start fading previously generated parts of the stream
      palir(&pixels[i].rouge);
      palir(&pixels[i].vert);
      palir(&pixels[i].bleu);
      palir(&pixels[NOMBRE - i - 1].rouge);
      palir(&pixels[NOMBRE - i - 1].vert);
      palir(&pixels[NOMBRE - i - 1].bleu);
    }
}
void blanchirIntervalle(Led * pixels, int debut, int fin)
{
    for (int i = debut; i < fin-1; i++)
    {
        pixels[i] = FabriqueLed::creerCouleur(255, 255, 255);      
        pixels[NOMBRE - i - 1] = pixels[i];
    }  
}
void rougirIntervalle(Led * pixels, int debut, int fin)
{
    for (int i = debut; i < fin-1; i++)
    {
        pixels[i] = FabriqueLed::creerCouleur(255, 0, 0);      
        pixels[NOMBRE - i - 1] = pixels[i];
    }  
}

