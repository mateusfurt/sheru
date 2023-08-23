#include <stdio.h>
#include <string.h>

void sortnome(char linhas[][100], int count){
  int i, j, menor;
  char tmp[100];
  for (i = 0; i < count-1; i++) {
    menor = i;
    for (j = i + 1; j < count; j++) {
      if (strcmp(linhas[j], linhas[menor]) < 0) {
        menor = j;
      }
    }
    strcpy(tmp, linhas[menor]);
    strcpy(linhas[menor], linhas[i]);
    strcpy(linhas[i], tmp);
  }
}

int main()
{
    int i;
    char linhas[5][100]={"bc", "ad", "ef", "do", "aa"};
    sortnome(linhas, 5);
    for(i=0;i<5;i++){
        printf("%s\n", linhas[i]);
    }

    return 0;
}