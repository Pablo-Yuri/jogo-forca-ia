# 🎮 Jogo da Forca com IA

Jogo da Forca interativo para terminal Linux desenvolvido em C++17, com integração à API Gemini (Google AI) para geração automática de palavras e dicas.

## ✨ Características

- 🎯 Interface colorida com controles de seta
- 🤖 Modo IA: palavras e dicas geradas automaticamente via Google Gemini
- 📝 Modo Manual: jogue com suas próprias palavras
- 🔐 Segurança: chave de API via variável de ambiente
- 🛠️ Build automatizado com Makefile
- 🎨 Visual ASCII art com animações

## 🚀 Quick Start

```bash
# 1. Clone o repositório
git clone https://github.com/Pablo-Yuri/jogo-forca-ia.git
cd jogo-forca-ia

# 2. Instale dependências (Debian/Ubuntu)
sudo apt-get install build-essential libcurl4-openssl-dev nlohmann-json3-dev

# 3. Configure a API key (obtenha em https://aistudio.google.com/app/apikey)
export GEMINI_API_KEY="sua_chave_aqui"

# 4. Compile e execute
make run
```

## 📋 Requisitos

- GCC/G++ com suporte a C++17
- cURL (desenvolvimento)
- nlohmann-json
- Make
- Terminal com suporte ANSI

## 🎮 Como Jogar

1. Escolha entre **Modo IA** (palavra automática) ou **Modo Manual**
2. Use as **setas ↑↓** para navegar no menu
3. Pressione **Enter** para selecionar
4. Tente adivinhar a palavra letra por letra ou arrisque a palavra completa
5. Você tem 4 tentativas antes do boneco ser enforcado!

## 🛠️ Compilação

**Com Makefile (recomendado):**
```bash
make build      # Compila
make run        # Compila e executa
make clean      # Remove binários
```

**Manual:**
```bash
g++ -std=c++17 main.cpp -o main.exe -lcurl -Wall -O2
```

## 📁 Estrutura do Projeto

```
jogo-forca-ia/
├── main.cpp              # Lógica principal do jogo
├── funcoesEmetodos.h     # Classe Forca e utilitários
├── integracaoGemini.h    # Interface com API Gemini
├── Makefile              # Automação de build
├── Realme.md             # Documentação completa
└── README.md             # Este arquivo
```

## 🔧 Tecnologias Utilizadas

- **C++17**: Linguagem principal
- **cURL**: Requisições HTTP à API
- **nlohmann/json**: Parsing de JSON
- **termios**: Controle de terminal (setas, buffer)
- **Google Gemini API**: Geração de conteúdo por IA

## 🔑 Configuração da API Key

### Temporária (sessão atual):
```bash
export GEMINI_API_KEY="sua_chave_aqui"
```

### Permanente (bash):
```bash
echo 'export GEMINI_API_KEY="sua_chave_aqui"' >> ~/.bashrc
source ~/.bashrc
```

### Permanente (zsh):
```bash
echo 'export GEMINI_API_KEY="sua_chave_aqui"' >> ~/.zshrc
source ~/.zshrc
```

### Obter chave:
1. Acesse [Google AI Studio](https://aistudio.google.com/app/apikey)
2. Faça login com sua conta Google
3. Clique em "Create API key"
4. Copie a chave gerada

## 📖 Documentação Completa

Veja [Realme.md](Realme.md) para:
- Instalação detalhada
- Configuração de variáveis de ambiente
- Troubleshooting completo
- Explicação do Makefile
- Tratamento de erros da API

## 🐛 Troubleshooting

### Erro: `undefined reference to curl_*`
```bash
# Instale a biblioteca de desenvolvimento
sudo apt-get install libcurl4-openssl-dev
```

### Erro: `nlohmann/json.hpp: No such file`
```bash
# Instale o header JSON
sudo apt-get install nlohmann-json3-dev
```

### Erro 429 (Quota exceeded)
- Você excedeu o limite de requisições do plano gratuito
- Aguarde o reset diário ou use outro modelo

### Erro 404 (Model not found)
- Verifique se está usando um modelo válido (gemini-pro, gemini-1.5-pro)
- Consulte a [documentação oficial](https://ai.google.dev/gemini-api/docs)

## 🤝 Contribuindo

Contribuições são bem-vindas! Sinta-se livre para:

1. Fork o projeto
2. Crie uma branch (`git checkout -b feature/MinhaFeature`)
3. Commit suas mudanças (`git commit -m 'Add: nova feature'`)
4. Push para a branch (`git push origin feature/MinhaFeature`)
5. Abra um Pull Request

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## 🔗 Links Úteis

- [Google AI Studio](https://aistudio.google.com/app/apikey) - Obtenha sua API key
- [Gemini API Docs](https://ai.google.dev/gemini-api/docs) - Documentação oficial
- [nlohmann/json](https://github.com/nlohmann/json) - Biblioteca JSON para C++
- [cURL](https://curl.se/) - Biblioteca de transferência de dados

## 👨‍💻 Autor

**Pablo Yuri**
- GitHub: [@Pablo-Yuri](https://github.com/Pablo-Yuri)
- Linkedin: [@Pablo Yuri](www.linkedin.com/in/pablo-yuri)

---

⭐ Se este projeto te ajudou, considere dar uma estrela!
