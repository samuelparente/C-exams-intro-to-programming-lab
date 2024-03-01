//Introdução à programação - E-fólio B - alínea C
//Samuel Parente, n.º2104178

//**************** Includes ****************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//**************** Defines ****************

#define BUFFER_ENTRADA 100

//**************** Structs e variáveis ****************

//Lista de Jogadores
struct Jogadores {
    char **nomes;
    int numeroDeJogadores;
};

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

//Inicializa uma lista de jogos
struct ListaDeJogos inicializarListaDeJogos() {
    
    struct ListaDeJogos listaDeJogos;
    listaDeJogos.arrayDeJogos = NULL;
    listaDeJogos.numeroDeJogos = 0;
    return listaDeJogos;

}

//Lê os nomes dos jogadores
struct Jogadores lerNomesJogadores(void) {
    
    struct Jogadores jogadores;
    jogadores.nomes = NULL;
    jogadores.numeroDeJogadores = 0;

    char buffer[BUFFER_ENTRADA];
   
    //Lê enquanto não encontra primeira linha vazia
    while (1) {

        //Verifica leitura
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            
            //Erro ao ler a linha
            printf("Erro ao ler a linha.\n");
            exit(EXIT_FAILURE);
        
        }

        //Remove a quebra de linha se existir
        buffer[strcspn(buffer, "\n")] = '\0';

        //Se a linha está vazia, encerra a leitura
        if (buffer[0] == '\0') {
        
            break;
        
        }

        //Aloca dinamicamente espaço para o novo nome
        char *novoNome = strdup(buffer);
        
        //Verifica se alocou correctamente a memória
        if (novoNome == NULL) { 
            
            printf("Erro ao alocar memória para o nome do jogador.\n");
            
             //Liberta memória e termina o programa
            free(novoNome);
            exit(EXIT_FAILURE);
       
        }

        //Realoca o array de nomes
        char **nomesTemp = (char **)realloc(jogadores.nomes, (jogadores.numeroDeJogadores + 1) * sizeof(char *));
       
        //Verifica se realocou correctamente a memória
        if (nomesTemp == NULL) {
            
            printf("Erro ao realocar memória para o array de nomes.\n");
            
             //Liberta memória e termina o programa
            free(nomesTemp);
            exit(EXIT_FAILURE);
        
        }

        // Atualiza o array de nomes
        jogadores.nomes = nomesTemp;
        jogadores.nomes[jogadores.numeroDeJogadores] = novoNome;
        jogadores.numeroDeJogadores++;

    }
    
    return jogadores;
}

//Lê as linhas de entrada e realizar operações nos dados
struct ListaDeJogos lerLinhas(int *numJogos, int *numTotalJogadores) {

    int contadorLinhasVazias = 0;
    int flagNovoJogo = 0;
   
    //Inicializa a lista dos jogos
    struct ListaDeJogos listaDeJogos = inicializarListaDeJogos();

    //Cria um novo jogo
    struct Jogo jogoNovo = criarJogo();

    //Aloca memória para ler a entrada de dados
    linhaTemp = (char *)malloc(BUFFER_ENTRADA);

    //Verifica se alocou correctamente a memória
    if (linhaTemp == NULL) {
        
        printf("Erro ao alocar memória para ler entrada de dados.\n");
        
        //Liberta memória e termina o programa
        free(linhaTemp);
        exit(EXIT_FAILURE);
    
    }

    //Lê enquanto houver dados
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
            
            //Verifica se formato de entrada está correcto
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

    //Calcula o número de jogadores
    listaDeJogos.numTotalJogadores = 0;
    
    for (int i = 0; i < listaDeJogos.numeroDeJogos-1; ++i) {
       
        listaDeJogos.numTotalJogadores += listaDeJogos.arrayDeJogos[i].numeroDeJogadores;
    
    }

    //Atribui o número total de jogadores
    *numTotalJogadores = listaDeJogos.numTotalJogadores;

    // Retorna a lista de jogos
    return listaDeJogos;

}

// Função para libertar a memória alocada
void libertarMemoria(struct ListaDeJogos *listaDeJogos) {
   
    // Liberta a memória alocada para os jogadores de cada jogo
    for (int i = 0; i < listaDeJogos->numeroDeJogos; ++i) {
       
        for (int j = 0; j < listaDeJogos->arrayDeJogos[i].numeroDeJogadores; ++j) {
            
            free(listaDeJogos->arrayDeJogos[i].arrayDeJogadores[j].nome);
        
        }
       
        free(listaDeJogos->arrayDeJogos[i].arrayDeJogadores);
    
    }

    // Liberta a memória alocada para os jogos
    free(listaDeJogos->arrayDeJogos);  

}

// Função para mostrar os dados recebendo a lista de jogos como parâmetro
void mostraDados(const struct ListaDeJogos *listaDeJogos) {
    
    for (int i = 0; i < listaDeJogos->numeroDeJogos-1; ++i) {
    
        printf("Jogo %d:\n", i + 1);

        for (int j = 0; j < listaDeJogos->arrayDeJogos[i].numeroDeJogadores; ++j) {
    
            printf("  Jogador %d: Nome: %s, Pontos: %d\n", j + 1, listaDeJogos->arrayDeJogos[i].arrayDeJogadores[j].nome, listaDeJogos->arrayDeJogos[i].arrayDeJogadores[j].pontos);
        }

    }

}

//Calcula vitorias e total de pontos apenas para os jogadores fornecidos
void calcularVitoriasPontos(const struct ListaDeJogos *listaDeJogos, const struct Jogadores *jogadores) {
   
    for (int i = 0; i < jogadores->numeroDeJogadores; i++) {
        
        int totalPontos = 0;
        int vitorias = 0;

        for (int j = 0; j < listaDeJogos->numeroDeJogos - 1; j++) {
            
            // Encontra o índice do jogador atual no jogo
            int indiceJogadorNoJogo = -1;
           
            for (int k = 0; k < listaDeJogos->arrayDeJogos[j].numeroDeJogadores; k++) {
               
                if (strcmp(listaDeJogos->arrayDeJogos[j].arrayDeJogadores[k].nome, jogadores->nomes[i]) == 0) {
                    
                    indiceJogadorNoJogo = k;
                    break;

                }

            }

            //Se o jogador está no jogo, calcular pontos
            if (indiceJogadorNoJogo != -1) {
               
                totalPontos += listaDeJogos->arrayDeJogos[j].arrayDeJogadores[indiceJogadorNoJogo].pontos;

                //Verifica se o jogador ganhou
                if (listaDeJogos->arrayDeJogos[j].arrayDeJogadores[indiceJogadorNoJogo].pontos >= 2) {
                    
                    int pontosJogadorAtual = listaDeJogos->arrayDeJogos[j].arrayDeJogadores[indiceJogadorNoJogo].pontos;
                    int jogadoresComMaisPontos = 0;

                    for (int k = 0; k < listaDeJogos->arrayDeJogos[j].numeroDeJogadores; k++) {
                        
                        if (listaDeJogos->arrayDeJogos[j].arrayDeJogadores[k].pontos > pontosJogadorAtual) {
                            jogadoresComMaisPontos++;
                        }

                    }

                    if (jogadoresComMaisPontos == 0) {
                        
                        vitorias++;
                    }

                }

            }

        }

        //Mostra os resultados para o jogador atual
        printf("%s - %d pontos, %d vitorias.\n", jogadores->nomes[i], totalPontos, vitorias);

    }

}

//**************** Entrada do programa principal ****************

int main()
{
     int numJogos, numTotalJogadores;
    
    //Lê os nomes dos jogadores para calcular os pontos
    struct Jogadores jogadores = lerNomesJogadores();

    //Lê os dados dos jogos
    struct ListaDeJogos listaDeJogos = lerLinhas(&numJogos, &numTotalJogadores);

    //Calcula vitorias e total de pontos
    calcularVitoriasPontos(&listaDeJogos, &jogadores);

    // Libera a memória no final do programa
    libertarMemoria(&listaDeJogos);

    return 0;
}
