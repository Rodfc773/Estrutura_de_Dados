#include <iostream>
#include <string.h>
#include <algorithm> 
using namespace std;

int verificar_char(char letra, int i)
{
    char array[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    if(i == 26)
    {
        return 0;
    }
    else
    {
        if (letra == array[i] || letra == toupper(array[i]))
        {
            return 1;
        }

        return verificar_char(letra, i + 1);
        
    }
    
    
}
void verificar_nome(string nome, int i, int tam)
{
    if(i < tam)
    {
        if(nome[0] != toupper(nome[0]) || nome[0] == ' ')
        {
            cout << "!- ERROR -!\n" << "--> O nome digitado não começa com letra maiuscula ou possui um espaço em branco no caracter inicial, logo é um nome inválido\n";
            return;

        }
        if ( verificar_char(nome[i], 1)  == 0)
        {
            cout << "!- ERROR -!\n" << "--> O nome digitado possui um caracter especial ou possui um numero, logo não é considerado um nome válido\n" ;

            return ;
        }
        else
        {
            verificar_nome(nome, i + 1, tam);
        }  
    }
}
int main()
{
    string nome;

    cin >> nome;

    int tam;

    tam = nome.size();

    verificar_nome(nome, 0, tam);

    
}