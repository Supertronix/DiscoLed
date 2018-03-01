#define BRILLANCE_MAX 180
const uint8_t BRILLANCE = 1;
unsigned int iterationCollision = 0;
bool encours = true;

void initialiserCollision()
{
  for (int i = 0; i < NOMBRE; i++)
  {
    pixels[i] = FabriqueLed::creerCouleur(0, 0, 0);
  }
}
void palir(unsigned char *valeur, unsigned char degre = 2)
{
  unsigned char palissement = *valeur >> degre;  // cree un ratio de la valeur
  *valeur -= palissement;  
}

bool animerCollision()
{
  if (iterationCollision == 0)
  {
    pixels[NOMBRE - 1]= pixels[0] = FabriqueLed::creerCouleur(BRILLANCE_MAX, 0, 0);
    pixels[NOMBRE - 3] = pixels[NOMBRE - 2] = pixels[1] = pixels[2] = FabriqueLed::creerCouleur(255, 255, 255);
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
  
  rougirIntervalle(dernierStart, finTete + 1);
  palirIntervalle(0, debutTete);
  blanchirIntervalle(finTete, (NOMBRE+1)/2 + 1);
  
  //if(finTete < (NOMBRE+1)/2 - 1) pixels[finTete + 2] = pixels[NOMBRE - finTete - 2] = FabriqueLed::creerCouleur(255, 255, 255);
  if(finTete < (NOMBRE+1)/2 - 2) pixels[finTete + 1] = pixels[NOMBRE - finTete - 1] = FabriqueLed::creerCouleur(255, 255, 255);
  
  discoled.afficher(pixels);
  iterationCollision++;  
  if(finTete >= (NOMBRE+1)/2 - 2) iterationCollision = 0;
}

void palirIntervalle(int debut, int fin)
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
void blanchirIntervalle(int debut, int fin)
{
    for (int i = debut; i < fin-1; i++)
    {
        pixels[i] = FabriqueLed::creerCouleur(255, 255, 255);      
        pixels[NOMBRE - i - 1] = pixels[i];
    }  
}
void rougirIntervalle(int debut, int fin)
{
    for (int i = debut; i < fin-1; i++)
    {
        pixels[i] = FabriqueLed::creerCouleur(255, 0, 0);      
        pixels[NOMBRE - i - 1] = pixels[i];
    }  
}

