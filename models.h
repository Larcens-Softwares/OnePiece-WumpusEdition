#include <string>
#include <vector>
using namespace std;

class GrandLine {
    private:
        vector<vector<Elemento>> cenario;
    public:
        GrandLine(vector<vector<Elemento>> cenar);
        ~GrandLine();
        void set_grand_line(vector<vector<Elemento>> cenar);
        vector<vector<Elemento>> get_grand_line();
};

enum TipoElemento{Pirata,Marinha,EspacoVazio,Obstaculo,OnePiece};
enum Movimento{up = 1,down,left,right};

class Elemento { // abstrata
    private:
        string nome;
        TipoElemento tipo;
    public:
        Elemento(string nome, TipoElemento tipo);
        ~Elemento();
        virtual void set_tipo_elemento(TipoElemento tipo) = 0;
        virtual TipoElemento get_tipo_elemento() = 0;

        virtual void set_nome_elemento(string nome) = 0;
        virtual string get_nome_elemento() = 0;
};


class Pessoa: public Elemento { // abstrata
    private:
        int hp;
    public:
        Pessoa(int hp);
        ~Pessoa();
        virtual void set_hp(int hp) = 0;
        virtual int get_hp() = 0;
};

// RAMBOX ROBLOX
class OnePiece : public Elemento{
    private:
        float peso;
    public:
        OnePiece(float peso);
        ~OnePiece();
        void set_peso(float peso);
        float get_peso();
};

class Pirata: public Pessoa {
    private:
        float peso;
        float peso_adicional; // => 0
    public:
        Pirata(float peso);
        ~Pirata();
        void set_peso_adicional(float peso_adicional);
        float get_peso_adicional();

        void set_peso(float peso);
        float get_peso();
};

class Marinha: public Pessoa {
    private:
        bool estado;
    public:
        Marinha(bool estado);
        ~Marinha();
        void set_estado(bool estado);
        bool get_estado();
};
