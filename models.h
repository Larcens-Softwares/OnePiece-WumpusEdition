#include <string>
#include <vector>
using namespace std;

class GrandLine {
private:
    vector<vector<Elemento>> cenario;
public:
    GrandLine(vector<vector<Elemento>> cenar);
    ~GrandLine();
};

enum TipoElemento{Pirata,Marinha,EspacoVazio,Obstaculo,OnePiece};
enum Movimento{up,down,left,right};


// Classes Abstratas
class Elemento {
private:
    string nome;
    TipoElemento tipo;
public:
    Elemento();
    ~Elemento();
};

class Pessoa: public Elemento {
private:
    int hp;
public:
    Pessoa():Elemento();
    ~Pessoa();
};


// Classes herdeiras
class OnePiece : public Elemento{
private:
    float peso;
public:
    OnePiece();
    ~OnePiece();
};

class Pirata: public Pessoa {
private:
    float peso;
    float peso_add; // => 0
public:
    Pirata();
    ~Pirata();
};

class Marinha: public Pessoa {
private:
    bool estado;
public:
    Marinha();
    ~Marinha();
};
