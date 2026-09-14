/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * TP1_02
 */

import java.util.Scanner;
import java.util.Random;

class tp1_02{

    /**
     * Verifica se a string lida e a condicao de parada (FIM).
     * @param s string que sera testada
     * @return true se a string for FIM, false caso contrario
     */
    public static boolean fim(String s) {
        boolean resp = false;
        
        if (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M') {
            resp = true;
        }
        
        return resp;
    }

    /**
     * Sorteia duas letras aleatorias e substitui as ocorrencias da primeira pela segunda.
     * @param s string original que sera alterada
     * @param gerador objeto Random instanciado na main para sortear as letras
     * @return string com as substituicoes efetuadas
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
     * Metodo principal para leitura das linhas, configuracao da semente e impressao.
     * @param args argumentos da linha de comando
     */
    public static void main(String[] args) {
        Scanner leitor = new Scanner(System.in);
        
        Random gerador = new Random();
        gerador.setSeed(4);
        
        while (leitor.hasNextLine() == true) {
            String linha = leitor.nextLine();
            
            if (fim(linha) == true) {
                break;
            }
            
            String n = alterar(linha, gerador);
            System.out.println(n);
        }
        
        leitor.close();
    }
}