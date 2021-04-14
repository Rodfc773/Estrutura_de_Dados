#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

using namespace std;

struct no
{
    int senha;
    int prioriade;
    no *prox;
};

no *Criar(no *fila_primeiro)
{
    fila_primeiro = NULL;

    return fila_primeiro;
}
no *Inserir(no *fila_primeiro, no *fila_ultimo, int senha, int prioridade)
{
    no *novo;

    novo = (no*)malloc(sizeof(no));

    if (!novo)
    {
        printf("Fila cheia!Por favor Aguarde\n");
        return fila_ultimo;
    }
    else
    {
        if (fila_ultimo == NULL && fila_ultimo == fila_primeiro)
        {
            novo->senha = senha;
            novo->prioriade = prioridade;
            novo->prox = NULL;

            fila_primeiro = novo;
            fila_ultimo = novo;

            return fila_ultimo;
        }
        else
        {
            no *aux;

            aux = fila_primeiro;

            while (aux != fila_ultimo)
            {
                senha += 1 ;
                aux = aux->prox;
            }

           
                senha += 1;
                novo->senha = senha;
                novo->prioriade = prioridade;
                novo->prox = NULL;

                fila_ultimo->prox = novo;
                fila_ultimo = novo;
            

            return fila_ultimo;
            
        }
    }
    
}
no *Remover(no *primeiro, int prioridade)
{
    if (primeiro == NULL)
    {
        return primeiro;
    }
    else
    {
        no *aux = primeiro;

        primeiro = primeiro->prox;

        printf("!+-- POR FAVOR SENHA : %d DE PRIORIDADE: %d, COMPAREÇA A CENTRAL DE ATENDIMENTO --!\n\n", aux->senha, prioridade);

        free(aux);

        return primeiro;
    }
    
}
int tamanho_fila(no *fila_primeiro, int tam)
{
    if (fila_primeiro == NULL)
    {
        return tam;
    }
    else
    {
        tam += 1;
        return tamanho_fila(fila_primeiro->prox, tam);
    }

}
void imprimir(no *fila_primeiro)
{
    if (fila_primeiro != NULL)
    {
        
        printf("|(Senha : %d,", fila_primeiro->senha);
        printf(" Prioridade: %d)", fila_primeiro->prioriade);

        imprimir(fila_primeiro->prox);
    }
    
}
int balanceamento(int tam_zero, int tam_um, int tam_dois)
{
    if (tam_zero == tam_um && tam_um == tam_dois)
    {
        return 1;
    }
    else if (tam_zero == tam_um)
    {
        return 2;
    }
    else
    {
        if (tam_zero > tam_um && tam_um >= tam_dois)
        {
            return 3;
        }
        else if(tam_um > tam_dois && tam_dois >= tam_zero)
        {
            return 4;
        }
        else
        {
            return 5;
        }
        
    }
    
    
}
int main()
{
    no *fila_primeiro_zero;
    no *fila_ultimo_zero;
    no *fila_primeiro_um;
    no *fila_ultimo_um;
    no *fila_primeiro_dois;
    no *fila_ultimo_dois;

    fila_primeiro_zero = Criar(fila_primeiro_zero);

    fila_ultimo_zero = fila_primeiro_zero;

    fila_primeiro_um = Criar(fila_primeiro_um);

    fila_ultimo_um = fila_primeiro_um;

    fila_primeiro_dois = Criar(fila_primeiro_dois);

    fila_ultimo_dois = fila_primeiro_dois;


    int opcao;
    int controle = 0;

    int balancear;

    int control_zero = 0 ;
    int control_um = 0; 
    int control_dois = 0;


    while (1)
    {
        printf("!---- SISTEMA DE GERENCIAMENTO DE FILAS ----!\n");
        printf("!---- ESCOLHA UMA DAS OPÇÕES ABAIXO: -------!\n");
        printf("|++++ (1) : Gerar nova senha\n|++++ (2) : Chamar senha\n|++++ (3) : imprimir\n|++++ (Qualquer outra tecla) : Sair\n|++++ opção: ");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            system("clear");

            printf("|----- GERADOR DE SENHA ----------------------|\n");
            printf("|----- O cliente possui qual prioridade? ->: ");

            int prioridade;

            scanf("%d", &prioridade);

            if ( prioridade == 0)
            {
                if (fila_ultimo_zero == NULL && fila_ultimo_zero == fila_primeiro_zero)
                {
                    fila_ultimo_zero = Inserir(fila_primeiro_zero, fila_ultimo_zero, 1, prioridade);

                    fila_primeiro_zero = fila_ultimo_zero;
                }
                else
                {
                    fila_ultimo_zero = Inserir(fila_primeiro_zero, fila_ultimo_zero, 1, prioridade);
                }
                
                
            }
            if ( prioridade == 1)
            {
                if (fila_ultimo_um == NULL && fila_ultimo_um == fila_primeiro_um)
                {
                    fila_ultimo_um = Inserir(fila_primeiro_um, fila_ultimo_um, 1, prioridade);
                    fila_primeiro_um = fila_ultimo_um;
                }
                else
                {
                    fila_ultimo_um = Inserir(fila_primeiro_um, fila_ultimo_um, 1, prioridade);
                }
            }
            if ( prioridade == 2)
            {
                if (fila_ultimo_dois == NULL && fila_ultimo_dois == fila_primeiro_dois)
                {
                    fila_ultimo_dois = Inserir(fila_primeiro_dois, fila_ultimo_dois, 1, prioridade);
                    fila_primeiro_dois = fila_ultimo_dois;
                }
                else
                {
                    fila_ultimo_dois = Inserir(fila_primeiro_dois, fila_ultimo_dois, 1, prioridade);
                }
            }

            printf("|----------------------------------------------|\n");

            printf("\n!! -- Senha inserida --!!\n\n");

            controle += 1;

             if (controle >= 4)
            {
                balancear = balanceamento(tamanho_fila(fila_primeiro_zero, 0), tamanho_fila(fila_ultimo_um, 0), tamanho_fila(fila_ultimo_dois, 0));

                controle = 0;
            }

            continue;

        }
        if (opcao == 2)
        {
            system("clear");

            if (balancear > 0 && balancear <= 2 || balancear == 5)
            {
                if (control_dois < 2)
                {
                    
                    fila_primeiro_dois = Remover(fila_primeiro_dois, 2);
                    
                    control_dois += 1;
                }
                else
                {
                    if (control_um < 1)
                    {
                        
                        fila_primeiro_um = (Remover(fila_primeiro_um, 1));  
                        
                        control_um += 1;
                        
                    }
                    else
                    {
                        if (control_zero < 1)
                        {
                            fila_primeiro_zero = (Remover(fila_primeiro_zero, 0));

                                
                            
                            control_zero += 1;
                        }
                        else
                        {
                            control_um = 0;
                            control_zero = 0;
                            control_dois = 0;
                        }
                        
                    }
                    
                }

                 
            }
            if (balancear == 3)
            {
                if (control_dois < 1)
                {
                    
                    fila_primeiro_dois = Remover(fila_primeiro_dois, 2);
                    
                    control_dois += 1;
                }
                else
                {
                    if (control_um < 1)
                    {
                        
                        fila_primeiro_um = (Remover(fila_primeiro_um, 1));

                        control_um += 1;
                        
                    }
                    else
                    {
                        if (control_zero < 2)
                        {
                            
                            fila_primeiro_zero = (Remover(fila_primeiro_zero, 0));  
                            
                            control_zero += 1;
                        }
                        else
                        {
                            control_um = 0;
                            control_zero = 0;
                            control_dois = 0;
                        }
                        
                    }
                    
                }
            }
            if (balancear == 4)
            {
                if (control_dois < 2)
                {
                    
                    fila_primeiro_dois = Remover(fila_primeiro_dois, 2);
                    
                    control_dois += 1;
                }
                else
                {
                    if (control_um < 1)
                    {
                        
                        fila_primeiro_um = (Remover(fila_primeiro_um, 1));

                            
                        control_um += 1;
                        
                    }
                    else
                    {
                        if (control_zero < 1)
                        {
                            
                            fila_primeiro_zero = (Remover(fila_primeiro_zero, 0));

                            control_zero += 1;
                        }
                        else
                        {
                            control_um = 0;
                            control_zero = 0;
                            control_dois = 0;
                        }
                        
                    }
                    
                }
            }
            
            
            continue;
            
        }
        if (opcao == 3)
        {
            system("clear");
            printf("\n|+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_|\n");

            imprimir(fila_primeiro_zero);
            printf("\n");

            printf("\n|+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_|\n");

            imprimir(fila_primeiro_um);

            printf("\n");
            printf("\n|+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_|\n");

            imprimir(fila_primeiro_dois);

            printf("\n");
            printf("\n|+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_|\n");

            continue;
        } 
        else
        {
            break;
        }
    }
    

}
