#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

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
    Aluno *raiz;
    int nivelMaximo;
};

Alunos a;
int cont = 0;

void inicializa(){
	a.raiz = NULL;
    a.nivelMaximo = 0;
}

void insere(Aluno *y){
    if(a.raiz == NULL){
        a.raiz = y;
    } else {
        Aluno *atual = a.raiz;
        bool inserido = false;
        int nivelAtual = 0;
        while (!inserido) {
            if(strcmp(y->nome, atual->nome) == 0){
                inserido = true; 
            } else{
                if(strcmp(y->nome, atual->nome) < 0 && atual->esquerda == NULL){
                    atual->esquerda = y;
                    cont++;
                    inserido = true;
                } else if(strcmp(y->nome, atual->nome) > 0 && atual->direita == NULL){
                    atual->direita = y;
                    cont++;
                    inserido = true;
                } else{
                    if(strcmp(y->nome, atual->nome) < 0){
                        atual = atual->esquerda;
                    } else {
                        atual = atual->direita;
                    }               
                }
            }
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
            insere(novo);
            
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
    cout << "Adicionados: " << cont << "\n" << endl;
    cout << "Nivel maximo da arvore: " << a.nivelMaximo << "\n" << endl;

	

	

    system("pause");
}