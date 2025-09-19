#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;
#define TAMANHO (1 << 20)

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *direita;
    Aluno *esquerda;
};

struct Alunos{
    Aluno** aluno;
    int tamanho;
    int quantidade;
};

Alunos listaSequencial;
//Aluno *listaSequencial = new Aluno[TAMANHO];

void inicializa(){
	listaSequencial.aluno = new Aluno*[TAMANHO];
    listaSequencial.tamanho = TAMANHO;
    listaSequencial.quantidade = 0;
    for(int i = 0; i < TAMANHO; i++) listaSequencial.aluno[i] = NULL;
}

void atualizaAltura(int pos){
	int alturaEsquerda = 0;
	int alturaDireita = 0;
	int posFilhoDireita = (2*pos)+2;
	int posFilhoEsquerda = (2*pos)+1;
	if(listaSequencial.aluno[posFilhoDireita] != NULL){
		alturaDireita = 1 + lisSequencial.aluno[posFilhoDireita]->altura;
	}
	if(listaSequencial.aluno[posFilhoEsquerda] != NULL){
		alturaEsquerda = 1 + listaSequencial.aluno[posFilhoEsquerda]->altura;
	}
	
	listaSequencial.aluno[pos]->altura = max(alturaEsquerda,alturaDireita);
}

int insere(Aluno *y, int pos){
    if(listaSequencial.quantidade >= listaSequencial.tamanho){
        cout << "Lista cheia, nao e possivel inserir mais alunos." << endl;
        return 1;
    }
    if(pos >= listaSequencial.tamanho){
        return 0;
    }
    if(listaSequencial.aluno[pos] == NULL){
        listaSequencial.aluno[pos] = y;
        listaSequencial.quantidade++;
		atualizaAltura(pos);
        return 0;
    }else{
        if(strcmp(y->nome, listaSequencial.aluno[pos]->nome) >= 0){
            int direita = (2*pos) + 2;
            return insere(y, direita);
        }else{
            int esquerda = (2*pos) + 1;
            return insere(y, esquerda);
        }
    }
}

Aluno *lerAluno(){
    Aluno *b = new Aluno;
    return b;
}

void lerDados( const char *nomeArquivo){
	FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << "\n" << endl;
        return;
    }
    char linha[300];

	if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        cout << "Arquivo vazio ou erro na leitura\n" << endl;
        fclose(arquivo);
        return;
    }

	Aluno* novo;
	int count = 1;
    while ((novo = new Aluno) != NULL) {

		//if(count == 1000) break;
		

		if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            novo->direita = NULL;
            novo->esquerda = NULL;
            count++;
            if(insere(novo,0) != 0){
                delete novo;
                break;
            }
            
        } else {
            delete novo;
            break;
        }
	}			
	fclose(arquivo);
	cout << "Leitura concluida. Total de alunos: " << count << "\n" << endl;
}


void printAluno(Aluno *p){
	cout << "---Aluno encontrado---" << endl;
	cout<< "Matricula: " << p->matricula << endl;
	cout<< "CPF: " << p->cpf << endl;
	cout<< "Nome: " << p->nome << endl;
	cout<< "Nota: " << p->nota << endl;
	cout<< "Idade: " << p->idade << endl;
	cout<< "Curso: " << p->curso << endl;
	cout<< "Cidade: " << p->cidade << endl;
	cout << "----------------------" << endl;
	
	return ;
}

int main(){
	inicializa();
	cout << "=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n" << endl;
    
    time_t inicio, fim;
    inicio = clock();
	lerDados("alunos_completos.csv");
	
	fim = clock();
	cout << "Tempo de leitura: " << (int)fim - inicio << " milissegundos\n" << endl;
    cout << "Quantidade maxima: " << listaSequencial.quantidade << "\n" << endl;

	

	

    system("pause");
}
