#include "camadaFisica.h"

void CamadaFisicaTransmissora(const vector<int>& quadro, int codificacaoFisica) {
  
  vector<int> fluxoBrutoDeBits;
  switch (codificacaoFisica) {
    case COD_BINARIA:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
      break;
    case COD_MANCHESTER:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
      break;
    case COD_BIPOLAR:
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
      break;
    default:
      cout << "MODO DE CODIFICAÇÃO NÃO ENCONTRADO" << endl;
      break;
  }

  MeioDeComunicacao(fluxoBrutoDeBits, codificacaoFisica);
}


// Simula a transmissão de informação no meio de comunicação, 
// passando de um PontoA (transmissor) para um PontoB (receptor) 
void MeioDeComunicacao(const vector<int>& fluxoBrutoDeBits, int codificacaoFisica) {
  vector<int> fluxoBrutoDeBitsPontoA;
  vector<int> fluxoBrutoDeBitsPontoB;
  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  
  for (unsigned i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
    fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA.at(i));
  }

  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, codificacaoFisica);
}


void CamadaFisicaReceptora(const vector<int>& fluxoBrutoDeBits, int codificacaoFisica) {
  
  vector<int> quadro;
  switch (codificacaoFisica) {
    case COD_BINARIA:
      quadro = CamadaFisicaReceptoraCodificacaoBinaria(fluxoBrutoDeBits);
      break;
    case COD_MANCHESTER:
      quadro = CamadaFisicaReceptoraCodificacaoManchester(fluxoBrutoDeBits);
      break;
    case COD_BIPOLAR:
      quadro = CamadaFisicaReceptoraCodificacaoBipolar(fluxoBrutoDeBits);
      break;
    default:
      cout << "MODO DE DECODIFICAÇÃO NÃO ENCONTRADO" << endl;
      break;
  }
  CamadaDeAplicacaoReceptora(quadro);
}


vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro) {
  cout << endl << "CODIFICAÇÃO BINÁRIA:";

  for (unsigned i = 0; i < quadro.size(); i++) {

    // Para cada 8 Bits (caracter)
    if (i % 8 == 0) { 
      cout << endl;
    }
    cout << quadro.at(i);
  }
  cout << endl;

  return quadro;
}


vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
  vector<int> manchesterBits;
  cout << endl << "CODIFICAÇÃO MANCHESTER:";

  for (unsigned i = 0; i < quadro.size(); i++) {
    manchesterBits.push_back(quadro.at(i) ^ CLK_MANCHESTER.at(0));
    manchesterBits.push_back(quadro.at(i) ^ CLK_MANCHESTER.at(1));
    
    // Para cada 8 Bits (caracter)
    if (i % 8 == 0) {  
      cout << endl;
    }
    
    // CLK_MANCHESTER = [0,1] serve para padronizar a codificação
    cout << (quadro.at(i) ^ CLK_MANCHESTER.at(0));
    cout << (quadro.at(i) ^ CLK_MANCHESTER.at(1));
  }  
  cout << endl;

  return manchesterBits;
}


vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
  bool umNegativo = false;  // O bipolar começa com 1 positivo
  cout << endl << "CODIFICAÇÃO BIPOLAR:";

  for (unsigned i = 0; i < quadro.size(); i++) {

    // Para cada 8 Bits (caracter)
    if (i % 8 == 0) { 
      cout << endl;
    }
    if (quadro.at(i) == 1) {
      if (umNegativo) {
        quadro.at(i) = -1;
        cout << "-1";
      } else {
        cout << " 1";
      }
      umNegativo = !umNegativo;
    } else {
      cout << " 0";
    }
    cout << " ";
  }
  cout << endl;

  return quadro;
}


vector<int> CamadaFisicaReceptoraCodificacaoBinaria(
    vector<int> fluxoBrutoDeBits) {
  return fluxoBrutoDeBits;
}


vector<int> CamadaFisicaReceptoraCodificacaoManchester(
    vector<int> fluxoBrutoDeBits) {
  vector<int> bitsDecodificados;
  for (unsigned i = 0; i < fluxoBrutoDeBits.size(); i += 2) {  // Sinal original
    bitsDecodificados.push_back(fluxoBrutoDeBits.at(i));       // está na xor com 0
  }

  return bitsDecodificados;
}


vector<int> CamadaFisicaReceptoraCodificacaoBipolar(
    vector<int> fluxoBrutoDeBits) {
  for (unsigned i = 0; i < fluxoBrutoDeBits.size(); i++) {  // Faz o módulo de tudo
    fluxoBrutoDeBits.at(i) = fabs(fluxoBrutoDeBits.at(i)); 
  }

  return fluxoBrutoDeBits;
}
