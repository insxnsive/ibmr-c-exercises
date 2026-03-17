/*
=====================
| RPG Simples 1.0
| Documentado com alguns comentários para estudar.
| Perfeito para aprender exemplos práticos de:
| switch, while, if, else
| Feito por Dylan Martins IBMR
=====================
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sleepMs(ms) usleep(ms * 1000)

int eHp = 25;
int hHp = 100;
double pDmg = 5.0;
int eDmg = 9;
int potions = 3;
int potionEf = 15;

/*
Criando uma função personalizada para:
o texto poder aparecer lentamente
*/

void typeText(const char *text, int delayMs) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout); // Utilizando a stdlib isso se torna possível
        if (text[i] == '.') {
            sleepMs(delayMs * 25); // If para se tiver "." o delay ser maior para ser mais dramático
        } else {
            sleepMs(delayMs);
        }
    }
    sleep(2); // Dar uma pausa dramática entre os textos
    printf("\n");
}

int main() {
  int hDecision;
  int enemyCount = 0;
  const int MAX_ENEMIES = 5;

  srand(time(NULL)); // Necessário apenas uma vez e exige a lib <time.h>

  typeText("Echoes mutter through your mind..", 20); // Esse número seguido da função typeText serve para definir o delay entre os caracteres aparecendo.
  typeText("'Is this some sort of nightmare?' You ask yourself...", 20);
	typeText("There's no point in going back now!!", 10);
	sleep(1); // Esperar 1 segundo
  printf("========= GAUNTLET START! =========\n");

  while (enemyCount < MAX_ENEMIES && hHp > 0) { // Enquanto a quantidade de inimigos for menor que a quantidade máxima de inimigos & HP do herói for maior que 0
    eHp = 25;
    enemyCount++; // Todas as vezes que um inimigo morrer, aparece outro

    printf("\n>>> ENEMY #%d APPEARS! <<<\n", enemyCount);

      while (hHp > 0) { // eHp começa positivo e a derrota do inimigo já é tratada com "break" mais abaixo
        printf("\n| --- YOUR TURN (Enemy %d/%d) ---\n", enemyCount, MAX_ENEMIES);
        printf("| Your HP: %d | Enemy HP: %d | Potions: %d |\n", hHp, eHp, potions);
        printf("| 1. Attack | 2. Guard | 3. Potion | 4. Gamble | 5. Flee\n");
        printf("| - Your choice: ");
        // Mantido scanf de propósito para fins educacionais (entrada básica em C).
        scanf("%d", &hDecision);

        const double r = (rand() % 3) + 1; // Criando uma variável que gera números aleatórios com limitação usando a stdlib.h e diversificando o resultado
        double multiplier = r*.7; // Multiplicador usando a variável aleatória para a opção Gamble

        	switch(hDecision) {
            case 1: // Use os cases para definir opções esperadas
            {
              const double hResult = r * pDmg; // Declaro e atribuo junto para ficar mais claro onde a variável é usada
              eHp -= hResult; // Tira o resultado de dano e ja define no HP do inimigo
              printf("| [YOU] Dealt %f DMG!\n", hResult);
              break;
            }
            case 2:
            {
              int def = r * 2; // Declaro e atribuo junto para manter a variável perto do uso
              hHp += def;
              printf("| [YOU] Defended for %d HP!\n", def);
              break;
            }
          	case 3:
              if (potions >= 0) { // Aqui eu antes verifico se você ainda tem poções
                potions--;
                hHp += potionEf;
                printf("| [YOU] Restored %d HP!\n", potionEf);
              } else { // Se tiver menos que/ou 0 poções, joga para o else
                printf("| [SYSTEM] No potions left!\n");
              }
              	break;
              case 4:
              	pDmg += multiplier; // Uso a variável la em cima de multiplier pra fazer esse gamble
              	if (multiplier < 1) {
              		printf("[YOU] Gambling made you %.1fx weaker...", r*.7);
								} else {
									printf("[YOU] Gambling made you %.1fx stronger!", r*.7);
								}
                break;
              case 5:
              	printf("You fled the scene... How heroic...\n");
                return 0; // return 0; fecha o código aqui mesmo
              default: // Usem "default" para adicionar uma opção que não está programada ou sendo esperada
                printf("You stood still, unsure of what to do.\n");
                break;
            }
            if (eHp <= 0) { // Utilizo então do if novamente para verificar se o hp do inimigo é menor que ou igual a 0 para parar aqui
                printf("\n[VICTORY] Enemy #%d defeated!\n", enemyCount);
                sleep(1);
                break;
            }
            int eResult = ((rand() % 2) + 1) * eDmg; // Declaração+atribuição juntas deixam a leitura do turno mais direta
            hHp -= eResult;
            printf("| [ENEMY] Dealt %d DMG to you!\n", eResult);

            if (hHp <= 0) { // If para verificar se o "player" está morto
                printf("\n[DEFEAT] You have fallen...\n");
                break;
            }
        }
    }

    if (hHp > 0) { // If fora do while para caso você esteja com o hp acima de 0 até o final, ganhe.
        printf("\n!!! YOU CONQUERED THE GAUNTLET !!!\n");
    }

    printf("========= GAME OVER =========\n");
    return 0; // Parar o código aqui.
}