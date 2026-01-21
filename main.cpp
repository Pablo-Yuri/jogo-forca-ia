#include "funcoesEmetodos.h"
void Forca::exibirdesenho(string palavraEscondida[], bool desvendou) {
    system("clear");
    cout << "DICA: " << (dicas.empty() ? "Sem dica" : dicas[0]) << " | Tentativas: " << tentativasRestantes << endl;
    cout << "Letras usadas: ";
    for (const auto& l : letrasUsadas) cout << l << " ";
    cout << endl << endl;

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
        cout << "  |        " << (tentativasRestantes <= 2 ? "\\|/" : " ") << endl;
        cout << "  |         " << (tentativasRestantes <= 1 ? " |" : " ") << endl;
        cout << "  |        " << (tentativasRestantes <= 0 ? "/ \\" : " ") << endl;
    }

    cout << " _|___      ";
    for (int i = 0; i < (int)palavraSecreta.length(); i++) cout << palavraEscondida[i] << " ";
    cout << endl << endl;

    if (desvendou) cout << "\033[1;32mPARABENS! Voce salvou o boneco!\033[0m" << endl;
    else if (tentativasRestantes <= 0) cout << "\033[1;31mGAME OVER! A palavra era: " << palavraSecreta << "\033[0m" << endl;
}

// void limparBuffer() {
//     tcflush(STDIN_FILENO, TCIFLUSH); 
// }

int main() {
    Forca jogo;
    system("clear");
    cout << "=== CONFIGURACAO (LINUX) ===" << endl;
    cout << "Palavra Secreta: ";
    getline(cin, jogo.palavraSecreta);
    limparBuffer();
    cout << "Dica: ";
    string d; getline(cin, d);
    limparBuffer();
    jogo.dicas.push_back(d);
    
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
        int tecla = getch_linux();

        if (tecla == 27) { // Tecla de seta no Linux
            getch_linux(); // Pula o [
            int direcao = getch_linux();
            if (direcao == 65) selecionado = (selecionado - 1 + (int)opcoes.size()) % (int)opcoes.size(); // Cima
            else if (direcao == 66) selecionado = (selecionado + 1) % (int)opcoes.size(); // Baixo
        } 
        else if (tecla == 10) { // Enter no Linux
            if (seleciona do == 0) {
                cout << "Digite uma letra: ";
                char L; cin >> L;
                limparBuffer();
                L = toupper(L);
                ganhou = jogo.segredo(palavraEscondida, "", L); // Valida a letra
                cout << "teste"<< endl;
                getch_linux(); // Pula o [
            } 
            else if (selecionado == 1) {
                cout << "Digite a palavra: ";
                string P; cin >> P;
                limparBuffer();
                for(char &c : P) c = toupper(c);
                ganhou = jogo.segredo(palavraEscondida, P);
                if (!ganhou && jogo.tentativasRestantes <= 0) break;
                getch_linux(); 
            } 
            else if (selecionado == 2) break;
        }
    }

    jogo.exibirdesenho(palavraEscondida, ganhou);
    cout << "\nPressione Enter para sair...";
    getch_linux();
    
    delete[] palavraEscondida;
    return 0;
}