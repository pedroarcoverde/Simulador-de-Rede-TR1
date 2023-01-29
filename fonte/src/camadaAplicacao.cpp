#include "camadaAplicacao.h"

void AplicacaoTransmissora() {

  string mensagem;
  int codificacaoFisica = 0;
  cout << endl << "DIGITE UMA MENSAGEM: " << endl;
  getline(cin, mensagem);

  cout << endl
       << "ESCOLHA UM MODO DE CODIFICAÇÃO:" << endl
       << "0 - Binária" << endl
       << "1 - Manchester" << endl
       << "2 - Bipolar" << endl;
  cin >> codificacaoFisica;

  CamadaDeAplicacaoTransmissora(mensagem, codificacaoFisica);
}


void CamadaDeAplicacaoTransmissora(const string& mensagem, int codificacaoFisica) {
  
  vector<int> quadro = TransformaStringEmASCII(mensagem);
  CamadaFisicaTransmissora(quadro, codificacaoFisica);
}


vector<int> TransformaStringEmASCII(string mensagem) {

  vector<int> quadro;
  cout << endl << "MENSAGEM EM ASCII:" << endl;
  
  // Pega a mensagem inteira
  for (unsigned i = 0; i < mensagem.size(); i++) {  
    vector<int> tempQuadro;
    int charBi = int(mensagem.at(i));

    // 8 bits a cada letra
    for (unsigned j = 0; j < ASCII_MAX_BITS; j++) {  
      if (charBi % 2 == 0) {
        tempQuadro.push_back(0);
      } else {
        tempQuadro.push_back(1);
      }
      charBi = charBi >> 1;
    }

    cout << mensagem.at(i) << " - ";

    for (int k = ASCII_MAX_BITS - 1; k >= 0; k--) {
      // Adiciona a letra ao vetor maior
      quadro.push_back(tempQuadro.at(k));  
      cout << tempQuadro.at(k);
    }
    cout << endl;
  }

  // Retorna o quadro
  return quadro;
}


void CamadaDeAplicacaoReceptora(const vector<int>& quadro) {
  string mensagem = TransformaASCIIEmString(quadro);
  AplicacaoReceptora(mensagem);
}


string TransformaASCIIEmString(vector<int> quadro) {
  string mensagem = "";
  int intChar = 0;

  // Pega a mensagem inteira
  for (unsigned i = 0; i < quadro.size(); i++) {
    if (i != 0 && i % ASCII_MAX_BITS == 0) {
      // Adiciona cada letra
      mensagem.append(1, char(intChar));  
      intChar = 0;
    }
    intChar = intChar << 1;   // Forma cada letra
    intChar += quadro.at(i);  // adicionando o int e shiftando para esquerda
  }
  
  // Adiciona última letra (ficou pra trás)
  mensagem.append(1, char(intChar));  
  return mensagem;
}


void AplicacaoReceptora(const string& mensagem) {
  cout << endl << "MENSAGEM RECEBIDA: " << mensagem << endl << endl;
}
