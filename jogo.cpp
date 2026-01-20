#include <iostream>
#include <fstream>
#include <cstring>
//#include <cctype>
#include <random>
#include <chrono>

using namespace std;

//Variáveis do Jogo
#define pathArquivo "dicionario.txt"
#define tamanhoPalavra 6
#define tamanhoPalavraMaxima 47
#define qtdPalavraMaxima 20000
#define MAXIMO_TENTATIVAS 10

struct dicionario {
    char listaPalavras[qtdPalavraMaxima][tamanhoPalavraMaxima];
    int qtdPalavras;
};

void capitalizaPalavra(char palavra[])
{
    for (int i = 0; palavra[i] != '\0';i++)
    {
        if (palavra[i] >= 'a' && palavra[i] <= 'z')
        {
            palavra[i] = palavra[i] - 'a' + 'A'; // +32
        }
    }
/*   for (int i = 0; palavra[i] != '\0';i++)
        palavra[i]= (char) toupper(palavra[i]);*/
}


void criaDicionario(dicionario dicionario)
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
                strcat(dicionario.listaPalavras[quantPalavras], buffer);
                quantPalavras++;
            }
        }
        arquivo.close();
        dicionario.qtdPalavras = qtdPalavras;
    }
    return;
}

void selecionaPalavra(char palavraResposta[])
{
    random_device semente;
    mt19937 gerador(semente());
    uniform_int_distribution distribuicao(1,qtdPalavras);
    int indicePalavra = distribuicao(gerador);
    strcat(palavraResposta,dicionario[indicePalavra]);
    capitalizaPalavra(palavraResposta);
    return;
}

bool verificaIgualdadePalavras(char p1[], char p2[]) {
    for (int i = 0; i < tamanhoPalavra; i++) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}

bool validaChute(char chute[],dicionario dicionario) {
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
        if (verificaIgualdadePalavras(chute, dicionario.listaPalavras[i])) {
            return true;
        }
    }
    return false;
}


void pegaChute(char chute[],dicionario dicionario)
{
    cin >> chute;

    // LIDA COM ERROS

    while (cin.fail() || !(validaChute(chute,dicionario)))
    {
        cout<<"ENTRADA INVALIDA, DEVE SER UMA PALAVRA EXISTENTE COM 6 CARACTERES\n";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> chute;
    }
    capitalizaPalavra(chute);

}

bool verificaPalavraTemLetra(char palavra[], char letra) {
    for (int i = 0; i < tamanhoPalavra; i ++) {
        if (palavra[i] == letra) {
            return true;
        }
    }
    
    return false;
}

bool verificaChute(char chute[], char palavraResposta[]) {
    
    char vetorImpresso[tamanhoPalavra+1];

    if (verificaIgualdadePalavras(chute,palavraResposta))
    {
        for (int i = 0; vetorImpresso[i] != '\0'; i++)
        {
            cout<<'O';
        }
        return true;
    }
    else
    {
        // As copias servem para retirarmos os pares 1 a 1 dos vetores sem modificar permanentemente a informação.
        char chuteCopia[tamanhoPalavra+1];
        char palavraRespostaCopia[tamanhoPalavra+1];

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
             if (verificaPalavraTemLetra(palavraResposta, chute[i])) {
                vetorImpresso[i] = 'X';
            }
        }
        for (int i = 0; vetorImpresso != '\0'; i++)
            cout << vetorImpresso[i];
        cout<<endl;
        return false;
    }
}

void logo()
{
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"                                                                      "<<endl;
    cout<<"     TERMO VERSAO C++                                                 "<<endl;
    cout<<"                                        feito por Vinicius e Heitor   "<<endl;
    cout<<"----------------------------------------------------------------------"<<endl<<endl;
}
void jogarNovamente()
{
    cout << "Gostaria de Jogar Novamente? (digite s pra sim, qualquer outra coisa pra nao)"
    char r;
    cin>>r;
    capitalizaPalavra(r);
    if(r == 'S')
    {
        jogo();
    }
    else
    {
        cout<<"Até a proxima!"
        exit[0];
    }

}
void jogo()
{
    dicionario dicionario = criaDicionario();
    char palavraResposta [tamanhoPalavra + 1] = "";
    selecionaPalavra(palavraResposta);
    
    // cout<<palavraResposta<<endl;
    
    logo();
    
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
    jogo();
    return 0;
}