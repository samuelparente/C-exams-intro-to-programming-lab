//Introdução à programação - E-fólio B - alínea A
//Samuel Parente, n.º2104178

//**************** Includes ****************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//**************** Defines ****************

#define BUFFER_ENTRADA 100

//**************** Variáveis ****************

char *linhaTemp = NULL;  // Apontador para a string temporária para leitura iniciadp como NULL
char **jogadores = NULL; //Apontador para apontador do array de nomes (um nome é um array de caracteres)
int totalJogadores = 0; //Contador de jogadores
int totalCaracteres = 0; //Contador de caracteres

//**************** Funções ****************

//Função para libertar a memória alocada
void libertaMemoria(void){

    free(linhaTemp);

    for (int i = 0; i < totalJogadores; i++) {
        free(jogadores[i]);
    }

    free(jogadores);
}

//Função para mostrar a quantidade de jogadores e de caracteres
void mostraDados(void){
   
    printf("%d %d\n", totalJogadores, totalCaracteres);    

}

//Função para ler as linhas de entrada que contêm os nomes
void lerLinhas(void){

    //Lê entrada enquanto houver dados
    while (1) {
       
        //Aloca espaço para ler a linha
        linhaTemp = (char *)malloc(BUFFER_ENTRADA);
        
        //Verifica se alocou com sucesso ou não
        if (linhaTemp == NULL) {
            
            printf("Erro a alocar espaco em memoria para ler a linha com o nome.\n");
            
            //Liberta memória e termina o programa
            free(linhaTemp);
            exit(EXIT_FAILURE);

        }

        //Leitura do nome e verificação correcta da leitura
        if (fgets(linhaTemp, BUFFER_ENTRADA, stdin) == NULL || linhaTemp[0] == '\n') {
            
            break;
        
        }

        //Remove a quebra de linha
        linhaTemp[strcspn(linhaTemp, "\n")] = '\0';

        //Aloca espaço para o novo nome do jogador
        char *novoNome = (char *)malloc(strlen(linhaTemp) + 1);
        
        //Verifica se alocou correctamente
        if (novoNome == NULL) {
          
            printf("Erro a alocar memoria para o nome do jogador.\n");
            
            //Liberta memória e termina o programa
            free(novoNome);
            exit(EXIT_FAILURE);
        
        }

        // Copia o nome para o novo espaço alocado
        strcpy(novoNome, linhaTemp);

        // Realoca o vetor para incluir o novo nome
        jogadores = (char **)realloc(jogadores, (totalJogadores + 1) * sizeof(char *));

        //Verifica se alocou correctamente
        if (jogadores == NULL) {
            
            printf("Erro ao realocar memoria do vetor de jogadores.\n");
            
            //Liberta memória e termina o programa
            free(jogadores);
            exit(EXIT_FAILURE);

        }

        // Atribui o novo nome ao vetor
        jogadores[totalJogadores] = novoNome;

        // Atualiza as contagens
        totalJogadores++;
        totalCaracteres += strlen(linhaTemp);

    }

    
    // Liberta a memória alocada
    libertaMemoria();

}

//**************** Entrada do programa principal ****************

int main() {
  
    //Chama a função para ler as linhas com os nomes
    lerLinhas();
    
    //Mostra o total de jogadores e de caracteres
    mostraDados();

    return 0;
}