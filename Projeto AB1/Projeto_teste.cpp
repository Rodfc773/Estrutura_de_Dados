#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Cidade
{
    char nome_cidade[25];
    Cidade *left;
    Cidade *rigth;
    int log;
    int lat;
    int altura;
    int fator;
    int distancia;
};
struct Latitude
{
    int Lat;
    int altura;
    int fator;

    Latitude *left;
    Latitude *rigth;

    
};

struct Longentidude
{
    int Log;
    Longentidude *prox;
    Latitude *cordenada;
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
int Altura_cidade(Cidade *city, int h1, int h2)
{
    if (city->left != NULL)
    {
        h1 = Altura_cidade(city->left, h1, h2);
    }
    else
    {
        h1 += 0;
    }

    if (city->rigth != NULL)
    {
        h2 = Altura_cidade(city->rigth, h1, h2);
    }
    else
    {
        h2 += 0;
    }
    return 1 + Max(h1, h2);
    
}
int Altura_lat(Latitude *lat, int h1, int h2)
{
    if (lat->left != NULL)
    {
        h1 = Altura_lat(lat->left, h1, h2);
    }
    else
    {
        h1 += 0;
    }

    if (lat->rigth != NULL)
    {
        h2 = Altura_lat(lat->rigth, h1, h2);
    }
    else
    {
        h2 += 0;
    }
    return 1 + Max(h1, h2);
}
void Set_high_cidade(Cidade *city)
{
    if (city == NULL)
    {
        return;
    }
    else
    {
        if (city->left == NULL && city->rigth == NULL)
        {
            city->altura = Altura_cidade(city, 0, 0);
            city->fator = 0;
        }
        else if (city->left == NULL)
        {
            
            city->altura = 1 + Altura_cidade(city->rigth, 0, 0);
        }
        else if (city->rigth == NULL)
        {
            
            city->altura = 1 + Altura_cidade(city->left, 0, 0);
        }
        else
        {
            city->altura = 1 + Max(Altura_cidade(city->left, 0, 0), Altura_cidade(city->rigth, 0, 0));
           
        }

        Set_high_cidade(city->left);
        Set_high_cidade(city->rigth);
    }
    
}
void Set_high_lat(Latitude *lat)
{
    if (lat == NULL)
    {
        return;
    }
    else
    {
        if (lat->left == NULL && lat->rigth == NULL)
        {
            lat->altura = Altura_lat(lat, 0, 0);
            lat->fator = 0;
        }
        else if (lat->left == NULL)
        {
            
            lat->altura = 1 + Altura_lat(lat->rigth, 0, 0);
        }
        else if (lat->rigth == NULL)
        {
            
            lat->altura = 1 + Altura_lat(lat->left, 0, 0);
        }
        else
        {
            lat->altura = 1 + Max(Altura_lat(lat->left, 0, 0), Altura_lat(lat->rigth, 0, 0));
           
        }

        Set_high_lat(lat->left);
        Set_high_lat(lat->rigth);
    }
}
int Fator_cidade(Cidade *esq, Cidade *dir)
{
    if (esq == NULL && dir == NULL)
    {
        return 0;
    }
    else if (esq == NULL)
    {
        return 0 - dir->altura;
    }
    else if(dir == NULL)
    {
        return esq->altura;
    }
    else
    {
        return esq->altura - dir->altura;
    }
    
    
}
int Fator_lat(Latitude *esq, Latitude *dir)
{
    if (esq == NULL && dir == NULL)
    {
        return 0;
    }
    else if (esq == NULL)
    {
        return 0 - dir->altura;
    }
    else if(dir == NULL)
    {
        return esq->altura;
    }
    else
    {
        return esq->altura - dir->altura;
    }
}
Cidade *Rot_direita_cidade(Cidade *city)
{
    Cidade *aux1, *aux2;

    aux1 = city->left;
    aux2 = aux1->rigth;

    aux1->rigth = city;
    city->left =  aux2;
    city = aux1;

    return city;
}
Cidade *Rot_esquerda_cidade(Cidade *city)
{
    Cidade *aux1, *aux2;

    aux1 = city->rigth;
    aux2 = aux1->left;

    aux1->left = city;
    city->rigth =  aux2;
    city = aux1;

    return city;
}
Latitude *Rot_direita_lat(Latitude *city)
{
    Latitude *aux1, *aux2;

    aux1 = city->left;
    aux2 = aux1->rigth;

    aux1->rigth = city;
    city->left =  aux2;
    city = aux1;

    return city;
}
Latitude *Rot_esquerda_lat(Latitude *city)
{
    Latitude *aux1, *aux2;

    aux1 = city->rigth;
    aux2 = aux1->left;

    aux1->left = city;
    city->rigth =  aux2;
    city = aux1;

    return city;
}
Cidade *Balacear_city(Cidade *city)
{
    if (city == NULL)
    {
       return NULL;
    }
    else
    {
        Cidade *aux;

        city->fator = Fator_cidade(city->left, city->rigth);

        if (city->fator < -1)
        {
            aux = city->rigth;

            aux->fator = Fator_cidade(aux->left, aux->rigth);

            if (aux->fator == 1)
            {
                city->rigth = Rot_direita_cidade(city->rigth);
                city = Rot_esquerda_cidade(city);
            }
            else
            {
                city = Rot_esquerda_cidade(city);
            }
            city->rigth = Balacear_city(city->rigth);
            
        }
        if (city->fator > 1)
        {
            aux = city->left;

            aux->fator = Fator_cidade(aux->left, aux->rigth);

            if (aux->fator == -1)
            {
                city->left = Rot_esquerda_cidade(city->left);
                city = Rot_direita_cidade(city);
            }
            else
            {
                city = Rot_direita_cidade(city);
            }
            city->rigth = Balacear_city(city->left);
        }
        return city;
        
    }
    
}
Latitude *Balancear_lat(Latitude *city)
{
    if (city == NULL)
    {
        return NULL;
    }
    else
    {
        Latitude *aux;

        city->fator = Fator_lat(city->left, city->rigth);

        printf("Raiz: %d, Fator: %d", city->Lat, city->fator);

        if (city->fator < -1)
        {
            aux = city->rigth;

            aux->fator = Fator_lat(aux->left, aux->rigth);

            if (aux->fator == 1)
            {
                city->rigth = Rot_direita_lat(city->rigth);
                city = Rot_esquerda_lat(city);
            }
            else
            {
                city = Rot_esquerda_lat(city);
            }
            city->rigth = Balancear_lat(city->rigth);
        }
                
        if (city->fator > 1)
        {
            aux = city->left;

            aux->fator = Fator_lat(aux->left, aux->rigth);

            if (aux->fator == -1)
            {
                city->left = Rot_esquerda_lat(city->left);
                city = Rot_direita_lat(city);
            }
            else
            {
                city = Rot_direita_lat(city);
            }
            city->rigth = Balancear_lat(city->left);
            
            
        }
        return city;
    }
    
}
void Chamar_set_high_cordeana(Longentidude *log)
{
    if (log == NULL)
    {
        return;
    }
    else
    {
        Set_high_lat(log->cordenada);

        Chamar_set_high_cordeana(log->prox);
    }
}
void Chamar_balancear_cord(Longentidude *log)
{
    if (log == NULL)
    {
        return;
    }
    else
    {
        Latitude *aux = log->cordenada;
        //printf("Antiga Raiz: %d de log: %d\n",aux->Lat, log->Log );
        log->cordenada = Balancear_lat(log->cordenada);
        //printf("Nova Raiz: %d de log: %d\n",aux->Lat, log->Log );

        Chamar_balancear_cord(log->prox);
    }
    
}
Cidade *Verificar_city_nome(Cidade *city, char nome[25])
{
    if (city == NULL)
    {
        return NULL;
    }
    else
    {
        if (strlen(city->nome_cidade) <  strlen(nome))
        {
            city->rigth = Verificar_city_nome(city->rigth, nome);
        }
        else if (strlen(city->nome_cidade) >  strlen(nome))
        {
            city->left = Verificar_city_nome(city->left, nome);
        }
        else
        {
            if (strcmp(city->nome_cidade, nome) < 0)
            {
                city->rigth = Verificar_city_nome(city->rigth, nome);
            }
            else if (strcmp(city->nome_cidade, nome) > 0)
            {
                city->left = Verificar_city_nome(city->left, nome);
            }
            else
            {
                return city;
            }
        }
        return city;
    }
    
    
}
Cidade *Verificar_city_cordenadas(Cidade *city, int lat, int log)
{
    if (city == NULL)
    {
        return NULL;
    }
    else
    {
        Verificar_city_cordenadas(city->left, lat, log);
        if (city->lat == lat && city->log == log)
        {
            return city;
        }
        Verificar_city_cordenadas(city->rigth, lat, log);

        return city;
        
    }
    
}
Cidade *Inserir_cidade(Cidade *raiz,char nome[25], int log, int lat)
{
    if (raiz == NULL)
    {
        raiz = (Cidade*)malloc(sizeof(Cidade));

        strcpy(raiz->nome_cidade,nome);
        raiz->log = log;
        raiz->lat = lat;

        return raiz;

    }
    else
    {
        if (strlen(raiz->nome_cidade) < strlen(nome))
        {
            raiz->rigth = Inserir_cidade(raiz->rigth, nome, log, lat);
        }
        else if(strlen(raiz->nome_cidade) > strlen(nome))
        {
            raiz->left = Inserir_cidade(raiz->left, nome, log, lat);
        }
        else
        {
            if (strcmp(raiz->nome_cidade, nome) < 0)
            {
               raiz->rigth = Inserir_cidade(raiz->rigth, nome, log, lat);
            }
            else if (strcmp(raiz->nome_cidade, nome) > 0)
            {
                raiz->left = Inserir_cidade(raiz->left, nome, log, lat);
            }
            
            
        }
        return raiz;
    }
    
}
Latitude *Inserir_Lat(Latitude *lat,int x)
{
    if (lat == NULL)
    {
       lat = (Latitude*)malloc(sizeof(Latitude));

       lat->left = NULL;
       lat->rigth = NULL;

       lat->Lat = x;
       return lat;
    }
    else if (lat->Lat < x)
    {
        lat->rigth = Inserir_Lat(lat->rigth, x);
    }
    else if(lat->Lat > x)
    {
        lat->left = Inserir_Lat(lat->left, x);
    }
    return lat;
    
    
}
Longentidude *Inserir_longetidude(Longentidude *logit, int lat,int log)
{
    Longentidude *Cidadevo;
    Longentidude *aux;

    Cidadevo = (Longentidude*)malloc(sizeof(Longentidude));

    if (!Cidadevo)
    {
        printf("O database das cidades está cheia\n");
        return logit;
    }
    else
    {
        if (logit == NULL)
        {
            Cidadevo->Log = log;
            Cidadevo->prox = NULL;
            Cidadevo->cordenada = Inserir_Lat(Cidadevo->cordenada, lat);

            logit = Cidadevo;

            return logit;
        }
        else
        {
            aux = logit;

            while (aux->prox != NULL && aux->Log < log)
            {
                aux = aux->prox;
            }
            if (aux->prox == NULL)
            {
               if (aux->Log < log)
               {
                   Cidadevo->Log = log;
                   Cidadevo->prox = NULL;
                   Cidadevo->cordenada = Inserir_Lat(Cidadevo->cordenada, lat);
                   aux->prox = Cidadevo;  
               }
               else if (aux->Log > log)
               {
                    Cidadevo->Log = aux->Log;
                    Cidadevo->prox = aux->prox;
                    Cidadevo->cordenada = aux->cordenada;

                    aux->Log = log;
                    aux->prox = Cidadevo;   
                    aux->cordenada = NULL;
                    aux->cordenada = Inserir_Lat(aux->cordenada, lat);
               }
               else
               {
                   aux->cordenada = Inserir_Lat(aux->cordenada, lat);
               }
               
               
            }
            else
            {
                if (aux->Log > log)
                {
                    Cidadevo->Log = aux->Log;
                    Cidadevo->prox = aux->prox;
                    
                    Cidadevo->cordenada = aux->cordenada;

                    aux->Log = log;
                    aux->prox = Cidadevo;  
                    
                    aux->cordenada = NULL;
                    aux->cordenada = Inserir_Lat(aux->cordenada, lat);

                }
                else
               {
                   aux->cordenada = Inserir_Lat(aux->cordenada, lat);
               }

                
            }

            return logit;
            
        }
        
    }
    
}
Cidade *Remover_city(Cidade *city, char nome[25], int lat, int log)
{
    if (city == NULL)
    {
        
        return NULL;
    }
    else
    {
        if (strlen(city->nome_cidade) < strlen(nome))
        {
            city->rigth = Remover_city(city->rigth, nome, lat, log);
        }
        else if (strlen(city->nome_cidade) > strlen(nome))
        {
            city->left = Remover_city(city->left, nome, lat, log);
        }
        else
        {
            if (strcmp(city->nome_cidade, nome) < 0)
            {
                city->rigth = Remover_city(city->rigth, nome, lat, log);
            }
            else if (strcmp(city->nome_cidade, nome) > 0)
            {
                city->left = Remover_city(city->left, nome, lat, log);
            }
            else
            {
                if (city->left == NULL && city->rigth == NULL)
                {
                    free(city);
                    return NULL;
                }
                else if(city->rigth == NULL)
                {
                    Cidade *aux = city;
                    city = city->left;
                    free(aux);
                }
                else if (city->left == NULL)
                {
                    Cidade *aux = city;
                    city = city->rigth;
                    free(aux);
                }
                else
                {
                    Cidade *aux = city->left;

                    while (aux->rigth != NULL)
                    {
                        aux = aux->rigth;
                    }
                    city->lat = aux->lat;
                    city->log = aux->log;
                    strcpy(city->nome_cidade, aux->nome_cidade);

                    aux->lat = lat;
                    aux->log = log;
                    strcpy(aux->nome_cidade, nome);

                    city->left = Remover_city(city->left, nome, lat, log);
                
                }
            }
            
            
        }
        return city;
        
    }
 
}

Latitude *Remover_lat(Latitude *lati, int lat)
{
    if (lati == NULL)
    {
        return NULL;
    }
    else
    {
        if (lati->Lat < lat)
        {
            lati->rigth = Remover_lat(lati->rigth, lat);
        }
        else if (lati->Lat > lat)
        {
           lati->left = Remover_lat(lati->left, lat);
        }
        else
        {
            if (lati->left == NULL && lati->rigth == NULL)
            {
                free(lati);

                return NULL;
                
            }
            else if (lati->rigth == NULL)
            {
              
                Latitude *aux;

                aux = lati;
                lati = lati->left;
                free(aux);  
            }
            else if (lati->left == NULL)
            {
                
                Latitude *aux;

                aux = lati;
                lati = lati->rigth;
                free(aux);
                  
            }
            else
            {
                
                Latitude *aux;

                aux = lati->left;

                while (aux->rigth != NULL)
                {
                    aux = aux->rigth;
                }
                lati->Lat = aux->Lat;
                aux->Lat = lat;

                lati->left = Remover_lat(lati->left, lat);
                      
            }
             
        }
        
        return lati;
    }
    
}
Longentidude *Remover_log(Longentidude *log,int logit, int latid)
{
    Longentidude *aux, *anterior;

    aux = log;

    if (log == NULL)
    {
        return NULL;
    }
    else
    {
        while (aux != NULL && aux->Log != logit)
        {
            anterior = aux;
            aux = aux->prox;
        }
        if (aux->Log == logit)
        {
            printf("--> ta entrando aqui <---\n");
            aux->cordenada = Remover_lat(aux->cordenada, latid);

            if (aux->cordenada == NULL)
            {
                anterior->prox = aux->prox;
                free(aux);
                return NULL;
            }
            
            
        }
        return log;
        
    }
    
}
void Imprimir_cidades(Cidade *city)
{
    if (city == NULL)
    {
        return;
    }
    else
    {
        Imprimir_cidades(city->left);
        printf("Cidade : %s, Lat = %d, log = %d\n\n", city->nome_cidade, city->lat, city->log);
        Imprimir_cidades(city->rigth);
    }
    
}
void Inordem(Latitude *lat)
{
    if (lat == NULL)
    {
        printf("NULL");
    }
    else
    {
        printf("(");
        Inordem(lat->left);
        printf("), ");
        printf("%d,", lat->Lat);
        printf(" (");
        Inordem(lat->rigth);
        printf(")");
    }
    
}
void Imprimir(Longentidude *Log)
{
    if (Log == NULL)
    {
        return;
    }
    else
    {
        printf("Log: %d:\n", Log->Log);
        Inordem(Log->cordenada);
        Imprimir(Log->prox);
    }
    
}
int main()
{
    Cidade *raiz = NULL;
    Longentidude *log = NULL;

    int opcao;

    while (1)
    {
       printf("!+_+_+_+ Sistema de Dados de Cidades +_+_+_+!\n");
       printf("!(1) : Inserir\n!(2) : Remover\n!(3) : Consultar\n_>> ");
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

            printf("Digite uma latitude(Numeros inteiros): ");
            scanf("%d", &latid);

            printf("Digite uma longitude(Numeros inteiros): ");
            scanf("%d", &longit);


            raiz = Inserir_cidade(raiz, nome, longit, latid);
            log = Inserir_longetidude(log, latid, longit);

            Set_high_cidade(raiz);
            raiz = Balacear_city(raiz);

            Chamar_set_high_cordeana(log);
            Chamar_balancear_cord(log);

            continue;
       }
       if (opcao == 2)
       {
            if (log == NULL )
            {
                printf("!-- A base de dados ta vazia-- !\n\n");
                continue;
            }

            printf("Deseja excluir por (1) : nome ou por (2) :coordenadas? \n");
            int mod;
            
            scanf("%d", &mod);
            Cidade *aux;

            if (mod == 1)
            {
                printf("Digite o nome da cidade a ser deletada\n_>> ");
                char name[25];

                scanf(" %[^\n]", name);

                while (validar_nome(name) == 0)
                {
                    printf("Por Favor Digite um nome valido\n_>> ");
                    scanf(" %[^\n]", name);
                }

                aux = Verificar_city_nome(raiz, name);

                if (aux == NULL)
                {
                    printf("!-- A Cidade não se encontra Cidade banco de dados --!\n");
                    continue;
                }
                else
                {
                    printf("!-- A cidade: %s, Foi Removia com sucesso --!", name);
                }
            
                raiz = Remover_city(raiz, name, aux->lat, aux->log);

                log = Remover_log(log, aux->log, aux->lat);
            }
            else
            {
                printf("Digite as Coordenadas a serem Removidas\n");
                int x,y;

                printf("Lat: ");
                scanf("%d", &x);

                printf("Log: ");
                scanf("%d", &y);
                

                aux = Verificar_city_cordenadas(raiz, x, y);

                if (aux == NULL)
                {
                    printf("!-- A Cidade não se encontra Cidade banco de dados --!\n");
                    continue;
                }
                else
                {
                    printf("!-- A cidade de Coordenadas: Lat = %d e Log = %d, Foi Removida com sucesso --!\n", aux->lat, aux->log);
                }
                

                raiz = Remover_city(raiz, aux->nome_cidade, x, y);

                log = Remover_log(log, y, x);

            }
            
            Set_high_cidade(raiz);
            raiz = Balacear_city(raiz);

            Chamar_set_high_cordeana(log);
            Chamar_balancear_cord(log);
            
            
            continue;
       }
       if (opcao == 3)
       {

            printf("|-----------------------------------|\n");
            Imprimir(log);
            printf("\n|-----------------------------------|\n");
           
           continue;
       }
       else
       {
           break;
       }
    }
}