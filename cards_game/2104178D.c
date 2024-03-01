//Introdução à programação - E-fólio A - alínea d
//Samuel Parente, n.º2104178

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMERO_CARTAS 64 //Quantidade de cartas do baralho
#define TAMANHO_STRING_CARTA 4 // Tamanho de cada string para cada carta (3 caracteres + 1 para o caracter nulo '\0')
#define TAMANHO_MAXIMO_ENTRADA 4  // Tamanho máximo do vetor de inteiros das posicoes das cartas a serem lidos
#define COLUNA_LINHA_MINIMA 11 // Posições mínimas para coluna e linha formato ColunaLinha
#define COLUNA_LINHA_MAXIMA 88 // Posições máximas para coluna e linha formato ColunaLinha
#define POSICAO_INVALIDA 999999 //Número aleatório para indicar que a posição é inválida.
#define TAMANHO_MAXIMO_LINHA 100 //tamanho buffer entrada

//Função para gerar números aleatórios
unsigned int randaux() {
    
    static long seed=1;
    return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);

}

//Baralhar os códigos das cartas
int* Baralhar(int v[], int n) {
    
    int i, j, aux;

    for (i = 0; i < n-1; i++){
    
        j = i + randaux() % (n-i);
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;	
    
    }
}

//Preenche o baralho com os dados das strings fornecidas no enunciado
void preencheCartas(char baralho[][TAMANHO_STRING_CARTA]) {

    for (int i = 0; i < NUMERO_CARTAS; ++i) {
    
    // Preencher a operação (troca a cada 16 cartas)
    char operacao;
    
    switch (i / 16) {
    case 0:
        operacao = '+';
        break;
    case 1:
        operacao = '-';
        break;
    case 2:
        operacao = '*';
        break;
    case 3:
        operacao = '/';
        break;
    }
    
    // Preencher o número (1 a 4, troca a cada 4 cartas)
    int numero = i / 4 % 4 + 1;
    
    // Preencher a letra (A a D, troca a cada carta)
    char letra = 'A' + (i % 4);
    
    // Formatar a string e armazenar
    snprintf(baralho[i], TAMANHO_STRING_CARTA, "%c%d%c", operacao, numero, letra);
    }
}

//Verificar o input do utilizador
void validaPosicoes(int posicoesCartas[]){
    
    int i, flagErroForaLimites = 0 ; 
    
    //valida as posições fornecidas pelo utilizador
    for (i = 0; i<4; i++){
        
        if(posicoesCartas[i] >=COLUNA_LINHA_MINIMA && posicoesCartas[i] <= COLUNA_LINHA_MAXIMA && flagErroForaLimites == 0){
            
            ;
            
        }
        else if(posicoesCartas[i] >=COLUNA_LINHA_MINIMA && posicoesCartas[i] <= COLUNA_LINHA_MAXIMA && flagErroForaLimites == 1){
            
            posicoesCartas[i] = POSICAO_INVALIDA;
            flagErroForaLimites == 1;
            break;
            
        }
        else{
            posicoesCartas[i] = POSICAO_INVALIDA;
            flagErroForaLimites == 1;
            break;
        }
    }
    //resto das entradas vai ficar invalida porque encontrou uma invalida
    for(i;i<4;i++){
         posicoesCartas[i] = POSICAO_INVALIDA;
    }
    
}

//mostra no ecra o baralho
void mostraBaralho(char baralhoEmJogo[][TAMANHO_STRING_CARTA], int estadoBaralhoJogo[]) {
    
    printf("    [1] [2] [3] [4] [5] [6] [7] [8]\n");

    for (int i = 0; i < 8; i++) { //corre colunas
    
        printf("[%d] ",i+1);
        
        for (int j = 0; j < 8; j++) { //corre linha
     
            int indice = i + j * 8;
            
                if(estadoBaralhoJogo[indice]==0){

                    printf("### ");

                }
                else if(estadoBaralhoJogo[indice]==1){

                    printf("%3s ",  baralhoEmJogo[indice]);

                }
                else if(estadoBaralhoJogo[indice]==2){

                    printf("   ");

                }
                else{

                        printf("###");

                }
           
        }
            
     printf("\n");
    }
  
}

//inicia/reinicia o vector com os códigos das cartas 
void reiniciaCodigosCartas(int codigosCartas[]){

    for (int i = 0; i < 64; i++) {
    
        codigosCartas[i] = i;
            
    }
  
}

//inicia/reinicia o vector com o estado das cartas 
void reiniciaEstadoBaralho(int estadoBaralhoJogo[]){

    for (int i = 0; i < 64; i++) {
    
        estadoBaralhoJogo[i] = 0;
            
    }
  
}

//limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void iniciaPorDefeitoPosicoes(int posicoesCartas[]){
    
    for(int i = 0; i < TAMANHO_MAXIMO_ENTRADA; i++){
        
        posicoesCartas[i] = POSICAO_INVALIDA;
        
    }
}

void criaBaralhoJogo(int codigosCartas[], char baralhoEmJogo[][TAMANHO_STRING_CARTA] , char baralho[][TAMANHO_STRING_CARTA]){

    int i, j = 0;

    for(i = 0; i<64; i++){

        j = codigosCartas[i];
        strcpy(baralhoEmJogo[i],baralho[j]);

    }

}

void lerEntradaJogada(char *ptr, char linha[], int posicoesCartas[]){
    
     printf("Insira ate 4 numeros inteiros iguais ou superiores a 10 separados por espaço: \n");
    
    //Limpar buffer para não haver "lixo" lido indesejado e lè entrada
    limparBuffer();
    fgets(linha, TAMANHO_MAXIMO_LINHA, stdin);
    
    int i = 0;
    while (i < TAMANHO_MAXIMO_ENTRADA && *ptr != '\0') {
        int num;
        int ret = sscanf(ptr, "%d", &num);

        if (ret == 1) {
            posicoesCartas[i++] = num;

            // Avança para o próximo número na string
            while (*ptr != ' ' && *ptr != '\0') {
                ptr++;
            }

            // Avança para o próximo caracter não vazio
            while (*ptr == ' ') {
                ptr++;
            }
        } else {
            // Se não foi possível ler um número, para o loop
            break;
        }
    }
}

// Função jogar
void jogar (char baralhoEmJogo[64][TAMANHO_STRING_CARTA], int posicoesCartas[TAMANHO_MAXIMO_ENTRADA], int estadoBaralhoJogo[]) {
    for (int i = 0; i < TAMANHO_MAXIMO_ENTRADA - 1; ++i) {
        for (int j = i + 1; j < TAMANHO_MAXIMO_ENTRADA; ++j) {
            // Obtém os índices correspondentes na matriz 8x8
            int colunaI = (posicoesCartas[i] / 10) - 1;
            int linhaI = (posicoesCartas[i] % 10) - 1;

            int colunaJ = (posicoesCartas[j] / 10) - 1;
            int linhaJ = (posicoesCartas[j] % 10) - 1;

            // Verifica se pelo menos uma propriedade é igual
            if (baralhoEmJogo[linhaI * 8 + colunaI][0] == baralhoEmJogo[linhaJ * 8 + colunaJ][0] ||
                baralhoEmJogo[linhaI * 8 + colunaI][1] == baralhoEmJogo[linhaJ * 8 + colunaJ][1] ||
                baralhoEmJogo[linhaI * 8 + colunaI][2] == baralhoEmJogo[linhaJ * 8 + colunaJ][2]) {
                
                //DEBUG
                // Pelo menos uma propriedade é igual
                printf("Cartas iguais encontradas:\n");
                printf("Carta %d: Coluna %d, Linha %d\n", i + 1, colunaI, linhaI);
                printf("Carta %d: Coluna %d, Linha %d\n", j + 1, colunaJ, linhaJ);
            }
        }
    }
}

//Ponto de entrada do programa
void main() {
    
    int desperdicio, i, aux, jogo = 0;
    int codigosCartas[NUMERO_CARTAS]; //Criar um array com os valores de 1 a 64 que sao os códigos das cartas
    char baralho[NUMERO_CARTAS][TAMANHO_STRING_CARTA];  // Definir o vetor de strings para criar um baralho
    int posicoesCartas[TAMANHO_MAXIMO_ENTRADA]; // Guarda as posições que o utilizador inseriu
    char linha[TAMANHO_MAXIMO_LINHA]; // Armazena em bruto a entrada do utilizador
    char *ptr = linha; //Apontador para os dados em bruto a serem tratados
    char baralhoEmJogo[NUMERO_CARTAS][TAMANHO_STRING_CARTA]; //vetor com baralho do jogo
    int estadoBaralhoJogo[NUMERO_CARTAS]; //Armazena estado jogo. 0 carta nao virada,1 carta virada, 2 carta eliminada
    int contadorJogadas;
    //inicia o vetor codigos das cartas
    reiniciaCodigosCartas(codigosCartas);

    //inicia o vetor do estado do baralho
    reiniciaEstadoBaralho(estadoBaralhoJogo);
    
    //inicia o vetor de entrada das posições
    iniciaPorDefeitoPosicoes(posicoesCartas);

    //Preencher o vetor das cartas com os valores fornecidos na alinea a
    preencheCartas(baralho);

    //ler entrada do utilizador para o gerador de números aleatórios
    printf("Insira 1 numero inteiro maior ou igual a 0: \n");
    scanf("%d", &desperdicio);
    
    //"alimenta" o gerador de numeros aleatórios consoante entrada do utilizador
    for(int z=0; z<desperdicio; z++){
    randaux();
    }

    // Baralhar os codigos dos índices das cartas
    Baralhar(codigosCartas, NUMERO_CARTAS);
    
    //Cria o baralho para o jogador jogar, de forma a manter o baralho ordenado original para outras operaçoões
    criaBaralhoJogo(codigosCartas,baralhoEmJogo,baralho);

    //começa o jogo
    jogo = 1;
    contadorJogadas = 0;

    while(jogo == 1){
   
        //ler entrada da sequencia de números das posições das cartas
        lerEntradaJogada(ptr, linha, posicoesCartas);

        //jogar
        jogar(baralhoEmJogo,posicoesCartas,estadoBaralhoJogo);

        if (contadorJogadas <= 5 && jogo == 1){

            //Mostrar o baralho mas apenas com as cartas seleccionadas 5 vezes
            mostraBaralho(baralhoEmJogo, estadoBaralhoJogo);
            contadorJogadas++;
        
        }
        else if (contadorJogadas > 5 && jogo == 1){

            //continua a jogar mas nao mostra o baralho
            
            contadorJogadas++;
        
        }
        else{
            //fim jogo. mostra baralho final e quantidade de cartas por revelar e quantidade de jogadas
        }
    }
}