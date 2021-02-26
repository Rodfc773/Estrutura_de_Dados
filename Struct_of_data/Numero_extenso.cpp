#include <iostream>
#include <strings.h>

using namespace std;

int Verificacao_sinal(char numero)
{
    int num = numero;
    if(num == 43 || num == 45)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Verificacao_digito(string numero, int i, int tam)
{
    if (i == tam)
    {
        return 1;
        
        
    }
    else
    {
        int num = numero[i];

        if (num >= 48 && num <= 57)
        {
            return Verificacao_digito(numero, i + 1, tam);
        }
        else
        {
            return 0;
        }
        
    }
    
}
int Verificar_virgula(string numero, int i, int tam)
{
    for (i ; i < tam; i++)
    {
        int num = numero[i];
        if (num == 44)
        {
            return 1;
        }
        
    }
    return 0;
    
    
}
int find_virgula(string numero, int i, int tam, int pos)
{
    for (int i = 0; i < tam; i++)
    {
        if (numero[i] == ',')
        {
            pos = i;

            return pos;

        }
        
    }
    return 0;
    
}
void Numero_extenso_com_virgula(string numero, int pos, int tam)
{
    char pos_virgula[tam - pos];
    char pre_virgula[pos];

}
int main()
{
    string numero;
    
    getline(cin, numero);

    int tam = numero.size();

    if (Verificacao_digito(numero, 0 , tam))
    {
        if (tam == 0)
        {
            cout << "       !------- ERROR -------!\n      O Numero digitado é inválido\n";
        }
        
        else
        {
            if (Verificacao_digito(numero, 1, tam))
            {
                cout << "O Numero {" << numero <<"} É Natural\n";
            }
            else
            {
                if (Verificar_virgula(numero, 0, tam) && tam >= 2)
                {
                    cout << "O Numero {" << numero <<"} É Real\n";
                }
                else
                {
                     cout << "       !------- ERROR -------!\n      O Numero digitado é inválido\n";
                }
            }
        }
    
        
    }
    else
    {
        if (Verificacao_sinal(numero[0]))
        {
            if (tam == 1)
            {
                cout << "       !------- ERROR -------!\n      O Numero digitado é inválido\n";
            }
            else
            {
                if (Verificacao_digito(numero, 1 , tam))
                {
                    cout << "O Numero {" << numero <<"} É Inteiro\n";
        
                }
                else
                {
                    if (Verificar_virgula(numero, 0, tam) && tam > 2)
                    {
                        
                    }
                    else
                    {
                        cout << "       !------- ERROR -------!\n      O Numero digitado é inválido\n";
                    }
                    
                }
                
                
            }
            
        }
    }
    
}
    

   