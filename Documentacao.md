# Forca (Linux) – Setup e Execução

Este projeto contém um jogo de Forca em C++ (terminal) e um exemplo de integração com a API Gemini (Google) usando cURL e nlohmann/json.

## Requisitos
- GCC/G++ com C++17
- Make (opcional)
- cURL (runtime e headers de desenvolvimento)
- nlohmann/json (header-only)

Em Debian/Ubuntu e derivados:

```bash
sudo apt-get update
sudo apt-get install -y build-essential curl libcurl4-openssl-dev nlohmann-json3-dev
```

## Estrutura
- [main.cpp](main.cpp): jogo de forca com menu e integração com IA
- [funcoesEmetodos.h](funcoesEmetodos.h): classe Forca e utilitários (setas, buffer, etc.)
- [integracaoGemini.h](integracaoGemini.h): protótipo da função `requisicao()`
- [Makefile](Makefile): automação de compilação

## Configurar chave da API (Gemini)
```

Alternativa (mais segura): use variável de ambiente e leia no código. Exemplo de export:

```bash
export GEMINI_API_KEY="SEU_GEMINI_API_KEY_AQUI"
```

> Dica: Gere a chave em https://aistudio.google.com/app/apikey

Para tornar permanente no bash:

```bash
echo 'export GEMINI_API_KEY="SEU_GEMINI_API_KEY_AQUI"' >> ~/.bashrc
source ~/.bashrc
```

No zsh, use `~/.zshrc` no lugar de `~/.bashrc`.

## Compilar

**Com Makefile (recomendado):**

```bash
cd Forca
make build      # Compila main.exe
make run        # Compila (se necessário) e executa
make clean      # Remove binários gerados
```

**Manualmente (sem Makefile):**

```bash
g++ -std=c++17 main.cpp -o main.exe -lcurl -Wall -O2
```

### Como o Makefile funciona

O Makefile automatiza a compilação. Veja a estrutura:

```makefile
CXX := g++                          # Compilador
CXXFLAGS := -std=c++17 -Wall -O2    # Flags de compilação
CURL_LIBS := -lcurl                 # Bibliotecas necessárias

BIN_MAIN := main.exe                # Arquivo de saída
SRC_MAIN := main.cpp                # Arquivo de entrada
HDR_FORCA := funcoesEmetodos.h      # Headers que main.cpp depende
HDR_INTEGRACAO := integracaoGemini.h

# Alvo "build" - compila main.exe se fonte ou header mudarem
build: $(BIN_MAIN)

# Receita - comando para criar main.exe
$(BIN_MAIN): $(SRC_MAIN) $(HDR_FORCA) $(HDR_INTEGRACAO)
	$(CXX) $(CXXFLAGS) $(CURL_CFLAGS) $(SRC_MAIN) -o $@ $(CURL_LIBS)

# Alvo "run" - compila e executa
run: $(BIN_MAIN)
	./$(BIN_MAIN)

# Alvo "clean" - remove arquivos gerados
clean:
	rm -f $(BIN_MAIN) *.o
```

**Vantagens:**
- Compila automaticamente se algo mudar
- Uma linha de comando instead of long g++ strings
- Suporta múltiplos alvos e arquivos

## Executar

Jogo de Forca com menu (modo manual ou com IA):

```bash
make run
# ou
./main.exe
```

## Erros comuns e soluções
- undefined reference to `curl_*` ao linkar:
	- Falta linkar a lib no final do comando. Use `-lcurl` (ou `$(pkg-config --libs libcurl)`). Ex.: `g++ integracaoGemini.cpp -o integracaoGemini.exe -lcurl`.

- fatal error: nlohmann/json.hpp: No such file or directory:
	- Instale o pacote: `sudo apt-get install nlohmann-json3-dev`.
	- Alternativa: inclua o header do repositório oficial em `./third_party/nlohmann/json.hpp` e ajuste o include path com `-I`.

- `./main.exe` sai com código 130:
	- Normalmente indica interrupção (Ctrl+C) ou sinal do terminal. Rode novamente e evite interromper.

- Proxy/firewall bloqueando a chamada HTTP:
	- Teste o cURL no terminal: `curl https://www.google.com`.
	- Se falhar, configure proxy/CA do sistema.

## Notas de uso (Linux)
- O jogo usa controles de setas do terminal (sequências ANSI) e leitura sem buffer via `termios`. Execute em um terminal comum (bash/zsh) com suporte ANSI.
- O `system("clear")` é usado para limpar a tela; em ambientes sem `clear`, substitua por `tput clear` ou remova a chamada.

## Próximos passos (opcional)
- Adicionar alvo `install` para compilar automaticamente dependências
- Suporte para múltiplos modelos da API (fallback automático)

