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


int criarDicionario(char dicionario[][tamanhoPalavraMaxima], int tamPalavra)
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
                if (tam > tamPalavra) 
                {
                    break;
                }
            }
            if (tam == tamPalavra) 
            {
                strcat(dicionario[quantPalavras], buffer);
                quantPalavras++;
            }
        }
        arquivo.close();
    }
    return quantPalavras;
}

void selecionarPalavra(char palavraResposta[], int qtdPalavras, char dicionario [][tamanhoPalavraMaxima])
{
    random_device semente;
    mt19937 gerador(semente());
    uniform_int_distribution distribuicao(1,qtdPalavras);
    int indicePalavra = distribuicao(gerador);
    strcat(palavraResposta,dicionario[indicePalavra]);
    return;
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

    return true;
}

void obterChute() {
    char chute[8];
    cin.getline(chute, 8);
    validarChute(chute);
}

int main()
{
    cout << "Teste 1" << endl;
    char dicionario[qtdPalavraMaxima][tamanhoPalavraMaxima];
    int qtdPalavras = criarDicionario(dicionario, tamanhoPalavra);
    char palavraResposta [tamanhoPalavraMaxima];
    selecionarPalavra(palavraResposta, qtdPalavras, dicionario);
    cout<<palavraResposta<<endl;

    return 0;
}