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
    Aluno *prox;
    Aluno *ante;
};

struct Alunos{
    Aluno *inicio;
    Aluno *fim;
    int quantidade;
};


// Alunos a[100];
Alunos a[1000]; //89357 milissegundos // 
// Alunos a[10000]; 
// Alunos a[100000];

void inicializa(){
	for(int i = 0; i < 1000; i++){
 		a[i].inicio = NULL;
    	a[i].fim = NULL;
    	a[i].quantidade = 0;
	}
   
}


void ordernarPorNome(){
	for(int pos = 0; pos < 1000; pos++){
		Aluno *aOrdenado[a[pos].quantidade];
		Aluno *atual = a[pos].inicio;
		int i = 0;
		while(atual != NULL){
			aOrdenado[i] = atual;
			atual = atual->prox;
			i++;
		}
		// Ordenar aOrdenado por nome
		qsort(aOrdenado, a[pos].quantidade, sizeof(Aluno*), [](const void *a, const void *b) {
			Aluno *alunoA = *(Aluno **)a;
			Aluno *alunoB = *(Aluno **)b;
			return strcmp(alunoA->nome, alunoB->nome);
		});
		a[pos].inicio = aOrdenado[0];
		a[pos].fim = aOrdenado[a[pos].quantidade - 1];
		for(int j = 0; j < a[pos].quantidade - 1; j++){
			aOrdenado[j]->prox = aOrdenado[j + 1];
			aOrdenado[j + 1]->ante = aOrdenado[j];
		}
	}
	
}

bool insere(int pos, Aluno *y){
    if(y == NULL) return false;
    if(a[pos].quantidade == 0){
    	// y->prox = NULL;
		// y->ante = a[pos].fim;
        a[pos].inicio = y;
        a[pos].fim = y;
    } else {
    	Aluno *atual = a[pos].inicio;
    	Aluno *anterior = NULL;
    	while(atual != NULL && strcmp(y->cpf, atual->cpf) > 0){
			anterior = atual;
			atual = atual->prox;
		}
    	if(anterior == NULL){
			y->prox = a[pos].inicio;
			y->ante = NULL;
			a[pos].inicio->ante = y;
			a[pos].inicio = y;
			
		}else if(atual == NULL){
			y->prox = NULL;
			y->ante = a[pos].fim;
			a[pos].fim->prox = y;
			a[pos].fim = y;
		}else{
			y->prox = atual->ante->prox;
			y->ante = atual->ante;
			atual->ante->prox = y;
			atual->ante = y;
		}
    	
	}
   	
    a[pos].quantidade++;
    return true;
}

Aluno *lerAluno(){
    Aluno *b = new Aluno;
    return b;
}


int funcaoHash100(const char* cpf){
	char ultimosDoisDigitos[3];
	strncpy(&ultimosDoisDigitos[0], cpf + 12, 1);
	strncpy(&ultimosDoisDigitos[1], cpf + 13, 1);
	ultimosDoisDigitos[2] = '\0';
	int pos = atoi(ultimosDoisDigitos);
	return pos;
}

int funcaoHash1000(const char* cpf){
	char ultimosDoisDigitos[4];
	strncpy(&ultimosDoisDigitos[0], cpf + 10, 1);
	strncpy(&ultimosDoisDigitos[1], cpf + 12, 1);
	strncpy(&ultimosDoisDigitos[2], cpf + 13, 1);
	ultimosDoisDigitos[3] = '\0';
	int pos = atoi(ultimosDoisDigitos);
	return pos;
}

int funcaoHash10000(const char* cpf){
	char ultimosDoisDigitos[5];
	strncpy(&ultimosDoisDigitos[0], cpf + 9, 1);
	strncpy(&ultimosDoisDigitos[1], cpf + 10, 1);
	strncpy(&ultimosDoisDigitos[2], cpf + 12, 1);
	strncpy(&ultimosDoisDigitos[3], cpf + 13, 1);
	ultimosDoisDigitos[4] = '\0';
	int pos = atoi(ultimosDoisDigitos);
	return pos;
}

int funcaoHash100000(const char* cpf){
	char ultimosDoisDigitos[6];
	strncpy(&ultimosDoisDigitos[0], cpf + 8, 1);
	strncpy(&ultimosDoisDigitos[1], cpf + 9, 1);
	strncpy(&ultimosDoisDigitos[2], cpf + 10, 1);
	strncpy(&ultimosDoisDigitos[3], cpf + 12, 1);
	strncpy(&ultimosDoisDigitos[4], cpf + 13, 1);
	ultimosDoisDigitos[5] = '\0';
	int pos = atoi(ultimosDoisDigitos);
	return pos;
}



Aluno *buscarMatricula(int pos,const char* matricula){
	Aluno *atual = a[pos].inicio;
	while(atual != NULL){
		if(strcmp(atual->matricula, matricula) == 0){			

			return atual;
		}
		atual = atual->prox;
	}
	
	return NULL;
}

Aluno *buscarCpf(int pos, const char* cpf){
	Aluno *atual = a[pos].inicio;

	while(atual != NULL){
		if(strcmp(atual->cpf, cpf) == 0){
				
			return atual;
		}
		atual = atual->prox;
	}

	return NULL;
}

Aluno *buscarNome(const char* nome){
	int pos;
	for(pos = 0; pos < 1000; pos++){
		Aluno *atual = a[pos].inicio;
		while(atual != NULL){
			if(strcmp(atual->nome, nome) == 0){
				
				return atual;
			}
			atual = atual->prox;
		}
	}
	
	return NULL;
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
            novo->prox = NULL;
            novo->ante = NULL;
			int pos = funcaoHash1000(novo->cpf);

			if (buscarCpf(pos, novo->cpf) == NULL) {
				// cout << count << endl;
				count ++;
				insere(pos,novo);
			}else{
				delete novo;
				continue;
			}
            
        } else {
            delete novo;
            break;
        }
	}			
	fclose(arquivo);
	cout << "Leitura concluida. Total de alunos: " << count << "\n" << endl;
}



void excluirAluno(int pos, Aluno *y){
	if(y->ante == NULL){
			a[pos].inicio = y->prox;
		}else{
			y->ante->prox = y->prox;
		}
		if(y->prox == NULL){
			a[pos].fim = y->ante;
		}else{
			y->prox->ante = y->ante;
		}
		delete y;
		a[pos].quantidade --;
		cout << "Aluno excluido com sucesso " << endl;
	return;
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
	
	// int excluir;
	// cout << "Se deseja excluir aluno digite 0 / Se deseja sair digite 1: ";
	// cin >>  excluir;
	// if(excluir == 0) {
	// 	int pos = funcaoHash1000(p->cpf);
	// 	excluirAluno(pos, p);
		
	// }
	
	return ;
}

void exibirAlunos(int pos) {
    cout << "\n=== LISTA DE ALUNOS ===\n" << endl;
    Aluno* atual = a[pos].inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->matricula);
        printf("  CPF: %s\n", atual->cpf);
        printf("  Nome: %s\n", atual->nome);
        printf("  Nota: %.2f\n", atual->nota);
        printf("  Idade: %d\n", atual->idade);
        printf("  Curso: %s\n", atual->curso);
        printf("  Cidade: %s\n", atual->cidade);
        printf("  ---\n");
        
        atual = atual->prox;
        contador++;
    }
    printf("Lista: %d Total: %d alunos\n\n", pos, a[pos].quantidade);
}

int main(){
	inicializa();
	cout << "=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n" << endl;
    
    time_t inicio, fim;
    inicio = clock();
	lerDados("alunos_completos.csv");
	

	fim = clock();
	cout << "Tempo de leitura: " << (int)fim - inicio << " milissegundos\n" << endl;
	
	
	inicio = clock();
	cout << "------ Os 10 alunos buscados ------\n" << endl;
	Aluno *procurado;
	procurado = buscarNome("Iolanda Prado Palmer");
	printAluno(procurado);
	procurado = buscarNome("Carmelo Amazonas Ross");
	printAluno(procurado);
	procurado = buscarNome("Fausto Rocha Canhoto");
	printAluno(procurado);
	procurado = buscarNome("Gema Saraiva Crawford");
	printAluno(procurado);
	procurado = buscarNome("Ruth Ascanio Copeland");
	printAluno(procurado);
	procurado = buscarNome("Alejandro Hanson Adauto");
	printAluno(procurado);
	procurado = buscarNome("Richard Camacho Martin");
	printAluno(procurado);
	procurado = buscarNome("Ignacio Neal Margot");
	printAluno(procurado);
	procurado = buscarNome("Matthew Liu Kaufman");
	printAluno(procurado);
	procurado = buscarNome("Alfeu Mitchell Knox");
	printAluno(procurado);
	
	fim = clock();
	cout << "Tempo de leitura: " << (int)fim - inicio << " milissegundos\n" << endl;

	ordernarPorNome();
	procurado = buscarNome("Iolanda Prado Palmer");
	printAluno(procurado);
	
	// char matricula[9];
	// Aluno *procurado;
	// cout << "Digite a matricula que deseja buscar: ";
    // cin >> matricula;
	// for(int pos = 0; pos < 1000; pos++) {
	// 	procurado = buscarMatricula(pos, matricula);
	// }
	// if(procurado != NULL){
	// 	printAluno(procurado);

	// }else{
	// 	cerr << "Matricula n�o encontrada" << endl;
	// } 
	
	// char cpf[15];
	// cout << "Digite o CPF que deseja buscar: ";
    // cin >> cpf;
	// procurado = buscarCpf(funcaoHash1000(cpf), cpf);
	// if(procurado != NULL){
	// 	printAluno(procurado);

	// 	int excluir;
	// 	cout << "Se deseja excluir aluno digite 0: ";
	// 	cin >>  excluir;
	// 	int pos = funcaoHash100(p->cpf);
	// 	if(excluir == 0) excluirAluno(pos, p);

	// } else{
	// 	cerr << "CPF n�o encontrado" << endl;
	// }

    system("pause");
}