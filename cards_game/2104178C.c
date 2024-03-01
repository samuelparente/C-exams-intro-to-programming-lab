//Introdução à programação - E-fólio A - alínea c
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
    
    // Preenche a operação (troca a cada 16 cartas)
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
void mostraBaralho(char baralho[][TAMANHO_STRING_CARTA], int codigosCartas[], int posicoesCartas[]) {
    
    int cartaEncontrada, linha, coluna;
    
    //Validar entrada do utilizador
    validaPosicoes(posicoesCartas);
    
    printf("    [1] [2] [3] [4] [5] [6] [7] [8]\n");

    for (int i = 0; i < 8; i++) { //corre colunas
    
        printf("[%d] ",i+1);
        
        for (int j = 0; j < 8; j++) { //corre linha
     
            int indice = i + j * 8;
            
            //verifica se a carta e a do utilizador para mostrar ou nao
            for(int h = 0; h < 4; h++){
            
                //separa em colunas e linhas e valida
                if(posicoesCartas[h] != 999999){
                    
                    coluna = (posicoesCartas[h] / 10) - 1; //subtrai 1 para facilitar pois os indices começam em 0
                    linha = (posicoesCartas[h] % 10) - 1; //subtrai 1 para facilitar pois os indices começam em 0
                
                     if(i == linha && j == coluna){
                    
                        cartaEncontrada = 1;
                        break;
                    }
                    else {
                        
                        cartaEncontrada = 0;
    
                    }
                    
                }
                else{
                    
                    cartaEncontrada = 0;

                }
           
            }
            
            if(cartaEncontrada == 1){
                printf("%3s ",  baralho[codigosCartas[indice]]);
            }
            else{
                printf("### ");
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

//Ponto de entrada do programa
void main() {
    
    int desperdicio, i, aux = 0;
    int codigosCartas[NUMERO_CARTAS]; // Criar um array com os valores de 1 a 64 que sao os códigos das cartas
    char baralho[NUMERO_CARTAS][TAMANHO_STRING_CARTA];  // Definir o vetor de strings para criar um baralho
    int posicoesCartas[TAMANHO_MAXIMO_ENTRADA]; // Array com as posições lidas da entrada do utilizador
    char linha[TAMANHO_MAXIMO_LINHA]; // Armazena a linha total escrita pelo utilizador
    char *ptr = linha; //Apontador para os dados brutos lidos da entrada do utilizador
    
    //inicia o vetor codigos das cartas
    reiniciaCodigosCartas(codigosCartas);
    
    //inicia o vetor de entrada das posições
    iniciaPorDefeitoPosicoes(posicoesCartas);

    //Preenche o vetor das cartas com os valores fornecidos na alinea a
    preencheCartas(baralho);

    //lê entrada do utilizador para o gerador de números aleatórios
    printf("Insira 1 numero inteiro maior ou igual a 0: \n");
    scanf("%d", &desperdicio);
    
    //lê entrada da sequencia de números das posições das cartas
    //dezenas-coluna, unidades-linha
    printf("Insira ate 4 numeros inteiros iguais ou superiores a 10 separados por espaço: \n");

    //Limpar buffer para não haver "lixo" indesejado na leitura
    limparBuffer();
    
    fgets(linha, sizeof(linha), stdin);
    
    i = 0;
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
    
    //"alimenta" o gerador de numeros aleatórios consoante entrada do utilizador
    for(int z=0; z<desperdicio; z++){
    randaux();
    }

    // Baralha os codigos dos índices das cartas
    Baralhar(codigosCartas, NUMERO_CARTAS);
    
    //Mostrar o baralho mas apenas com as cartas seleccionadas 
    mostraBaralho(baralho,codigosCartas,posicoesCartas);

}