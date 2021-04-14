#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

using namespace std;

struct data //lista de quantidades/validades
{
    char data_validade_dia[3];
    char data_validade_mes[3];
    char data_validade_ano[5];
    int quantidade;
    data *prox;
};

struct no //lista de codigos
{
    int codigo;
    char descricao[256];
    data *validade;
    char marca[20];
    no *prox;


};
no *Criar(no *produto)
{
    produto = NULL;
    

    return produto;
}
int validar_dia(char dia[3])
{
    int aux1 = dia[0];
    if (aux1 >= 48 && aux1 <= 51)
    {
        int aux2 = dia[1];

       if (aux1 == 51)
       {
           if (aux2 == 48 || aux2 == 49)
           {
               return 1;
           }
           else
           {
               return 0;
           }  
       }
       if (aux1 == 48 && aux2 == 48)
       {
           return 0;
       }
       
       else
       {
           return 1;
           
       }
       
    }
    else
    {
        return 0;
    }
    
}
int validar_mes(char mes[3])
{
    int mes_digito_um = mes[0];

    if (mes_digito_um == 48 || mes_digito_um == 49)
    {
        int mes_digito_dois = mes[1];

        if (mes_digito_um == 49)
        {
           if (mes_digito_dois >= 48 && mes_digito_dois < 51)
           {
               return 1;
           }
           else
           {
               return 0;
           }
           
        }
        else if (mes_digito_um == 48 && mes_digito_dois == 48)
        {
            return 0;
        }
        
        else
        {
            return 1;
        }
        
        
    }
    else
    {
        return 0;
    }
    
}
int comparar_dia(char dia_produto[3], char dia[3])
{
    if (strcmp(dia_produto,dia) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int Comparar_mes(char mes_produto[3], char mes[3])
{
    if (strcmp(mes_produto,mes) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int comparar_ano(char ano_produto[5], char ano[5])
{
    if (strcmp(ano_produto, ano) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
data *Inserir_validade(data *val, char dia[3], char mes[3], char ano[5], int quantidade)//Oredena e inseri novas datas de validades e quantidades de um mesmo produto
{
    data *novo;

    novo = (data*)malloc(sizeof(data));

    if (!novo)
    {
        printf("A quantidade desse produto chegou ao limite\n");
        return val;
    }
    else
    {
        if (val == NULL)
        {
            strcpy(novo->data_validade_dia, dia);
            strcpy(novo->data_validade_mes, mes);
            strcpy(novo->data_validade_ano, ano);
            novo->quantidade += quantidade;
            novo->prox = NULL;
            val = novo;

            return val;
        }
        else
        {
            data *aux;

            aux = val;

            while ( (aux->prox != NULL && comparar_dia(aux->data_validade_dia, dia)) && (Comparar_mes(aux->data_validade_mes, mes) && comparar_ano(aux->data_validade_ano, ano) ))
            {
                aux = aux->prox;
            }

            if (aux->prox == NULL)
            {
                if (comparar_ano(aux->data_validade_ano,ano))
                {
                    novo->prox = aux->prox;
                    strcpy(novo->data_validade_ano, ano);
                    strcpy(novo->data_validade_mes, mes);
                    strcpy(novo->data_validade_dia, dia);
                    novo->quantidade += quantidade;
                    aux->prox = novo;

                    
                }
                else if (strcmp(aux->data_validade_ano, ano) == 0)
                {
                    if (Comparar_mes(aux->data_validade_mes,mes))
                    {
                        novo->prox = aux->prox;
                        strcpy(novo->data_validade_ano, ano);
                        strcpy(novo->data_validade_mes, mes);
                        strcpy(novo->data_validade_dia, dia);
                        novo->quantidade += quantidade;
                        aux->prox = novo;
                    }
                    else if (strcmp(aux->data_validade_mes, mes) == 0)
                    {
                        if (comparar_dia(aux->data_validade_dia, dia))
                        {
                            novo->prox = aux->prox;
                            strcpy(novo->data_validade_ano, ano);
                            strcpy(novo->data_validade_mes, mes);
                            strcpy(novo->data_validade_dia, dia);
                            novo->quantidade += quantidade;
                            aux->prox = novo;
                        }
                        else if(strcmp(aux->data_validade_dia, dia) == 0)
                        {
                            aux->quantidade += quantidade;
                        }
                        else
                        {
                            novo->prox = aux->prox;
                            strcpy(novo->data_validade_dia, aux->data_validade_dia);
                            strcpy(novo->data_validade_mes, aux->data_validade_mes);
                            strcpy(novo->data_validade_ano, aux->data_validade_ano);
                            novo->quantidade = aux->quantidade;

                            aux->prox = novo;
                            strcpy(aux->data_validade_dia, dia);
                            strcpy(aux->data_validade_mes, mes);
                            strcpy(aux->data_validade_ano, ano);
                            aux->quantidade = quantidade;
                        }
                        
                    }
                    else
                    {
                        novo->prox = aux->prox;
                        strcpy(novo->data_validade_dia, aux->data_validade_dia);
                        strcpy(novo->data_validade_mes, aux->data_validade_mes);
                        strcpy(novo->data_validade_ano, aux->data_validade_ano);
                        novo->quantidade = aux->quantidade;

                        aux->prox = novo;
                        strcpy(aux->data_validade_dia, dia);
                        strcpy(aux->data_validade_mes, mes);
                        strcpy(aux->data_validade_ano, ano);
                        aux->quantidade = quantidade;
                    }
                    
                }
                else
                {
                    novo->prox = aux->prox;
                    strcpy(novo->data_validade_dia, aux->data_validade_dia);
                    strcpy(novo->data_validade_mes, aux->data_validade_mes);
                    strcpy(novo->data_validade_ano, aux->data_validade_ano);
                    novo->quantidade = aux->quantidade;

                    aux->prox = novo;
                    strcpy(aux->data_validade_dia, dia);
                    strcpy(aux->data_validade_mes, mes);
                    strcpy(aux->data_validade_ano, ano);
                    aux->quantidade = quantidade;
                }
                    
                return val;
            }
            else
            {
                if (comparar_ano(aux->data_validade_ano,ano))
                {
                    novo->prox = aux->prox;
                    strcpy(novo->data_validade_ano, ano);
                    strcpy(novo->data_validade_mes, mes);
                    strcpy(novo->data_validade_dia, dia);
                    novo->quantidade += quantidade;
                    aux->prox = novo;

                    
                }
                else if (strcmp(aux->data_validade_ano, ano) == 0)
                {
                    if (Comparar_mes(aux->data_validade_mes,mes))
                    {
                        novo->prox = aux->prox;
                        strcpy(novo->data_validade_ano, ano);
                        strcpy(novo->data_validade_mes, mes);
                        strcpy(novo->data_validade_dia, dia);
                        novo->quantidade += quantidade;
                        aux->prox = novo;
                    }
                    else if (strcmp(aux->data_validade_mes, mes) == 0)
                    {
                        if (comparar_dia(aux->data_validade_dia, dia))
                        {
                            novo->prox = aux->prox;
                            strcpy(novo->data_validade_ano, ano);
                            strcpy(novo->data_validade_mes, mes);
                            strcpy(novo->data_validade_dia, dia);
                            novo->quantidade += quantidade;
                            aux->prox = novo;
                        }
                        else if(strcmp(aux->data_validade_dia, dia) == 0)
                        {
                            aux->quantidade += quantidade;
                        }
                        else
                        {
                            novo->prox = aux->prox;
                            strcpy(novo->data_validade_dia, aux->data_validade_dia);
                            strcpy(novo->data_validade_mes, aux->data_validade_mes);
                            strcpy(novo->data_validade_ano, aux->data_validade_ano);
                            novo->quantidade = aux->quantidade;

                            aux->prox = novo;
                            strcpy(aux->data_validade_dia, dia);
                            strcpy(aux->data_validade_mes, mes);
                            strcpy(aux->data_validade_ano, ano);
                            aux->quantidade = quantidade;
                        }
                        
                    }
                    else
                    {
                        novo->prox = aux->prox;
                        strcpy(novo->data_validade_dia, aux->data_validade_dia);
                        strcpy(novo->data_validade_mes, aux->data_validade_mes);
                        strcpy(novo->data_validade_ano, aux->data_validade_ano);
                        novo->quantidade = aux->quantidade;

                        aux->prox = novo;
                        strcpy(aux->data_validade_dia, dia);
                        strcpy(aux->data_validade_mes, mes);
                        strcpy(aux->data_validade_ano, ano);
                        aux->quantidade = quantidade;
                    }
                    
                }
                else
                {
                    novo->prox = aux->prox;
                    strcpy(novo->data_validade_dia, aux->data_validade_dia);
                    strcpy(novo->data_validade_mes, aux->data_validade_mes);
                    strcpy(novo->data_validade_ano, aux->data_validade_ano);
                    novo->quantidade = aux->quantidade;

                    aux->prox = novo;
                    strcpy(aux->data_validade_dia, dia);
                    strcpy(aux->data_validade_mes, mes);
                    strcpy(aux->data_validade_ano, ano);
                    aux->quantidade = quantidade;
                }
                return val;
            }
            
            
        }
        
    }
    
}
no *Inserir(no *produto, int codigo, char marca[20], char descricao[256])//Inseri os codigos dos produtos na lista ordenadamente
{
    no *novo;

    novo = (no*) malloc(sizeof(no));

    if (!novo)
    {
        printf("Estoque Cheio\n");
        return produto;
    }
    else
    {
        char dia[3];
        char mes[3];
        char ano[5];
        int quantidade;

        printf("!-Digite a validade-!\n");
        printf("Digite o dia: ");
        scanf(" %[^\n]", dia);

        while (validar_dia(dia) == 0 || strlen(dia) > 2)
        {
           printf("O dia é inválido, por favor digitar numeros validos\n->: ");
            scanf(" %s", dia);
        }

        printf("Digite o mês: ");
        scanf(" %s", mes);

        while (validar_mes(mes) == 0 || strlen(mes) > 2)
        {
            printf("O mês é inválido, por favor digite uma data valida\n->: ");
            scanf(" %s", mes);
        }
        
        printf("Digite o ano: ");
        scanf(" %[^\n]", ano);

        while (strlen(ano) > 4)
        {
           printf("Ano inválido, Digite um ano válido: ");
            scanf(" %[^\n]", ano);
        }
        
        printf("Digite uma quantidade: ");
        scanf("%d", &quantidade);

        if (produto == NULL)
        {

            novo->codigo = codigo;
            strcpy(novo->marca, marca);
            strcpy(novo->descricao, descricao);

            novo->validade = Inserir_validade(novo->validade, dia, mes, ano, quantidade);
            novo->prox = NULL;

            produto = novo;

            return produto;  
        }
        else
        {
            no *aux;
            aux = produto;

            while (aux->prox != NULL && aux->codigo < codigo)
            {
                aux = aux->prox;
            }
            if (aux->prox == NULL)
            {
                if (aux->codigo < codigo)
                {
                    novo->prox == NULL;
                    novo->codigo = codigo;
                    strcpy(novo->marca, marca);
                    strcpy(novo->descricao, descricao);
                    aux->prox = novo;

                    novo->validade = Inserir_validade(novo->validade, dia, mes, ano, quantidade);
                }
                else if (aux->codigo == codigo)
                {
                    aux->validade = Inserir_validade(aux->validade, dia, mes, ano, quantidade);
                }
                else
                {
                    novo->codigo = aux->codigo;
                    novo->validade = aux->validade;
                    strcpy(novo->marca, aux->marca);
                    strcpy(novo->descricao, aux->descricao);
                    novo->prox = aux->prox;


                    aux->codigo = codigo;
                    strcpy(aux->marca, marca);
                    strcpy(aux->descricao, descricao);
                    
                    aux->validade = NULL;
                    aux->validade = Inserir_validade(aux->validade, dia,mes, ano, quantidade);
                    aux->prox = novo;   
                }
                return produto;  
            }
            else
            {
                if (aux->codigo == codigo)
                {
                    aux->validade = Inserir_validade(aux->validade, dia, mes, ano, quantidade);
                }
                else{
                    novo->codigo = aux->codigo;
                    novo->validade = aux->validade;
                    strcpy(novo->marca, aux->marca);
                    strcpy(novo->descricao, aux->descricao);
                    novo->prox = aux->prox;

                    aux->codigo = codigo;
                    strcpy(aux->marca, marca);
                    strcpy(aux->descricao, descricao);
                    aux->validade = NULL;
                    aux->validade = Inserir_validade(aux->validade, dia, mes, ano, quantidade);
                    aux->prox = novo;
                }
                return produto;
            }   
        }  
    } 
}
int tamanho(data *validade)
{
    int tamanho = 0;

    data *aux;

    aux = validade;

    while (aux != NULL)
    {
        tamanho += 1;
        aux = aux->prox;
    }
    return tamanho;
}
int tamanho_produtos(no *produto)
{
    int tam = 0;

    no *aux;

    aux = produto;

    while (aux != NULL)
    {
        tam += 1;
        aux = aux->prox;
    }
    return tam;
    
}
data *Retirar_validade(data *vali, int quantidade)
{
    data *aux;

    aux = vali;

    int total;

    aux->quantidade = aux->quantidade - quantidade;
    total = aux->quantidade;

    if (tamanho(vali) == 1)
    {
        if (aux->quantidade <= 0)
        {
            printf("\n!!----O Numero a ser Retirado é maior que o Existente, logo o produto será retirado do estoque----!!\n");
        
            vali = NULL;
            
            free(aux);
            return vali;
            
        }  
        else
        {
            aux->quantidade = total;  
            return vali;
        }
        
        
    }
    if (tamanho(vali) > 1)
    {
        while (aux->quantidade <= 0 && tamanho(vali) > 1)
        {
           vali = vali->prox;
           free(aux);
           aux = vali;
           aux->quantidade = aux->quantidade + total;
           total = aux->quantidade; 
        }
        if (tamanho(vali) == 0)
        {
            printf("\n!!----O Numero a ser Retirado é maior que os Existentes, logo o produto será retirado do estoque----!!\n");
            free(aux);
           
        }
        return vali;
        
    }
    return vali;
}
no *Retirar(no *produto, int codigo, int quantidade)
{
    no *aux;
    no *aux_pre;

    aux = produto;

    if (produto == NULL)
    {
        printf("\n!!--- ESTOQUE VAZIO ---!!\n");
        return produto;
    }
    
    else{

        while (aux->codigo != codigo && aux != NULL)
        {
            aux_pre = aux;
            aux = aux->prox;
        }

        if(aux == NULL)
        {
            printf("\n!--O produto não existe no estoque--!\n");
        }
        else
        {
            aux->validade = Retirar_validade(aux->validade, quantidade);

            if (aux->validade == NULL)
            {
                
                printf("Produto Esgotado\n");
                aux_pre->prox = aux->prox;
                free(aux);
                return produto;
            }
            
        }
        return produto;
        
    }
         
}

void lista_quantidades(data *val)
{
    data *aux = val;

    while (aux != NULL)
    {
        printf("|+-+-+-+-+-+-+-+-+-+-\n\n");
        printf("!-> Validade: %s/%s/%s\n", aux->data_validade_dia, aux->data_validade_mes, aux->data_validade_ano);
        printf("!-> Quantidade: %d\n", aux->quantidade);
        aux = aux->prox;
    }
    printf("|+-+-+-+-+-+-+-+-+-+-\n\n");

}
void Listar_produtos(no *produto)
{
    no *aux = produto;

    printf("\n|-------- LISTA DO ESTOQUE ----------------------|\n");
    while (aux != NULL)
    {
        printf("\n!-> Codigo: %d\n", aux->codigo);
        printf("!->Marca: %s\n", aux->marca);
        printf("!-> Descricão: %s\n", aux->descricao);
        lista_quantidades(aux->validade);

        aux = aux->prox;
    }
    printf("|--------------------------------------------------|\n\n");
}
void Consultar(no *produto, int codigo)
{
    no *aux;
    aux = produto;

    printf("|---------- CONSULTA ------------------------------|");

    while (aux != NULL)
    {
        if (aux->codigo == codigo)
        {
            printf("\n!-> Codigo: %d\n", aux->codigo);
            printf("!->Marca: %s\n", aux->marca);
            printf("!-> Descricão: %s\n", aux->descricao);
            lista_quantidades(aux->validade);
            printf("|--------------------------------------------------|\n\n");

            return;
        }
        
        aux = aux->prox;
    }

    printf("\n!!--O Produto não pertence ao estoque--!!\n\n");
    printf("|--------------------------------------------------|\n\n");
   
    
    
}
int main()
{
    no *produto;

    produto = Criar(produto);

    int opcao;
    int cod;
            char marca[20];
            char descricao[256];

    while (1)
    {
        printf("\n|----- SISTEMA DE GERENCIAMENTO DE ESTOQUE -----|\n");
        printf("|(1) : Inserir\n|(2) : Remover\n|(3) : Consultar\n|(4) : Listar estoque\n|(5) : Sair\n");
        printf("|opcao ->: ");
        scanf("%d", &opcao);
        printf("\n|-----------------------------------------------|\n");

        if (opcao == 1)
        {
            system("clear");

            printf("Digite um codigo: ");
            scanf("%d", &cod);

            printf("Digite a Marca: ");
            scanf(" %[^\n]", marca);

            printf("Digite uma Descrição: ");
            scanf(" %[^\n]", descricao);

            produto = Inserir(produto, cod, marca, descricao);

            printf("Produto Inserido!\n");

            continue;
        }
        if (opcao == 2)
        {
            printf("Digite um codigo de produto a ser retirado: ");
            scanf("%d", &cod);

            int quantidade;

            printf("Digite a quantidade a ser retirada\n");
            scanf("%d", &quantidade);

            produto = Retirar(produto, cod, quantidade);
        }
        
        if (opcao == 3)
        {
            system("clear");
            printf("Digite um codigo de produto a ser Consultado: ");
            scanf("%d", &cod);
            printf("\n\n");
            Consultar(produto, cod);
        }
        
        if (opcao == 4)
        {
            system("clear");
            Listar_produtos(produto);

            continue;
        }
        if (opcao == 5)
        {
            system("clear");

            printf("!--- SESSÃO ENCERRADA --!\n\n");
            break;
        }
          
    }
}