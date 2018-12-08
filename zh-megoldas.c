#include<stdio.h>
#include<stdlib.h>

typedef struct kupa {
  char nev[50];
  int evfolyam;
  int pontok;
} kupa;

int foglal(kupa **verseny_ptr, char *fajlnev, int *meret);

int main() {
  char fajlnev[50];
  int meret = 0;
  kupa *verseny = NULL;

  if(foglal(&verseny, fajlnev, &meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt!");
  }
  if (verseny) {
    printf("SIKEEER!");
  }
  return 0;
}

int foglal(kupa **verseny_ptr, char *fajlnev, int *meret) {
  FILE *fajl = NULL;
  char character;

  printf("Szervusz kedves felhasznalo, melyik fajlt nyissam meg?");
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
