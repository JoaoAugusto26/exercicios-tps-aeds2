/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp1_01
 */
import java.util.Scanner;

public class tp1_01{

    /**
     * Verifica se a string lida eh a condicao de parada do programa (FIM).
     * @param s string que sera testada
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
     * Aplica a cifra de Cesar deslocando os caracteres da palavra em 3 posicoes.
     * @param s string original
     * @return string criptografada
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
     * Metodo principal para ler as linhas, chamar o ciframento e imprimir o resultado.
     * @param args argumentos da linha de comando
     */
    public static void main(String[] args){
        Scanner leitor = new Scanner(System.in);

        while(leitor.hasNextLine() == true){
            String linha = leitor.nextLine();

            if(fim(linha) == true){
                break;
            }
            System.out.println(cif(linha));
        }

        leitor.close();
    }
}