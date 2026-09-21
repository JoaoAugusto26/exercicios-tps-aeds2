/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp2_07
 */

import java.util.Scanner;

/**
 * Estrutura dedicada ao armazenamento e formatacao da data de registro.
 */
class Data {
    private int ano;
    private int mes;
    private int dia;

    /**
     * Constroi uma data zerada.
     */
    public Data(){
        this.ano = 0;
        this.mes = 0;
        this.dia = 0;
    }

    /**
     * Constroi uma data com os valores especificados.
     * @param ano ano com quatro digitos
     * @param mes mes de 1 a 12
     * @param dia dia do mes
     */
    public Data(int ano, int mes, int dia){
        this.ano = ano;
        this.mes = mes;
        this.dia = dia;
    }

    /**
     * Getters e Setters
     * Garantem o encapsulamento da classe. O acesso aos campos privados
     * e feito exclusivamente por meio destes metodos.
     */
    public int getAno(){ return ano; }
    public void setAno(int ano){ this.ano = ano; }
    public int getMes(){ return mes; }
    public void setMes(int mes){ this.mes = mes; }
    public int getDia(){ return dia; }
    public void setDia(int dia){ this.dia = dia; }

    /**
     * Converte uma string AAAA-MM-DD em um objeto Data.
     * @param s string contendo a data
     * @return a Data correspondente
     */
    public static Data parseData(String s){
        String[] partes = s.split("-");
        int ano = Integer.parseInt(partes[0]);
        int mes = Integer.parseInt(partes[1]);
        int dia = Integer.parseInt(partes[2]);
        return new Data(ano, mes, dia);
    }

    /**
     * Formata a data no padrao DD/MM/AAAA.
     * @return a string formatada
     */
    public String format(){
        String textoDia = "" + dia;
        String textoMes = "" + mes;
        String textoAno = "" + ano;

        while(textoDia.length() < 2){
            textoDia = "0" + textoDia;
        }

        while(textoMes.length() < 2){
            textoMes = "0" + textoMes;
        }

        while(textoAno.length() < 4){
            textoAno = "0" + textoAno;
        }

        return textoDia + "/" + textoMes + "/" + textoAno;
    }
}

/**
 * Representa um veiculo com os atributos do dataset.
 */

class Veiculo {
    private int id;
    private String marca;
    private String modelo;
    private int ano;
    private String categoria;
    private String[] combustivel;
    private int cilindros;
    private double cilindrada;
    private String transmissao;
    private String tracao;
    private double consumoCidade;
    private double consumoEstrada;
    private double co2;
    private boolean turbo;
    private Data dataRegistro;

    /**
     * Constroi um veiculo vazio.
     */
    public Veiculo(){
        this.id = 0;
        this.marca = "";
        this.modelo = "";
        this.ano = 0;
        this.categoria = "";
        this.combustivel = new String[0];
        this.cilindros = 0;
        this.cilindrada = 0.0;
        this.transmissao = "";
        this.tracao = "";
        this.consumoCidade = 0.0;
        this.consumoEstrada = 0.0;
        this.co2 = 0.0;
        this.turbo = false;
        this.dataRegistro = new Data();
    }

    /**
     * Metodos de acesso aos quinze atributos do veiculo. Cada get devolve o
     * valor do campo correspondente e cada set o substitui. Como os atributos
     * sao privados, o acesso de fora da classe passa obrigatoriamente por eles.
     * Tres convencoes do dataset valem para os campos numericos: cilindros,
     * cilindrada e co2 valem zero nos eletricos puros. E dataRegistro guarda a
     * data do registro na fonte de dados, que nao e a data de fabricacao.
     */
    public int getId(){ return id; }
    public void setId(int id){ this.id = id; }
    public String getMarca(){ return marca; }
    public void setMarca(String marca){ this.marca = marca; }
    public String getModelo(){ return modelo; }
    public void setModelo(String modelo){ this.modelo = modelo; }
    public int getAno(){ return ano; }
    public void setAno(int ano){ this.ano = ano; }
    public String getCategoria(){ return categoria; }
    public void setCategoria(String categoria){ this.categoria = categoria; }
    public String[] getCombustivel(){ return combustivel; }
    public void setCombustivel(String[] combustivel){ this.combustivel = combustivel; }
    public int getCilindros(){ return cilindros; }
    public void setCilindros(int cilindros){ this.cilindros = cilindros; }
    public double getCilindrada(){ return cilindrada; }
    public void setCilindrada(double cilindrada){ this.cilindrada = cilindrada; }
    public String getTransmissao(){ return transmissao; }
    public void setTransmissao(String transmissao){ this.transmissao = transmissao; }
    public String getTracao(){ return tracao; }
    public void setTracao(String tracao){ this.tracao = tracao; }
    public double getConsumoCidade(){ return consumoCidade; }
    public void setConsumoCidade(double consumoCidade){ this.consumoCidade = consumoCidade; }
    public double getConsumoEstrada(){ return consumoEstrada; }
    public void setConsumoEstrada(double consumoEstrada){ this.consumoEstrada = consumoEstrada; }
    public double getCo2(){ return co2; }
    public void setCo2(double co2){ this.co2 = co2; }
    public boolean isTurbo(){ return turbo; }
    public void setTurbo(boolean turbo){ this.turbo = turbo; }
    public Data getDataRegistro(){ return dataRegistro; }
    public void setDataRegistro(Data dataRegistro){ this.dataRegistro = dataRegistro; }

    /**
     * Extrai os dados de uma linha CSV para montar o veiculo.
     * @param s linha completa do arquivo
     * @return veiculo preenchido
     */
    public static Veiculo parseVeiculo(String s){
        Veiculo v = new Veiculo();
        
        String[] colunas = s.split(",");

        v.setId(Integer.parseInt(colunas[0]));
        v.setMarca(colunas[1]);
        v.setModelo(colunas[2]);
        v.setAno(Integer.parseInt(colunas[3]));
        v.setCategoria(colunas[4]);
        
        v.setCombustivel(colunas[5].split(";"));
        
        if(colunas[6].length() == 0){
            v.setCilindros(0);
        } else {
            v.setCilindros(Integer.parseInt(colunas[6]));
        }

        if(colunas[7].length() == 0){
            v.setCilindrada(0.0);
        } else {
            v.setCilindrada(Double.parseDouble(colunas[7]));
        }

        v.setTransmissao(colunas[8]);
        v.setTracao(colunas[9]);

        if(colunas[10].length() == 0){
            v.setConsumoCidade(0.0);
        } else {
            v.setConsumoCidade(Double.parseDouble(colunas[10]));
        }

        if(colunas[11].length() == 0){
            v.setConsumoEstrada(0.0);
        } else {
            v.setConsumoEstrada(Double.parseDouble(colunas[11]));
        }

        if(colunas[12].length() == 0){
            v.setCo2(0.0);
        } else {
            v.setCo2(Double.parseDouble(colunas[12]));
        }

        v.setTurbo(Boolean.parseBoolean(colunas[13]));
        v.setDataRegistro(Data.parseData(colunas[14]));

        return v;
    }

    /**
     * Formata manualmente um numero decimal com ponto como separador.
     * @param valor numero a ser formatado
     * @param casas numero de casas decimais
     * @return string formatada
     */
    public static String decimal(double valor, int casas){
        long fator = 1;

        for(int i = 0; i < casas; i++){
            fator = fator * 10;
        }

        long total = (long) (valor * fator + 0.5);
        long parteInteira = total / fator;
        long parteDecimal = total % fator;

        String texto = "" + parteDecimal;

        while(texto.length() < casas){
            texto = "0" + texto;
        }

        return parteInteira + "." + texto;
    }

    /**
     * Gera a representacao em string do veiculo para impressao.
     * @return string formatada com todas as informacoes
     */
    public String format(){
        String listaCombustivel = "";
        for(int i = 0; i < combustivel.length; i++){
            listaCombustivel += combustivel[i];
            if(i < combustivel.length - 1){
                listaCombustivel += ",";
            }
        }
        
        return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano +
               " ## " + categoria + " ## [" + listaCombustivel + "] ## " + cilindros +
               " ## " + decimal(cilindrada, 1) + " ## " + transmissao +
               " ## " + tracao + " ## " + decimal(consumoCidade, 2) +
               " ## " + decimal(consumoEstrada, 2) + " ## " + decimal(co2, 1) +
               " ## " + turbo + " ## " + dataRegistro.format() + "]";
    }
}

/**
 * Classe utilitaria para ler e processar o arquivo CSV.
 */

class LeitorCsv {
    /**
     * Le o arquivo e devolve um vetor com os veiculos instanciados.
     * @param caminhoArquivo localizacao do CSV
     * @return vetor contendo os objetos Veiculo
     */
    public static Veiculo[] ler(String caminhoArquivo) throws Exception {
        Veiculo[] veiculos = new Veiculo[50000]; 
        int n = 0;
        
        Scanner scanner = new Scanner(new java.io.File(caminhoArquivo));
        
        if(scanner.hasNextLine()){
            scanner.nextLine(); 
        }
        
        while(scanner.hasNextLine()){
            String linha = scanner.nextLine();
            if(linha.length() > 0){
                veiculos[n] = Veiculo.parseVeiculo(linha);
                n = n + 1;
            }
        }
        scanner.close();
        
        Veiculo[] resposta = new Veiculo[n];
        for(int i = 0; i < n; i++){
            resposta[i] = veiculos[i];
        }
        
        return resposta;
    }
}

public class tp2_07 {
    /**
     * Ordena um balde pelo atributo cilindrada usando ordenacao por insercao.
     * E a mesma insercao da questao anterior, so que aplicada a um pedaco do
     * vetor e comparando numeros em vez de texto.
     * O deslocamento so acontece enquanto a cilindrada anterior for
     * estritamente maior, entao empates mantem a ordem em que entraram no
     * balde.
     * @param balde vetor de veiculos de um unico balde
     * @param n quantidade de veiculos ocupando o balde
     */
    public static void insercaoBalde(Veiculo[] balde, int n){
        for(int i = 1; i < n; i++){
            Veiculo tmp = balde[i];
            int j = i - 1;

            while(j >= 0 && balde[j].getCilindrada() > tmp.getCilindrada()){
                balde[j + 1] = balde[j];
                j--;
            }

            balde[j + 1] = tmp;
        }
    }

    /**
     * Ordena o vetor pelo atributo cilindrada usando o Bucketsort.
     * O enunciado fixa os parametros: dez baldes e a cilindrada normalizada
     * pelo valor 8.1. Dividir a cilindrada por 8.1 leva o valor para a faixa
     * de zero a um, e multiplicar por dez escolhe em qual dos dez baldes o
     * veiculo cai. Cada balde cobre uma faixa de 0.81 litro.
     * Depois de distribuir, cada balde e ordenado por insercao e os baldes
     * sao concatenados na ordem, do primeiro ao ultimo.
     * Os testes de indice negativo ou acima do ultimo balde existem para o
     * caso de aparecer uma cilindrada fora da faixa prevista pelo enunciado,
     * que sem eles acessaria posicao inexistente do vetor.
     * Como a distribuicao percorre a entrada em ordem e a insercao e estavel,
     * veiculos de mesma cilindrada mantem a ordem original.
     * @param array vetor de veiculos a ser ordenado
     * @param n quantidade de veiculos no vetor
     */
    public static void bucketSort(Veiculo[] array, int n){
        int numBaldes = 10;
        double normalizador = 8.1;

        Veiculo[][] baldes = new Veiculo[numBaldes][n];
        int[] tamanho = new int[numBaldes];

        for(int i = 0; i < numBaldes; i++){
            tamanho[i] = 0;
        }

        for(int i = 0; i < n; i++){
            int indice = (int) (array[i].getCilindrada() / normalizador * numBaldes);

            if(indice < 0){
                indice = 0;
            }

            if(indice >= numBaldes){
                indice = numBaldes - 1;
            }

            baldes[indice][tamanho[indice]] = array[i];
            tamanho[indice]++;
        }

        for(int i = 0; i < numBaldes; i++){
            insercaoBalde(baldes[i], tamanho[i]);
        }

        int pos = 0;

        for(int i = 0; i < numBaldes; i++){
            for(int j = 0; j < tamanho[i]; j++){
                array[pos] = baldes[i][j];
                pos++;
            }
        }
    }

    /**
     * Le o dataset, guarda em um vetor proprio os veiculos cujos ids aparecem
     * na entrada padrao, ordena esse vetor por cilindrada e imprime o resultado.
     * O laco consulta hasNextLine antes de ler porque a entrada pode terminar
     * sem o -1, e nesse caso o nextLine lancaria excecao.
     * A entrada termina na linha com -1.
     * @param args argumentos da linha de comando
     */
    public static void main(String[] args) throws Exception {
        
        Veiculo[] frota = LeitorCsv.ler("/tmp/veiculos.csv");
        Veiculo[] selecionados = new Veiculo[50000];
        int numSelecionados = 0;
        
        Scanner leitor = new Scanner(System.in);
        
        while(leitor.hasNextLine() == true){
            String entrada = leitor.nextLine();
            
            if(entrada.equals("-1") == true){
                break;
            }
            
            int idPesquisa = Integer.parseInt(entrada);
            
            for(int i = 0; i < frota.length; i++){
                if(frota[i].getId() == idPesquisa){
                    selecionados[numSelecionados] = frota[i];
                    numSelecionados++;
                    break;
                }
            }
        }
        
        bucketSort(selecionados, numSelecionados);
        
        for(int i = 0; i < numSelecionados; i++){
            System.out.println(selecionados[i].format());
        }
        
        leitor.close();
    }
}