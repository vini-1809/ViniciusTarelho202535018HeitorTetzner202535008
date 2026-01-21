#include <iostream>
#include <fstream>
#include <cstring>
//#include <cctype>
#include <random>
#include <chrono>

using namespace std;

#define pathArquivo "dicionario.txt"
#define tamanhoPalavra 6
#define tamanhoPalavraMaxima 47
#define qtdPalavraMaxima 12000
#define MAXIMO_TENTATIVAS 10
#define debugMode false

struct Dicionario {
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


Dicionario criaDicionario(Dicionario dicionario)
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
                capitalizaPalavra(buffer);
                strcat(dicionario.listaPalavras[qtdPalavras], buffer);
                qtdPalavras++;
            }
        }
        arquivo.close();
        dicionario.qtdPalavras = qtdPalavras;
    }
    return dicionario;
}

void selecionaPalavra(char palavraResposta[],Dicionario dicionario)
{
    random_device semente;
    mt19937 gerador(semente());
    uniform_int_distribution distribuicao(1,dicionario.qtdPalavras);
    int indicePalavra = distribuicao(gerador);
    strcat(palavraResposta,dicionario.listaPalavras[indicePalavra]);
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

bool validaChute(char chute[],Dicionario dicionario) {
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


void pegaChute(char chute[],Dicionario dicionario)
{
    cin >> chute;
    capitalizaPalavra(chute);

    // LIDA COM ERROS

    while (cin.fail() || !(validaChute(chute,dicionario)))
    {
        cout<<"ENTRADA INVALIDA, DEVE SER UMA PALAVRA EXISTENTE COM " << tamanhoPalavra <<  " CARACTERES\n";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> chute;
        capitalizaPalavra(chute);
    }

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
void logo()
{
    cout<<"----------------------------------------------------------------------\n";
    cout<<"                                                                      \n";
    cout<<"     TERMO VERSAO C++                                                 \n";
    cout<<"                                        feito por Vinicius e Heitor   \n";
    cout<<"----------------------------------------------------------------------\n\n";
    cout<<"Digite uma palavra para o jogo comecar!\n";
}

void jogo();

void jogaNovamente()
{
    cout << "Gostaria de Jogar Novamente? (digite s pra sim, qualquer outra coisa pra nao)"<<endl;
    char r;
    cin >> r;
    if(r == 'S' || r == 's')
    {
        cout<<endl;
        cin.clear();
        cin.ignore(256, '\n');
        jogo();
    }
    else
    {
        cout<<"Até a proxima!"<<endl;
        //exit(0);
    }

}

bool loopTentativas(Dicionario dicionario, char palavraResposta[]) {
    bool acertou = false;
    for (int i = 0; i < MAXIMO_TENTATIVAS; i++) {
        char chute[tamanhoPalavra + 1];
        pegaChute(chute,dicionario);
        acertou = verificaChute(chute, palavraResposta);
        if (acertou) {
            break;
        }
    }

    return acertou;
}

void jogo()
{
    Dicionario dicionario;
    dicionario = criaDicionario(dicionario);
    char palavraResposta[tamanhoPalavra + 1] = "";
    selecionaPalavra(palavraResposta, dicionario);
    
    if (debugMode)
    {
       cout<<palavraResposta<<endl; 
    }
    
    logo();
    
    bool acertou = loopTentativas(dicionario, palavraResposta);

    if (acertou) {
        cout << "Parabens, você ganhou!" << endl;
    }
    else {
        cout << "Você perdeu, que pena!" << endl;
    }
    jogaNovamente();
}
int main()
{
    jogo();
    return 0;
}