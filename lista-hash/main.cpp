#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
#define TAMANHO_INICIAL 1021
#define FATOR_CARGA 0.7
using namespace std;

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
};

struct Alunos{ 
    Aluno** tabelahash;
    bool* ocupado;
    int tamanhoAtual;
    int quantidade;
};

Alunos a;

void inicializa(){
    a.tamanhoAtual = TAMANHO_INICIAL;
    a.quantidade = 0;
    a.tabelahash = new Aluno*[a.tamanhoAtual];
    a.ocupado = new bool[a.tamanhoAtual];
    

    for(int i = 0; i < TAMANHO_INICIAL; i++){
        a.tabelahash[i] = NULL;
        a.ocupado[i] = false;
    }
   
}

int numeroPrimo(int n) {
    int primo = n;
    while (true) {
        int divisores = 2; // 1 e a ele mesmo
        for(int j = 2; j < primo; j++) {
            if (primo % j == 0) divisores++; // Encontrou um divisor, não é primo

        }
        if (divisores == 2) { // É primo
            return primo;
        }
        primo++;
    }
}

Aluno *lerAluno(){
    Aluno *b = new Aluno;
    return b;
}

int funcaoHash(const char* nome){
    int soma = 0;
    int i = 0;
    while (nome[i]!= '\0')
    {
        soma += (int)nome[i];
        i++;
    }
    int pos = soma % a.tamanhoAtual;
    if(a.tabelahash[pos] == NULL) {
        return pos;
    } else {
        int novaPos = 1 + (soma % (a.tamanhoAtual - 1));
        int re_hash = 0;
        while (a.tabelahash[novaPos] != NULL){
            re_hash = (pos + novaPos) % a.tamanhoAtual;
            pos = novaPos;
            novaPos = re_hash;
        }
        return novaPos;
    }
}

void expandirHash(){
    int tamanhoAntigo = a.tamanhoAtual;
    a.tamanhoAtual = numeroPrimo(tamanhoAntigo * 2);
    Aluno** tabelaHashAntiga = a.tabelahash;
    bool* ocupadoAntigo = a.ocupado; 

    a.tabelahash = new Aluno*[a.tamanhoAtual];
    a.ocupado = new bool[a.tamanhoAtual];

    for(int i = 0; i < a.tamanhoAtual; i++){
        a.tabelahash[i] = NULL;
        a.ocupado[i] = false;
    }

    for(int i = 0; i < tamanhoAntigo; i++){
        if(tabelaHashAntiga[i] != NULL){
            int pos = funcaoHash(tabelaHashAntiga[i]->nome);
            a.tabelahash[pos] = tabelaHashAntiga[i];
            a.ocupado[pos] = true;
        }
    }
    delete[] tabelaHashAntiga;
    delete[] ocupadoAntigo;
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
			int pos = funcaoHash(novo->nome);

            a.tabelahash[pos] = novo;
            a.ocupado[pos] = true;
            a.quantidade++;
            count++;
            
        } else {
            delete novo;
            break;
        }
        if ((double)a.quantidade / a.tamanhoAtual > FATOR_CARGA) {
            expandirHash();
        }
	}			
	fclose(arquivo);
	cout << "Leitura concluida. Total de alunos: " << count << "\n" << endl;
}


void printAluno(int pos){
    Aluno* atual = a.tabelahash[pos];
    if(atual == NULL) {
        cout << "Aluno n�o encontrado na posi����o " << pos << endl;
        return;
    }else{
        cout << "---Aluno encontrado---" << endl;
        cout<< "Matricula: " << atual->matricula << endl;
        cout<< "CPF: " << atual->cpf << endl;
        cout<< "Nome: " << atual->nome << endl;
        cout<< "Nota: " << atual->nota << endl;
        cout<< "Idade: " << atual->idade << endl;
        cout<< "Curso: " << atual->curso << endl;
        cout<< "Cidade: " << atual->cidade << endl;
        cout << "----------------------" << endl;
    }
	
}

void exibirAlunos() {
    cout << "\n=== LISTA DE ALUNOS ===\n" << endl;
    int pos = 0;
    Aluno* atual = a.tabelahash[pos];
    int contador = 1;
    
    while (contador <= a.quantidade && atual != NULL) {
        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->matricula);
        printf("  CPF: %s\n", atual->cpf);
        printf("  Nome: %s\n", atual->nome);
        printf("  Nota: %.2f\n", atual->nota);
        printf("  Idade: %d\n", atual->idade);
        printf("  Curso: %s\n", atual->curso);
        printf("  Cidade: %s\n", atual->cidade);
        printf("  ---\n");
        
        atual = a.tabelahash[pos++];
        contador++;
    }
    printf("Lista possui: %d alunos\n\n", contador);
}

int main(){
	inicializa();
	cout << "=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n" << endl;
    
    time_t inicio, fim;
    inicio = clock();
	lerDados("alunos_completos.csv");
	
	fim = clock();
	cout << "Tempo de leitura: " << (int)fim - inicio << " milissegundos\n" << endl;

	


    system("pause");
}