#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

int **criarMatriz(int tamanho)
{
    int **matriz = new int *[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        matriz[i] = new int[tamanho];
        for (int j = 0; j < tamanho; j++)
        {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void criaGrafoNaoDirecionado(int tamanho)
{
    int *acesso = new int[tamanho];
    int **matriz = criarMatriz(tamanho);

    int arestas = ((tamanho * tamanho) / 2) - tamanho;
    int cont = 0;
    while (cont <= arestas)
    {
        int x = rand() % tamanho;
        int y = rand() % tamanho;
        if (x != y)
        {
            if (matriz[x][y] == 0)
            {
                matriz[x][y] = 1;
                matriz[y][x] = 1;
                cont++;
            }
        }
    }

    ofstream arquivo("grafo.dot");
    if (arquivo.is_open())
    {
        arquivo << "graph G {" << endl;
        for (int i = 0; i < tamanho; i++)
        {
            arquivo << "  " << i << ";" << endl;
        }
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = i; j < tamanho; j++)
            {
                if (matriz[i][j] == 1)
                {
                    arquivo << "  " << i << " -- " << j << ";" << endl;
                }
            }
        }
        arquivo << "}" << endl;
        arquivo.close();
        cout << "Arquivo 'grafo.dot' criado com sucesso!" << endl;
    }
    else
    {
        cout << "Erro ao criar o arquivo" << endl;
    }

    for (int i = 0; i < tamanho; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void criaGrafoDirecionado(int tamanho)
{
    int *acesso = new int[tamanho];
    int **matriz = criarMatriz(tamanho);

    int arestas = ((tamanho * tamanho) / 2);
    int cont = 0;
    while (cont <= arestas)
    {
        int x = rand() % tamanho;
        int y = rand() % tamanho;
        if (x != y)
        {
            if (matriz[x][y] == 0)
            {
                matriz[x][y] = 1;
                cont++;
            }
        }
    }

    ofstream arquivo("grafo.dot");
    if (arquivo.is_open())
    {
        arquivo << "digraph G {" << endl;
        for (int i = 0; i < tamanho; i++)
        {
            arquivo << "  " << i << ";" << endl;
        }
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = i; j < tamanho; j++)
            {
                if (matriz[i][j] == 1)
                {
                    arquivo << "  " << i << " -> " << j << ";" << endl;
                }
            }
        }
        arquivo << "}" << endl;
        arquivo.close();
        cout << "Arquivo 'grafo.dot' criado com sucesso!" << endl;
    }
    else
    {
        cout << "Erro ao criar o arquivo" << endl;
    }

    for (int i = 0; i < tamanho; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void lerArquivoDOT(const string nomeArquivo){
    int vertices = -1;
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }
    string linha;
    while (getline(arquivo, linha)) {
        cout << linha << endl;
        vertices++;
        if (linha.find("-") != string::npos) {
            int **matriz = criarMatriz(vertices);
        }
    }
    
    arquivo.close();
}

int main()
{
    int tipo;
    int tamanho;
    cout << "--- Tipo de grafo ---" << endl;
    cout << "1 - Não direcionado" << endl;
    cout << "2 - Direcionado" << endl;
    cout << "--------------------" << endl;
    cout << "Escolha o tipo de grafo: " << endl;
    cin >> tipo;
    cout << "Tamanho do grafo (quantidade de vertices): " << endl;
    cin >> tamanho;

    if (tipo == 1)
    {
        cout << "Grafo não direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;

        criaGrafoNaoDirecionado(tamanho);
    }
    else if (tipo == 2)
    {
        cout << "Grafo direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;

        criaGrafoDirecionado(tamanho);
    }
    else
    {
        cout << "OpÃ§Ã£o tipo de grafico invÃ¡lida" << endl;
    }

    lerArquivoDOT("grafo.dot");

    return 0;
}
