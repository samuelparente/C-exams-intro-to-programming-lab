//Introdução à programação - E-fólio B - alínea B
//Samuel Parente, n.º2104178

//**************** Includes ****************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//**************** Defines ****************

#define BUFFER_ENTRADA 100

//**************** Structs e variáveis ****************

//Dados do jogador
struct Jogador {
    char *nome;
    int pontos;
};

//Dados de um jogo
struct Jogo {
    struct Jogador *arrayDeJogadores;
    int numeroDeJogadores;
};

//Dados da lista de jogos ocorridos
struct ListaDeJogos {
    struct Jogo *arrayDeJogos;
    int numeroDeJogos;
    int numTotalJogadores;
};

char *linhaTemp = NULL;
int totalJogos = 0;

//**************** Funções ****************

//Cria um novo jogador
struct Jogador criarJogador(const char *nome, int pontos) {
   
    struct Jogador novoJogador;
    novoJogador.nome = strdup(nome);
    novoJogador.pontos = pontos;
    return novoJogador;

}

//Cria um novo jogo
struct Jogo criarJogo() {
    
    struct Jogo novoJogo;
    novoJogo.arrayDeJogadores = NULL;
    novoJogo.numeroDeJogadores = 0;
    return novoJogo;

}

//Adiciona um jogador a um jogo
void adicionarJogadorAoJogo(struct Jogo *jogo, const struct Jogador *jogador) {
   
    jogo->numeroDeJogadores++;
    jogo->arrayDeJogadores = (struct Jogador *)realloc(jogo->arrayDeJogadores, jogo->numeroDeJogadores * sizeof(struct Jogador));
    jogo->arrayDeJogadores[jogo->numeroDeJogadores - 1] = *jogador;

}

//Adiciona um jogo a uma lista de jogos
void adicionarJogoALista(struct ListaDeJogos *listaDeJogos, const struct Jogo *jogo) {
    
    listaDeJogos->numeroDeJogos++;
    listaDeJogos->arrayDeJogos = (struct Jogo *)realloc(listaDeJogos->arrayDeJogos, listaDeJogos->numeroDeJogos * sizeof(struct Jogo));
    listaDeJogos->arrayDeJogos[listaDeJogos->numeroDeJogos - 1] = *jogo;
    listaDeJogos->numTotalJogadores += jogo->numeroDeJogadores;

}

//Inicializa a lista de jogos
struct ListaDeJogos inicializarListaDeJogos() {
   
    struct ListaDeJogos listaDeJogos;
    listaDeJogos.arrayDeJogos = NULL;
    listaDeJogos.numeroDeJogos = 0;
    return listaDeJogos;

}

//Desperdício de leitura dos nomes iniciais. Nesta alínea não são usados.
void lerNomesJogadores(void){

    //Aloca memória para ler entrada dos dados
    linhaTemp = (char *)malloc(BUFFER_ENTRADA);

    //Verifica se alocou com sucesso ou não
    if (linhaTemp == NULL) {
        
        printf("Erro ao alocar memoria para ler entrada de dados.\n");
        
        //Liberta memória e termina o programa
        free(linhaTemp);
        exit(EXIT_FAILURE);
    }

    //Lê entrada enquanto houver dados a ler
    while (1) {
        
        //Lê a linha
        fgets(linhaTemp, BUFFER_ENTRADA, stdin);

        //Linha vazia
        if (linhaTemp[0] == '\n')
        {
            
            break;
        
        }

    }

}

//Lê as linhas de entrada e realiza operações nos dados
struct ListaDeJogos lerLinhas(int *numJogos, int *numTotalJogadores) {

    int contadorLinhasVazias = 0;
    int flagNovoJogo = 0;

    //Desperdício de leitura
    lerNomesJogadores();

    //Inicializa a lista dos jogos
    struct ListaDeJogos listaDeJogos = inicializarListaDeJogos();

    //Cria um novo jogo
    struct Jogo jogoNovo = criarJogo();

    //Aloca espaço para ler a linha
    linhaTemp = (char *)malloc(BUFFER_ENTRADA);

    //Verifica se alocou com sucesso ou não
    if (linhaTemp == NULL) {

        printf("Erro ao alocar memoria para ler entrada de dados.\n");
        
        //Liberta memória e termina o programa
        free(linhaTemp);
        exit(EXIT_FAILURE);

    }

    //Leitura dos dados enquanto houver entrada de dados
    while (1) {
        
        fgets(linhaTemp, BUFFER_ENTRADA, stdin);

        //Encontrou linha em branco, indica início de um novo jogo
        if (linhaTemp[0] == '\n') {
            
            //Adiciona o jogo à lista de jogos
            adicionarJogoALista(&listaDeJogos, &jogoNovo);

            //Cria um novo jogo
            jogoNovo = criarJogo();
            contadorLinhasVazias++;

            //Se encontrou duas linhas em branco, indica fim dos dados
            if (contadorLinhasVazias == 2) {
               
                break;
            
            }

        } 
        //As linhas não estão vazias e representam um jogador e os seus pontos
        else {
            
            //Dados do novo jogador
            char *nomeJogador = strtok(linhaTemp, ":");
            char *pontos_str = strtok(NULL, ":");
            
            // Verifica se formato de entrada está correcto
            if (nomeJogador != NULL && pontos_str != NULL) {
                
                //Remove a quebra de linha se existir
                nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

                //Converte a string para um inteiro
                char *endptr;
                long pontos = strtol(pontos_str, &endptr, 10);

                //Verifica se a conversão foi bem-sucedida e se o valor é não negativo
                if (*endptr == '\n' || *endptr == '\0') {
                    
                    if (pontos >= 0) {
                        
                        //Cria o jogador
                        struct Jogador jogadorNovo = criarJogador(nomeJogador, (int)pontos);

                        //Adiciona o jogador ao jogo
                        adicionarJogadorAoJogo(&jogoNovo, &jogadorNovo);

                        //Reinicia o contador de linhas vazias
                        contadorLinhasVazias = 0;

                    } 
                    else {

                        printf("Pontos negativos não são permitidos: %s\n", linhaTemp);

                    }
                } 
                else {
                   
                    printf("Formato de pontos inválido: %s\n", linhaTemp);
                
                }
            }
            else {
                
                printf("Formato de entrada inválido: %s\n", linhaTemp);
                
            }
            
        }

    }
    
    //Atribui o número de jogos
    *numJogos = listaDeJogos.numeroDeJogos;

    //Calcula o numero de jogadores
    listaDeJogos.numTotalJogadores = 0; 
    
    for (int i = 0; i < listaDeJogos.numeroDeJogos-1; ++i) {
        
        listaDeJogos.numTotalJogadores += listaDeJogos.arrayDeJogos[i].numeroDeJogadores;
    
    }

    //Atribui o número de jogadores
    *numTotalJogadores = listaDeJogos.numTotalJogadores;

    //Retorna a lista de jogos
    return listaDeJogos;

}

//Função para libertar a memória alocada
void libertaMemoria(struct ListaDeJogos *listaDeJogos) {
    
    //Liberta a memória alocada para os jogadores de cada jogo
    for (int i = 0; i < listaDeJogos->numeroDeJogos; ++i) {
        
        for (int j = 0; j < listaDeJogos->arrayDeJogos[i].numeroDeJogadores; ++j) {
           
            free(listaDeJogos->arrayDeJogos[i].arrayDeJogadores[j].nome);
        
        }

        free(listaDeJogos->arrayDeJogos[i].arrayDeJogadores);
    
    }

    //Liberta a memória alocada para os jogos
    free(listaDeJogos->arrayDeJogos);

    //Liberta a memória alocada para ler a entrada
    free(linhaTemp);

}

/*
//Função para mostrar os dados
void mostraDados(const struct ListaDeJogos *listaDeJogos) {
    
    for (int i = 0; i < listaDeJogos->numeroDeJogos-1; ++i) {
        
        printf("Jogo %d:\n", i + 1);

        for (int j = 0; j < listaDeJogos->arrayDeJogos[i].numeroDeJogadores; ++j) {
          
            printf("  Jogador %d: Nome: %s, Pontos: %d\n", j + 1, listaDeJogos->arrayDeJogos[i].arrayDeJogadores[j].nome, listaDeJogos->arrayDeJogos[i].arrayDeJogadores[j].pontos);
        }

    }

}
*/

//**************** Entrada do programa principal ****************

int main()
{
    
    int numJogos, numTotalJogadores;

    //Chama a função para ler as linhas de entrada dos dados
    struct ListaDeJogos listaDeJogos = lerLinhas(&numJogos, &numTotalJogadores);

    //***debug***
    //mostraDados(&listaDeJogos);

    // Mostra o número de jogos e de jogadores
    printf("%d %d\n", numJogos-1,numTotalJogadores);

    //Liberta a memória
    libertaMemoria(&listaDeJogos);

    return 0;

}
