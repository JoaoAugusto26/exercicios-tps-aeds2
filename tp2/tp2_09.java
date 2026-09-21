/**
 * Nome: Joao Augusto Moreira Cunha
 * Materia: AEDS II - PUC Minas
 * tp2_09
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
 * Lista de veiculos com alocacao sequencial, adaptada da lista de inteiros
 * vista em sala. O vetor guarda referencias para os registros, nao copias:
 * inserir e remover movem apenas as referencias, e nao os dados do veiculo.
 * O atributo n diz quantas posicoes estao ocupadas; as posicoes de n em
 * diante existem no vetor mas nao fazem parte da lista.
 */
class Lista {
    private Veiculo[] array;
    private int n;

    /**
     * Cria uma lista vazia com capacidade padrao de dez posicoes.
     */
    public Lista(){
        this(10);
    }

    /**
     * Cria uma lista vazia com a capacidade informada.
     * @param tamanho quantidade maxima de registros que a lista comporta
     */
    public Lista(int tamanho){
        array = new Veiculo[tamanho];
        n = 0;
    }

    /**
     * Insere um registro na primeira posicao, deslocando os demais uma casa
     * para a direita. O deslocamento comeca do fim para o inicio, senao cada
     * copia sobrescreveria a posicao ainda nao movida.
     * @param veic registro a ser inserido
     * @throws Exception se a lista estiver cheia
     */
    public void inserirInicio(Veiculo veic) throws Exception {
        if(n >= array.length){
            throw new Exception("Erro: lista cheia");
        }

        for(int i = n; i > 0; i--){
            array[i] = array[i - 1];
        }

        array[0] = veic;
        n++;
    }

    /**
     * Insere um registro na ultima posicao ocupada da lista.
     * Nao ha deslocamento: a posicao n esta livre por definicao.
     * @param veic registro a ser inserido
     * @throws Exception se a lista estiver cheia
     */
    public void inserirFim(Veiculo veic) throws Exception {
        if(n >= array.length){
            throw new Exception("Erro: lista cheia");
        }

        array[n] = veic;
        n++;
    }

    /**
     * Insere um registro na posicao informada e desloca os demais para a
     * direita, do fim para o inicio pelo mesmo motivo do inserirInicio.
     * @param veic registro a ser inserido
     * @param posicao posicao de destino, entre zero e n
     * @throws Exception se a lista estiver cheia ou a posicao for invalida
     */
    public void inserir(Veiculo veic, int posicao) throws Exception {
        if(n >= array.length){
            throw new Exception("Erro: lista cheia");
        }

        if(posicao < 0 || posicao > n){
            throw new Exception("Erro: posicao invalida");
        }

        for(int i = n; i > posicao; i--){
            array[i] = array[i - 1];
        }

        array[posicao] = veic;
        n++;
    }

    /**
     * Remove e devolve o primeiro registro, deslocando os demais uma casa
     * para a esquerda. Aqui o deslocamento vai do inicio para o fim, porque
     * cada posicao so e sobrescrita depois de ja ter sido lida.
     * @return o registro removido
     * @throws Exception se a lista estiver vazia
     */
    public Veiculo removerInicio() throws Exception {
        if(n == 0){
            throw new Exception("Erro: lista vazia");
        }

        Veiculo resp = array[0];
        n--;

        for(int i = 0; i < n; i++){
            array[i] = array[i + 1];
        }

        return resp;
    }

    /**
     * Remove e devolve o ultimo registro. Basta reduzir n: a posicao deixa de
     * fazer parte da lista sem precisar mover nada.
     * @return o registro removido
     * @throws Exception se a lista estiver vazia
     */
    public Veiculo removerFim() throws Exception {
        if(n == 0){
            throw new Exception("Erro: lista vazia");
        }

        n--;

        return array[n];
    }

    /**
     * Remove e devolve o registro da posicao informada, deslocando os
     * seguintes uma casa para a esquerda.
     * @param posicao posicao do registro, entre zero e n menos um
     * @return o registro removido
     * @throws Exception se a lista estiver vazia ou a posicao for invalida
     */
    public Veiculo remover(int posicao) throws Exception {
        if(n == 0){
            throw new Exception("Erro: lista vazia");
        }

        if(posicao < 0 || posicao >= n){
            throw new Exception("Erro: posicao invalida");
        }

        Veiculo resp = array[posicao];
        n--;

        for(int i = posicao; i < n; i++){
            array[i] = array[i + 1];
        }

        return resp;
    }

    /**
     * Escreve os registros da lista, do primeiro ao ultimo, um por linha.
     */
    public void mostrar(){
        for(int i = 0; i < n; i++){
            System.out.println(array[i].format());
        }
    }
}

/**
 * Questao 9 do Trabalho Pratico 2: lista com alocacao sequencial.
 */
public class tp2_09 {

    /**
     * Localiza um veiculo do dataset pelo id, com pesquisa sequencial.
     * @param frota vetor com todos os veiculos lidos do arquivo
     * @param id identificador procurado
     * @return o veiculo correspondente, ou null se nao existir
     */
    public static Veiculo procurar(Veiculo[] frota, int id){
        Veiculo resp = null;

        for(int i = 0; i < frota.length; i++){
            if(frota[i].getId() == id){
                resp = frota[i];
                break;
            }
        }

        return resp;
    }

    /**
     * Escreve na saida a marca e o modelo de um registro removido.
     * O enunciado pede a palavra (R) seguida dos dois atributos, e a saida
     * esperada nao tem espaco entre o parentese e a marca.
     * @param veic registro que acabou de sair da lista
     */
    public static void mostrarRem(Veiculo veic){
        System.out.println("(R)" + veic.getMarca() + " " + veic.getModelo());
    }

    /**
     * Le o dataset e processa a entrada padrao em duas partes.
     * Na primeira, cada id vira um registro inserido no fim da lista; ela
     * termina na linha com -1.
     * Na segunda, a primeira linha diz quantos comandos virao, e cada comando
     * seguinte insere ou remove: II no inicio, IF no fim, I* na posicao
     * informada, RI do inicio, RF do fim e R* da posicao informada. Nos
     * comandos de insercao vem junto o id do registro; no I* a posicao vem
     * antes do id.
     * Cada remocao escreve uma linha; no fim a lista inteira e mostrada.
     * @param args argumentos da linha de comando
     */
    public static void main(String[] args) throws Exception {

        Veiculo[] frota = LeitorCsv.ler("/tmp/veiculos.csv");
        Lista lista = new Lista(1000);

        Scanner leitor = new Scanner(System.in);

        while(leitor.hasNextLine() == true){
            String entrada = leitor.nextLine();

            if(entrada.equals("-1") == true){
                break;
            }

            lista.inserirFim(procurar(frota, Integer.parseInt(entrada)));
        }

        int numComandos = 0;

        if(leitor.hasNextLine() == true){
            numComandos = Integer.parseInt(leitor.nextLine());
        }

        for(int i = 0; i < numComandos; i++){
            String[] partes = leitor.nextLine().split(" ");
            String comando = partes[0];

            if(comando.equals("II") == true){
                lista.inserirInicio(procurar(frota, Integer.parseInt(partes[1])));
            } else if(comando.equals("IF") == true){
                lista.inserirFim(procurar(frota, Integer.parseInt(partes[1])));
            } else if(comando.equals("I*") == true){
                lista.inserir(procurar(frota, Integer.parseInt(partes[2])), Integer.parseInt(partes[1]));
            } else if(comando.equals("RI") == true){
                mostrarRem(lista.removerInicio());
            } else if(comando.equals("RF") == true){
                mostrarRem(lista.removerFim());
            } else if(comando.equals("R*") == true){
                mostrarRem(lista.remover(Integer.parseInt(partes[1])));
            }
        }

        lista.mostrar();

        leitor.close();
    }
}
