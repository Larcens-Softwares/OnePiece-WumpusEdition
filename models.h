#include <string>
using namespace std;

class GrandLine {
private:
    // cenario
public:
    GrandLine ();
    ~GrandLine ();
};

enum tipo_elemento{pirata,marinha,espaco_vazio,obstaculo,one_piece};
enum movimento{up,down,left,right};

class Elemento {
private:
    string nome;
    tipo_elemento tipo;
public:
    Elemento ();
    ~Elemento ();
};

class Pessoa: public Elemento {
private:
    int hp;
public:
    Pessoa ();
    ~Pessoa ();
};

class OnePiece : public Elemento{
private:
    float peso;
public:
    OnePiece ();
    ~OnePiece ();
};

class Pirata: public Pessoa {
private:
    float peso;
    float peso_add; // => 0
public:
    Pirata ();
    ~Pirata ();
};

class Marinha: public Pessoa {
private:
    bool estado;
public:
    Marinha  ();
    ~Marinha  ();
};
