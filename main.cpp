#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum TipoElemento{pirata,marinha,espacoVazio,obstaculo,onePiece};

class Elemento{
private:
	string nome;
	TipoElemento tipo;
public:
   Elemento(string nome, TipoElemento tipo){
		this->nome = nome;
		this->tipo = tipo;
	}
   Elemento(){}
	 string GetNome(){
		 return nome;
	 }
	 TipoElemento GetTipo(){
		 return tipo;
	 }
	 void SetNome(string name){
		 	nome = name;
	}
	 void SetTipo(TipoElemento type){
		 tipo = type;
	 }
//	~Elemento(){}
};

class GrandLine {
private:
	int n;
public:
	void inicializar(vector<vector<Elemento>> cenario){
		int aux = 0;

		for (auto linha : cenario) {
			for (auto coluna : cenario.at(aux)) {
				cout << coluna.GetNome();
				cout << " ";
			}
			cout << endl;
			aux++;
		}
	}
	int GetCenario(){
		return n;
	}
	void SetCenario(int tamanho){
		n = tamanho;
	}
	//método para inicialização do cenario variavel n para o tamanho

	// GrandLine(vector<vector<Elemento>> _cenario){
	//	INICIAR GRANDLINE AQUI
	// }
	// ~GrandLine();
};

class Pessoa : public Elemento {
private:
	int hp;
public:

	Pessoa(int vida, string name, TipoElemento type): Elemento(name, type) { // tipo e TipoElemento e nao string(ALTERAR)
		hp = vida;
	}
	void SetVida(int vida){
		hp = vida;
	}
	int GetVida(){
		return hp;
	}
};

class Pirata : public Pessoa {
private:
	int peso;
	int pesoAdicional;
public:
	Pirata(int weight, int vida, string name, TipoElemento type) : Pessoa(vida, name, type) {
		peso = weight;
		pesoAdicional = 0;
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
};

class Marinha : public Pessoa {
private:
	bool estado;
public:

	Marinha(bool state, int vida, string name, TipoElemento type)	: Pessoa(vida, name, type) {
		estado = state;
	}

	void SetEstado(bool state) {
		estado = state;
	}
	bool GetEstado() {
		return estado;
	}
};

class OnePiece : public Elemento {
private:
	int peso;
public:
	OnePiece(string name, TipoElemento type, int weight) : Elemento(name, type) {
		peso = weight;
	}
	void SetPeso(int weight) {
		peso = weight;
	}
	int GetPeso() {
		return peso;
	}
};

void validando_spawn(int tamanho,vector<vector<Elemento>> cenario,	int *pos) {
	int randNumLinha, randNumColuna;
	bool validando = true;

	randNumLinha = rand() % (tamanho - 1) + 1;
	randNumColuna = rand() % (tamanho - 1) + 1;

	cout << "\t > Tentativa spawn : " << endl;
	while(validando == true){

		if(randNumLinha != 0 or randNumColuna != 0){
			cout << "\t\t Fail : Linha ou coluna [0]: " << randNumLinha << "," << randNumColuna << endl;

			if(randNumLinha != (tamanho - 1) or randNumColuna != (tamanho - 1)){
				cout << "\t\t Fail : Spawn no OnePiece [F]: " << randNumLinha << "," << randNumColuna << endl;

				if(cenario[randNumLinha][randNumColuna].GetNome() != "Pe" and cenario[randNumLinha][randNumColuna].GetNome() != "Ma"){
					cout << "\t\t Fail : Spawn em outros Elementos [F]: " << randNumLinha << "," << randNumColuna << endl;

					if(randNumLinha != (tamanho - 2) or randNumColuna != (tamanho - 2)){
						cout << "\t\t Fail : Proximidade do OnePiece: " << randNumLinha << "," << randNumColuna << endl;

						if((randNumLinha == (tamanho-1) and randNumColuna == (tamanho-2)) and
							(cenario[tamanho-2][tamanho-1].GetNome() == "Pe") ){
								cout << "\t\t Fail : Bloqueio de passagem [F]: " << randNumLinha << "," << randNumColuna << endl;
								validando = true; // volta ao loop
						}else if((randNumLinha == (tamanho-2) and randNumColuna == (tamanho-1)) and
							(cenario[tamanho-1][tamanho-2].GetNome() == "Pe")){
								cout << "\t\t Fail : Bloqueio de passagem [F]: " << randNumLinha << "," << randNumColuna << endl;
								validando = true; // volta ao loop
						}else{
							validando = false; // encerra requisitos de spawn
						}
					}
				}
			}
		}
		if(validando == true){
			randNumLinha = rand() % (tamanho - 1) + 1;
			randNumColuna = rand() % (tamanho - 1) + 1;
		}
	}

		pos[0] = randNumLinha;
		pos[1] = randNumColuna;
		cout << "\t\t Sucessfull : Posicao sorteada : " << pos[0] << "," << pos[1] << endl;

}
void init_player(){
	cout << "\n────────────────────────────────────────" << endl;
	cout << "─────────────▄▄██████████▄▄─────────────" << endl;
	cout << "─────────────▀▀▀───██───▀▀▀─────────────" << endl;
	cout << "─────▄██▄───▄▄████████████▄▄───▄██▄─────" << endl;
	cout << "───▄███▀──▄████▀▀▀────▀▀▀████▄──▀███▄───" << endl;
	cout << "──████▄─▄███▀──────────────▀███▄─▄████──" << endl;
	cout << "─███▀█████▀▄████▄──────▄████▄▀█████▀███─" << endl;
	cout << "─██▀──███▀─██████──────██████─▀███──▀██─" << endl;
	cout << "──▀──▄██▀──▀████▀──▄▄──▀████▀──▀██▄──▀──" << endl;
	cout << "─────███───────────▀▀───────────███─────" << endl;
	cout << "─────██████████████████████████████─────" << endl;
	cout << "─▄█──▀██──███───██────██───███──██▀──█▄─" << endl;
	cout << "─███──███─███───██────██───███▄███──███─" << endl;
	cout << "─▀██▄████████───██────██───████████▄██▀─" << endl;
	cout << "──▀███▀─▀████───██────██───████▀─▀███▀──" << endl;
	cout << "───▀███▄──▀███████────███████▀──▄███▀───" << endl;
	cout << "─────▀███────▀▀██████████▀▀▀───███▀─────" << endl;
	cout << "───────▀─────▄▄▄───██───▄▄▄─────▀───────" << endl;
	cout << "──────────── ▀▀██████████▀▀─────────────" << endl;
	cout << "────────────────────────────────────────" << endl;

	cout << "\n ______   .__   __.  _______    .______    __   _______   ______  _______    " << endl;
	cout << "/  __  \\  |  \\ |  | |   ____|   |   _  \\  |  | |   ____| /      ||   ____|   " << endl;
	cout << "|  |  | | |   \\|  | |  |__      |  |_)  | |  | |  |__   |  ,----'|  |__      " << endl;
	cout << "|  |  | | |  . `  | |   __|     |   ___/  |  | |   __|  |  |     |   __|     " << endl;
	cout << "|  `--' | |  |\\   | |  |____    |  |      |  | |  |____ |  `----.|  |____    " << endl;
	cout << "\\______/  |__| \\__| |_______|   | _|      |__| |_______| \\______||_______|   " << endl;
	getchar();
	system("CLS");
	system("clear");
}

int main(){
	system("CLS");
	system("clear");
	init_player();

	enum Direction { up = 1, down, left, right };
 	int tamanho,pos[2];// posição dos elementos
	char TamCen[256];

 	cout << " -- Selecione um nivel --" << endl;
	cout << "\t > NIVEL 4  - - - - 4" << endl; // 4
	cout << "\t > NIVEL 5  - - - - 5" << endl; // 5
	cout << "\t > NIVEL 6  - - - - 6" << endl; // 6
	cout << "\t > NIVEL 7  - - - - 7" << endl; // 7
	cout << "\t > SAIR  - - - - -  8" << endl; // EXIT
	cout << "\t > Digite o numero: ";

	cin >> TamCen; cout << "\n";
	tamanho = atoi(TamCen);
	if(tamanho == 8){
		return 0;
	}
	while(tamanho > 7 or tamanho < 4){
		cout << "\t\t -------- NIVEL INVALIDO!!!" << endl;
		cout << " \n-- Selecione um nivel --" << endl;
 		cin >> TamCen;
		tamanho = atoi(TamCen);
	}

	vector< vector<Elemento> > cenario(tamanho,vector<Elemento>(tamanho));  // vector cenario (n x n)
 	int aux = 0, aux2 = 0, aux3 = 0;

// Gerando novas seeds (rand);
 	srand(time(NULL));
//----------------------PIRATA-----------------------//

	Pirata player(70,5,"Jo",pirata); // weight,vida,name,type
	cenario.at(0).at(0).SetNome(player.GetNome());
	cenario.at(0).at(0).SetTipo(player.GetTipo());

//-----------------------ONE PIECE-------------------//

	OnePiece tesouro("Te",onePiece,300); // nome, tipo , peso
	cenario.at(tamanho-1).at(tamanho-1).SetNome(tesouro.GetNome());
	cenario.at(tamanho-1).at(tamanho-1).SetTipo(tesouro.GetTipo());

//-----------------------OBSTACULOS----------------- //
cout << "\n\t------------ Desenvolvedor debug ------------" << '\n';

	Elemento obst("Pe",obstaculo); // name, type
	for(int pedra = 1; pedra <= (tamanho / 2); pedra++){
		validando_spawn(tamanho, cenario, pos);
		cenario.at(pos[0]).at(pos[1]).SetNome(obst.GetNome());
		cenario.at(pos[0]).at(pos[1]).SetTipo(obst.GetTipo());
	}
//----------------------- MARINHA ------------------//
	string ui_estado_marinha; // imprime estado
	Marinha mar(false, 5, "Ma", marinha); // state,vida,name,type
	validando_spawn(tamanho,cenario,pos);
	cenario.at(pos[0]).at(pos[1]).SetNome(mar.GetNome());
	cenario.at(pos[0]).at(pos[1]).SetTipo(mar.GetTipo());
	ui_estado_marinha = mar.GetEstado()? "Marinha em alerta":"Marinha Dormindo";

//---------------------ESPAÇOS VAZIOS--------------//
 	for (auto a : cenario) {
		for (auto b : cenario.at(aux)) {
			if (b.GetNome() != "Jo" && b.GetNome() != "Te" && b.GetNome() != "Pe" && b.GetNome() != "Ma") {
				b.SetNome("~~");
 				b.SetTipo(espacoVazio);
				cenario.at(aux).at(aux2) = b;
			}
 			aux2++;
 		}
 		aux2 = 0;
 		aux++;
 	}

//----------------GERANDO CENARIO-----------------//

	GrandLine cenar;
	cenar.inicializar(cenario);

//----------MOVIMENTO----------------------------//
	getchar();
	getchar();
	system("clear");
	fflush(stdin);
	aux = 0;
	aux2 = 0;
	int control = 0;
	while (true) {
		Direction direction = Direction(rand() % 4 + 1);
		if (direction == up) {
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and aux > 0 and control == 0) {
						if (cenario[aux - 1][aux2].GetNome() != "Pe" and cenario[aux - 1][aux2].GetNome() != "Ma") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							// proxima posição
							cenario.at(aux - 1).at(aux2).SetNome(player.GetNome());
							cenario.at(aux - 1).at(aux2).SetTipo(player.GetTipo());
							
							cenar.inicializar(cenario);
							control++;
							getchar();
							system("CLS");
							system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (direction == down) {
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and aux < (tamanho - 1) and control == 0) {
						if (cenario[aux + 1][aux2].GetNome() != "Pe" and cenario[aux + 1][aux2].GetNome() != "Ma") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							// proxima posição
							cenario.at(aux + 1).at(aux2).SetNome(player.GetNome());
							cenario.at(aux + 1).at(aux2).SetTipo(player.GetTipo());
							
							cenar.inicializar(cenario);
							control++;
							getchar();
							system("CLS");
							system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (direction == left) {
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and aux2 > 0 and control == 0) {
						if (cenario[aux][aux2 - 1].GetNome() != "Pe" and cenario[aux][aux2 - 1].GetNome() != "Ma") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(obstaculo);
							// proxima posição
							cenario.at(aux).at(aux2 - 1).SetNome(player.GetNome());
							cenario.at(aux).at(aux2 - 1).SetTipo(player.GetTipo());
							
							cenar.inicializar(cenario);
							control++;
							getchar();
							system("CLS");
							system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (direction == right) {
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and
						aux2 < (tamanho - 1) and control == 0) {
						if (cenario[aux][aux2 + 1].GetNome() != "Pe" and cenario[aux][aux2 + 1].GetNome() != "Ma") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(obstaculo);
							// proxima posição
							cenario.at(aux).at(aux2 + 1).SetNome(player.GetNome());
							cenario.at(aux).at(aux2 + 1).SetTipo(player.GetTipo());
							
							cenar.inicializar(cenario);
							control++;
							getchar();

							system("CLS");
							system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		}
		aux = 0;

		control = 0;
		aux = 0;
		aux2 = 0;
		fflush(stdin);
	}
	return 0;
}
