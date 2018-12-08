#include<stdio.h>
#include<stdlib.h>

typedef struct kupa {
  char nev[50];
  int evfolyam;
  int pontok;
} kupa;

int foglal(kupa **verseny_ptr, char *fajlnev, int *meret);
int beolvas(kupa *verseny, char *fajlnev, int meret);
void konzolra(kupa *verseny, int meret);

int main() {
  char fajlnev[50];
  int meret = 0;
  kupa *verseny = NULL;

  if(foglal(&verseny, fajlnev, &meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt, vagy foglalni helyet!");
  }
  if(beolvas(verseny, fajlnev, meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt!");
  }
  konzolra(verseny, meret);
  return 0;
}

int foglal(kupa **verseny_ptr, char *fajlnev, int *meret) {
  FILE *fajl = NULL;
  char character;

  printf("Szervusz kedves felhasznalo, melyik fajlt nyissam meg? ");
  scanf("%49s", fajlnev);

  fajl = fopen(fajlnev, "r");
  if (!fajl) {
    return 1;
  }

  while ((character = fgetc(fajl)) != EOF) {
    if (character == '\n') {
      (*meret)++;
    }
  }

  *verseny_ptr = (kupa *) malloc(*meret * sizeof(kupa));

  if (!(*verseny_ptr)) {
    return 1;
  }

  fclose(fajl);
  return 0;
}

int beolvas(kupa *verseny, char *fajlnev, int meret) {
  FILE *fajl = NULL;
  int i;

  fajl = fopen(fajlnev, "r");
  if (!fajl) {
    return 1;
  }

  for (i = 0; i < meret; i++) {
    fscanf(fajl, "%12s%d", verseny[i].nev, &verseny[i].evfolyam);
  }

  fclose(fajl);
  return 0;
}

void konzolra(kupa *verseny, int meret) {
  int i;
  for(i = 0; i < meret; i++) {
    printf("nev: %s, evfolyam: %d\n", verseny[i].nev, verseny[i].evfolyam);
  }
}
