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
BIN_GEMINI := integracaoGemini.exe

# Sources
SRC_MAIN := main.cpp
SRC_GEMINI := integracaoGemini.cpp

# Headers
HDR_FORCA := funcoesEmetodos.h
HDR_API := ../APIgemini.h

.PHONY: all clean run-main run-gemini

all: $(BIN_MAIN) $(BIN_GEMINI)

$(BIN_MAIN): $(SRC_MAIN) $(HDR_FORCA)
	$(CXX) $(CXXFLAGS) $(CURL_CFLAGS) $< -o $@

$(BIN_GEMINI): $(SRC_GEMINI) $(HDR_API)
	$(CXX) $(CXXFLAGS) $(CURL_CFLAGS) $< -o $@ $(CURL_LIBS)

run-main: $(BIN_MAIN)
	./$(BIN_MAIN)

run-gemini: $(BIN_GEMINI)
	./$(BIN_GEMINI)

clean:
	rm -f $(BIN_MAIN) $(BIN_GEMINI)
