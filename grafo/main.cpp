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
    cout << "--- Tipo de grafo ---" << endl;
    cout << "1 - Direcionado" << endl;
    cout << "2 - Não direcionado" << endl;
    cout << "--------------------" << endl;
    cout << "Escolha o tipo de grafo: " << endl;
    cin >> tipo;
    cout << "Tamanho do grafo (quantidade de vertices): " << endl;
    cin >> tamanho;
    switch (tipo)
    {
    case 1:
        cout << "Grafo direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;
        int *acesso = new int[tamanho];
        int **matriz = new int *[tamanho];
        for (int i = 0; i < tamanho; i++)
        {
            matriz[i] = new int[tamanho];
            for(int j = 0; j < tamanho; j++) {
                matriz[i][j] = 0; 
            }
        }

        for (int i = 0; i < tamanho; i++){
            delete[] matriz[i];
        }
        delete[] matriz;
        break;
    case 2:
        cout << "Grafo não direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;
        break;
    default:
        cout << "Opção tipo de grafico inválida" << endl;
    }
    return 0;
}