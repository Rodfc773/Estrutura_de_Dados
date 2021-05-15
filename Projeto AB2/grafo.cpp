#include <iostream>

using namespace std;

struct grafo
{
    int elem;
    grafo *prox;
};
struct vetor
{
    grafo *vetor[10];
};

// V = [a, b, c, d]
// A = [(a,b), (a, c), (b, d), (d, d)]
vetor *array = NULL;

void Controi_vetor(vetor *array)
{
    printf("Quantos vertices o vetor terá?\n");

    int num_vertices;

    scanf("%d", &num_vertices);

    for (int i = 0; i < num_vertices; i++)
    {
        printf("Quantos arcos partem do vertice %d?\n", i);

        int num_arcos;

        scanf("%d", &num_arcos);

        for (int j = 0; j < num_arcos; j++)
        {
            printf("Qual é o primeiro arco que sai de %d: ", i);

            int arco;

            scanf("%d", &arco);

            if (array->vetor[i] == NULL)
            {
                array->vetor[i] = (grafo*) malloc(sizeof(grafo));

                if (!array->vetor[i])
                {
                    printf("Não foi possivel alocar memoria\n");
                }
                else
                {
                    array->vetor[i]->elem = arco;
                    array->vetor[i]->prox = NULL;
                }
                
            }
            else
            {   
                grafo *aux, *novo;

                aux = array->vetor[i];

                while (aux != NULL)
                {
                    aux = aux->prox;
                }

                novo = (grafo*)malloc(sizeof(grafo));
                novo->elem = arco;
                novo->prox = NULL;

                aux = novo; 
                
            }

        }
        
    }
}
void Imprimir(grafo *vetor[])
{
    for (int i = 0; i < 10; i++)
    {
        printf("Vertice: %d, tem arcos para os vertices: ", vetor[i]->elem);

        grafo *aux = vetor[i]->prox;

        while (aux != NULL)
        {
            printf("%d, ", aux->elem);
            aux = aux->prox;
        }
        
    }
    
    
}
int main()
{
    Controi_vetor(array);
    Imprimir(array->vetor);
}
