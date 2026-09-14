/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_10
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
 * Verifica se o caractere recebido e uma vogal.
 * @param c caractere a ser testado
 * @return 1 se for vogal, 0 caso contrario
 */
int vogal(char c){
    int resp = 0;
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
       c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
        resp = 1;
    }
    return resp;
}

/**
 * Verifica se o caractere recebido e uma letra.
 * @param c caractere a ser testado
 * @return 1 se for uma letra entre a-z ou A-Z, 0 caso contrario
 */
int letra(char c){
    int resp = 0;
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        resp = 1;
    }
    return resp;
}

/**
 * Metodo recursivo para verificar se a string so tem vogais.
 * @param s string original
 * @param i indice atual da recursao
 * @return 1 se so tiver vogais, 0 caso contrario
 */
int vogaisRec(char s[], int i){
    int resp;
    
    if(s[i] == '\0' || s[i] == '\n' || s[i] == '\r'){
        resp = 1; 
    } else if(vogal(s[i]) == 0){
        resp = 0; 
    } else {
        resp = vogaisRec(s, i + 1);
    }
    
    return resp;
}

/**
 * Metodo chamador para inicializar a recursividade de vogais.
 * @param s string a ser testada
 * @return 1 se for composta so de vogais, 0 caso contrario
 */
int vogais(char s[]){
    return vogaisRec(s, 0);
}

/**
 * Metodo recursivo para verificar se a string so tem consoantes.
 * @param s string original
 * @param i indice atual da recursao
 * @return 1 se so tiver consoantes, 0 caso contrario
 */
int consoantesRec(char s[], int i){
    int resp;
    
    if(s[i] == '\0' || s[i] == '\n' || s[i] == '\r'){
        resp = 1;
    } else if(letra(s[i]) == 0 || vogal(s[i]) == 1){
        resp = 0; 
    } else {
        resp = consoantesRec(s, i + 1);
    }
    
    return resp;
}

/**
 * Metodo chamador para inicializar a recursividade de consoantes.
 * @param s string a ser testada
 * @return 1 se for composta so de consoantes, 0 caso contrario
 */
int consoantes(char s[]){
    return consoantesRec(s, 0);
}

/**
 * Metodo recursivo para verificar se a string e um numero inteiro.
 * @param s string original
 * @param i indice atual da recursao
 * @return 1 se tiver apenas digitos, 0 caso contrario
 */
int inteiroRec(char s[], int i){
    int resp;
    
    if(s[i] == '\0' || s[i] == '\n' || s[i] == '\r'){
        resp = 1;
    } else if(s[i] < '0' || s[i] > '9'){
        resp = 0;
    } else {
        resp = inteiroRec(s, i + 1);
    }
    
    return resp;
}

/**
 * Metodo chamador para inicializar a recursividade de inteiros.
 * @param s string a ser testada
 * @return 1 se for um numero inteiro, 0 caso contrario
 */
int inteiro(char s[]){
    return inteiroRec(s, 0);
}

/**
 * Metodo recursivo para verificar se a string e um numero real.
 * @param s string original
 * @param i indice atual da recursao
 * @param pontos contador de separadores
 * @return 1 se for um numero real valido, 0 caso contrario
 */
int realRec(char s[], int i, int pontos){
    int resp;
    
    if(pontos > 1){
        resp = 0; 
    } else if(s[i] == '\0' || s[i] == '\n' || s[i] == '\r'){
        resp = 1;
    } else if(s[i] == '.' || s[i] == ','){
        resp = realRec(s, i + 1, pontos + 1);
    } else if(s[i] < '0' || s[i] > '9'){
        resp = 0;
    } else {
        resp = realRec(s, i + 1, pontos);
    }
    
    return resp;
}

/**
 * Metodo chamador para inicializar a recursividade de numeros reais.
 * @param s string a ser testada
 * @return 1 se for um numero real valido, 0 caso contrario
 */
int real(char s[]){
    return realRec(s, 0, 0); 
}

/**
 * Metodo principal que le as strings e imprime as quatro validacoes.
 * @return 0 padrao da linguagem C
 */
int main(){
    char lin[1000];

    while(fgets(lin, 1000, stdin) != NULL && fim(lin) == 0){
        if(vogais(lin) == 1){
            printf("SIM ");
        } else {
            printf("NAO ");
        }

        if(consoantes(lin) == 1){
            printf("SIM ");
        } else {
            printf("NAO ");
        }

        if(inteiro(lin) == 1){
            printf("SIM ");
        } else {
            printf("NAO ");
        }

        if(real(lin) == 1){
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
    }

    return 0;
}