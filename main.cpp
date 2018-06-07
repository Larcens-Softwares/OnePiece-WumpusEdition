
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

class Pessoa : public Elemento {
 private:
	int hp;
 public:
	 void SetVida(int vida){
		 hp = vida;
	 }
	 int GetVida(){
		 return hp;
	 }

	Pessoa(int vida, string name, TipoElemento type): Elemento(name, type) { // tipo e TipoElemento e nao string(ALTERAR)
		hp = vida;
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
		if(peso < pesoAdicional){
		pesoAdicional += weightAdd;
		}else{
			cout << "Não é possível carregar mais One Piece." << endl;
		}
	}
	int GetPeso() {
		return peso;
	}
	int GetPesoAdd() {
		return pesoAdicional;
	}
	
	int IdentificarTesouro (vector<vector<Elemento>> cenario, int tamanho){
		if (cenario.at(tamanho-1).at(tamanho-3).GetNome() == "Jo"){
			if(cenario.at(tamanho-1).at(tamanho-2).GetNome() != "Pe"){	
				if (cenario.at(tamanho-1).at(tamanho-2).GetNome() != "Ma"){
					return 0;
				}
			}	
		}


		if (cenario.at(tamanho-3).at(tamanho-1).GetNome() == "Jo") {
			if (cenario.at(tamanho-2).at(tamanho-1).GetNome() != "Pe"){
				if (cenario.at(tamanho-1).at(tamanho-2).GetNome() != "Ma"){
					return 0;
				}
			}
		}
		
		if (cenario.at(tamanho-1).at(tamanho-2).GetNome() == "Jo" or cenario.at(tamanho-2).at(tamanho-1).GetNome() == "Jo"){
			return 0;
		}

		return 1;
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
		peso -= weight;
	}
	int GetPeso() {
		return peso;
	}
};

void validando_spawn(int tamanho,vector<vector<Elemento>> cenario,int  *pos) {
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

vector<vector<Elemento>> move_marinha(vector<vector<Elemento>> cenario, Marinha mar,int tamanho,string move){
	int control = 0;
	int aux = 0, aux2 = 0;
	
	cout << " Marinha: ";		
	if (move == "down") {
			cout << "up ↑";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Ma" and aux > 0 and control == 0) {
						if (cenario[aux - 1][aux2].GetNome() != "Pe" and cenario[aux - 1][aux2].GetNome()!= "Jo" and cenario[aux - 1][aux2].GetNome() != "Te") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							// proxima posição
							cenario.at(aux - 1).at(aux2).SetNome(mar.GetNome());
							cenario.at(aux - 1).at(aux2).SetTipo(mar.GetTipo());
							
							control++;
							// getchar();
							// system("CLS");
							// system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (move == "up") {
			cout << "down ↓ ";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Ma" and aux < (tamanho - 1) and control == 0) {
						if (cenario[aux + 1][aux2].GetNome() != "Pe" and cenario[aux + 1][aux2].GetNome()!= "Jo" and 
							cenario[aux + 1][aux2].GetNome() != "Te") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							// proxima posição
							cenario.at(aux + 1).at(aux2).SetNome(mar.GetNome());
							cenario.at(aux + 1).at(aux2).SetTipo(mar.GetTipo());

							// cenar.inicializar(cenario);
							control++;
							// getchar();
							// system("CLS");
							// system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (move == "right") {
			cout << "left ← ";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Ma" and aux2 > 0 and control == 0) {
						if (cenario[aux][aux2 - 1].GetNome() != "Pe" and cenario[aux][aux2 - 1].GetNome()!= "Jo"){
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							// proxima posição
							cenario.at(aux).at(aux2 - 1).SetNome(mar.GetNome());
							cenario.at(aux).at(aux2 - 1).SetTipo(mar.GetTipo());
							
							// cenar.inicializar(cenario);
							control++;
							// getchar();
							// system("CLS");
							// system("clear");
						}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (move == "left") {
			cout << "right → ";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Ma" and aux2 < (tamanho - 1) and control == 0) {
						if (cenario[aux][aux2 + 1].GetNome() != "Pe" and cenario[aux][aux2 + 1].GetNome()!= "Jo" and 
							cenario[aux][aux2 + 1].GetNome() != "Te") {
							// espaço vazio ao sair
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							// proxima posição
							cenario.at(aux).at(aux2 + 1).SetNome(mar.GetNome());
							cenario.at(aux).at(aux2 + 1).SetTipo(mar.GetTipo());
							
							// cenar.inicializar(cenario);
							control++;
							// getchar();

							// system("CLS");
							// system("clear");
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
		aux2 = 0;
		fflush(stdin);
		return cenario;
}

vector<vector<Elemento>> MoverPirata(vector<vector<Elemento>> cenario, int tamanho, Pirata player, Marinha mar){
	int aux = 0, aux2 = 0, control = 0;
	int rodadas_marinha = 0;	
	
	enum Direction { up = 1, down, left, right };
	Direction direction = Direction(rand() % 4 + 1);

		cout << "Luffy: ";

		if (direction == up) {
			string move = "up";
			cout << "up ↑  " ;
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and  aux > 0 and control == 0) {
						
						// Caso movimento colide com obstaculos
		 				if(cenario[aux - 1][aux2].GetNome() == "Pe" and cenario[aux - 1][aux2].GetNome() != "Ma"){
		 					mar.SetEstado(true);
		 					cenario = move_marinha(cenario,mar,tamanho,move);
		 					rodadas_marinha += 1;
		 				}

						if (cenario[aux - 1][aux2].GetNome() != "Pe" and cenario[aux - 1][aux2].GetNome() != "Ma") {
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							cenario.at(aux - 1).at(aux2).SetNome(player.GetNome());
							cenario.at(aux - 1).at(aux2).SetTipo(player.GetTipo());
							control++;
						
		 				}else if(cenario[aux - 1][aux2].GetNome() == "Ma"){
		 					cout << "entrei" << endl;
		 					int vida = player.GetVida();
		 					cout << vida << endl;
		 					vida--;
		 					cout << vida << endl;
		 					player.SetVida(vida);
		 					cout << player.GetVida() << endl;
		 				}

					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (direction == down) {
			string move = "down";
			cout << "down ↓  ";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and  aux < (tamanho - 1)  and control == 0) {
						
						// Caso movimento colide com obstaculos
		 				if(cenario[aux + 1][aux2].GetNome() == "Pe" and cenario[aux + 1][aux2].GetNome() != "Ma"){
		 					mar.SetEstado(true);
		 					cenario = move_marinha(cenario,mar,tamanho,move);
		 					rodadas_marinha += 1;
		 				}

						if (cenario[aux + 1][aux2].GetNome() != "Pe" and cenario[aux + 1][aux2].GetNome() != "Ma") {
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							cenario.at(aux + 1).at(aux2).SetNome(player.GetNome());
							cenario.at(aux + 1).at(aux2).SetTipo(player.GetTipo());
							control++;
						
						}else if(cenario[aux + 1][aux2].GetNome() == "Ma"){
		 					cout << "entrei" << endl;
		 					int vida = player.GetVida();
		 					cout << vida << endl;
		 					vida--;
		 					cout << vida << endl;
		 					player.SetVida(vida);
		 					cout << player.GetVida() << endl;
		 				}

					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (direction == left) {
			string move = "left";
			cout << "left ←  ";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and aux2 > 0 and control == 0) {
						
						// Caso movimento colide com obstaculos
		 				if(cenario[aux][aux2 - 1].GetNome() == "Pe" and cenario[aux][aux2 - 1].GetNome() != "Ma"){
		 					mar.SetEstado(true);
		 					cenario = move_marinha(cenario,mar,tamanho,move);
		 					rodadas_marinha += 1;
		 				}

						if (cenario[aux][aux2 - 1].GetNome() != "Pe" and cenario[aux][aux2 - 1].GetNome() != "Ma") {
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							cenario.at(aux).at(aux2 - 1).SetNome(player.GetNome());
							cenario.at(aux).at(aux2 - 1).SetTipo(player.GetTipo());
							control++;
						
						}else if(cenario[aux][aux2 - 1].GetNome() == "Ma"){
		 					cout << "entrei" << endl;
		 					int vida = player.GetVida();
		 					cout << vida << endl;
		 					vida--;
		 					cout << vida << endl;
		 					player.SetVida(vida);
		 					cout << player.GetVida() << endl;
		 				}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		} else if (direction == right) {
			string move = "right";
			cout << "right →  ";
			for (auto linha : cenario) {
				for (auto coluna : cenario.at(aux)) {
					if (cenario[aux][aux2].GetNome() == "Jo" and aux2 < (tamanho - 1) and control == 0) {
						
						// Caso movimento colide com obstaculos
		 				if(cenario[aux][aux2 +  1].GetNome() == "Pe" and cenario[aux][aux2 + 1].GetNome() != "Ma"){
		 					mar.SetEstado(true);
		 					cenario = move_marinha(cenario,mar,tamanho,move);
		 					rodadas_marinha += 1;
		 				}


						if (cenario[aux][aux2 + 1].GetNome() != "Pe" and cenario[aux][aux2 + 1].GetNome() != "Ma") {
							cenario.at(aux).at(aux2).SetNome("~~");
							cenario.at(aux).at(aux2).SetTipo(espacoVazio);
							cenario.at(aux).at(aux2 + 1).SetNome(player.GetNome());
							cenario.at(aux).at(aux2 + 1).SetTipo(player.GetTipo());
							control++;
						
						}else if(cenario[aux][aux2 + 1].GetNome() == "Ma"){
		 					cout << "entrei" << endl;
		 					int vida = player.GetVida();
		 					cout << vida << endl;
		 					vida--;
		 					cout << vida << endl;
		 					player.SetVida(vida);
		 					cout << player.GetVida() << endl;
		 				}
					}
					aux2++;
				}
				aux2 = 0;
				aux++;
			}
		}
		control = 0;
		aux = 0;
		aux2 = 0;
		fflush(stdin);
		return cenario;
}




class GrandLine {
private:
	int n;
public:
    vector<vector<Elemento>> inicializar(int tamanho, vector<vector<Elemento>> cenario,Pirata player, Marinha mar, Elemento obst, OnePiece tesouro){
		int aux = 0, aux2 = 0 , pos[2];


		// -------- gerando jogador---------- //
		cenario.at(0).at(0).SetNome(player.GetNome());
		cenario.at(0).at(0).SetTipo(player.GetTipo());
		
		// -------- gerando one piece----------//
		cenario.at(tamanho-1).at(tamanho-1).SetNome(tesouro.GetNome());
		cenario.at(tamanho-1).at(tamanho-1).SetTipo(tesouro.GetTipo());
	    cout << "\n\t------------ Desenvolvedor debug ------------" << '\n';

	    // -------- gerando obstaculos ---------//
		for(int pedra = 1; pedra <= (tamanho / 2); pedra++){
			validando_spawn(tamanho, cenario, pos);
			cenario.at(pos[0]).at(pos[1]).SetNome(obst.GetNome());
			cenario.at(pos[0]).at(pos[1]).SetTipo(obst.GetTipo());
		}

	  	// ------- gerando marinha ------------//
		validando_spawn(tamanho,cenario,pos);
		cenario.at(pos[0]).at(pos[1]).SetNome(mar.GetNome());
		cenario.at(pos[0]).at(pos[1]).SetTipo(mar.GetTipo());
		
		// -------- gerando espaços vazios -----------//
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
	  	aux = 0;
		return cenario;
	}
	int GetCenario(){
		return n;
	}
	void SetCenario(int tamanho){
		n = tamanho;
	}
	void ImprimirCenario(vector<vector<Elemento>> cenario, Pirata player){
		int aux = 0;
		cout << endl << endl;
		for (auto linha : cenario) {
			cout << "\t";
			for (auto coluna : cenario.at(aux)) {
				cout << coluna.GetNome();
				cout << " ";
			}
			cout << endl;
			aux++;
		}
		int vida;
		vida = player.GetVida();
		cout << "\n\t< ♡ ♡ ♡ ♡ ♡"<< vida<< "> " << endl;

	}
};


void menu_player(){
	cout << endl << endl << endl << endl << "\t\t01001100 01100001 01110010 01100011 01100101 01101110 01110011 01010011" << endl << "\t\t01101111 01100110 01110100 01110111 01100001 01110010 01100101 01110011" <<
	endl << "\t\t\t\t\tLarcens Softwares " << endl << endl << "\t\t\t\t\t  Lucas Santos" << endl << endl << "\t\t\t\t\t  Victor Wilker" << endl << endl << "\t\t\t\t\t  Vitor Novaes" << endl;
	getchar();
	system("CLS");
	system("clear");


	cout << "\n\t\t────────────────────────────────────────" << endl;
	cout << "\t\t─────────────▄▄██████████▄▄─────────────" << endl;
	cout << "\t\t─────────────▀▀▀───██───▀▀▀─────────────" << endl;
	cout << "\t\t─────▄██▄───▄▄████████████▄▄───▄██▄─────" << endl;
	cout << "\t\t───▄███▀──▄████▀▀▀────▀▀▀████▄──▀███▄───" << endl;
	cout << "\t\t──████▄─▄███▀──────────────▀███▄─▄████──" << endl;
	cout << "\t\t─███▀█████▀▄████▄──────▄████▄▀█████▀███─" << endl;
	cout << "\t\t─██▀──███▀─██████──────██████─▀███──▀██─" << endl;
	cout << "\t\t──▀──▄██▀──▀████▀──▄▄──▀████▀──▀██▄──▀──" << endl;
	cout << "\t\t─────███───────────▀▀───────────███─────" << endl;
	cout << "\t\t─────██████████████████████████████─────" << endl;
	cout << "\t\t─▄█──▀██──███───██────██───███──██▀──█▄─" << endl;
	cout << "\t\t─███──███─███───██────██───███▄███──███─" << endl;
	cout << "\t\t─▀██▄████████───██────██───████████▄██▀─" << endl;
	cout << "\t\t──▀███▀─▀████───██────██───████▀─▀███▀──" << endl;
	cout << "\t\t───▀███▄──▀███████────███████▀──▄███▀───" << endl;
	cout << "\t\t─────▀███────▀▀██████████▀▀▀───███▀─────" << endl;
	cout << "\t\t───────▀─────▄▄▄───██───▄▄▄─────▀───────" << endl;
	cout << "\t\t──────────── ▀▀██████████▀▀─────────────" << endl;
	cout << "\t\t────────────────────────────────────────" << endl;

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
	menu_player();

 	int tamanho,pos[2];// posição dos elementos
	char TamCen[256];
// ---------------- Menu inicial -----------------//
 	cout << " -- Selecione um nivel --" << endl;
	cout << "\t > NIVEL 4  - - - - 4" << endl; // 4
	cout << "\t > NIVEL 5  - - - - 5" << endl; // 5
	cout << "\t > NIVEL 6  - - - - 6" << endl; // 6
	cout << "\t > NIVEL 7  - - - - 7" << endl; // 7
	cout << "\t > SAIR  - - - - -  8" << endl; // EXIT
	cout << "\t > Digite o numero: ";

	cin >> TamCen;cout << endl;
	tamanho = atoi(TamCen);
	if(tamanho == 8){
		return 0;
	}
	while(tamanho > 7 or tamanho < 4){
		cout << ">-------- NIVEL INVALIDO!!!----------<" << endl;
		cout << " \n-- Selecione um nivel --" << endl;
 		cin >> TamCen;
		tamanho = atoi(TamCen);
	}

	vector< vector<Elemento> > cenario(tamanho,vector<Elemento>(tamanho));  // vector cenario (n x n)
	Pirata player(70,5,"Jo",pirata); // weight,vida,name,type
    OnePiece tesouro("Te",onePiece,300); // nome, tipo , peso
    Elemento obst("Pe",obstaculo); // name, type
    Marinha mar(false, 5, "Ma", marinha); // state,vida,name,type
    // string ui_estado_marinha; // imprime estado
    // ui_estado_marinha = mar.GetEstado()? "Marinha em alerta":"Marinha Dormindo";

// ---------------- Gerando novas seeds (rand) -------------- //;
 	srand(time(NULL));
 	//ola

// ---------------- Inicializando Cenario -------------------- //;
	 
	 GrandLine mapa;
	 cenario = mapa.inicializar(tamanho,cenario,player,mar,obst,tesouro);
	 mapa.ImprimirCenario(cenario,player);

//----------MOVIMENTO----------------------------//
	getchar();
	getchar();
	system("CLS");
	system("clear");
	fflush(stdin);
	int haki = 1,auxHaki = 0;
	int aux = 0, aux2 = 0;
	int vida = player.GetVida();
	while (vida != 0) {
		cout << ">-- Movimentos:\t\t\t>-- Nivel: " << tamanho << endl;
		haki = player.IdentificarTesouro(cenario,tamanho);
		if(haki == 1 or auxHaki == 1){
			cenario = MoverPirata(cenario,tamanho,player,mar);
			mapa.ImprimirCenario(cenario,player);
			getchar();
		}else if(haki == 0 and auxHaki == 0){
			if(cenario.at(tamanho-3).at(tamanho-1).GetNome() == "Jo"){
				cenario.at(tamanho-3).at(tamanho-1).SetNome("~~");
				cenario.at(tamanho-2).at(tamanho-1).SetNome(player.GetNome());
				cenario.at(tamanho-3).at(tamanho-1).SetTipo(espacoVazio);
				cenario.at(tamanho-2).at(tamanho-1).SetTipo(player.GetTipo());
				mapa.ImprimirCenario(cenario,player);
			}else if(cenario.at(tamanho-1).at(tamanho-3).GetNome() == "Jo"){
				cenario.at(tamanho-1).at(tamanho-3).SetNome("~~");
				cenario.at(tamanho-1).at(tamanho-2).SetNome(player.GetNome());
				cenario.at(tamanho-1).at(tamanho-3).SetTipo(espacoVazio);
				cenario.at(tamanho-1).at(tamanho-2).SetTipo(player.GetTipo());
				mapa.ImprimirCenario(cenario,player);
			}else if(cenario.at(tamanho-1).at(tamanho-2).GetNome() == "Jo"){
				cenario.at(tamanho-1).at(tamanho-2).SetNome("~~");
				cenario.at(tamanho-1).at(tamanho-1).SetNome(player.GetNome());
				cenario.at(tamanho-1).at(tamanho-2).SetTipo(espacoVazio);
				cenario.at(tamanho-1).at(tamanho-1).SetTipo(player.GetTipo());
				mapa.ImprimirCenario(cenario,player);
				auxHaki = 1;
				haki = 1;
			}else if(cenario.at(tamanho-2).at(tamanho-1).GetNome() == "Jo"){
				cenario.at(tamanho-2).at(tamanho-1).SetNome("~~");
				cenario.at(tamanho-1).at(tamanho-1).SetNome(player.GetNome());
				cenario.at(tamanho-2).at(tamanho-1).SetTipo(espacoVazio);
				cenario.at(tamanho-1).at(tamanho-1).SetTipo(player.GetTipo());
				mapa.ImprimirCenario(cenario,player);
				auxHaki = 1;
				haki = 1;
			}
			getchar();
		 	}
		system("CLS");
		system("clear");
		vida = player.GetVida();
	}
	
	return 0;
}  