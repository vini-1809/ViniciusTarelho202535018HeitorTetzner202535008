#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <chrono>

using namespace std;

#define pathArquivo "dicionario.txt"
#define tamanhoPalavra 6
#define tamanhoPalavraMaxima 47
#define qtdPalavraMaxima 12000
#define MAXIMO_TENTATIVAS 10

struct dicionario {
    char listaPalavras[qtdPalavraMaxima][tamanhoPalavraMaxima];
    int qtdPalavras;
};

void capitalizaPalavra(char palavra[])
{
    for (int i = 0; palavra[i] != '\0';i++)
        palavra[i]= (char) toupper(palavra[i]);
}


dicionario criarDicionario(dicionario dicionario)
{
    int qtdPalavras = 0;
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
                strcat(dicionario.listaPalavras[qtdPalavras], buffer);
                qtdPalavras++;
            }
        }
        arquivo.close();
        dicionario.qtdPalavras = qtdPalavras;
    }
    return dicionario;
}

void selecionarPalavra(char palavraResposta[],dicionario dicionario)
{
    random_device semente;
    mt19937 gerador(semente());
    uniform_int_distribution distribuicao(1,dicionario.qtdPalavras);
    int indicePalavra = distribuicao(gerador);
    strcat(palavraResposta,dicionario.listaPalavras[indicePalavra]);
    capitalizaPalavra(palavraResposta);
    return;
}

bool palavrasIguais(char p1[], char p2[]) {
    for (int i = 0; i < tamanhoPalavra; i++) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}

bool validarChute(char chute[],dicionario dicionario) {
    int tam;
    for (tam = 1; chute[tam-1] != '\0'; tam++) {
        if (tam > tamanhoPalavra) {
            return false;
        }
    }
    if (tam < tamanhoPalavra) {
        return false;
    }

    for (int i = 0; i < dicionario.qtdPalavras; i ++) {
        if (palavrasIguais(chute, dicionario.listaPalavras[i])) {
            return true;
        }
    }
    return false;
}


void pegaChute(char chute[],dicionario dicionario)
{
    cin >> chute;

    // LIDA COM ERROS

    while (cin.fail() || !(validarChute(chute,dicionario)))
    {
        cout<<"ENTRADA INVALIDA, DEVE SER UMA PALAVRA EXISTENTE COM " << tamanhoPalavra <<  " CARACTERES\n";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> chute;
    }
    capitalizaPalavra(chute);

}

bool palavraTemLetra(char palavra[], char letra) {
    for (int i = 0; i < tamanhoPalavra; i ++) {
        if (palavra[i] == letra) {
            return true;
        }
    }
    
    return false;
}

bool verificaChute(char chute[], char palavraResposta[]) {
    char vetorImpresso[tamanhoPalavra+1] = {};
    if (palavrasIguais(chute,palavraResposta))
    {
        for (int i = 0; vetorImpresso[i] != '\0'; i++)
        {
            cout<<'O';
        }
        return true;
    }
    else
    {    
        char chuteCopia[tamanhoPalavra+1] = {};
        char palavraRespostaCopia[tamanhoPalavra+1] = {};

        for(int i = 0; i < tamanhoPalavra; i++) {

            chuteCopia[i] = chute[i];
            palavraRespostaCopia[i] = palavraResposta[i];
            vetorImpresso[i] = '_';

            if (chute[i] == palavraResposta[i]) {
                vetorImpresso[i]='O';
                palavraRespostaCopia[i]='1';
                chuteCopia[i] = '2';
            }
        }

        for(int i = 0; i < tamanhoPalavra; i++) {
             if (palavraTemLetra(palavraRespostaCopia, chuteCopia[i])) {
                vetorImpresso[i] = 'X';
            }
        }
        for (int i = 0; i < tamanhoPalavra; i++)
            cout << vetorImpresso[i];
        cout<<endl;
        return false;
    }
}
void menu()
{
    dicionario dicionario = criarDicionario(dicionario);
    char palavraResposta [tamanhoPalavra + 1] = "";
    selecionarPalavra(palavraResposta, dicionario);
    
    cout<<palavraResposta<<endl;

    bool acertou = false;
    for (int i = 0; i < MAXIMO_TENTATIVAS; i++) {
        char chute[tamanhoPalavra + 1];
        pegaChute(chute,dicionario);
        acertou = verificaChute(chute, palavraResposta);
        if (acertou) {
            break;
        }
    }

    if (acertou) {
        cout << "Parabens" << endl;
    }
    else {
        cout << "Vc perdeu :(" << endl;
    }
}
int main()
{
    menu();
    return 0;
}