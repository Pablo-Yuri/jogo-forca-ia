#include <iostream>
#include <vector>
#include <cctype>
#include <limits>
#include <algorithm>
#include <termios.h>
#include <unistd.h>

using namespace std;

// Função para ler teclas no Linux sem esperar pelo Enter
int getch_linux() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void limparBuffer() {
    tcflush(STDIN_FILENO, TCIFLUSH); 
}

class Forca {
public:
    string palavraSecreta;
    vector<string> dicas;
    int tentativasRestantes;
    vector<string> letrasUsadas;

    void maiusculo(string &str);
    void esconderPalavra(string palavraEscondida[]);
    void revelarPalavra(string palavraEscondida[]);
    void registrarLetraUsada(char tentativa_letra, string palavraEscondida[]);
    bool verificarLetraUsada(char tentativa_letra);
    bool segredo(string palavraEscondida[], string tentativa_palavra = "", char tentativa_letra = '\0');
    
    bool MenuInicial();
    void exibirMenu(const vector<string>& opcoes, int selecionado);
    void exibirdesenho(string palavraEscondida[], bool desvendou = false);
};

void Forca::maiusculo(string &str) {
    for (char &c : str) c = toupper(c);
}

void Forca::esconderPalavra(string palavraEscondida[]) {
    for (int i = 0; i < (int)palavraSecreta.length(); i++) {
        palavraEscondida[i] = (palavraSecreta[i] != ' ') ? "_" : " ";
    }
}

void Forca::revelarPalavra(string palavraEscondida[]) {
    for (int i = 0; i < (int)palavraSecreta.length(); i++) {
        palavraEscondida[i] = palavraSecreta[i];
    }
}

bool Forca::verificarLetraUsada(char tentativa_letra) {
    string s(1, tentativa_letra);
    return find(letrasUsadas.begin(), letrasUsadas.end(), s) != letrasUsadas.end();
}

void Forca::registrarLetraUsada(char tentativa_letra, string palavraEscondida[]) {
    if (verificarLetraUsada(tentativa_letra)) return;
    letrasUsadas.push_back(string(1, tentativa_letra));
    
    // bool acertou = false;
    for (int i = 0; i < (int)palavraSecreta.length(); i++) {
        if (palavraSecreta[i] == tentativa_letra) {
            palavraEscondida[i] = tentativa_letra;
            // acertou = true;
        }
    }
    // if (!acertou) tentativasRestantes--;
}

bool Forca::segredo(string palavraEscondida[], string tentativa_palavra, char tentativa_letra) {
    if (tentativa_palavra != "") {
        if (tentativa_palavra == palavraSecreta) {
            revelarPalavra(palavraEscondida);
            return true;
        } else {
            tentativasRestantes--;
            return false;
        }
    }
    registrarLetraUsada(tentativa_letra, palavraEscondida);
    
    for(int i=0; i < (int)palavraSecreta.length(); i++) {
        if(palavraEscondida[i] == "_") return false;
    }
    return true;
}

void Forca::exibirMenu(const vector<string>& opcoes, int selecionado) {
    cout << "\n----------- OPCOES -----------" << endl;
    // if (selecionado < 0) selecionado += 1;
    for (int i = 0; i < (int)opcoes.size(); ++i) {
        if (i == selecionado) {
            // Destaque em verde no Linux
            cout << "\033[1;32m  > [ " << opcoes[i] << " ] <\033[0m" << endl;
        } else {
            cout << "      " << opcoes[i] << endl;
        }
    }
    // cout << "selecionado: " << selecionado << endl; 
    cout << "------------------------------" << endl;
}

bool Forca::MenuInicial(){
    vector<string> opcoesInicio = {"Jogar com IA", "Jogar sem IA", "Sair"};
    // bool ganhou = false;
    int selecionado = 0;
    while (true) {
        system("clear");
        // jogo.exibirdesenho(palavraEscondida);
        exibirMenu(opcoesInicio, selecionado);
        
        // cout << "tecla: " << tecla << endl;
        // cout << "selecionado: " << selecionado << endl;
        int tecla = getch_linux();

        if (tecla == 27) { // Tecla de seta no Linux
            getch_linux(); // Pula o [
            int direcao = getch_linux();
            if (direcao == 65) selecionado = (selecionado - 1 + (int)opcoesInicio.size()) % (int)opcoesInicio.size(); // Cima
            else if (direcao == 66) selecionado = (selecionado + 1) % (int)opcoesInicio.size(); // Baixo
        } 
        else if (tecla == 10) { // Enter no Linux
            if (selecionado == 0) {
                // Jogar com IA
                cout << "Jogar com IA selecionado!" << endl;
                // break;  
                getch_linux();
                return true; 
            } 
            else if (selecionado == 1) {
                // Jogar sem IA
                cout << "Jogar sem IA selecionado!" << endl;
                getch_linux(); 
                return false;
            } 
            else if (selecionado == 2) {
                cout << "Sair selecionado!" << endl;
                exit(0);
            }
        }
    }
}