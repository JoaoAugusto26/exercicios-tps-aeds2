/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_05
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o tamanho util da string, ignorando a quebra de linha.
 * @param s vetor de caracteres a ser medido
 * @return numero de caracteres reais da string
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
 * Converte os digitos presentes na string para um numero inteiro.
 * @param s linha lida da entrada
 * @return valor inteiro formado pelos digitos
 */
int Int(char s[]){
    int resp = 0;
    int tam = taman(s);
    
    for(int i = 0; i < tam; i++){
        if(s[i] >= '0' && s[i] <= '9'){
            resp = (resp * 10) + (s[i] - '0');
        }
    }
    
    return resp;
}

/**
 * Metodo recursivo que soma os digitos de um numero inteiro.
 * @param n numero inteiro para calcular a soma dos digitos
 * @return soma total dos digitos
 */
int soma(int n){
    int resp;

    if(n == 0){
        resp = 0;
    } else {
        resp = (n % 10) + soma(n / 10);
    }

    return resp;
}

/**
 * Metodo principal que le as entradas e imprime a soma dos digitos.
 * @return 0 padrao da linguagem C
 */
int main(){
    char lin[1000];

    while(fgets(lin, 1000, stdin) != NULL && fim(lin) == 0){
        int num = Int(lin);
        printf("%d\n", soma(num));
    }

    return 0;
}
