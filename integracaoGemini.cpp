// g++ -std=c++17 integracaoGemini.cpp -o integracaoGemini.exe -lcurl

#include <iostream>
#include <string>
#include <cstdlib>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// Callback para armazenar resposta da requisição
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Função para fazer requisição à API do Gemini
string callGeminiAPI(const string& apiKey, const string& prompt) {
    CURL* curl = curl_easy_init();
    
    if (!curl) {
        cerr << "Erro ao inicializar CURL" << endl;
        return "";
    }
    
    // URL da API do Gemini
    string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=" + apiKey;
    
    // Preparar payload JSON
    json payload;
    payload["contents"][0]["parts"][0]["text"] = prompt;
    
    string payloadStr = payload.dump();
    string readBuffer;
    
    // Configurar requisição CURL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
    
    // Headers
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    // Callback para armazenar resposta
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    
    // Executar requisição
    CURLcode res = curl_easy_perform(curl);
    
    if (res != CURLE_OK) {
        cerr << "Erro na requisição: " << curl_easy_strerror(res) << endl;
    }
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    
    return readBuffer;
}

// Função para extrair texto da resposta
string extractResponseText(const string& response) {
    try {
        auto jsonResponse = json::parse(response);
        
        if (jsonResponse.contains("candidates") && 
            jsonResponse["candidates"].size() > 0 &&
            jsonResponse["candidates"][0].contains("content") &&
            jsonResponse["candidates"][0]["content"].contains("parts") &&
            jsonResponse["candidates"][0]["content"]["parts"].size() > 0) {
            
            return jsonResponse["candidates"][0]["content"]["parts"][0]["text"];
        }
    } catch (const exception& e) {
        cerr << "Erro ao parsear JSON: " << e.what() << endl;
    }
    
    return "";
}

int main() {
    cout << "=== Demo API Gemini em C++ ===" << endl;
    cout << endl;
    
    // A chave de API DEVE ser fornecida via variável de ambiente GEMINI_API_KEY
    const char* envKey = std::getenv("GEMINI_API_KEY");
    
    // Verificar se a variável foi setada
    if (!envKey) {
        cerr << "\n" << string(60, '=') << endl;
        cerr << "❌ ERRO: Variável de ambiente GEMINI_API_KEY não foi definida!" << endl;
        cerr << string(60, '=') << endl;
        cerr << "\nPara executar este programa, você DEVE definir a chave:" << endl;
        cerr << "\n  1. Temporariamente (sessão atual):" << endl;
        cerr << "     export GEMINI_API_KEY=\"sua_chave_aqui\"" << endl;
        cerr << "\n  2. Permanentemente (bash):" << endl;
        cerr << "     echo 'export GEMINI_API_KEY=\"sua_chave_aqui\"' >> ~/.bashrc" << endl;
        cerr << "     source ~/.bashrc" << endl;
        cerr << "\n  3. Permanentemente (zsh):" << endl;
        cerr << "     echo 'export GEMINI_API_KEY=\"sua_chave_aqui\"' >> ~/.zshrc" << endl;
        cerr << "     source ~/.zshrc" << endl;
        cerr << "\n  4. Verificar se está setada:" << endl;
        cerr << "     echo $GEMINI_API_KEY" << endl;
        cerr << "\n📖 Obtenha sua chave em: https://aistudio.google.com/app/apikey" << endl;
        cerr << string(60, '=') << "\n" << endl;
        return 1;
    }
    
    string apiKey(envKey);
    
    // Verificar se a variável está vazia
    if (apiKey.empty()) {
        cerr << "\n❌ ERRO: A variável GEMINI_API_KEY está vazia!" << endl;
        cerr << "Defina com um valor válido:" << endl;
        cerr << "   export GEMINI_API_KEY=\"sua_chave_aqui\"" << endl;
        return 1;
    }
    
    // Fazer requisição
    // string prompt = "Qual é a capital do Brasil?";
    string prompt = "Gere uma palavra para um jogo da forca, tambem me de uma dica sobre essa palavra, que não a entregue pelo contexto.";
    cout << "Pergunta: " << prompt << endl;
    cout << "Aguardando resposta..." << endl;
    
    string response = callGeminiAPI(apiKey, prompt);
    string answer = extractResponseText(response);
    
    if (!answer.empty()) {
        cout << "\nResposta: " << answer << endl;
    } else {
        cout << "\nErro ao obter resposta." << endl;
        cout << "Resposta bruta: " << response << endl;
    }
    
    cout << answer << endl;

    return 0;
}
