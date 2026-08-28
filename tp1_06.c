/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_06
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o tamanho real da string, parando na quebra de linha ou terminador.
 * @param s vetor de caracteres a ser medido
 * @return tamanho da string
 */
int taman(char s[]){
    int resp = 0;
    
    while(s[resp] != '\0' && s[resp] != '\n' && s[resp] != '\r'){
        resp++;
    }
    
    return resp;
}

/**
 * Verifica se a palavra lida e a condicao de parada (FIM).
 * @param s string lida da entrada padrao
 * @return 1 se for FIM, 0 caso contrario
 */
int fim(char s[]){
    int resp = 0;
    
    if(taman(s) == 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M'){
        resp = 1;
    }
    
    return resp;
}

/**
 * Converte um caractere maiusculo para minusculo.
 * @param c caractere que sera convertido
 * @return o caractere em minuscula, ou ele mesmo se ja for minusculo
 */
int minusc(char c){
    int resp = c;

    if(c >= 'A' && c <= 'Z'){
        resp = c + ('a' - 'A');
    }

    return resp;
}

/**
 * Verifica se duas palavras sao anagramas contando a frequencia das letras.
 * @param s1 primeira palavra do par
 * @param s2 segunda palavra do par
 * @return 1 se forem anagramas, 0 caso contrario
 */
int anagram(char s1[], char s2[]){
    int resp = 1;
    int tam1 = taman(s1);
    int tam2 = taman(s2);

    if(tam1 != tam2){
        resp = 0;
    } else {
        int cont[256];
        
        for(int i = 0; i < 256; i++){
            cont[i] = 0;
        }

        for(int i = 0; i < tam1; i++){
            cont[(unsigned char)minusc(s1[i])]++;
            cont[(unsigned char)minusc(s2[i])]--;
        }

        for(int i = 0; i < 256; i++){
            if(cont[i] != 0){
                resp = 0;
            }
        }
    }

    return resp;
}

/**
 * Metodo principal que le os pares de palavras e imprime SIM ou NAO.
 * @return 0 padrao da linguagem C
 */
int main(){
    char s1[1000];
    char s2[1000];

    while(scanf("%999s", s1) == 1 && fim(s1) == 0){
        if(scanf("%999s", s2) != 1){
            break;
        }

        if(anagram(s1, s2) == 1){
            printf("SIM\n");
        } else {
            printf("NAO\n"); 
        }
    }

    return 0;
}