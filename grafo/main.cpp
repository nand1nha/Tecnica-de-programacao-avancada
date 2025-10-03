#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

int main()
{
    int tipo;
    int tamanho;
    cout << "Tipo de grafo" << endl;
    cout << "1 - Direcionado" << endl;
    cout << "2 - Não direcionado" << endl;
    cout << "Escolha o tipo de grafo: " << endl;
    cin >> tipo;
    cout << "Tamanho do grafo (quantidade de vertices): " << endl;
    cin >> tamanho;
    switch (tipo)
    {
    case 1:
        cout << "Grafo direcionado" << endl;
        break;
    case 2:
        cout << "Grafo não direcionado" << endl;
        break;
    default:
        cout << "Opção inválida" << endl;
    }
    return 0;
}