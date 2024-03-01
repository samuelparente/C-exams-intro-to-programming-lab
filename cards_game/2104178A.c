//Introdução à programação - E-fólio A - alínea a
//Samuel Parente, n.º2104178

#include <stdio.h>

#define NUMERO_CARTAS 64 //Quantidade de cartas do baralho
#define TAMANHO_STRING_CARTA 4 // Tamanho de cada string para cada carta (3 caracteres + 1 para o caracter nulo '\0')

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

int main() {

    int codigo;   
    char baralho[NUMERO_CARTAS][TAMANHO_STRING_CARTA];  // Definir o vetor de strings para criar um baralho
    
    //Preencher o vetor das cartas com os valores fornecidos
    preencheCartas(baralho);
    
    //Solicitar ao utilizador o código
    printf("Insira o codigo: ");
    scanf("%d", &codigo);

    //Verifica se o código pertence ao baralho e mostra a carta correspondente
    if (codigo >= 0 && codigo < 64) {
        printf("%s\n", baralho[codigo]); //carta ok
    } 
    else {
        printf("Carta invalida.\n"); //carta não existe no baralho
    }
   
return 0;
}
