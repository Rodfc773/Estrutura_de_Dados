#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>

using namespace std;

struct no
{
    int info;
    no *lef;
    no *right;
    int altura;
    int fator;
    int nivel;
    
};

no *Rot_direita(no *arvore)
{
    no *aux1, *aux2;

    aux1 = arvore->lef;
    aux2 = aux1->right;

    aux1->right = arvore;
    arvore->lef =  aux2;
    arvore = aux1;

    return arvore;
}
no *Rot_esquerda(no *arvore)
{
    no *aux1, *aux2;

    aux1 = arvore->right;
    aux2 = aux1->lef;

    aux1->lef = arvore;
    arvore->right =  aux2;
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
    if (arvore->lef != NULL)
    {
        h1 = Altura(arvore->lef, h1, h2);
    }
    else
    {
        h1 += 0;
    }
    if (arvore->right != NULL)
    {
        h2 = Altura(arvore->right, h1, h2);
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
        if (arvore->lef == NULL && arvore->right == NULL)
        {
            arvore->altura = Altura(arvore, 0, 0);
            arvore->fator = 0;
        }
        else if (arvore->lef == NULL)
        {
            
            arvore->altura = 1 + Altura(arvore->right, 0, 0);
        }
        else if (arvore->right == NULL)
        {
            
            arvore->altura = 1 + Altura(arvore->lef, 0, 0);
        }
        else
        {
            arvore->altura = 1 + Max(Altura(arvore->lef, 0, 0), Altura(arvore->right, 0, 0));
           
        }

        Set_high(arvore->lef);
        Set_high(arvore->right);
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
        
        arvore->fator = Fator(arvore->lef, arvore->right);

        printf("Nó: %d, Fator:%d\n\n",arvore->info, arvore->fator);

        if (arvore->fator < -1)
        {
            aux = arvore->right;

            aux->fator = Fator(aux->lef, aux->right);

            if (aux->fator == 1)
            {
                printf("ta entrando no if\n\n");
                arvore->right = Rot_direita(arvore->right);
                arvore = Rot_esquerda(arvore);
            }
            else
            {
                printf("ta entrando no else\n\n");
                arvore = Rot_esquerda(arvore);
            }
             
            arvore->right = Balancear(arvore->right);
            
        }
        if (arvore->fator > 1)
        {
            aux = arvore->lef;
            aux->fator = Fator(aux->lef, aux->right);

            if (aux->fator == -1)
            {
                arvore->lef = Rot_esquerda(arvore->lef);
                arvore = Rot_direita(arvore);
            }
            else
            {
                arvore = Rot_direita(arvore);
            }

            arvore->lef= Balancear(arvore->lef);
        }
        return arvore;
    } 
    
}
no *Inserir(no *arvore, int elemento, int nivel)
{
    if (arvore == NULL)
    {
        arvore = (no*)malloc(sizeof(no));

        arvore->lef = NULL;
        arvore->right = NULL;
        arvore->info = elemento;
        arvore->nivel = nivel;

        return arvore;
    }
    else 
    {
        if(arvore->info < elemento)
        {
            nivel += 1;
            arvore->right = Inserir(arvore->right, elemento, nivel);

            

        }
        if (arvore->info > elemento)
        {
        
            nivel += 1;
            arvore->lef = Inserir(arvore->lef, elemento,nivel);  

            

         
        }
        return arvore;
    }
    
    
}
no *Retirar(no *arvore, int elemento)
{
    if (arvore == NULL)
    {
        printf("Esse elemento não pertence a arvore\n");

        return NULL;
    }
    else 
    {
        if (arvore->info < elemento)
        {
            arvore->right = Retirar(arvore->right, elemento);
        }
        if (arvore->info > elemento)
        {
            arvore->lef = Retirar(arvore->lef, elemento);
        }
        else
        {
            if (arvore->lef == NULL && arvore->right == NULL)
            {
                free(arvore);
                return NULL;
            }
            else if (arvore->right == NULL)
            {
                no *aux;
                aux = arvore;
                arvore = arvore->lef;
                free(aux);
            }
            else if (arvore->lef == NULL)
            {
                no *aux;
                aux = arvore;
                arvore = arvore->right;
                free(aux);
            }
            else
            {
                no *aux = arvore->lef;

                while (aux->right != NULL)
                {
                    aux = aux->right;
                }

                arvore->info = aux->info;
                aux->info = elemento;

                arvore->lef = Retirar(arvore->lef, elemento);
                
            }
                 
        }
        return arvore;
    }
    
}
void Inordem(no *arvore)
{
    if (arvore == NULL)
    {
        printf(" NULL ");
    }
    else
    {
       
        printf("(");

        Inordem(arvore->lef);

        printf(")");

        printf(", %d , ", arvore->info);

        printf("(");

        Inordem(arvore->right);

        printf(")");
    }
    
}
void Pos_ordem(no *arvore)
{
    if (arvore == NULL)
    {
        printf("NULL");
    }
    else
    {
       
        printf("(");

        Inordem(arvore->lef);

        printf(")");

        printf("(");

        Inordem(arvore->right);

        printf(")");
        printf(", %d [ALtura: %d, Nivel: %d], ", arvore->info, arvore->altura, arvore->nivel);
    }
}
int main()
{
    no *arvore = NULL;

    int elemento;

    int opcao;

    int nivel;

    while (1)
    {
       printf("!-- Sistema de Arvore --!\n");

       printf("|(1) : Inserir\n|(2) : Remover\n|(3) : Inordem\n|(4) : Pre-ordem\n|(5) : Pos-ordem\n|(6) : Balancear\n");

       printf("!-----------------------!\n");

       printf("_>> ");

       scanf("%d", &opcao);

       if (opcao == 1)
       {
           system("clear");

           printf("Digite um elemento a ser Inserido : ");
           
           scanf("%d", &elemento);

           arvore = Inserir(arvore, elemento, 0);      

           continue;
       }
       if (opcao == 2)
       {
           system("clear");

           printf("Digite um elemento a ser Retirado: ");

           scanf("%d", &elemento);

           arvore = Retirar(arvore, elemento);


           continue;
       }
       if (opcao == 3)
       {    
            system("clear");
            printf("\nInordem: ");
            printf("\n");

            Inordem(arvore);
            printf("\n\n");

            continue;
       }
       if (opcao == 6)
       {
            system("clear");
         
           printf("!--- A ARVORE AGORA ESTÁ BALANCEADA ---!\n");
            Set_high(arvore);
           printf("Antiga raíz: %d\n\n\n", arvore->info);
           arvore = Balancear(arvore);
           printf("Nova raíz: %d\n\n\n", arvore->info);
           Set_high (arvore);

           continue;
       }
       else
       {
           break;
       }
       
       
    }
}