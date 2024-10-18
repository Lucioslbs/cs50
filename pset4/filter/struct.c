#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;
// Usamos sizeof (node) para obter a quantidade certa de memória para alocar, e
// malloc retorna um ponteiro que salvamos como
node *n = malloc(sizeof(node));

// Queremos ter certeza de que malloc conseguiu obter memória para nós
if(n != NULL)
{
     // Isso é equivalente a (*n).number, onde primeiro vamos para o nó apontado
     // para por n e, em seguida, defina a propriedade number. Em C, também podemos usar este
     // notação de seta
     n->number = 1

     // Então precisamos ter certeza de que o ponteiro para o próximo nó em nossa lista
     // não é um valor lixo, mas o novo nó não apontará para nada (por enquanto)
     n->next = NULL;
}
n = malloc(sizeof(node));

if(n != NULL)
{
    n->number = 2;
    n->next = NULL;
}
list->next = n;

n = malloc(sizeof(node));

if(n != NULL)
{
    n->number = 3;
    n->next = NULL;
}
list->next->next = n;
