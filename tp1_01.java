/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_01
 */
import java.util.Scanner;

public class tp1_01{

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
     * Cifra a linha deslocando cada caractere tres posicoes no seu codigo,
     * conforme a chave fixa tres definida no enunciado. O deslocamento e
     * aplicado ao caractere em si, sem retorno ao inicio do alfabeto, de
     * modo que espacos, digitos e pontuacao tambem sao deslocados.
     * @param s linha a ser cifrada
     * @return a linha com todos os caracteres deslocados em tres posicoes
     */
    public static String cif(String s){
        String resp = "";

        for(int i = 0; i < s.length(); i++){
            char c = (char) (s.charAt(i) + 3);
            resp = resp + c;
        }

        return resp;
    }

    /**
     * Le a entrada padrao linha a linha ate encontrar FIM e escreve, para
     * cada linha lida, a sua versao cifrada.
     * @param args nao utilizado
     */
    public static void main(String[] args){
        Scanner leitor = new Scanner(System.in);

        String linha = leitor.nextLine();

        while(fim(linha) == false){
            System.out.println(cif(linha));
            linha = leitor.nextLine();
        }

        leitor.close();
    }
}