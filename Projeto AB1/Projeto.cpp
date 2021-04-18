#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

struct no
{
    char nome[25];
    int lat;
    int log;
    int fator;
    int altura;
    int distancia;

    no *esq;
    no *dir;
};
struct Lista
{
    char letra;

    Lista *proximo;
    no *arv;
};
int validar_nome(char nome[25])
{

    int verif; 

    for (int i = 1; i < strlen(nome); i++)
    {
        int j = nome[i];

        if (nome[0] >= 65 && nome[0] <= 90)
        {
            if (j >= 97 && j <= 122)
            {
                continue;
            }
            else
            {
                return 0;
            }
            
        }
        else
        {
            return 0;
        }
        
    }
    return 1;
   
}
no *Rot_direita(no *arvore)
{
    no *aux1, *aux2;

    aux1 = arvore->esq;
    aux2 = aux1->dir;

    aux1->dir = arvore;
    arvore->esq =  aux2;
    arvore = aux1;

    return arvore;
}
no *Rot_esquerda(no *arvore)
{
    no *aux1, *aux2;

    aux1 = arvore->dir;
    aux2 = aux1->esq;

    aux1->esq = arvore;
    arvore->dir =  aux2;
    arvore = aux1;

    return arvore;
}
int Max(int h1, int h2)
{
    if (h1 > h2)
    {
        return h1;
    }
    else
    {
        return h2;
    }
    
}
int Altura(no *arvore, int h1, int h2)
{
    if (arvore->esq != NULL)
    {
        h1 = Altura(arvore->esq, h1, h2);
    }
    else
    {
        h1 += 0;
    }
    if (arvore->dir != NULL)
    {
        h2 = Altura(arvore->dir, h1, h2);
    }
    else
    {
        h2 += 0;
    }

    return 1 + Max(h1, h2);
    
}
void Set_high(no *arvore)
{
    if (arvore == NULL)
    {
        return;
    }
    else
    {  
        if (arvore->esq == NULL && arvore->dir == NULL)
        {
            arvore->altura = Altura(arvore, 0, 0);
            arvore->fator = 0;
        }
        else if (arvore->esq == NULL)
        {
            
            arvore->altura = 1 + Altura(arvore->dir, 0, 0);
        }
        else if (arvore->dir == NULL)
        {
            
            arvore->altura = 1 + Altura(arvore->esq, 0, 0);
        }
        else
        {
            arvore->altura = 1 + Max(Altura(arvore->esq, 0, 0), Altura(arvore->dir, 0, 0));
           
        }

        Set_high(arvore->esq);
        Set_high(arvore->dir);
    }
    
}
int Fator(no *arvore_esq, no *arvore_direita)
{
    if (arvore_esq == NULL && arvore_direita == NULL)
    {
        return 0;
    }
    else if (arvore_esq == NULL)
    {
        return 0 - arvore_direita->altura;
    }
    else if (arvore_direita == NULL)
    {
        return arvore_esq->altura;
    }
    else
    {
        return arvore_esq->altura - arvore_direita->altura;
    }
    
}
no *Balancear(no *arvore)
{
    if (arvore == NULL)
    {
        return arvore;
    }
    else
    {
        no *aux;
        
        arvore->fator = Fator(arvore->esq, arvore->dir);

        if (arvore->fator < -1)
        {
            aux = arvore->dir;

            aux->fator = Fator(aux->esq, aux->dir);

            if (aux->fator == 1)
            {
                
                arvore->dir = Rot_direita(arvore->dir);
                arvore = Rot_esquerda(arvore);
            }
            else
            {   
                arvore = Rot_esquerda(arvore);
            }
             
            arvore->dir = Balancear(arvore->dir);
            
        }
        if (arvore->fator > 1)
        {
            aux = arvore->esq;
            aux->fator = Fator(aux->esq, aux->dir);

            if (aux->fator == -1)
            {
                arvore->esq = Rot_esquerda(arvore->esq);
                arvore = Rot_direita(arvore);
            }
            else
            {
                arvore = Rot_direita(arvore);
            }

            arvore->esq= Balancear(arvore->esq);
        }
        return arvore;
    } 
    
}
no *Inserir(no *arvore, char nome[25], int lat , int log)
{
    if (arvore == NULL)
    {
        arvore = (no*)malloc(sizeof(no));

        arvore->esq = NULL;
        arvore->dir = NULL;

        arvore->lat = lat;
        arvore->log = log;
        strcpy(arvore->nome, nome); 
        

        return arvore;
    }
    else 
    {
        if (strlen(arvore->nome) < strlen(nome))
        {
            arvore->dir = Inserir(arvore->dir ,nome, lat, log);
        }
        else if(strlen(arvore->nome) > strlen(nome))
        {
            arvore->esq = Inserir(arvore->esq, nome, lat, log);
        }
        else
        {
            if (strcmp(arvore->nome, nome) < 0)
            {
                arvore->dir = Inserir(arvore->dir, nome, lat, log);

            }
            else if(strcmp(arvore->nome, nome) > 0)
            {
                arvore->esq = Inserir(arvore->esq, nome, lat, log);
            }
            
        }
        
        return arvore;
    }
    
    
}
Lista *Inserir_lista(Lista *list, char letra, char nome[25], int lat, int log)
{
    Lista *aux, *novo;

    novo = (Lista*)malloc(sizeof(Lista));

    if (!novo)
    {
        printf("!-- A Base de dados de ta cheia --!\n");
        return list;
    }
    else
    {
        if (list == NULL)
        {
            novo->letra = letra;
            novo->proximo = NULL;
            novo->arv = Inserir(novo->arv, nome, lat, log);

            list = novo;
            return list;
        }
        
        else
        {
            aux = list;

            while (aux->proximo != NULL && aux->letra < letra)
            {
                aux = aux->proximo;
            }
            if (aux->proximo == NULL)
            {
                if (aux->letra > letra)
                {
                    novo->proximo = aux->proximo;
                    novo->letra = aux->letra;
                    novo->arv = aux->arv;

                    aux->letra = letra;
                    aux->proximo = novo;
                    aux->arv = NULL;
                    aux->arv = Inserir(aux->arv, nome, lat, log);
                }
                else if (aux->letra == letra)
                {
                    aux->arv = Inserir(aux->arv,nome, lat, log);
                }
                else
                {
                    novo->proximo = aux->proximo;
                    novo->letra = letra;
                    novo->arv = Inserir(novo->arv, nome, lat, log);

                    aux->proximo = novo;
                }
                        
             }
            else
            {
                if (aux->letra == letra)
                {
                    aux->arv = Inserir(aux->arv,nome, lat, log);
                }
                else
                {
                    novo->proximo = aux->proximo;
                    novo->letra = aux->letra;
                    novo->arv = aux->arv;

                    aux->letra = letra;
                    aux->proximo = novo;
                    aux->arv = NULL;

                    aux->arv = Inserir(aux->arv, nome, lat, log);
                }
            }
        }
       
        
        return list;
    }
    
    
}
no *Retirar_arvore_nome(no *arvore, char nome[25])
{
    if (arvore == NULL)
    {
        return NULL;
    }
    else
    {
        if (strlen(arvore->nome) < strlen(nome))
        {
            arvore->dir = Retirar_arvore_nome(arvore->dir, nome);

        }
        else if(strlen(arvore->nome) > strlen(nome))
        {
            arvore->esq = Retirar_arvore_nome(arvore->esq, nome);
        }
        else
        {
            if (strcmp(arvore->nome, nome) < 0)
            {
                arvore->dir = Retirar_arvore_nome(arvore->dir, nome);
            }
            else if (strcmp(arvore->nome, nome) > 0)
            {
                arvore->esq = Retirar_arvore_nome(arvore->esq, nome);
            }
            else
            {
                if (arvore->esq == NULL && arvore->dir == NULL)
                {
                    free(arvore);
                    return NULL;
                }
                else if (arvore->dir == NULL)
                {
                    no *aux;
                    aux = arvore;
                    arvore = arvore->esq;
                    free(aux);
                }
                else if (arvore->esq == NULL)
                {  
                    no *aux;
                    aux = arvore;
                    arvore = arvore->dir;
                    free(aux);
                }
                else
                {
                    no *aux = arvore->esq;

                    while (aux->dir != NULL)
                    {
                        aux = aux->dir;
                    }

                    int lat, log;

                    lat = arvore->lat;
                    log = arvore->log;
                    
                    strcpy(arvore->nome, aux->nome);
                    arvore->lat = aux->lat;
                    arvore->log = aux->log;

                    strcpy(aux->nome, nome);
                    aux->lat = lat;
                    aux->log = log;

                    arvore->esq = Retirar_arvore_nome(arvore->esq, nome);
                
                } 
            }
            
        }
        return arvore;
    }
    
}
no *verificar_no(no *arvore, int lat, int log)
{
    if (arvore == NULL)
    {
        return NULL;
    }
    else
    {
        verificar_no(arvore->esq, lat, log);

        if (arvore->lat == lat && arvore->log == log)
        {
            return arvore;
        }
        else
        {
            return NULL;
        }
        
        verificar_no(arvore->dir, lat, log);
        
    }
    
}
no *search_cord(Lista *list, int lat, int log)
{
    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        Lista *aux = list;
        no *aux_no;

        while (aux != NULL)
        {
            aux_no = verificar_no(aux->arv, lat, log);

            if (aux_no != NULL)
            {
               return aux_no;
            }
            aux = aux->proximo;
            
        }
        return aux_no;
    }
}
no *Verificar_cordenada(Lista *list, int lat, int log)
{
    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        Lista *aux = list;
        no *aux_no;

        while (aux != NULL)
        {
            aux_no = verificar_no(aux->arv, lat, log);

            if (aux_no == NULL)
            {
               return aux_no;
            }
            aux = aux->proximo;
            
        }
        return aux_no;
    }
    
}
Lista *Remover_por_cordenada(Lista *list, int lat, int log)
{
    Lista *aux, *anterior;

    if (list == NULL)
    {
        printf("!-- A base de dados tá vazia --!\n");

        return list;
    }
    else
    {
        aux = list;

        no *aux_no;

        aux_no = search_cord(list, lat, log);


        if (aux_no == NULL)
        {
            printf("A cordenada não existe no banco de dados\n");
        }
        else
        {

            printf("A Cidade de Cordenadas: (Lat = %d,Log = %d), Foi removida\n", aux_no->lat, aux_no->log);
            char nome[25];

            strcpy(nome, aux_no->nome);

            char letra = nome[0];


            
            if (list->proximo == NULL)
            {
                if (aux->letra == letra)
                {
                    aux->arv = Retirar_arvore_nome(aux->arv, nome);

                    if (aux->arv == NULL)
                    {
                        free (list);
                        return NULL;
                    }
                }
            }
            else
            {

                while (aux->proximo != NULL && aux->letra != letra)
                {
                    anterior = aux;
                    aux = aux->proximo;
                }
                if (aux->proximo == NULL)
                {
                    if (aux->letra == letra)
                    {
                     aux->arv = Retirar_arvore_nome(aux->arv, nome);

                        if (aux->arv == NULL)
                        {
                         anterior->proximo = aux->proximo;
                        free (aux);
                        }
                    }
                }
                else
                {
                    aux->arv = Retirar_arvore_nome(aux->arv, nome);

                    if (aux->arv == NULL)
                    {
                     anterior->proximo = aux->proximo;

                        free(aux);
                    }
            
                }
             }
        }
        return list;
        
    }

    
}
Lista *Remover_lista_por_nome(Lista *list, char letra, char nome[25])
{
    Lista *aux, *anterior;

    aux = list;
    
    if (list == NULL)
    {
        printf("!-- A base de dados tá vazia --!\n");

        return list;
    }
    else
    {
        printf("A cidade de nome: %s, foi removida com sucesso\n\n", nome);
        if (list->proximo == NULL)
        {
           if (aux->letra == letra)
           {
               aux->arv = Retirar_arvore_nome(aux->arv, nome);

               if (aux->arv == NULL)
               {
                   free (list);
                   return NULL;
               }
           }
        }
        else
        {

            while (aux->proximo != NULL && aux->letra != letra)
            {
                anterior = aux;
                aux = aux->proximo;
            }
            if (aux->proximo == NULL)
            {
                if (aux->letra == letra)
                {
                    aux->arv = Retirar_arvore_nome(aux->arv, nome);

                    if (aux->arv == NULL)
                    {
                        anterior->proximo = aux->proximo;
                        free (aux);
                    }
                }
            }
            else
            {
                aux->arv = Retirar_arvore_nome(aux->arv, nome);

                if (aux->arv == NULL)
                {
                    anterior->proximo = aux->proximo;

                    free(aux);
                }
            
            }
        }
        return list;
    }
    
    
}

void Imprimir_arvore(no *arvore)
{
    if (arvore == NULL)
    {
       return;
    }
    else
    {
        
       
        Imprimir_arvore(arvore->esq);

        printf("Cidade: %s, lat = %d, Log = %d\n", arvore->nome, arvore->lat, arvore->log);


        Imprimir_arvore(arvore->dir);
    }
    
}
void Imprimir_arvore_distancia(no *arvore, int lat, int log)
{
    if (arvore == NULL)
    {
       return;
    }
    else
    {
        
        Imprimir_arvore(arvore->esq);

        double dist;

        dist = sqrt(pow(arvore->lat - lat,2) + pow(arvore->log - log, 2));

        printf("Cidade: %s, lat = %d, Log = %d, Distancia da cordenada selecionada: %.2lf Km\n", arvore->nome, arvore->lat, arvore->log, dist);

        Imprimir_arvore(arvore->dir);
    }
}
void Imprimir_cidades(Lista *list, int mod, int lat, int log)
{
    Lista *aux;

    aux = list;

    if (mod == 0)
    {
        while (aux != NULL)
        {   
            printf("\n+_+_+_+_+_+_+_+_+_+_+_+_+_+\n");
            printf("Cidades com a letra %c: \n", aux->letra);
            Imprimir_arvore(aux->arv);
            printf("\n+_+_+_+_+_+_+_+_+_+_+_+_+_+\n");
            printf("\n\n");
            aux = aux->proximo;
        }
    }
    else
    {
         while (aux != NULL)
        {   
            printf("\n+_+_+_+_+_+_+_+_+_+_+_+_+_+\n");
            printf("Cidades com a letra %c: \n", aux->letra);
            Imprimir_arvore_distancia(aux->arv, lat, log);
            printf("\n\n");
            printf("\n+_+_+_+_+_+_+_+_+_+_+_+_+_+\n");
            aux = aux->proximo;
        }
    }
    
}
void chamar_balanceamento(Lista *list)
{
    if (list == NULL)
    {
        return;
    }
    else
    {
        Set_high(list->arv);
        list->arv = Balancear(list->arv);

        chamar_balanceamento(list->proximo);
    }
    
}
int main()
{
    Lista *head = NULL;

    int opcao;

    while (1)
    {
        printf("!-- Sistema de Gerenciamento de dados de cidades--!\n");
        printf("|(1) : Inserir\n|(2) : Remover\n|(3) : Consultar\n|(Qualquer outra tecla) : Sair\n_>> ");

        scanf("%d", &opcao);

        if (opcao == 1)
        {
            system("clear");
            char nome[25];
            printf("Digite o nome da cidade a ser inserida: ");
            scanf(" %[^\n]", nome);

            while (validar_nome(nome) == 0)
            {
                printf("Por Favor Digite um nome valido\n_>> ");
                scanf(" %[^\n]", nome);
            }

            int longit;
            int latid;

            printf("Digite uma Latitude: ");
            scanf("%d", &latid);

            printf("Digite uma Longitude: ");
            scanf("%d", &longit);

            while (Verificar_cordenada(head, latid, longit) != NULL)
            {
                printf("Por Favor Digite outra Coordenada, essa ja peretence a uma cidade existente\n_>> Lat: ");
                scanf("%d", &latid);
                printf("_>> Log: ");
                scanf("%d", &longit);
            }

            head = Inserir_lista(head, nome[0], nome, latid, longit);

            no *aux;
            aux = head->arv;
            printf("Antiga raíz: %s\n", aux->nome);
            chamar_balanceamento(head);
            aux = head->arv;
            printf("Nova raíz: %s\n", aux->nome);
            continue;
        }
        if (opcao == 2)
        {
            system("clear");
            printf("Deseja excluir por (1) : nome ou por (2) :coordenadas? \n");
            printf("_>> ");
            int mod;
            
            scanf("%d", &mod);
            
            if (mod == 1)
            {
                char nome[25];
                printf("Digite o nome da cidade a ser inserida: ");
                scanf(" %[^\n]", nome);

                while (validar_nome(nome) == 0)
                {
                    printf("Por Favor Digite um nome valido\n_>> ");
                    scanf(" %[^\n]", nome);
                }
                head = Remover_lista_por_nome(head, nome[0], nome);
            }
            else
            {
                printf("Digite as Coordenadas a serem Removidas\n");
                int x,y;

                printf("Lat: ");
                scanf("%d", &x);

                printf("Log: ");
                scanf("%d", &y);

                head = Remover_por_cordenada(head, x, y);
            }
            chamar_balanceamento(head);
            continue;
            
        }
        
        if (opcao == 3)
        {
            system("clear");
            int option;

            printf("Deseja Listar as cidades em relação a uma cordenada específica?\n");
            printf("(1) : Sim\n(0) : Não\n");

            scanf("%d", &option);

            if (option == 1)
            {
                printf("Digite uma Latitude: ");
                int lat;

                scanf("%d", &lat);
                printf("Digite uma Longitude: ");

                int log; 
                scanf("%d", &log);

                Imprimir_cidades(head , option, lat, log);


            }
            else
            {
                Imprimir_cidades(head , option, 0, 0);
            }
            
            continue;
        }
        else
        {
            break;
        }
        
        
    }

}