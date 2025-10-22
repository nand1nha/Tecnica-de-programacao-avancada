#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

struct Vertice;

struct Vizinho {
    Vertice *vizinho;
    Vizinho *proximoVizinho;
};

struct Vertice {
    int id;
    Vizinho *vizinhos;
};

Vertice *grafo;
void inicializa(int tamanho){
    grafo = new Vertice[tamanho];
    for(int i = 0; i < tamanho; i++){
        grafo[i].id=i;
        grafo[i].vizinhos = NULL;
    }
}

//nao direcionado
//falar que o B é vizinho de A
void adicionaVizinho(Vertice *a, Vertice *b){
    if (a == NULL || b == NULL)
        return;
    Vizinho *aux;
    if(a->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        a->vizinhos = temp;
    }else{
        aux = a->vizinhos;
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        Vizinho *temp = new Vizinho;
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }
    //agora eu preciso fazer o mesmo processo para
    //fazer o A ser vizinho de B
    if(b->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        b->vizinhos = temp;
    }else{
        aux = b->vizinhos;
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        Vizinho *temp = new Vizinho;
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }
}

void gerarArquivoDOT(int tamanho){
    ofstream arquivo("grafo.dot");
    if (arquivo.is_open())
    {
        arquivo << "graph G {" << endl;
        for (int i = 0; i < tamanho; i++)
        {
            arquivo << "  " << i << ";" << endl;
        }
        for (int i = 0; i < tamanho; i++){
            Vizinho *aux = grafo[i].vizinhos;
            while (aux != NULL && i < aux->vizinho->id){
                arquivo << "  " << i << " -- " << aux->vizinho->id << ";" << endl;
                aux = aux->proximoVizinho;
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
}

void lerArquivoDOT(){
    int vertices = -1;
    ifstream arquivo("grafo.dot");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " <<endl;
        return;
    }
    string linha;
    int x;
    int y;
    while (getline(arquivo, linha)) {
        cout << linha << endl;
        vertices++;
        if(linha.find("-") != string::npos){
            inicializa(vertices);
        }
        if(sscanf(linha.c_str(),"%d--%d;",&x,&x) == 2){
            adicionaVizinho(&grafo[x], &grafo[y]);
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

        inicializa(tamanho);
        int arestaTotal = (tamanho * (tamanho - 1)) / 2;
        int cont = 0;
        while(cont < (arestaTotal*porcentagem)/100){
            int x = rand() % tamanho;
            int y = rand() % tamanho;
            if(x != y){
                adicionaVizinho(&grafo[x], &grafo[y]);
                cont++;
            }
        }
        gerarArquivoDOT(tamanho);
    }
    else if (tipo == 2)
    {
        cout << "Grafo direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;
        cout << "Porcentagem de preenchimento: " << porcentagem << "%" << endl;

        inicializa(tamanho);
    }
    else
    {
        cout << "OpÃƒÂ§ÃƒÂ£o tipo de grafico invÃƒÂ¡lida" << endl;
    }

    lerArquivoDOT();

    return 0;
}
