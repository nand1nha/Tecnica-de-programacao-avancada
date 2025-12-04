#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
#include <utility>
#include <algorithm>
#include <random>
#include <iterator>
#include <vector> 
using namespace std;

struct Vertice;

struct Vizinho {
    Vertice *vizinho;
    Vizinho *proximoVizinho;
    int peso;
    int ligacao;
};

struct Vertice {
    int id;
    Vizinho *vizinhos;
    int pintar;
    int qntVizinhos;
};

Vertice *grafo;
void inicializa(int tamanho){
    grafo = new Vertice[tamanho];
    for(int i = 0; i < tamanho; i++){
        grafo[i].id=i;
        grafo[i].vizinhos = NULL;
        grafo[i].pintar = false;
    }
}

void adicionaVizinhoNaoDirecionado(Vertice *a, Vertice *b, int ligacao, int peso){
    if (a == NULL || b == NULL)
        return;
    Vizinho *aux;
    if(a->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
        temp->peso = peso;
        temp->ligacao = ligacao;
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        a->vizinhos = temp;
    }else{
        aux = a->vizinhos;
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        Vizinho *temp = new Vizinho;
        temp->peso = peso;
        temp->ligacao = ligacao;
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }
    if(b->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
        temp->peso = peso;
        temp->ligacao = ligacao;
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        b->vizinhos = temp;
    }else{
        aux = b->vizinhos;
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        Vizinho *temp = new Vizinho;
        temp->peso = peso;
        temp->ligacao = ligacao;
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }
    a->qntVizinhos++;
    b->qntVizinhos++;
}

void adicionaVizinhoDirecionado(Vertice *a, Vertice *b, int ligacao, int peso){
    if (a == NULL || b == NULL)
        return;
    Vizinho *aux;
    if(a->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
        temp->peso = peso;
        temp->ligacao = ligacao;
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
        temp->peso = peso;
        temp->ligacao = ligacao;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }
    a->qntVizinhos++;
}

void gerarArquivoDOTNaoDirecionado(int tamanho){
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
            while (aux != NULL){
                if(i < aux->vizinho->id){
                    arquivo << "  " << i << " -- " << aux->vizinho->id << " [label=" << aux->ligacao << ",weight=" << aux->peso << "]" << ";" << endl;
                }
                aux = aux->proximoVizinho;
            }
        }
        arquivo << "}" << endl;
        arquivo.close();
        cout << "Arquivo 'grafo.dot' criado com sucesso!" << endl;
        system("dot -Tpng grafo.dot -o grafo.png");
    }
    else
    {
        cout << "Erro ao criar o arquivo" << endl;
    }
}

void gerarArquivoDOTDirecionado(int tamanho){
    ofstream arquivo("grafo.dot");
    if (arquivo.is_open())
    {
        arquivo << "digraph G {" << endl;
        for (int i = 0; i < tamanho; i++)
        {
            arquivo << "  " << i << ";" << endl;
        }
        for (int i = 0; i < tamanho; i++){
            Vizinho *aux = grafo[i].vizinhos;
            while (aux != NULL){
                arquivo << "  " << i << " -> " << aux->vizinho->id << " [label=" << aux->ligacao << ",weight=" << aux->peso << "]" << ";" << endl;
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
    string tipo;
    getline(arquivo,tipo, ' ');
    cout << tipo << endl;
    int x;
    int y;
    int ligacao;
    int peso;
    while (getline(arquivo, linha)) {
        cout << linha << endl;
        vertices++;
        if(linha.find("-") != string::npos){
            inicializa(vertices);
        }
        if(strcmp(tipo.c_str(),"graph") == 0){
                if(sscanf(linha.c_str(),"%d--%d [label=%d,weight=%d];",&x,&y,&ligacao,&peso) == 4){
                    adicionaVizinhoNaoDirecionado(&grafo[x], &grafo[y], ligacao, peso);
                }
        }else{
             if(sscanf(linha.c_str(),"%d->%d [label=%d,weight=%d];",&x,&y,&ligacao,&peso) == 4){
                    adicionaVizinhoDirecionado(&grafo[x], &grafo[y], ligacao, peso);
                }
        }
    }
    
    arquivo.close();
}

void valorAleatorioNaoDirecionado(int tamanho, int ligacoes, int totalArestas){
    vector<pair<int,int> > arestas(totalArestas);
    int cont = 0;
    for(int i = 0; i < tamanho; i++){
        for(int j = i+1; j < tamanho; j++){
            arestas[cont] = make_pair(i,j);
            cont++;
        }

    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(arestas.begin(), arestas.end(), g);
    for(int i = 0; i < ligacoes; i++){
        int peso = rand() % 10 + 1;
        adicionaVizinhoNaoDirecionado(&grafo[arestas[i].first], &grafo[arestas[i].second], peso, peso);
    }

}

void valorAleatorioDirecionado(int tamanho, int ligacoes, int totalArestas){
    vector<pair<int,int> > arestas(totalArestas);
    int cont = 0;
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if(i != j){
                arestas[cont] = make_pair(i,j);
                cont++;
            }
        }

    }
    for(int i = 0; i < totalArestas*totalArestas; i++){
        int x = rand() % totalArestas;
        int y = rand() % totalArestas;
        swap(arestas[x], arestas[y]);
    }
    for(int i = 0; i < ligacoes; i++){
        int peso = rand() % 10 + 1;
        adicionaVizinhoDirecionado(&grafo[arestas[i].first], &grafo[arestas[i].second], peso, peso);
    }

}


void grafoConexo(int tamanho){
    int *acesso = new int[tamanho];
    for(int i = 0; i < tamanho; i++){
        acesso[i] = 0;
    }
    acesso[0] = 1;
    for(int k = 0; k < tamanho; k++){
        for(int i = 0; i < tamanho; i++){
            if(acesso[i] == 1){
                Vizinho *aux = grafo[i].vizinhos;
                while(aux != NULL){
                    acesso[aux->vizinho->id] = 1;
                    aux = aux->proximoVizinho;
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

int guloso (Vertice *G, int *color, int tamanho) {
    int k = 0;
    for(int i = 0; i < tamanho; i++){
        color[i] = -1;
    }
    for(int i = 0; i < tamanho; i++){
        bool available[100];
        int c;
        for(c = 0; c < k; c++){
            available[c] = true;
        }
        for(Vizinho *aux = G[i].vizinhos; aux != NULL; aux = aux->proximoVizinho){
            if(color[aux->vizinho->id] != -1){
                available[color[aux->vizinho->id]] = false;
            }
        }
        c = 0;
        while(c < k &&  !available[c]){
            c++;
        }
        if (c < k){
            color[i] = c;
            G[i].pintar = c;
        }else{
            color[i] = k;
            G[i].pintar = k;
            k++;
        }
    }
    return k;
}

void dsatur (Vertice *G, int *color, int tamanho) {
    int maiorValor = -1;
    int pos;
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if(G[j].qntVizinhos > maiorValor){
                maiorValor = G[i].qntVizinhos;
                pos = j;
            }
        }
        color[i] = pos;
    }
    for(int i = 0; i < tamanho; i++){
        cout << color[i] << " ";
    }

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

        valorAleatorioNaoDirecionado(tamanho, (arestaTotal*porcentagem)/100, arestaTotal);
        gerarArquivoDOTNaoDirecionado(tamanho);
        grafoConexo(tamanho);

        cout << "Coloracao gulosa do grafo:" << endl;
        int *color = new int[tamanho];
        int cores = guloso(grafo, color, tamanho);
        cout << "Numero de cores usadas: " << cores << endl;
    }
    else if (tipo == 2)
    {
        cout << "Grafo direcionado" << endl;
        cout << "Tamanho do grafo: " << tamanho << endl;
        cout << "Porcentagem de preenchimento: " << porcentagem << "%" << endl;

        inicializa(tamanho);
        int arestaTotal = (tamanho * (tamanho - 1));
        
        valorAleatorioDirecionado(tamanho, (arestaTotal*porcentagem)/100, arestaTotal);
        gerarArquivoDOTDirecionado(tamanho);
        grafoConexo(tamanho);
    }
    else
    {
        cout << "OpÃƒÂ§ÃƒÂ£o tipo de grafico invÃƒÂ¡lida" << endl;
    }

    return 0;
}
