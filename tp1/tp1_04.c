/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_04
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o tamanho real da string, ignorando a quebra de linha.
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
 * Verifica se a string lida e a condicao de parada (FIM).
 * @param s linha lida da entrada padrao
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
 * Preenche o vetor de resposta com a string lida de tras pra frente.
 * @param s string original
 * @param resp vetor de destino onde a string invertida sera salva
 */
void inverter(char s[], char resp[]){
    int tam = taman(s);
    int j = 0;

    for(int i = tam - 1; i >= 0; i--){
        resp[j] = s[i];
        j++;
    }
    
    resp[j] = '\0'; 
}

/**
 * Metodo principal que le as entradas e imprime as strings invertidas.
 * @return 0 padrao da linguagem C
 */
int main(){
    char lin[1000];
    char invert[1000];

    while(fgets(lin, 1000, stdin) != NULL && fim(lin) == 0){
        inverter(lin, invert);
        printf("%s\n", invert);
    }

    return 0;
}