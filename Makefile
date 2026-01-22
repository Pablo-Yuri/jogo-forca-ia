# Simple Makefile for Forca project (Linux)

CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

# Try to get curl flags from pkg-config; fallback to -lcurl
CURL_CFLAGS := $(shell pkg-config --cflags libcurl 2>/dev/null)
CURL_LIBS := $(shell pkg-config --libs libcurl 2>/dev/null)
ifeq ($(strip $(CURL_LIBS)),)
  CURL_LIBS := -lcurl
endif

# Binaries
BIN_MAIN := main.exe

# Sources
SRC_MAIN := main.cpp

# Headers
HDR_FORCA := funcoesEmetodos.h
HDR_INTEGRACAO := integracaoGemini.h

.PHONY: all clean run build

build: $(BIN_MAIN)

$(BIN_MAIN): $(SRC_MAIN) $(HDR_FORCA) $(HDR_INTEGRACAO)
	$(CXX) $(CXXFLAGS) $(CURL_CFLAGS) $(SRC_MAIN) -o $@ $(CURL_LIBS)

run-main: $(BIN_MAIN)
	./$(BIN_MAIN)

run: run-main

clean:
	rm -f $(BIN_MAIN) *.o


# make build      # Compila (cria main.exe)
# make run        # Compila e executa
# make clean      # Remove binários