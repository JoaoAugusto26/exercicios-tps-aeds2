/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_12
 */
import java.util.Scanner;

public class tp1_12 {

    /**
     * Verifica se a string lida e a condicao de parada (FIM).
     * @param s string a ser testada
     * @return true se a string for FIM, false caso contrario
     */
    public static boolean fim(String s){
        boolean resp = false;

        if(s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M'){
            resp = true;
        }

        return resp;
    }

    /**
     * Converte os caracteres numericos da string em um numero inteiro.
     * @param s string contendo os digitos
     * @return o valor inteiro gerado
     */
    public static int Int(String s){
        int resp = 0;
        
        for(int i = 0; i < s.length(); i++){
            if(s.charAt(i) >= '0' && s.charAt(i) <= '9'){
                resp = (resp * 10) + (s.charAt(i) - '0');
            }
        }
        
        return resp;
    }

    /**
     * Metodo recursivo que soma os digitos de um numero inteiro.
     * @param n numero inteiro para calcular a soma
     * @return soma total dos digitos
     */
    public static int soma(int n){
        int resp;

        if(n == 0){
            resp = 0;
        } else {
            resp = (n % 10) + soma(n / 10);
        }

        return resp;
    }

    /**
     * Metodo principal que le as entradas e imprime os resultados.
     * @param args argumentos da linha de comando
     */
    public static void main(String[] args){
        Scanner leitor = new Scanner(System.in);

        while(leitor.hasNextLine() == true){
            String lin = leitor.nextLine();

            if(fim(lin) == true){
                break;
            }

            int num = Int(lin);
            System.out.println(soma(num));
        }

        leitor.close();
    }
}