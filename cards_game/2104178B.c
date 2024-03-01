//Introdução à programação - E-fólio A - alínea b
//Samuel Parente, n.º2104178

#include <stdio.h>

#define NUMERO_CARTAS 64 //Quantidade de cartas do baralho
#define TAMANHO_STRING_CARTA 4 // Tamanho de cada string para cada carta (3 caracteres + 1 para o caracter nulo '\0')

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

//mostra no ecra o baralho
void mostraBaralho(char baralho[][TAMANHO_STRING_CARTA], int codigosCartas[]) {
    
    printf("    [1] [2] [3] [4] [5] [6] [7] [8]\n");

    for (int i = 0; i < 8; i++) { //corre colunas
      printf("[%d] ",i+1);
        for (int j = 0; j < 8; j++) { //corre linha
            int indice = i + j * 8;
            printf("%3s ",  baralho[codigosCartas[indice]]);
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

//Ponto de entrada do programa
void main() {
    
    int desperdicio, i;
    int codigosCartas[NUMERO_CARTAS]; // Criar um array com os valores de 1 a 64 que sao os códigos das cartas
    char baralho[NUMERO_CARTAS][TAMANHO_STRING_CARTA];  // Definir o vetor de strings para criar um baralho

    //inicia o vetor codigos das cartas
    reiniciaCodigosCartas(codigosCartas);

    //Preencher o vetor das cartas com os valores fornecidos na alinea a
    preencheCartas(baralho);

    //ler entrada do utilizador
    scanf("%d", &desperdicio);
    
    //"alimenta" o gerador de numeros aleatórios consoante entrada do utilizador
    for(int z=0; z<desperdicio; z++){
    randaux();
    }

    // Baralhar os codigos dos índices das cartas
    Baralhar(codigosCartas, NUMERO_CARTAS);

    //Mostrar o baralho no ecra
    mostraBaralho(baralho,codigosCartas);

}