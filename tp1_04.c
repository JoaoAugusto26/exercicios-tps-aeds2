/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_04
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o comprimento util da linha, parando na quebra de linha.
 * O fgets guarda o '\n' final dentro do vetor, e ele nao faz parte
 * do conteudo a ser invertido.
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
 * Indica se a linha lida e a marca de encerramento da entrada.
 * Devolve int em vez de bool porque a Regra 5 permite apenas os tipos
 * primitivos e as funcoes de stdio.h e stdlib.h.
 * @param s linha lida da entrada padrao
 * @return 1 se a linha e exatamente FIM, 0 caso contrario
 */
int fim(char s[]){
    int resp = 0;

    if(taman(s) == 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M'){
        resp = 1;
    }

    return resp;
}

/**
 * Copia s para resp na ordem inversa e fecha o resultado com '\0'.
 * O resultado sai pelo segundo parametro porque em C nao se devolve um
 * vetor declarado dentro da funcao: ele deixa de existir quando a
 * chamada termina. Cabe a quem chama fornecer um vetor de destino com
 * espaco suficiente para a string e o terminador.
 * @param s string de origem, preservada
 * @param resp vetor de destino onde a string invertida e escrita
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
 * Le a entrada padrao linha a linha ate encontrar a marca FIM ou o fim
 * do arquivo, e escreve, para cada linha lida, o seu conteudo invertido.
 * O laco e controlado pelo retorno do fgets porque a entrada pode
 * terminar sem a marca FIM, e nesse caso o fgets falha sem alterar o
 * vetor, o que deixaria o laco preso na ultima linha.
 * @return 0 ao termino normal do programa
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