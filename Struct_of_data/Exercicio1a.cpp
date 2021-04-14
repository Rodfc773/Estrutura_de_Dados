#include <iostream>
#include <stdlib.h>
#include <strings.h>

using namespace std;

struct no{
    no *prox;
    char elemento;
};

no *Criar(no *topo)
{
    topo = NULL;

    return topo;
}

no *inserir(no *topo)
{
    no *novo;

    novo = (no*)malloc(sizeof(no));

    if (!novo)
    {
        printf("A pilha está cheia\n");

        return topo;
    }
    if (topo == NULL)
    {
        novo->prox = NULL;
        topo = novo;

        return topo;
    }
    else
    {
        novo->prox = topo;

        return novo;
    }
    
    
}
no *Remover(no *topo)
{
    no *aux;

    aux = topo;

    topo = topo->prox;

    free(aux);

    return topo;

}
int Validar(int i, int tam, no *topo, string teste)
{
    if (i == tam)
    {
        if (topo == NULL)
        {
            return 1;
        }
        else
        {
            //printar Aguardando fecha parenteses na posição i, !-- Error --!
            return 0;
        }
        
    }
    else
    {
        if (teste[i] == ')' && topo == NULL)
        {
            // indice - 1 não tem um abre parenteses.
           return 0;
        }
        else
        {
            if (teste[i] == ')')
            {
                topo = Remover(topo);
            }
            else
            {
                topo = inserir(topo);
            }
            
            return Validar(i + 1, tam, topo, teste);
        }
        
    }
    
}
int main()
{
    no *topo;
    string teste;
    

    topo = Criar(topo);
    getline(cin, teste);

    int tam = teste.size();

   int res = Validar(0, tam, topo, teste);

   if (res == 1)
   {
       printf("A expressão é valida\n");
   }
   else
   {
       printf("A expressão não é valida\n");
   }
   


}