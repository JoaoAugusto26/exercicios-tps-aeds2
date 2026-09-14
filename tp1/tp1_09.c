/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_09
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o tamanho util da string, ignorando as quebras de linha.
 * @param s vetor de caracteres a ser medido
 * @return quantidade de caracteres validos
 */
int taman(char s[]){
    int resp = 0;
    
    while(s[resp] != '\0' && s[resp] != '\n' && s[resp] != '\r'){
        resp++;
    }
    
    return resp;
}

/**
 * Verifica se a string lida e a condicao de parada do programa (FIM).
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
 * Metodo recursivo que aplica o deslocamento da cifra de Cesar.
 * @param s string original
 * @param resp vetor de destino onde a linha cifrada e escrita
 * @param i posicao atual (contador da recursao)
 */
void cifrarRec(char s[], char resp[], int i){
    if(s[i] == '\0' || s[i] == '\n' || s[i] == '\r'){
        resp[i] = '\0';
    } else {
        resp[i] = s[i] + 3;
        cifrarRec(s, resp, i + 1);
    }
}

/**
 * Metodo chamador que inicializa o indice da recursividade em 0.
 * @param s linha a ser cifrada
 * @param resp vetor de destino onde a linha cifrada e escrita
 */
void cifrar(char s[], char resp[]){
    cifrarRec(s, resp, 0);
}

/**
 * Metodo principal que le as strings da entrada e imprime as versoes cifradas.
 * @return 0 padrao da linguagem C
 */
int main(){
    char lin[1000];
    char cif[1000];

    while(fgets(lin, 1000, stdin) != NULL && fim(lin) == 0){
        cifrar(lin, cif);
        printf("%s\n", cif);
    }

    return 0;
}