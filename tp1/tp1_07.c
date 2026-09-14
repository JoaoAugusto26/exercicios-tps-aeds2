/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_07
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
 * Encontra o tamanho da maior substring que nao possui caracteres repetidos.
 * Utiliza um vetor auxiliar para marcar os caracteres ja lidos na janela atual.
 * @param s string que sera analisada
 * @return comprimento da maior substring encontrada
 */
int maxSubstring(char s[]){
    int resp = 0;
    int tam = taman(s);
    int cont[256];

    for(int i = 0; i < 256; i++){
        cont[i] = 0;
    }

    int inicio = 0;
    for(int i = 0; i < tam; i++){
        while(cont[(unsigned char)s[i]] > 0){
            cont[(unsigned char)s[inicio]]--;
            inicio++;
        }
        
        cont[(unsigned char)s[i]]++;
        
        if((i - inicio + 1) > resp){
            resp = i - inicio + 1;
        }
    }

    return resp;
}

/**
 * Metodo principal que le as strings da entrada e imprime os resultados.
 * @return 0 padrao da linguagem C
 */
int main(){
    char lin[1000];

    while(fgets(lin, 1000, stdin) != NULL && fim(lin) == 0){
        printf("%d\n", maxSubstring(lin));
    }

    return 0;
}