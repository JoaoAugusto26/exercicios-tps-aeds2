/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp3_01
 */

import java.util.Scanner;

/**
 * Representa a data de registro de um veiculo.
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
     * Metodos de acesso aos atributos da data. Cada get devolve o valor do
     * campo correspondente e cada set o substitui. Como os atributos sao
     * privados, o acesso de fora da classe passa obrigatoriamente por eles.
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
    public static Veiculo parseVeic(String s){
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
        String listaComb = "";
        for(int i = 0; i < combustivel.length; i++){
            listaComb += combustivel[i];
            if(i < combustivel.length - 1){
                listaComb += ",";
            }
        }
        
        return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano +
               " ## " + categoria + " ## [" + listaComb + "] ## " + cilindros +
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
     * @param caminho localizacao do CSV
     * @return vetor contendo os objetos Veiculo
     */
    public static Veiculo[] ler(String caminho) throws Exception {
        Veiculo[] veics = new Veiculo[50000]; 
        int n = 0;
        
        Scanner leitor = new Scanner(new java.io.File(caminho));
        
        if(leitor.hasNextLine()){
            leitor.nextLine(); 
        }
        
        while(leitor.hasNextLine()){
            String l = leitor.nextLine();
            if(l.length() > 0){
                veics[n] = Veiculo.parseVeic(l);
                n = n + 1;
            }
        }
        leitor.close();
        
        Veiculo[] resp = new Veiculo[n];
        for(int i = 0; i < n; i++){
            resp[i] = veics[i];
        }
        
        return resp;
    }
}

/**
 * Questao 1 do Trabalho Pratico 3: ordenacao por mergesort.
 */
public class tp3_01 {

    /**
     * Compara dois veiculos pela chave da ordenacao: primeiro o consumo na
     * cidade e, em caso de empate, a categoria.
     * A categoria usa o compareTo direto, sem ignorar a caixa como na questao
     * 4 do TP2: as treze categorias do dataset seguem a mesma convencao de
     * maiusculas, entao a ordem pelo codigo do caractere ja e a alfabetica.
     * @param a primeiro veiculo
     * @param b segundo veiculo
     * @return negativo se a vem antes, positivo se vem depois, zero se
     *         empatarem nas duas chaves
     */
    public static int comparar(Veiculo a, Veiculo b){
        int resp = 0;

        if(a.getConsumoCidade() < b.getConsumoCidade()){
            resp = -1;
        } else if(a.getConsumoCidade() > b.getConsumoCidade()){
            resp = 1;
        } else {
            resp = a.getCategoria().compareTo(b.getCategoria());
        }

        return resp;
    }

    /**
     * Ordena o vetor com mergesort. Este metodo so faz a primeira chamada
     * recursiva, com os limites do vetor inteiro.
     * @param array vetor de veiculos a ser ordenado
     * @param n quantidade de veiculos no vetor
     */
    public static void mergesort(Veiculo[] array, int n){
        mergesort(array, 0, n - 1);
    }

    /**
     * Divide o trecho entre esq e dir ao meio, ordena cada metade
     * recursivamente e depois intercala as duas metades ja ordenadas.
     * Um trecho com um elemento so ja esta ordenado, e e ai que a recursao
     * para.
     * @param array vetor de veiculos
     * @param esq primeira posicao do trecho
     * @param dir ultima posicao do trecho
     */
    public static void mergesort(Veiculo[] array, int esq, int dir){
        if(esq < dir){
            int meio = (esq + dir) / 2;
            mergesort(array, esq, meio);
            mergesort(array, meio + 1, dir);
            intercalar(array, esq, meio, dir);
        }
    }

    /**
     * Junta duas metades vizinhas e ja ordenadas, a de esq ate meio e a de
     * meio + 1 ate dir, em um unico trecho ordenado.
     * As metades sao copiadas para dois vetores auxiliares, e a cada passo o
     * menor entre os primeiros de cada uma volta para o vetor original. No
     * empate sai o da metade da esquerda, o que mantem a ordem de entrada
     * entre registros iguais e deixa o mergesort estavel.
     * @param array vetor de veiculos
     * @param esq inicio da metade da esquerda
     * @param meio fim da metade da esquerda
     * @param dir fim da metade da direita
     */
    public static void intercalar(Veiculo[] array, int esq, int meio, int dir){
        int n1 = meio - esq + 1;
        int n2 = dir - meio;

        Veiculo[] a1 = new Veiculo[n1];
        Veiculo[] a2 = new Veiculo[n2];

        int i = 0;
        int j = 0;
        int k = esq;

        for(i = 0; i < n1; i++){
            a1[i] = array[esq + i];
        }

        for(j = 0; j < n2; j++){
            a2[j] = array[meio + 1 + j];
        }

        i = 0;
        j = 0;

        while(i < n1 && j < n2){
            if(comparar(a1[i], a2[j]) <= 0){
                array[k] = a1[i];
                i++;
            } else {
                array[k] = a2[j];
                j++;
            }

            k++;
        }

        while(i < n1){
            array[k] = a1[i];
            i++;
            k++;
        }

        while(j < n2){
            array[k] = a2[j];
            j++;
            k++;
        }
    }

    /**
     * Le o dataset, guarda em um vetor proprio os veiculos cujos ids aparecem
     * na entrada padrao, ordena esse vetor por consumo na cidade, com a
     * categoria como desempate, e imprime o resultado.
     * O laco consulta hasNextLine antes de ler porque a entrada pode terminar
     * sem o -1, e nesse caso o nextLine lancaria excecao.
     * A entrada termina na linha com -1.
     * @param args argumentos da linha de comando
     */
    public static void main(String[] args) throws Exception {

        Veiculo[] frota = LeitorCsv.ler("/tmp/veiculos.csv");
        Veiculo[] selec = new Veiculo[50000];
        int numSelec = 0;

        Scanner leitor = new Scanner(System.in);

        while(leitor.hasNextLine() == true){
            String entrada = leitor.nextLine();

            if(entrada.equals("-1") == true){
                break;
            }

            int idPesq = Integer.parseInt(entrada);

            for(int i = 0; i < frota.length; i++){
                if(frota[i].getId() == idPesq){
                    selec[numSelec] = frota[i];
                    numSelec++;
                    break;
                }
            }
        }

        mergesort(selec, numSelec);

        for(int i = 0; i < numSelec; i++){
            System.out.println(selec[i].format());
        }

        leitor.close();
    }
}
