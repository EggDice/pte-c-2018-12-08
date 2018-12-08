#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct kupa {
  char nev[50];
  int evfolyam;
  int pontok;
} kupa;

int foglal(kupa **verseny_ptr, char *fajlnev, int *meret);
int beolvas(kupa *verseny, char *fajlnev, int meret);
void konzolra(kupa *verseny, int meret);
int versenyeztet(kupa *verseny, int meret);
int maximum(kupa *verseny, int meret);

int main() {
  char fajlnev[50];
  int meret = 0;
  kupa *verseny = NULL;

  if (foglal(&verseny, fajlnev, &meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt, vagy foglalni helyet!");
  }
  if (beolvas(verseny, fajlnev, meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt!");
  }
  konzolra(verseny, meret);
  if (versenyeztet(verseny, meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt!");
  }
  if (maximum(verseny, meret)) {
    printf("Hat sajnos nem lehetett megnyitni a fajlt!");
  }
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

int versenyeztet(kupa *verseny, int meret) {
  FILE *fajl = NULL;
  int i;
  srand(time(NULL));

  fajl = fopen("verseny.txt", "w");
  if (!fajl) {
    return 1;
  }

  printf("A verseny erdmenye:\n");
  fprintf(fajl, "A verseny erdmenye:\n");
  for (i = 0; i < meret; i++) {
    verseny[i].pontok = rand();
    printf("nev: %s\t evf.: %d\t pontok: %d\n", verseny[i].nev, verseny[i].evfolyam, verseny[i].pontok);
    fprintf(fajl, "nev: %s\t evf.: %d\t pontok: %d\n", verseny[i].nev, verseny[i].evfolyam, verseny[i].pontok);
  }

  fflush(fajl);
  fclose(fajl);
  return 0;
}

int maximum(kupa *verseny, int meret) {
  FILE *fajl = NULL;
  int i;
  int max = verseny[0].pontok;

  fajl = fopen("verseny.txt", "a");
  if (!fajl) {
    return 1;
  }

  for (i = 1; i < meret; i++) {
    if (verseny[i].pontok > max) {
      max = verseny[i].pontok;
    }
  }

  printf("A legnagyobb pontszam: %d\n", max);
  fprintf(fajl, "A legnagyobb pontszam: %d\n", max);

  for (i = 0; i < meret; i++) {
    if (verseny[i].pontok == max) {
      printf("Max pontos: nev: %s\t evf.: %d\t pontok: %d\n", verseny[i].nev, verseny[i].evfolyam, verseny[i].pontok);
      fprintf(fajl, "Max pontos: nev: %s\t evf.: %d\t pontok: %d\n", verseny[i].nev, verseny[i].evfolyam, verseny[i].pontok);
    }
  }

  fflush(fajl);
  fclose(fajl);
  return 0;
}
