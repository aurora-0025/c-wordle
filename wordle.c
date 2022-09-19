#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int checkWord(char* word)
{
    int error=0;
    FILE *fp;
    char* p;
    char str[10000];
    fp = fopen("allWords.txt", "r");
    int namesLen = -1;
    while (word[++namesLen] != '\0') continue;
    if(namesLen != 5) return error=1;
    while ((fgets(str, 10000, fp)) != NULL)
    {
        p = strstr(str, word);

        if (p)
        {
            error=0;
            break;
        }
        else error=1;
    }
    return error;
}

void getRandomWord(char* word)
{
    srand(time(NULL));
    int randomnumber = rand() % 1018;
    FILE *fp;
    fp=fopen("answers.txt", "r");
    fseek(fp, randomnumber * 6, SEEK_SET);
    fgets (word, 6, fp);
    fclose(fp);
}

int wordle(char guessWord[], char word[])
{

    char arr1[6];
    char arr2[6];
    char result[6][30];
    strcpy(arr1, guessWord);
    strcpy(arr2, word);
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        sprintf(result[i], "\033[1;97;100m %c \033[0m", arr1[i]);
        if(arr1[i] == arr2[i]) {
            count++;
            sprintf(result[i], "\033[1;97;42m %c \033[0m", arr1[i]);
            arr1[i] = '1';
            arr2[i] = '0';
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if(arr1[i] == arr2[j]){
                sprintf(result[i], "\033[1;97;43m %c \033[0m", arr1[i]);
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%s", result[i]);
    }
    
    if(count == 5) return 1;
    return 0;
}


void main() {
    int turn=0;
    char guess[10];
    char answer[6];

    getRandomWord(answer);
    printf("\033[1;96m====================\033[0m\n");
    printf("\033[1;96m|     C-WORDLE     |\033[0m\n");
    printf("\033[1;96m====================\033[0m\n");
    while(turn<5) {
        turn+=1;
        printf("Enter guess %d: ", turn);
        scanf("%s", guess);
        if(checkWord(guess) == 1)
        {
            printf("\033[1;91mInvalid word!\033[0m");
            turn--;
        }
        else if(wordle(guess, answer) == 1)
        {
            printf("\n\033[1;96mYou Found The Word in your %d guess(es)!\033[0m\n", turn);
            break;
        }
        else if(turn == 5)
        {
            printf("\n\033[1;91mYou failed, get rekt bozo!\nThe word was %s\033[0m\n", answer);
            break;
        }
        printf("\n");
    }
}