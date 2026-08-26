/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * TP1_02
 */

import java.util.Scanner;
import java.util.Random;

class tp1_02{

    /**
     * Indica se a linha lida e a marca de encerramento da entrada.
     * A comparacao e feita caractere a caractere porque a Regra 5 permite
     * apenas charAt e length na classe String.
     * @param s linha lida da entrada padrao
     * @return true se a linha e exatamente FIM, false caso contrario
     */
    public static boolean fim(String s) {
        boolean resp = false;
        
        if (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M') {
            resp = true;
        }
        
        return resp;
    }

    /**
     * Sorteia duas letras minusculas pelo gerador recebido e devolve uma
     * nova string em que toda ocorrencia da primeira foi trocada pela
     * segunda. O gerador vem por parametro em vez de ser criado aqui
     * dentro porque o setSeed seria refeito a cada chamada e todas as
     * linhas acabariam sorteando as mesmas duas letras.
     * @param s linha a ser alterada
     * @param gerador fonte de numeros aleatorios, com semente ja definida
     * @return a linha com as substituicoes aplicadas
     */
    public static String alterar(String s, Random gerador) {
        String resp = "";
        
        char letra1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
        char letra2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
        
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == letra1) {
                resp += letra2; 
            } else {
                resp += s.charAt(i);
            }
        }
        
        return resp;
    }

    /**
     * Le a entrada padrao linha a linha ate encontrar FIM e escreve, para
     * cada linha, o resultado da substituicao aleatoria. A semente e fixada
     * em quatro conforme o enunciado, para que a correcao automatica obtenha
     * sempre a mesma sequencia de letras sorteadas.
     * @param args nao utilizado
     */
    public static void main(String[] args) {
        Scanner leitor = new Scanner(System.in);
        
        Random gerador = new Random();
        gerador.setSeed(4);
        
        String linha = leitor.nextLine();
        
        while (fim(linha) == false) {
            String n = alterar(linha, gerador);
            System.out.println(n);
            
            linha = leitor.nextLine();
        }
        
        leitor.close();
    }
}