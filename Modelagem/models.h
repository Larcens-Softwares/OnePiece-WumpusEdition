using namespace std;
#include <iostream>
#include <string>
#include "main2.cpp"

class Elemento{
 private:
	string nome;
	TipoElemento tipo;
 public:
   	Elemento(string nome, TipoElemento tipo);
   	Elemento();
	string GetNome();
	TipoElemento GetTipo();
	void SetNome(string name);
	void SetTipo(TipoElemento type);
	~Elemento();
};

class Pessoa : public Elemento {
 private:
	int hp;
 public:
	Pessoa(int vida, string name, TipoElemento type): Elemento(name, type);
	void SetVida(int vida);
	int GetVida();

};

class Pirata : public Pessoa {
 private:
	int peso;
	int pesoAdicional;
 public:
	Pirata(int weight, int vida, string name, TipoElemento type) : Pessoa(vida, name, type);
	void SetPeso(int weight);
	void SetPesoAdd(int weightAdd);
	void SetPesoRed(int weightAdd);
	int GetPeso();
	int GetPesoAdd();
	int IdentificarTesouro (vector<vector<Elemento>> cenario, int tamanho);
	
};

class Marinha : public Pessoa {
 private:
	bool estado;
 public:
	Marinha(bool state, int vida, string name, TipoElemento type)	: Pessoa(vida, name, type);
	void SetEstado(bool state);
	bool GetEstado();
};

class OnePiece : public Elemento {
 private:
	int peso;
 public:
	OnePiece(string name, TipoElemento type, int weight) : Elemento(name, type);
	void SetPeso(int weight);
	int GetPeso();
};

void validando_spawn(int tamanho,vector<vector<Elemento>> cenario,int  *pos);
vector<vector<Elemento>> move_marinha(vector<vector<Elemento>> cenario, Marinha mar,int tamanho,string move);
vector<vector<Elemento>> MoverPirata(vector<vector<Elemento>> cenario, int tamanho, Pirata *player, Marinha mar, int *rodadas_marinha, int *proxima_rodada);


class GrandLine {
private:
	int n;
public:
    vector<vector<Elemento>> inicializar(int tamanho, vector<vector<Elemento>> cenario,Pirata player, Marinha mar, Elemento obst, OnePiece tesouro);
	int GetCenario();
	void SetCenario(int tamanho);
	void ImprimirCenario(vector<vector<Elemento>> cenario, Pirata player);
};


void menu_player();
void game_over();
void you_win();
