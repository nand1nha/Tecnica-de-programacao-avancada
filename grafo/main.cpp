#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

void grafoConexo(int **matriz, int tamanho){
	int *acesso = new int[tamanho];
	for(int i = 0; i < tamanho; i++){
		acesso[i] = 0;
	}
    acesso[0] = 1;
    for(int i = 0; i < tamanho; i++){
        if(acesso[i] == 1){
           for(int j = 0; j < tamanho; j++){
                if(matriz[i][j] == 1){
                    acesso[j] = 1;
                }
            }
        }
        
    }

    for(int i = 0; i < tamanho; i++){
        if(acesso[i] == 0){
            cout << "Grafo nÃ£o conexo" << endl;
            delete[] acesso;
            return;
        }
    }
    cout << "Grafo conexo" << endl;
    delete[] acesso;
	
}

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

void criaGrafoNaoDirecionado(int tamanho, int porcentagem)
{
    int **matriz = criarMatriz(tamanho);
    int arestaTotal = (tamanho * (tamanho - 1)) / 2;
    int arestas = (arestaTotal*porcentagem)/100;
    int cont = 0;
    while (cont < arestas)
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
            for (int j = 0; j < tamanho; j++)
            {
                if (matriz[i][j] == 1  && i < j)
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

    grafoConexo(matriz,tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void criaGrafoDirecionado(int tamanho, int porcentagem)
{
    int **matriz = criarMatriz(tamanho);
    int arestasTotal = (tamanho * (tamanho - 1));
    int arestas = (arestasTotal*porcentagem)/100;
    int cont = 0;
    while (cont < arestas)
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
            for (int j = 0; j < tamanho; j++)
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

    grafoConexo(matriz,tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void lerArquivoDOT(){
    int vertices = -1;
    ifstream arquivo("grafo.dot");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " <<endl;
        return;
    }
    string linha;
	string tipo;
	getline(arquivo, tipo,' ');
    int x;
    int y;
    int **matriz;
    while (getline(arquivo, linha)) {
        cout << linha << endl;
        vertices++;
        if (linha.find("-") != string::npos) {
            matriz = criarMatriz(vertices);
        }
		if(strcmp(tipo.c_str(),"digraph")){
			if(sscanf(linha.c_str(),"%d->%d;",&x,&y) == 2){
				matriz[x][y] = 1;
			}
		}else{
			 if(sscanf(linha.c_str(),"%d--%d;",&x,&y) == 2){
				matriz[x][y] = 1;
			}
		}
        
    }
    
    arquivo.close();
}

int main()
{
    int tipo;
    int tamanho;
    int porcentagem;
    cout << "--- Tipo de grafo ---" << endl;
    cout << "1 - NÃ£o direcionado" << endl;
    cout << "2 - Direcionado" << endl;
    cout << "--------------------" << endl;
    cout << "Escolha o tipo de grafo: " << endl;
    cin >> tipo;
    cout << "Tamanho do grafo (quantidade de vertices): " << endl;
    cin >> tamanho;
    cout << "Porcentagem de preenchimento (0 a 100): " << endl;
    cin >> porcentagem;

    if (tipo == 1)
    {
        cout << "Grafo nÃ£o direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;
        cout << "Porcentagem de preenchimento: " << porcentagem << "%" << endl;

        criaGrafoNaoDirecionado(tamanho, porcentagem);
    }
    else if (tipo == 2)
    {
        cout << "Grafo direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;
        cout << "Porcentagem de preenchimento: " << porcentagem << "%" << endl;

        criaGrafoDirecionado(tamanho, porcentagem);
    }
    else
    {
        cout << "OpÃƒÂ§ÃƒÂ£o tipo de grafico invÃƒÂ¡lida" << endl;
    }

    lerArquivoDOT();

    return 0;
}
