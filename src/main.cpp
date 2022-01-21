#include <iostream>
#include <fstream>
#include <vector>
#include "services/notion.hpp"

using namespace std;


void checkFile( ifstream& entrada, string message ) {
  if ( entrada.eof() ) {
    throw runtime_error( "\n\t[ARQUIVO DE ENTRADA]: " + message );
  }
}

int main() {
  try {
    string repository;
    string pr;
    ifstream entrada( "../entradas/entrada.in" );

    if ( !entrada.is_open() ) {
      string format = "\n\t    Linha 1: NOME DO ARQUIVO CSV";
      format += "\n\t    Linha 2: CARD";
      format += "\n\t    Linha 3: AMBIENTE";
      format += "\n\t    Linha 4: ARQUIVO DE SAÍDA (SOMENTE O NOME, SEM O DIRETORIO)";
      string errorMessage = "\n\t[ARQUIVO_DE_ENTRADA]: Pf crie o arquivo de entrada \"entrada.in\"";
      string formatDescription = "\nSeguindo esta formatação: ";
      throw runtime_error( errorMessage + formatDescription + format );
    }


    string arquivo_csv;
    checkFile( entrada, "Arquivo CSV é obrigatório" );
    getline( entrada, arquivo_csv );
    cout << "Arquivo de entrada: " << arquivo_csv << endl;


    string card;
    checkFile( entrada, "Card é obrigatório" );
    getline( entrada, card );
    cout << "Card: " << card << endl;


    string ambiente;
    checkFile( entrada, "Ambiente é obrigatório" );
    getline( entrada, ambiente );
    cout << "Ambiente: " << ambiente << endl << endl;

    string arquivoSaida;
    checkFile( entrada, "Arquivo de Saida é obrigatório" );
    getline( entrada, arquivoSaida );
    cout << "Arquivo de Saida: " << arquivoSaida << endl << endl;

    string pathSaida = "../responses/" + arquivoSaida;
    ofstream out( pathSaida.c_str() );

    NotionParse notion;
    MyAmbiente myAmbiente = notion.parseNotionCSV( ambiente, arquivo_csv );

    string all = "";

    for ( int i = 0; i < myAmbiente.objects.size(); i++ ) {
      PrObject prObject = myAmbiente.objects.at( i );
      string discord = "[" + myAmbiente.tag + "] ";
      discord += myAmbiente.prefix + card + " (" + prObject.name + ")\n";
      discord += prObject.link + "\n";
      discord += myAmbiente.aproves + "\n";
      all += discord + "\n";
    }
    cout << "PRS:\n" << all;
    out << all;
    out.close();
  }
  catch ( runtime_error& error ) {
    cout << "ERROR: " << error.what() << endl;
  }

  return 0;
}