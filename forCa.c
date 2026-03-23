#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {

    char palavras[][20] = {"python", "computador", "programa", "teclado", "internet"};
    char palavra[20];
    char descoberto[20];
    char letra;

    int tentativas = 6;
    int tamanho;
    int i;
    int acertou;

    srand(time(NULL));

    int indice = rand() % 5;
    strcpy(palavra, palavras[indice]);

    tamanho = strlen(palavra);

    for(i = 0; i < tamanho; i++){
        descoberto[i] = '_';
    }

    descoberto[tamanho] = '\0';

    printf("=== JOGO DA FORCA ===\n");
    //jogo principal, vai rodar enquanto houver tentativas
    while(tentativas > 0 && strcmp(palavra, descoberto) != 0){

        printf("\nPalavra: %s\n", descoberto);
        printf("Tentativas restantes: %d\n", tentativas);

        printf("Digite uma letra: ");
        scanf(" %c", &letra);

        acertou = 0;
        //procura pela letra digitada na palavra secreta e marca o acerto
        for(i = 0; i < tamanho; i++){
            if(palavra[i] == letra){
                descoberto[i] = letra;
                acertou = 1;
            }
        }
        //diminui o numero de tentativas em caso de erro
        if(!acertou){
            tentativas--;
            printf("Letra errada!\n");
        }
    }
    //resultado da rodada
    if(strcmp(palavra, descoberto) == 0){
        printf("\nVoce venceu!\n");
    }else{
        printf("\nVoce perdeu!\n");
    }

    printf("A palavra era: %s\n", palavra);

    return 0;
}