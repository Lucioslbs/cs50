#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool creates_cycle(int loser, int winner, bool temp_locked[MAX][MAX]);
bool dfs(int loser, int winner, bool visited[], bool temp_locked[MAX][MAX]);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Número de eleitores: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Verifica se o nome fornecido corresponde ao nome de um candidato válido
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Atualiza a matriz de classificação para indicar a preferência de classificação do
            // eleitor para esse candidato
            ranks[rank] = i;
            return true; // Retorna verdadeiro indicando que a classificação foi registrada com
                         // sucesso
        }
    }

    return false; // Retorna falso indicando que o nome não corresponde a nenhum candidato válido
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Atualiza a matriz de classificação global para adicionar as preferências do eleitor atual
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int preferred_candidate =
                ranks[i]; // Obtém o candidato preferido do eleitor para a i-ésima preferência
            int other_candidate = ranks[j]; // Obtém o outro candidato para a j-ésima preferência
            preferences[preferred_candidate]
                       [other_candidate]++; // Incrementa a preferência de preferred_candidate sobre
                                            // other_candidate
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Itera sobre cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        // Itera sobre cada outro candidato (j) além do candidato atual (i)
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Verifica se o candidato i é preferido ao candidato j
            if (preferences[i][j] > preferences[j][i])
            {
                // Adiciona o par de candidatos à matriz de pares, se i é preferido a j
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // Verifica se o candidato j é preferido ao candidato i
            else if (preferences[j][i] > preferences[i][j])
            {
                // Adiciona o par de candidatos à matriz de pares, se j é preferido a i
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Implementação do algoritmo de ordenação Bubble Sort
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            // Calcula a força de vitória para o par atual e o próximo par
            int strength_current = preferences[pairs[j].winner][pairs[j].loser];
            int strength_next = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            // Se a força de vitória do próximo par for maior que a força de vitória do par atual,
            // troca-os
            if (strength_next > strength_current)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Cria uma cópia do gráfico locked para verificar se a adição de uma aresta criará um ciclo
    bool temp_locked[MAX][MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            temp_locked[i][j] = locked[i][j];
        }
    }

    // Adiciona as arestas em ordem decrescente de força de vitória
    for (int i = 0; i < pair_count; i++)
    {
        // Verifica se a adição da aresta criará um ciclo
        if (!creates_cycle(pairs[i].loser, pairs[i].winner, temp_locked))
        {
            // Adiciona a aresta ao gráfico locked se não criar um ciclo
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Declaração da função creates_cycle com a assinatura correta
bool creates_cycle(int loser, int winner, bool temp_locked[MAX][MAX]);

// Definição da função creates_cycle com a assinatura correta
bool creates_cycle(int loser, int winner, bool temp_locked[MAX][MAX])
{
    // Inicializa um vetor de visitados para controlar os nós visitados durante a busca em
    // profundidade
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    // Realiza uma busca em profundidade a partir do nó do perdedor
    return dfs(loser, winner, visited, temp_locked);
}

// Função auxiliar para realizar busca em profundidade (DFS)
bool dfs(int loser, int winner, bool visited[], bool temp_locked[MAX][MAX])
{
    // Marca o nó atual como visitado
    visited[loser] = true;

    // Itera sobre todos os nós adjacentes ao nó atual (perdedor)
    for (int i = 0; i < candidate_count; i++)
    {
        // Verifica se há uma aresta do nó atual (perdedor) para o nó adjacente (candidato
        // preferido)
        if (temp_locked[loser][i])
        {
            // Se o nó adjacente ainda não foi visitado, realiza uma busca em profundidade recursiva
            if (!visited[i])
            {
                // Se uma chamada recursiva encontrar o nó de destino (vencedor), retorna
                // verdadeiro, indicando que um ciclo foi encontrado
                if (dfs(i, winner, visited, temp_locked))
                {
                    return true;
                }
            }
            // Se o nó adjacente já foi visitado e é o nó de destino (vencedor), retorna verdadeiro,
            // indicando que um ciclo foi encontrado
            else if (i == winner)
            {
                return true;
            }
        }
    }

    // Se nenhum ciclo for encontrado, retorna falso
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Itera sobre cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;

        // Verifica se o candidato é derrotado por algum outro candidato
        for (int j = 0; j < candidate_count; j++)
        {
            // Se houver uma aresta de j para i no gráfico locked
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        // Se o candidato não for derrotado por nenhum outro candidato, ele é uma fonte
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return; // Termina a função após imprimir o vencedor
        }
    }
}
