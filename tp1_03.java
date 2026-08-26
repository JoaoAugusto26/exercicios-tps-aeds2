/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_03
 */

import java.util.Scanner;

public class tp1_03{

    /**
     * Indica se a linha lida e a marca de encerramento da entrada.
     * A comparacao e feita caractere a caractere porque a Regra 5 permite
     * apenas charAt e length na classe String.
     * @param s linha lida da entrada padrao
     * @return true se a linha e exatamente FIM, false caso contrario
     */
    public static boolean fim(String s){
        boolean resp = false;

        if(s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M'){
            resp = true;
        }

        return resp;
    }

    /**
     * Indica se o caractere e uma vogal, maiuscula ou minuscula.
     * @param c caractere a testar
     * @return true se c e uma das cinco vogais, false caso contrario
     */
    public static boolean vogal(char c){
        boolean resp = false;
        
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
            resp = true;
        }
        
        return resp;
    }

    /**
     * Indica se o caractere e uma letra do alfabeto, maiuscula ou minuscula.
     * Letras acentuadas e cedilha ficam de fora porque a Regra 9 manda
     * considerar apenas os codigos entre A e Z e entre a e z.
     * @param c caractere a testar
     * @return true se c esta em a-z ou A-Z, false caso contrario
     */
    public static boolean letra(char c){
        boolean resp = false;
        
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            resp = true;
        }
        
        return resp;
    }

    /**
     * Indica se a linha e formada somente por vogais. Uma linha vazia
     * devolve true, pois o laco nao chega a executar e nada contradiz a
     * condicao.
     * @param s linha lida da entrada padrao
     * @return true se todos os caracteres sao vogais, false caso contrario
     */
    public static boolean vogais(String s){
        boolean resp = true;

        for(int i = 0; i < s.length(); i++){
            if(vogal(s.charAt(i)) == false){
                resp = false;
            }
        }

        return resp;
    }

    /**
     * Indica se a linha e formada somente por consoantes. Cada caractere
     * precisa ser letra e nao ser vogal: apenas negar a vogal deixaria
     * passar espaco, digito e pontuacao.
     * @param s linha lida da entrada padrao
     * @return true se todos os caracteres sao consoantes, false caso contrario
     */
    public static boolean consoantes(String s){
        boolean resp = true;

        for(int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            if(letra(c) == false || vogal(c) == true){
                resp = false;
            }
        }

        return resp;
    }

    /**
     * Indica se a linha corresponde a um numero inteiro, isto e, se e
     * formada somente por digitos.
     * @param s linha lida da entrada padrao
     * @return true se todos os caracteres estao entre 0 e 9, false caso contrario
     */
    public static boolean inteiro(String s){
        boolean resp = true;

        for(int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            if(c < '0' || c > '9'){
                resp = false;
            }
        }

        return resp;
    }

    /**
     * Indica se a linha corresponde a um numero real. Conta os separadores
     * ponto e virgula, aceitando no maximo um, e exige que o restante seja
     * digito. Um separador solto no inicio ou no fim e aceito, como em 12.
     * e ,05, porque e assim que a saida esperada os classifica.
     * @param s linha lida da entrada padrao
     * @return true se a linha representa um numero real, false caso contrario
     */
    public static boolean real(String s){
        boolean resp = true;
        int cont = 0;

        for(int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            
            if(c == '.' || c == ','){
                cont = cont + 1;
            } else if(c < '0' || c > '9'){
                resp = false;
            }
        }

        if(cont > 1){
            resp = false;
        }

        return resp;
    }

    /**
     * Le a entrada padrao linha a linha ate encontrar FIM e escreve, para
     * cada linha, quatro respostas separadas por espaco indicando se ela e
     * somente vogais, somente consoantes, um inteiro e um real. As respostas
     * usam NAO sem til, conforme a saida esperada.
     * @param args nao utilizado
     */
    public static void main(String[] args){
        Scanner leitor = new Scanner(System.in);
        String lin = leitor.nextLine();

        while(fim(lin) == false){
            String x1;
            String x2;
            String x3;
            String x4;

            if(vogais(lin) == true){
                x1 = "SIM";
            } else {
                x1 = "NAO";
            }

            if(consoantes(lin) == true){
                x2 = "SIM";
            } else {
                x2 = "NAO";
            }

            if(inteiro(lin) == true){
                x3 = "SIM";
            } else {
                x3 = "NAO";
            }

            if(real(lin) == true){
                x4 = "SIM";
            } else {
                x4 = "NAO";
            }

            System.out.println(x1 + " " + x2 + " " + x3 + " " + x4);
            
            lin = leitor.nextLine();
        }

        leitor.close();
    }
}