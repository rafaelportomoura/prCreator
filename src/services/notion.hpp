#include <iostream>
#include <fstream>
#include <vector>
#include "strings.hpp"

using namespace std;

struct PrObject {
  string link;
  string name;
  string status;
};

struct MyAmbiente {
  vector<PrObject> objects;
  string prefix;
  string tag;
  string aproves;
  string pr_collum_name;
  int detailsForDiscord[3];
};

enum { TAG, PREFIX, APROVES, NAME, PR, STATUS, PR_COLLUM_NAME };
enum { AMBIENTE_NAME, AMBIENTE_PR, AMBIENTE_STATUS };

class NotionParse {
  private:
  StringsClass myStringClass;
  ifstream leitura;

  public:
  NotionParse() {};

  MyAmbiente getAmbienteDetails( string ambiente ) {
    MyAmbiente myAmbiente;
    leitura.open( "database/ambientes.csv" );
    if ( leitura.fail() ) {
      throw runtime_error( "[GET AMBIENT DETAILS]: Arquivo de database faltando" );
    }
    string line;
    getline( leitura, line );
    vector<string> properties;
    bool finded = false;
    while ( !leitura.eof() && !finded ) {
      getline( leitura, line );
      properties = myStringClass.split( line, ',', 0 );
      if ( properties.at( TAG ) == ambiente ) {
        myAmbiente.tag = properties.at( TAG );
        myAmbiente.prefix = properties.at( PREFIX );
        myAmbiente.aproves = properties.at( APROVES );
        myAmbiente.pr_collum_name = properties.at( PR_COLLUM_NAME );
        myAmbiente.detailsForDiscord[AMBIENTE_NAME] = stoi( properties.at( NAME ) );
        myAmbiente.detailsForDiscord[AMBIENTE_PR] = stoi( properties.at( PR ) );
        myAmbiente.detailsForDiscord[AMBIENTE_STATUS] = stoi( properties.at( STATUS ) );
        finded = true;
      }
    }
    leitura.close();
    return myAmbiente;
  }


  MyAmbiente parseNotionCSV( string ambiente, string arquivo ) {
    MyAmbiente myAmbiente = getAmbienteDetails( ambiente );
    string line;
    string path = "../files/" + arquivo;
    ifstream csv( path.c_str() );
    if ( !csv.is_open() ) {
      throw runtime_error( "[CSV]: POR FAVOR INSIRA UM ARQUIVO CSV VÁLIDO" );
    }
    getline( csv, line );
    vector<string> myStrings;

    while ( !csv.eof() ) {
      getline( csv, line );
      myStrings = myStringClass.split( line, ',', 0 );

      string ambientePrCollumnName = myAmbiente.pr_collum_name;
      string pr_status = myStrings.at( myAmbiente.detailsForDiscord[AMBIENTE_STATUS] );

      if ( myStringClass.findString( ambientePrCollumnName, pr_status ) ) {
        PrObject prObject;
        prObject.link = myStrings.at( myAmbiente.detailsForDiscord[AMBIENTE_PR] );
        prObject.name = myStrings.at( myAmbiente.detailsForDiscord[AMBIENTE_NAME] );
        prObject.status = pr_status;
        myAmbiente.objects.push_back( prObject );
      }
    }
    csv.close();
    return myAmbiente;
  }

};
