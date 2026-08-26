/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_06
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o comprimento util da string, parando no terminador ou na
 * quebra de linha.
 * @param s vetor de caracteres terminado em '\0'
 * @return numero de caracteres antes de '\0', '\n' ou '\r'
 */
int taman(char s[]){
    int resp = 0;
    
    while(s[resp] != '\0' && s[resp] != '\n' && s[resp] != '\r'){
        resp++;
    }
    
    return resp;
}

/**
 * Indica se a string lida e a marca de encerramento da entrada.
 * Devolve int em vez de bool porque a Regra 5 permite apenas os tipos
 * primitivos e as funcoes de stdio.h e stdlib.h.
 * @param s string lida da entrada padrao
 * @return 1 se a string e exatamente FIM, 0 caso contrario
 */
int fim(char s[]){
    int resp = 0;
    
    if(taman(s) == 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M'){
        resp = 1;
    }
    
    return resp;
}

/**
 * Converte uma letra maiuscula na minuscula correspondente e devolve
 * qualquer outro caractere inalterado. A conversao soma a distancia
 * entre 'a' e 'A' porque tolower pertence a ctype.h, biblioteca que
 * esta fora das permitidas pela Regra 5.
 * @param c caractere a converter
 * @return o caractere em minuscula, ou ele mesmo se nao for maiuscula
 */
int minusc(char c){
    int resp = c;

    if(c >= 'A' && c <= 'Z'){
        resp = c + ('a' - 'A');
    }

    return resp;
}

/**
 * Verifica se duas strings sao anagramas, ignorando maiusculas.
 * Tamanhos diferentes ja descartam o par. Nos demais casos, uma tabela
 * de 256 contadores e incrementada pelos caracteres de s1 e decrementada
 * pelos de s2: se toda a tabela terminar zerada, as duas usam exatamente
 * as mesmas letras. O cast para unsigned char impede indice negativo,
 * ja que char tem sinal e um byte acima de 127 acessaria fora do vetor.
 * @param s1 primeira string do par
 * @param s2 segunda string do par
 * @return 1 se sao anagramas, 0 caso contrario
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
 * Le pares de palavras da entrada padrao ate encontrar FIM ou o fim do
 * arquivo, e escreve SIM ou NAO para cada par conforme sejam anagramas.
 * A largura 999 impede que uma palavra maior que o vetor o ultrapasse,
 * e o retorno do scanf controla o laco porque a entrada pode terminar
 * sem a marca FIM, caso em que o vetor manteria o valor anterior e o
 * laco nunca pararia.
 * @return 0 ao termino normal do programa
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