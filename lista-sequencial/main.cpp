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

struct Aluno
{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    int altura;
};

struct Alunos
{
    Aluno **aluno;
    int tamanho;
    int quantidade;
};

Alunos listaSequencial;
// Aluno *listaSequencial = new Aluno[TAMANHO];

void inicializa()
{
    listaSequencial.aluno = new Aluno *[TAMANHO];
    listaSequencial.tamanho = TAMANHO;
    listaSequencial.quantidade = 0;
    for (int i = 0; i < TAMANHO; i++)
        listaSequencial.aluno[i] = NULL;
}

void atualizaAltura(int pos)
{
    int alturaEsquerda = 0;
    int alturaDireita = 0;
    int posFilhoDireita = (2 * pos) + 2;
    int posFilhoEsquerda = (2 * pos) + 1;
    if (listaSequencial.aluno[posFilhoDireita] != NULL && posFilhoDireita <= listaSequencial.tamanho)
    {
        alturaDireita = 1 + listaSequencial.aluno[posFilhoDireita]->altura;
    }
    if (listaSequencial.aluno[posFilhoEsquerda] != NULL && posFilhoEsquerda <= listaSequencial.tamanho)
    {
        alturaEsquerda = 1 + listaSequencial.aluno[posFilhoEsquerda]->altura;
    }

    listaSequencial.aluno[pos]->altura = max(alturaEsquerda, alturaDireita);
}

void rotacaoSimplesDireita(int pos)
{
    Aluno *x = listaSequencial.aluno[(2 * pos) + 1];
    Aluno *T2 = listaSequencial.aluno[(2 * ((2 * pos) + 1)) + 2];

    listaSequencial.aluno[(2 * ((2 * pos) + 1)) + 2] = listaSequencial.aluno[pos];
    listaSequencial.aluno[(2 * pos) + 1] = T2;
    listaSequencial.aluno[pos] = x;

    atualizaAltura((2 * pos) + 1);
    atualizaAltura(pos);
}

void rotacaoSimplesEsquerda(int pos)
{
    Aluno *x = listaSequencial.aluno[(2 * pos) + 2];
    Aluno *T2 = listaSequencial.aluno[(2 * ((2 * pos) + 2)) + 1];

    // Executa a rotação
    listaSequencial.aluno[(2 * ((2 * pos) + 2)) + 1] = listaSequencial.aluno[pos];
    listaSequencial.aluno[(2 * pos) + 2] = T2;
    listaSequencial.aluno[pos] = x;

    // Atualiza alturas
    atualizaAltura((2 * pos) + 2);
    atualizaAltura(pos);
}

void rotacaoDuplaEsquerda(int pos)
{
    // Primeiro uma rotação simples à direita em y->dir
    rotacaoSimplesDireita((2 * pos) + 2);
    // Depois rotação simples à esquerda em y
    rotacaoSimplesEsquerda(pos);
}

void rotacaoDuplaDireita(int pos)
{
    rotacaoSimplesEsquerda((2 * pos) + 1);
    rotacaoSimplesDireita(pos);
}

int insere(Aluno *y, int pos)
{
    if (pos >= listaSequencial.tamanho)
    {
        return 1;
    }
    if (listaSequencial.aluno[pos] == NULL)
    {
        listaSequencial.aluno[pos] = y;
        listaSequencial.quantidade++;

        atualizaAltura(pos);

        int alturaEsq;
        int alturaDir;
        int alturaEsqFilhoEsq;
        int alturaEsqFilhoDir;
        int alturaDirFilhoEsq;
        int alturaDirFilhoDir;
        int posFilhoEsquerda = (2 * pos) + 1;
        int posFilhoDireita = (2 * pos) + 2;

        if (listaSequencial.aluno[(2 * pos) + 1] == NULL || (2 * pos) + 1 > listaSequencial.tamanho)
        {
            alturaEsq = 0;
            alturaEsqFilhoEsq = 0;
            alturaEsqFilhoDir = 0;
        }
        else
        {
            alturaEsq = 1 + listaSequencial.aluno[(2 * pos) + 1]->altura;
            if ((2 * posFilhoEsquerda) + 1 <= listaSequencial.tamanho && listaSequencial.aluno[(2 * posFilhoEsquerda) + 1] != NULL)
            {
                alturaEsqFilhoEsq = 1 + listaSequencial.aluno[(2 * posFilhoEsquerda) + 1]->altura;
            }
            if ((2 * posFilhoEsquerda) + 2 <= listaSequencial.tamanho && listaSequencial.aluno[(2 * posFilhoEsquerda) + 2] != NULL )
            {
                alturaEsqFilhoDir = 1 + listaSequencial.aluno[(2 * posFilhoEsquerda) + 2]->altura;
            }
        }
        if (listaSequencial.aluno[(2 * pos) + 2] == NULL || (2 * pos) + 2 > listaSequencial.tamanho)
        {
            alturaDir = 0;
            alturaDirFilhoEsq = 0;
            alturaDirFilhoDir = 0;
        }
        else
        {
            alturaDir = 1 + listaSequencial.aluno[(2 * pos) + 2]->altura;
            if ((2 * posFilhoDireita) + 2 > listaSequencial.tamanho && listaSequencial.aluno[(2 * posFilhoDireita) + 2] != NULL)
            {
                alturaDirFilhoDir = 1 + listaSequencial.aluno[(2 * posFilhoDireita) + 2]->altura;
            }
            if ((2 * posFilhoDireita) + 2 > listaSequencial.tamanho && listaSequencial.aluno[(2 * posFilhoDireita) + 1] != NULL)
            {
                alturaDirFilhoEsq = 1 + listaSequencial.aluno[(2 * posFilhoDireita) + 1]->altura;
            }
        }

        int balanceamento = (alturaEsq - alturaDir);

        if (balanceamento > 1 && (alturaEsqFilhoEsq - alturaEsqFilhoDir) >= 0)
        {
            rotacaoSimplesDireita(pos);
        }
        if (balanceamento < 1 && (alturaDirFilhoEsq - alturaDirFilhoDir) <= 0)
        {
            rotacaoSimplesEsquerda(pos);
        }
        if (balanceamento > 1 && (alturaEsqFilhoEsq - alturaEsqFilhoDir) < 0)
        {
            rotacaoDuplaDireita(pos);
        }
        if (balanceamento < 1 && (alturaDirFilhoEsq - alturaDirFilhoDir) > 0)
        {
            rotacaoDuplaEsquerda(pos);
        }
        return 0;
    }
    else
    {
        if (strcmp(y->nome, listaSequencial.aluno[pos]->nome) >= 0)
        {
            int direita = (2 * pos) + 2;
            return insere(y, direita);
        }
        else
        {
            int esquerda = (2 * pos) + 1;
            return insere(y, esquerda);
        }
    }
}

Aluno *lerAluno()
{
    Aluno *b = new Aluno;
    return b;
}

void lerDados(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        cout << "Erro ao abrir o arquivo " << nomeArquivo << "\n"
             << endl;
        return;
    }
    char linha[300];

    if (fgets(linha, sizeof(linha), arquivo) == NULL)
    {
        cout << "Arquivo vazio ou erro na leitura\n"
             << endl;
        fclose(arquivo);
        return;
    }

    Aluno *novo;
    int count = 1;
    while ((novo = new Aluno) != NULL)
    {

        // if(count == 1000) break;

        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n",
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7)
        {
            novo->altura = 0;
            count++;
            insere(novo, 0);
        }
        else
        {
            delete novo;
            break;
        }
    }
    fclose(arquivo);
    cout << "Leitura concluida. Total de alunos: " << count << "\n"
         << endl;
}

void printAluno(Aluno *p)
{
    cout << "---Aluno encontrado---" << endl;
    cout << "Matricula: " << p->matricula << endl;
    cout << "CPF: " << p->cpf << endl;
    cout << "Nome: " << p->nome << endl;
    cout << "Nota: " << p->nota << endl;
    cout << "Idade: " << p->idade << endl;
    cout << "Curso: " << p->curso << endl;
    cout << "Cidade: " << p->cidade << endl;
    cout << "----------------------" << endl;

    return;
}

int main()
{
    inicializa();
    cout << "=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n"
         << endl;

    time_t inicio, fim;
    inicio = clock();
    lerDados("alunos_completos.csv");

    fim = clock();
    cout << "Tempo de leitura: " << (int)fim - inicio << " milissegundos\n"
         << endl;
    cout << "Quantidade maxima: " << listaSequencial.quantidade << "\n"
         << endl;

    system("pause");
}
