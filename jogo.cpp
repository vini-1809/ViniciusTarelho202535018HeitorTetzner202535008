#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <chrono>

using namespace std;

#define pathArquivo "dicionario.txt"
#define tamanhoPalavra 6
#define tamanhoPalavraMaxima 46
#define qtdPalavraMaxima 20000

int qtdPalavras = 0;
char dicionario[qtdPalavraMaxima][tamanhoPalavraMaxima];


int criarDicionario()
{
    int quantPalavras = 0;
    ifstream arquivo(pathArquivo);
    char buffer[tamanhoPalavraMaxima];

    if (arquivo.is_open()) 
    {
        while (arquivo.getline(buffer, tamanhoPalavraMaxima)) 
        {
            int tam;
            for(tam = 0; buffer[tam] != '\0'; tam++) 
            {
                if (tam > tamanhoPalavra) 
                {
                    break;
                }
            }
            if (tam == tamanhoPalavra) 
            {
                strcat(dicionario[quantPalavras], buffer);
                quantPalavras++;
            }
        }
        arquivo.close();
    }
    return quantPalavras;
}

void selecionarPalavra(char palavraResposta[])
{
    random_device semente;
    mt19937 gerador(semente());
    uniform_int_distribution distribuicao(1,qtdPalavras);
    int indicePalavra = distribuicao(gerador);
    strcat(palavraResposta,dicionario[indicePalavra]);
    return;
}

bool palavrasIguais(char p1[], char p2[]) {
    for (int i = 0; i < 6; i++) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}

bool validarChute(char chute[]) {
    int tam;
    for (tam = 0; chute[tam] != '\0'; tam++) {
        if (tam >= 6) {
            return false;
        }
    }
    if (tam < 6) {
        return false;
    }

    for (int i = 0; i < qtdPalavras; i ++) {
        if (!palavrasIguais(chute, dicionario[i])) {
            return false;
        }
    }

    return true;
}


void pegaChute()
{
    char chute[8];
    cin >> chute;

    // LIDA COM ERROS

    while (cin.fail() || validarChute(chute) == -1)
    {
        cout<<"ENTRADA INVALIDA, DEVE SER UMA PALAVRA EXISTENTE COM 6 CARACTERES\n";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> chute;
    }

}

int main()
{
    cout << "Teste 1" << endl;
    qtdPalavras = criarDicionario();
    char palavraResposta [tamanhoPalavraMaxima] = "";
    selecionarPalavra(palavraResposta);
    cout<<palavraResposta<<endl;
    return 0;
}