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
- [main.cpp](main.cpp): jogo de forca (standalone, sem rede)
- [funcoesEmetodos.h](funcoesEmetodos.h): utilitários e lógica do jogo
- [integracaoGemini.cpp](integracaoGemini.cpp): exemplo chamando a API Gemini
- [../APIgemini.h](../APIgemini.h): define a sua chave de API (`MinhaApiKeyGemini`)

## Configurar chave da API (Gemini)
Você pode manter como no código, criando/ajustando o arquivo [../APIgemini.h](../APIgemini.h):

```cpp
#include <iostream>
using namespace std;

// Substitua pela sua chave do Google AI Studio
string MinhaApiKeyGemini = "SEU_GEMINI_API_KEY_AQUI";
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
Entre na pasta `Forca/`:

```bash
cd Forca
```

Jogo de Forca (apenas terminal):

```bash
g++ -std=c++17 main.cpp -o main.exe -Wall -O2
```

Exemplo de integração com Gemini (cURL + JSON):

```bash
g++ -std=c++17 integracaoGemini.cpp -o integracaoGemini.exe -lcurl -Wall -O2
```

Se usar `pkg-config` para garantir os flags do cURL:

```bash
g++ -std=c++17 integracaoGemini.cpp -o integracaoGemini.exe $(pkg-config --cflags --libs libcurl) -Wall -O2
```

Com Makefile (já incluído nesta pasta):

```bash
make            # compila main.exe e integracaoGemini.exe
make run-main   # executa o jogo
make run-gemini # executa a integração com a API
make clean      # remove binários
```

## Executar
Jogo de Forca:

```bash
./main.exe
```

Integração Gemini (retorna texto com a palavra/dica):

```bash
./integracaoGemini.exe
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
- Trocar a chave em arquivo por variável de ambiente para evitar versionar segredo.
- Adicionar `Makefile` com alvos `build` e `run` para simplificar o fluxo.

