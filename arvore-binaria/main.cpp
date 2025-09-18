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
    int altura;
};

struct Alunos{
    Aluno *raiz;
    int nivelMaximo;
    int quantidade;
};

Alunos a;
int cont = 0;

void inicializa(){
	a.raiz = NULL;
    a.nivelMaximo = 0;
    a.quantidade = 0;
}

void atualizaAltura(Aluno *no){
    int alturaEsquerda = 0;
    int alturaDireita = 0;
    if(no->esquerda == NULL){
        alturaEsquerda = 0;
    }else{
        alturaEsquerda = 1 + no->esquerda->altura;
    }
    if(no->direita == NULL){
        alturaDireita = 0;
    }else{
        alturaDireita = 1 + no->direita->altura;
    }
    no->altura = 1 + max(alturaEsquerda, alturaDireita);
}

Aluno* rotacaoSimplesDireita(Aluno* y){
    Aluno *x = y->esq;
    Aluno *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    atualizaAltura(y);
    atualizaAltura(x);

    return x;
}

Aluno* rotacaoSimplesEsquerda(Aluno* y){
    Aluno *x = y->dir;
    Aluno *T2 = x->esq;

    // Executa a rotação
    x->esq  = y;
    y->dir = T2;

    // Atualiza alturas
    atualizaAltura(y);
    atualizaAltura(x);

    // Novo nó raiz
    return x;
}

Aluno* rotacaoDuplaEsquerda(Aluno* y){
    // Primeiro uma rotação simples à direita em y->dir
    y->dir = rotacaoSimplesDireita(y->dir);
    // Depois rotação simples à esquerda em y
    return rotacaoSimplesEsquerda(y);

}

Aluno* rotacaoDuplaDireita(Aluno* y){
    y->esq = rotacaoSimplesEsquerda(y->esq);
    return rotacaoSimplesDireita(y);
}

Aluno* insere(Aluno *y, Aluno *raizAtual){
    if(raizAtual == NULL){
        a.quantidade++;
        return y;   
    }
    if(strcmp(y->nome, raizAtual->nome) >= 0){
        raizAtual->direita = insere(y, raizAtual->direita); 
    }else{
        raizAtual->esquerda = insere(y, raizAtual->esquerda);
    }
    atualizaAltura(raizAtual);

    int balanceamento = (raizAtual->esquerda - raizAtual->direita);

    if(balanceamento > 1 && (raizAtual->esquerda->altura - raizAtual->direita->altura) >= 0){
        return rotacaoSimplesDireita(raizAtual);
    }
    if(balanceamento < -1 && (raizAtual->esquerda->altura - raizAtual->direita->altura) <= 0){
        return rotacaoSimplesEsquerda(raizAtual);
    }
    if(balanceamento > 1 && (raizAtual->esquerda->altura - raizAtual->direita->altura) < 0){
        return rotacaoDuplaDireita(raizAtual);
    }
    if(balanceamento < -1 && (raizAtual->esquerda->altura - raizAtual->direita->altura) > 0){
        return rotacaoDuplaEsquerda(raizAtual);
    }





    return raizAtual;
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
            novo->altura = 0;
            count++;
            a.raiz = insere(novo, a.raiz);
            
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
    cout << "Adicionados: " << a.quantidade << "\n" << endl;
    cout << "Nivel maximo da arvore: " << a.nivelMaximo << "\n" << endl;

	

	

    system("pause");
}
