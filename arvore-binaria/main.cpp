#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

struct Aluno
{
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

struct Alunos
{
    Aluno *raiz;
    int nivelMaximo;
    int quantidade;
};

Alunos a;
int cont = 0;

void inicializa()
{
    a.raiz = NULL;
    a.nivelMaximo = 0;
    a.quantidade = 0;
}

void atualizaAltura(Aluno *no)
{
    int alturaEsquerda = 0;
    int alturaDireita = 0;
    if (no->esquerda == NULL)
    {
        alturaEsquerda = 0;
    }
    else
    {
        alturaEsquerda = 1 + no->esquerda->altura;
    }
    if (no->direita == NULL)
    {
        alturaDireita = 0;
    }
    else
    {
        alturaDireita = 1 + no->direita->altura;
    }
    no->altura = max(alturaEsquerda, alturaDireita);
}

Aluno *rotacaoSimplesDireita(Aluno *y)
{
    Aluno *x = y->esquerda;
    Aluno *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizaAltura(y);
    atualizaAltura(x);

    return x;
}

Aluno *rotacaoSimplesEsquerda(Aluno *y)
{
    Aluno *x = y->direita;
    Aluno *T2 = x->esquerda;

    // Executa a rotação
    x->esquerda = y;
    y->direita = T2;

    // Atualiza alturas
    atualizaAltura(y);
    atualizaAltura(x);

    // Novo nó raiz
    return x;
}

Aluno *rotacaoDuplaEsquerda(Aluno *y)
{
    // Primeiro uma rotação simples à direita em y->dir
    y->direita = rotacaoSimplesDireita(y->direita);
    // Depois rotação simples à esquerda em y
    return rotacaoSimplesEsquerda(y);
}

Aluno *rotacaoDuplaDireita(Aluno *y)
{
    y->esquerda = rotacaoSimplesEsquerda(y->esquerda);
    return rotacaoSimplesDireita(y);
}

Aluno *insere(Aluno *y, Aluno *raizAtual)
{
    if (raizAtual == NULL)
    {
        a.quantidade++;
        return y;
    }
    if (strcmp(y->nome, raizAtual->nome) >= 0)
    {
        raizAtual->direita = insere(y, raizAtual->direita);
    }
    else
    {
        raizAtual->esquerda = insere(y, raizAtual->esquerda);
    }
    atualizaAltura(raizAtual);

    int alturaEsq;
    int alturaDir;
    int alturaEsqFilhoEsq;
    int alturaEsqFilhoDir;
    int alturaDirFilhoEsq;
    int alturaDirFilhoDir;

    if (raizAtual->esquerda == NULL)
    {
        alturaEsq = 0;
        alturaEsqFilhoEsq = 0;
        alturaEsqFilhoDir = 0;
    }
    else
    {
        alturaEsq = 1 + raizAtual->esquerda->altura;
        if (raizAtual->esquerda->esquerda != NULL)
        {
            alturaEsqFilhoEsq = 1 + raizAtual->esquerda->esquerda->altura;
        }
        if (raizAtual->esquerda->direita != NULL)
        {
            alturaEsqFilhoDir = 1 + raizAtual->esquerda->direita->altura;
        }
    }
    if (raizAtual->direita == NULL)
    {
        alturaDir = 0;
        alturaDirFilhoEsq = 0;
        alturaDirFilhoDir = 0;
    }
    else
    {
        alturaDir = 1 + raizAtual->direita->altura;
        if (raizAtual->direita->direita != NULL)
        {
            alturaDirFilhoDir = 1 + raizAtual->direita->direita->altura;
        }
        if (raizAtual->direita->esquerda != NULL)
        {
            alturaDirFilhoEsq = 1 + raizAtual->direita->esquerda->altura;
        }
    }

    int balanceamento = (alturaEsq - alturaDir);

    if (balanceamento > 1 && (alturaEsqFilhoEsq - alturaEsqFilhoDir) >= 0)
    {
        return rotacaoSimplesDireita(raizAtual);
    }
    if (balanceamento < -1 && (alturaDirFilhoEsq - alturaDirFilhoDir) <= 0)
    {
        return rotacaoSimplesEsquerda(raizAtual);
    }
    if (balanceamento > 1 && (alturaEsqFilhoEsq - alturaEsqFilhoDir) < 0)
    {
        return rotacaoDuplaDireita(raizAtual);
    }
    if (balanceamento < -1 && (alturaDirFilhoEsq - alturaDirFilhoDir) > 0)
    {
        return rotacaoDuplaEsquerda(raizAtual);
    }

    return raizAtual;
}

Aluno *excluir(Aluno *y, Aluno *raizAtual)
{
    if (raizAtual == NULL)
    {
        return raizAtual;
    }
    if (strcmp(y->nome, raizAtual->nome) > 0)
    {
        raizAtual->direita = excluir(y, raizAtual->direita);
    }
    else if (strcmp(y->nome, raizAtual->nome) < 0)
    {
        raizAtual->esquerda = excluir(y, raizAtual->esquerda);
    }
    else if (strcmp(y->nome, raizAtual->nome) == 0)
    {
        if ((raizAtual->esquerda == NULL) && (raizAtual->direita == NULL))
        {
            delete raizAtual;
            a.quantidade--;
            return NULL;
        }
        if (raizAtual->esquerda == NULL && raizAtual->direita != NULL)
        {
            Aluno *temp = raizAtual->direita;
            delete raizAtual;
            a.quantidade--;
            return temp;
        }
        if (raizAtual->esquerda != NULL && raizAtual->direita == NULL)
        {
            Aluno *temp = raizAtual->esquerda;
            delete raizAtual;
            a.quantidade--;
            return temp;
        }
        if (raizAtual->esquerda != NULL && raizAtual->direita != NULL)
        {
            Aluno *temp = raizAtual->direita;
            while (temp->esquerda != NULL)
            {
                temp = temp->esquerda;
            }
            strcpy(raizAtual->nome, temp->nome);
            strcpy(raizAtual->matricula, temp->matricula);
            strcpy(raizAtual->cpf, temp->cpf);
            raizAtual->nota = temp->nota;
            raizAtual->idade = temp->idade;
            strcpy(raizAtual->curso, temp->curso);
            strcpy(raizAtual->cidade, temp->cidade);
            raizAtual->direita = excluir(temp, raizAtual->direita);
        }
    }

    atualizaAltura(raizAtual);

    int alturaEsq;
    int alturaDir;
    int alturaEsqFilhoEsq;
    int alturaEsqFilhoDir;
    int alturaDirFilhoEsq;
    int alturaDirFilhoDir;

    if (raizAtual->esquerda == NULL)
    {
        alturaEsq = 0;
        alturaEsqFilhoEsq = 0;
        alturaEsqFilhoDir = 0;
    }
    else
    {
        alturaEsq = 1 + raizAtual->esquerda->altura;
        if (raizAtual->esquerda->esquerda != NULL)
        {
            alturaEsqFilhoEsq = 1 + raizAtual->esquerda->esquerda->altura;
        }
        if (raizAtual->esquerda->direita != NULL)
        {
            alturaEsqFilhoDir = 1 + raizAtual->esquerda->direita->altura;
        }
    }
    if (raizAtual->direita == NULL)
    {
        alturaDir = 0;
        alturaDirFilhoEsq = 0;
        alturaDirFilhoDir = 0;
    }
    else
    {
        alturaDir = 1 + raizAtual->direita->altura;
        if (raizAtual->direita->direita != NULL)
        {
            alturaDirFilhoDir = 1 + raizAtual->direita->direita->altura;
        }
        if (raizAtual->direita->esquerda != NULL)
        {
            alturaDirFilhoEsq = 1 + raizAtual->direita->esquerda->altura;
        }
    }

    int balanceamento = (alturaEsq - alturaDir);

    if (balanceamento > 1 && (alturaEsqFilhoEsq - alturaEsqFilhoDir) >= 0)
    {
        return rotacaoSimplesDireita(raizAtual);
    }
    if (balanceamento < -1 && (alturaDirFilhoEsq - alturaDirFilhoDir) <= 0)
    {
        return rotacaoSimplesEsquerda(raizAtual);
    }
    if (balanceamento > 1 && (alturaEsqFilhoEsq - alturaEsqFilhoDir) < 0)
    {
        return rotacaoDuplaDireita(raizAtual);
    }
    if (balanceamento < -1 && (alturaDirFilhoEsq - alturaDirFilhoDir) > 0)
    {
        return rotacaoDuplaEsquerda(raizAtual);
    }

    return raizAtual;
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
            novo->direita = NULL;
            novo->esquerda = NULL;
            novo->altura = 0;
            count++;
            a.raiz = insere(novo, a.raiz);
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
    cout << "Adicionados: " << a.quantidade << "\n"
         << endl;

    system("pause");
}
