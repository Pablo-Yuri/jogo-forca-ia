#include "funcoesEmetodos.h"
#include "integracaoGemini.h"
// g++ -std=c++17 main.cpp -o main.exe -lcurl

void Forca::exibirdesenho(string palavraEscondida[] , bool desvendou) {
    system("clear");
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << " Tentativas: " << tentativasRestantes << endl;
    cout << " DICAS: " << (dicas.empty() ? "Sem dicas" : "") << endl; 
    for (int i = 0; i < (int)dicas.size(); i++) cout << "- " << dicas[i] << endl;
    cout << endl;
    cout << " Letras usadas: \033[1;31m";
    for (const auto& l : letrasUsadas) cout << l << " ";
    cout << "\033[0m" << endl << endl;

    if (desvendou) {
        cout << "   ___________" << endl;
        cout << "  | /" << endl;
        cout << "  |/        (^_^)" << endl;
        cout << "  |          \\|/" << endl;
        cout << "  |           |" << endl;
        cout << "  |          / \\" << endl;
    } else {
        cout << "   ___________" << endl;
        cout << "  | /        |" << endl;
        cout << "  |/       " << (tentativasRestantes <= 3 ? "(x_x)" : " ") << endl;
        cout << "  |        " << (tentativasRestantes <= 2 ? " \\|/" : " ") << endl;
        cout << "  |         " << (tentativasRestantes <= 1 ? " |" : " ") << endl;
        cout << "  |        " << (tentativasRestantes <= 0 ? " / \\" : " ") << endl;
    }

    cout << " _|___      ";
    for (int i = 0; i < (int)palavraSecreta.length(); i++) cout << "\033[1;34m" << palavraEscondida[i] << "\033[0m ";
    cout << endl << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

    if (desvendou) cout << "\033[1;32mPARABENS! Voce salvou o boneco!\033[0m" << endl;
    else if (tentativasRestantes <= 0) cout << "\033[1;31mGAME OVER! A palavra era: " << palavraSecreta << "\033[0m" << endl;
}

int main() {
    Forca jogo;
    system("clear");
    while (true){ // Loop para reiniciar o jogo, a saída é feita internamente
        if (jogo.MenuInicial()){
            // modo com IA
            cout << "==== Modo com IA ====" << endl;
            RespostaIA resposta = requisicao();
            if (resposta.ok) {
                jogo.palavraSecreta = resposta.palavra;
                jogo.dicas.push_back(resposta.dica);
            } else {
                cout << "\n❌ Falha ao obter ou parsear resposta da IA." << endl;
                if (!resposta.raw.empty()) {
                    cout << "Resposta bruta: " << resposta.raw << endl;
                }
            }
            cout << "\nPressione Enter para continuar...";
            getch_linux();
        } else {
            system("clear");
            cout << "==== Modo Manual ====" << endl;
            // jogo.exibirdesenho();
            cout << "Palavra Secreta: ";
            getline(cin, jogo.palavraSecreta);
            limparBuffer();
            cout << "Dica: ";
            string d; getline(cin, d);
            limparBuffer();
            jogo.dicas.push_back(d);
        }
        
        jogo.maiusculo(jogo.palavraSecreta);
        jogo.tentativasRestantes = 4;
        string* palavraEscondida = new string[jogo.palavraSecreta.length()];
        jogo.esconderPalavra(palavraEscondida);

        vector<string> opcoes = {"Tentar letra", "Tentar palavra", "Sair"};
        bool ganhou = false;
        int selecionado = 0;
        
        while (jogo.tentativasRestantes > 0 && !ganhou) {
            jogo.exibirdesenho(palavraEscondida);
            jogo.exibirMenu(opcoes, selecionado);
            
            // cout << "tecla: " << tecla << endl;
            // cout << "selecionado: " << selecionado << endl;
            cout << "Use as setas para navegar e Enter para selecionar." << endl;
            int tecla = getch_linux();

            if (tecla == 27) { // Tecla de seta no Linux
                getch_linux(); // Pula o [
                int direcao = getch_linux();
                if (direcao == 65) selecionado = (selecionado - 1 + (int)opcoes.size()) % (int)opcoes.size(); // Cima
                else if (direcao == 66) selecionado = (selecionado + 1) % (int)opcoes.size(); // Baixo
            } 
            else if (tecla == 10) { // Enter no Linux
                if (selecionado == 0) {
                    cout << "Digite uma letra: ";
                    char L; cin >> L;
                    limparBuffer();
                    L = toupper(L);
                    ganhou = jogo.segredo(palavraEscondida, "", L); // Valida a letra
                    // cout << "teste"<< endl;
                    getch_linux(); // Pula o [
                } 
                else if (selecionado == 1) {
                    cout << "Digite a palavra: ";
                    string P; cin >> P;
                    limparBuffer();
                    for(char &c : P) c = toupper(c);
                    ganhou = jogo.segredo(palavraEscondida, P);
                    getch_linux(); 
                } 
                else if (selecionado == 2){ 
                    cout << "Sair selecionado!" << endl;
                    exit(0);
                    break;
                }
            }
        }

        jogo.exibirdesenho(palavraEscondida, ganhou);
        cout << "\nPressione Enter para continuar...";
        getch_linux();
        
        delete[] palavraEscondida;
        jogo.dicas.clear();
        jogo.letrasUsadas.clear();
    }
}