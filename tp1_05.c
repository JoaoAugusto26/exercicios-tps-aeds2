/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_05
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Conta o comprimento util da linha, parando na quebra de linha.
 * O fgets guarda o '\n' final dentro do vetor, e ele nao faz parte
 * do conteudo lido.
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
 * Converte em numero inteiro os digitos presentes na linha, acumulando
 * resp vezes dez mais o valor do digito a cada posicao. Caracteres que
 * nao sao digitos, inclusive o sinal de menos, sao ignorados em vez de
 * zerarem o resultado, de modo que uma linha sem digito algum devolve
 * zero.
 * @param s linha lida da entrada padrao
 * @return valor inteiro formado pelos digitos encontrados
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
 * Soma os digitos de um numero inteiro, de forma recursiva.
 * O caso base e n igual a zero, quando nao restam digitos a somar.
 * No caso recursivo, o ultimo digito (n % 10) e somado ao resultado
 * obtido sobre o restante do numero (n / 10). Nao usa contador nem
 * acumulador porque o proprio n encolhe a cada chamada, o que dispensa
 * o metodo auxiliar de inicializacao.
 * @param n numero inteiro nao negativo
 * @return soma dos digitos de n
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
 * Le a entrada padrao linha a linha ate encontrar FIM ou o fim do
 * arquivo, e escreve a soma dos digitos de cada linha lida. O laco e
 * controlado pelo retorno do fgets porque a entrada pode terminar sem
 * a marca FIM, e nesse caso o fgets falha sem alterar o vetor, o que
 * deixaria o laco preso na ultima linha.
 * @return 0 ao termino normal do programa
 */
int main(){
    char lin[1000];

    while(fgets(lin, 1000, stdin) != NULL && fim(lin) == 0){
        int num = Int(lin);
        printf("%d\n", soma(num));
    }

    return 0;
}
