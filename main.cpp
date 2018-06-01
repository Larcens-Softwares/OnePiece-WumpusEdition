#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;


class Elemento{
private:
	friend class Pessoa;
	friend class Pirata;
	friend class Marinha;
	friend class OnePiece;
	friend class GrandLine;
	friend class Obstaculo;
	string nome;
	string tipo;
public:
	Elemento(string name, string type){ // ERRO
		nome = name;
		tipo = type;
	}
	virtual string GetNome();
	virtual string GetTipo();
	virtual void SetNome(string name);
	virtual void SetTipo(string type);
	~Elemento(){}
};

class GrandLine {
private:
	vector<vector<Elemento>> cenario;
	int n;
public:
	void inicializar(int n, vector<vector<Elemento>> cenario){
		int aux = 0, aux2 = 0;

		//Gerando espaços vazios
		for (auto a : cenario) {
			for (auto b : cenario.at(aux)) {
				if (b.GetNome() != "Jo" && b.GetNome() != "Te" &&
					b.GetNome() != "Pe" && b.GetNome() != "In") {
					b.SetNome("~~");
					b.SetTipo("~~");
					cenario.at(aux).at(aux2) = b;
				}
				aux2++;
			}
			aux2 = 0;
			aux++;
		}

		// Gerando Elementos
		for (auto linha : cenario) {
			for (auto coluna : cenario.at(aux)) {
				cout << coluna.GetNome() << coluna.GetTipo() << "\t";
				cout << " ";
			}
			cout << endl;
			aux++;
		}
	}
	vector<vector<Elemento>> GetCenario(){
		return cenario;
	}

	//método para inicialização do cenario variavel n para o tamanho

	// GrandLine(vector<vector<Elemento>> _cenario){
	//	INICIAR GRANDLINE AQUI
	// }
	// ~GrandLine();
};

class Obstaculo : public Elemento{
public:
	Obstaculo(string name, string type) : Elemento(name,type){}
	string GetNome(){
		return nome;
	}

	string GetTipo() {
		return tipo;
	}

	void SetNome(string name) {
		nome = name;
	}
	void SetTipo(string type) {
		tipo = type;
	}
	~Obstaculo(){}
};

class Pessoa : public Elemento {
private:
	friend class Pirata;
	friend class Marinha;
	int hp;
public:
	virtual void SetVida(int vida) = 0;

	virtual int GetVida() = 0;

	Pessoa(int vida, string name, string type): Elemento(name, type) { // tipo e TipoElemento e nao string(ALTERAR)
		hp = vida;
	}
};

class Pirata : public Pessoa {
private:
	int peso;
	int pesoAdicional;
public:
	Pirata(int weight, int vida, string name, string type) : Pessoa(vida, name, type) {
		peso = weight;
		pesoAdicional = 0;
	}
	void SetVida(int vida) {
		hp = vida;
	}
	int GetVida() {
		return hp;
	}
	void SetPeso(int weight) {
		peso = weight;
	}
	void SetPesoAdd(int weightAdd) {
		pesoAdicional += weightAdd;
	}
	int GetPeso() {
		return peso;
	}
	int GetPesoAdd() {
		return pesoAdicional;
	}
	string GetNome() {
		return nome;
	}

	string GetTipo() {
		return tipo;
	}

	void SetNome(string name) {
		nome = name;
	}
	void SetTipo(string type) {
		tipo = type;
	}
};

class Marinha : public Pessoa {
private:
	bool estado;
public:

	Marinha(bool state, int vida, string name, string type)	: Pessoa(vida, name, type) {
		estado = state;
	}

	void SetEstado(bool state) {
		estado = state;
	}
	void SetVida(int vida) {
		hp = vida;
	}
	int GetVida() {
		return hp;
	}
	bool GetEstado() {
		return estado;
	}
	string GetNome() {
		return nome;
	}

	string GetTipo() {
		return tipo;
	}

	void SetNome(string name) {
		nome = name;
	}
	void SetTipo(string type) {
		tipo = type;
	}

};

class OnePiece : public Elemento {
private:
	int peso;
public:
	void SetPeso(int weight) {
		peso = weight;
	}
	int GetPeso() {
		return peso;
	}
	string GetNome() {
		return nome;
	}
	string GetTipo() {
		return tipo;
	}
	void SetNome(string name) {
		nome = name;
	}
	void SetTipo(string type) {
		tipo = type;
	}
	OnePiece(string name, string type, int weight) : Elemento(name, type) {
		peso = weight;
	}
};

void validando_inimigos(int tamanho,vector<vector<Elemento>> cenario,	int *pos) {
	int randNumLinha, randNumColuna;
	int var = 0;

	randNumLinha = rand() % (tamanho - 1) + 1;
	randNumColuna = rand() % (tamanho - 1) + 1;

	// verifica se Elemento random posicao[0][x] ou [x][0]
	while (var == 0) {
		if (randNumLinha == 0 or randNumColuna == 0) {
			randNumLinha = rand() % (tamanho - 1) + 1;
			randNumColuna = rand() % (tamanho - 1) + 1;
		} else {
			var = 1;
		}
	}

	// verifica se Elemento random posicao ao redor do OnePiece
	var = 0;
	while (var == 0) {
		if (randNumLinha == (tamanho - 1) and randNumColuna == (tamanho - 1)) {
			randNumLinha = rand() % (tamanho - 1) + 1;
			randNumColuna = rand() % (tamanho - 1) + 1;
		} else {
			var = 1;
		}
	}

	// verifica se Elemento posição em outro Elemento
	var = 0;
	while (var == 0) {
		if (cenario[randNumLinha][randNumColuna].GetNome() == "Pe" or
			cenario[randNumLinha][randNumColuna].GetNome() == "In") {
			randNumLinha = rand() % (tamanho - 1) + 1;
			randNumColuna = rand() % (tamanho - 1) + 1;
		} else {
			var = 1;
		}
	}

	// verifica Elemento proximo ao OnePiece
	while (var == 0) {
		if (randNumLinha == (tamanho - 2) or randNumColuna == (tamanho - 2)) {
			randNumLinha = rand() % (tamanho - 1) + 1;
			randNumColuna = rand() % (tamanho - 1) + 1;
		} else {
			var = 1;
		}
	}

	pos[0] = randNumLinha;
	pos[1] = randNumColuna;
}

int main(){

	enum Direction { up = 1, down, left, right };
	enum TipoElemento{pirata,marinha,espacoVazio,obstaculo,onePiece};
 	int tamanho,pos[2];// posição dos elementos

 	cout << "Qual o tamanho do cenario?" << endl;
 	cin >> tamanho;
	vector<vector<Elemento>> cenario(tamanho,vector<Elemento>(tamanho));  // vector cenario (n x n)
 	// int aux = 0, aux2 = 0, aux3 = 0; // preencher cenario com vazios

// Gerando novas seeds (rand);
 	srand(time(NULL));
//----------------------PIRATA-----------------------//

	Pirata player(20,5,"Jo","pi"); // weight, vida,name,type
	cenario.at(0).at(0).SetNome(player.GetNome());
	cenario.at(0).at(0).SetTipo(player.GetTipo());

//-----------------------ONE PIECE-------------------//

	OnePiece tesouro("Te","One",20); // nome, tipo , peso
	cenario.at(tamanho-1).at(tamanho-1).SetNome(tesouro.GetNome());
	cenario.at(tamanho-1).at(tamanho-1).SetTipo(tesouro.GetTipo());

//-----------------------OBSTACULOS----------------- //

	Obstaculo obst("Pe","Ob"); // name, type
	for(int pedra = 1; pedra <= (tamanho / 2); pedra++){
		validando_inimigos(tamanho, cenario, pos);
		cout << pos[0] << pos[1] << '\n';
		cenario[pos[0]][pos[1]] = obst;
	}
//----------------------- MARINHA ------------------//
	string ui_estado_marinha; // imprime estado
	Marinha mar(true, 5, "Ma", "In"); // state,vida,name,type
	validando_inimigos(tamanho,cenario,pos);
	cenario[pos[0]][pos[1]] = mar;
	ui_estado_marinha = mar.GetEstado()? "Marinha em alerta":"Marinha Dormindo";

	GrandLine cenar;
	cenar.inicializar(tamanho,cenario);

	// 	cout << mar.GetNome() << endl;
	// 	cout << mar.GetVida() << endl;
	// 	cout << mar.GetTipo() << endl;
	// 	cout << ui_estado_marinha << endl;


// 	objAux.SetNome("In");
// 	objAux.SetTipo("Ma");
// 	validando_inimigos(tamanho, cenario, pos);
// 	cout << pos[0] << pos[1] << '\n';
// 	cenario[pos[0]][pos[1]] = objAux;
//
// //---------------------ESPAÇOS VAZIOS--------------//
//
// 	for (auto a : cenario) {
// 		for (auto b : cenario.at(aux)) {
// 			if (b.GetNome() != "Jo" && b.GetNome() != "Te" &&
// 				b.GetNome() != "Pe" && b.GetNome() != "In") {
// 				b.SetNome("~~");
// 				b.SetTipo("~~");
// 				cenario.at(aux).at(aux2) = b;
// 			}
// 			aux2++;
// 		}
// 		aux2 = 0;
// 		aux++;
// 	}
// //----------------GERANDO CENARIO-----------------//
// 	aux = 0;
//
// 	for (auto linha : cenario) {
// 		for (auto coluna : cenario.at(aux)) {
// 			cout << coluna.GetNome() << coluna.GetTipo() << "\t";
// 			cout << " ";
// 		}
// 		cout << endl;
// 		aux++;
// 	}
// 	//----------MOVIMENTO----------------------------//
// 	Getchar();
// 	fflush(stdin);
// 	aux = 0;
// 	aux2 = 0;
// 	int control = 0;
// 	while (true) {
// 		Direction direction = Direction(rand() % 4 + 1);
// 		if (direction == up) {
// 			for (auto linha : cenario) {
// 				for (auto coluna : cenario.at(aux)) {
// 					if (cenario[aux][aux2].GetNome() == "Jo" and
// 						aux < (tamanho - 1) and control == 0) {
// 						if (cenario[aux + 1][aux2].GetNome() != "Pe" and
// 							cenario[aux + 1][aux2].GetNome() != "In") {
// 							cenario[aux][aux2].SetNome("~~");
// 							cenario[aux][aux2].SetTipo("~~");
// 							cenario[aux + 1][aux2].SetNome("Jo");
// 							cenario[aux + 1][aux2].SetTipo("Pi");
// 							for (auto linha : cenario) {
// 								for (auto coluna : cenario.at(aux3)) {
// 									cout << coluna.GetNome() << coluna.GetTipo()
// 										 << "\t";
// 									cout << " ";
// 								}
// 								cout << endl;
// 								aux3++;
// 							}
// 							aux3 = 0;
// 							control++;
// 							Getchar();
// 							system("CLS");
// 							system("clear");
// 						}
// 					}
// 					aux2++;
// 				}
// 				aux2 = 0;
// 				aux++;
// 			}
// 		} else if (direction == down) {
// 			for (auto linha : cenario) {
// 				for (auto coluna : cenario.at(aux)) {
// 					if (cenario[aux][aux2].GetNome() == "Jo" and aux > 0 and
// 						control == 0) {
// 						if (cenario[aux - 1][aux2].GetNome() != "Pe" and
// 							cenario[aux - 1][aux2].GetNome() != "In") {
// 							cenario[aux][aux2].SetNome("~~");
// 							cenario[aux][aux2].SetTipo("~~");
// 							cenario[aux - 1][aux2].SetNome("Jo");
// 							cenario[aux - 1][aux2].SetTipo("Pi");
// 							control++;
// 							for (auto linha : cenario) {
// 								for (auto coluna : cenario.at(aux3)) {
// 									cout << coluna.GetNome() << coluna.GetTipo()
// 										 << "\t";
// 									cout << " ";
// 								}
// 								cout << endl;
// 								aux3++;
// 							}
// 							aux3 = 0;
// 							Getchar();
// 							system("CLS");
// 							system("clear");
// 						}
// 					}
// 					aux2++;
// 				}
// 				aux2 = 0;
// 				aux++;
// 			}
// 		} else if (direction == left) {
// 			for (auto linha : cenario) {
// 				for (auto coluna : cenario.at(aux)) {
// 					if (cenario[aux][aux2].GetNome() == "Jo" and aux2 > 0 and
// 						control == 0) {
// 						if (cenario[aux][aux2 - 1].GetNome() != "Pe" and
// 							cenario[aux][aux2 - 1].GetNome() != "In") {
// 							cenario[aux][aux2].SetNome("~~");
// 							cenario[aux][aux2].SetTipo("~~");
// 							cenario[aux][aux2 - 1].SetNome("Jo");
// 							cenario[aux][aux2 - 1].SetTipo("Pi");
// 							for (auto linha : cenario) {
// 								for (auto coluna : cenario.at(aux3)) {
// 									cout << coluna.GetNome() << coluna.GetTipo()
// 										 << "\t";
// 									cout << " ";
// 								}
// 								cout << endl;
// 								aux3++;
// 							}
// 							aux3 = 0;
// 							control++;
// 							Getchar();
// 							system("CLS");
// 							system("clear");
// 						}
// 					}
// 					aux2++;
// 				}
// 				aux2 = 0;
// 				aux++;
// 			}
// 		} else if (direction == right) {
// 			for (auto linha : cenario) {
// 				for (auto coluna : cenario.at(aux)) {
// 					if (cenario[aux][aux2].GetNome() == "Jo" and
// 						aux2 < (tamanho - 1) and control == 0) {
// 						if (cenario[aux][aux2 + 1].GetNome() != "Pe" and
// 							cenario[aux][aux2 + 1].GetNome() != "In") {
// 							cenario[aux][aux2].SetNome("~~");
// 							cenario[aux][aux2].SetTipo("~~");
// 							cenario[aux][aux2 + 1].SetNome("Jo");
// 							cenario[aux][aux2 + 1].SetTipo("Pi");
// 							for (auto linha : cenario) {
// 								for (auto coluna : cenario.at(aux3)) {
// 									cout << coluna.GetNome() << coluna.GetTipo()
// 										 << "\t";
// 									cout << " ";
// 								}
// 								cout << endl;
// 								aux3++;
// 							}
// 							aux3 = 0;
// 							control++;
// 							Getchar();
//
// 							system("CLS");
// 							system("clear");
// 						}
// 					}
// 					aux2++;
// 				}
// 				aux2 = 0;
// 				aux++;
// 			}
// 		}
// 		aux = 0;
//
// 		control = 0;
// 		aux = 0;
// 		aux2 = 0;
// 		fflush(stdin);
// 	}
// 	return 0;
}
