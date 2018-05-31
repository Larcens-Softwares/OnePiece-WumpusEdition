#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class elemento{
	string tipo;
	string nome;
 public:
	string getNome(){
		return nome;
	}
	string getTipo(){
		return tipo;
	}
	void setNome(string name){
		nome = name;
	}
	void setTipo(string type){
		tipo = type;
	}
};
void validando_inimigos(int tamanho, vector<vector<elemento>> cenario, int *pos){
	int randNumLinha,randNumColuna;
	int var=0;

	randNumLinha = rand() % (tamanho-1) + 1;
	randNumColuna = rand() % (tamanho-1) + 1;

		while(var==0){
			if(randNumLinha == 0 or randNumColuna == 0){
				randNumLinha = rand() % (tamanho-1) + 1;
				randNumColuna = rand() % (tamanho-1) + 1;
			}else{
				var=1;
			}
		}

		var=0;
		while(var==0){
			if(randNumLinha == (tamanho-1) and randNumColuna == (tamanho-1)){
				randNumLinha = rand() % (tamanho-1) + 1;
				randNumColuna = rand() % (tamanho-1) + 1;
			}else{
				var=1;
			}
		}

		var=0;
		while(var==0){
			if(cenario[randNumLinha][randNumColuna].getNome() == "Pe" or
				cenario[randNumLinha][randNumColuna].getNome() == "In"){
				randNumLinha = rand() % (tamanho-1) + 1;
				randNumColuna = rand() % (tamanho-1) + 1;
			}else{
				var=1;
			}
		}

		while(var==0){
			if(randNumLinha == (tamanho-2) or randNumColuna == (tamanho-2)){
				randNumLinha = rand() % (tamanho-1) + 1;
				randNumColuna = rand() % (tamanho-1) + 1;
			}else{
				var=1;
			}
		}

		pos[0] = randNumLinha;
		pos[1] = randNumColuna;
 }

int main(){
	enum Direction{up=1,down,left,right};
	int tamanho; // gerador de linhas e colunas
	int pos[2];
	elemento objAux; // auxiliar para informação dos objetos
	cout << "Qual o tamanho do cenario?" << endl;
	cin >> tamanho;


	vector<vector<elemento>> cenario(tamanho, vector<elemento>(tamanho)); // vector cenario (tamanho x tamanho)
	int aux = 0, aux2 = 0, aux3 = 0; // preencher cenario com vazios

	srand(time(NULL));
//----------------------PIRATA-----------------------//
	objAux.setNome("Jo");
	objAux.setTipo("Pi");
	cenario[0][0] = objAux;
//-----------------------ONE PIECE-------------------//
	objAux.setNome("Te");
	objAux.setTipo("One");
	cenario[tamanho-1][tamanho-1] = objAux;
//-----------------------OBSTACULOS----------------- //
  	objAux.setNome("Pe");
  	objAux.setTipo("Ob");
	for(int pedra=1 ; pedra <= (tamanho/2) ; pedra++){
		validando_inimigos(tamanho,cenario,pos);
		cout << pos[0] << pos[1] << '\n';
		cenario[pos[0]][pos[1]] = objAux;
	}
//----------------------- MARINHA ------------------//
	objAux.setNome("In");
  	objAux.setTipo("Ma");
	validando_inimigos(tamanho,cenario,pos);
	cout << pos[0] << pos[1] << '\n';
	cenario[pos[0]][pos[1]] = objAux;

//---------------------ESPAÇOS VAZIOS--------------//

 for(auto a : cenario){
		for(auto b : cenario.at(aux)){
			if(b.getNome() != "Jo" && b.getNome() != "Te" && b.getNome() != "Pe" && b.getNome() != "In" ){
				b.setNome("~~");
				b.setTipo("~~");
				cenario.at(aux).at(aux2) = b;
			}
				aux2++;
		}
		aux2 = 0;
		aux++;
	}
//----------------GERANDO CENARIO-----------------//

	aux=0;

	for(auto linha: cenario){
		for(auto coluna: cenario.at(aux)){
			cout << coluna.getNome() << coluna.getTipo() << "\t";
			cout << " ";
		}
		cout << endl;
		aux++;
	}
//----------MOVIMENTO----------------------------//
	getchar();
	fflush(stdin);
	aux = 0;
	aux2 = 0;
	int control = 0;
	while(true){
  	Direction direction = Direction(rand()%4+1);
		if(direction == up){
				for(auto linha: cenario){
					for(auto coluna: cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux < (tamanho-1) and control == 0){
							if(cenario[aux+1][aux2].getNome() != "Pe" and cenario[aux+1][aux2].getNome() != "In" ){
									cenario[aux][aux2].setNome("~~");
									cenario[aux][aux2].setTipo("~~");
									cenario[aux+1][aux2].setNome("Jo");
									cenario[aux+1][aux2].setTipo("Pi");
									for(auto linha: cenario){
										for(auto coluna: cenario.at(aux3)){
											cout << coluna.getNome() << coluna.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
											aux3++;
									}
									aux3 = 0;
									control++;
									getchar();
									// system("CLS"); system("clear");
							 }
						}
						aux2++;
					 }
					 aux2 = 0;
					 aux++;
				 }
		}else if(direction == down){
				for(auto linha: cenario){
					for(auto coluna: cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux > 0 and control == 0){
							if(cenario[aux-1][aux2].getNome() != "Pe" and cenario[aux-1][aux2].getNome() != "In" ){
									cenario[aux][aux2].setNome("~~");
									cenario[aux][aux2].setTipo("~~");
									cenario[aux-1][aux2].setNome("Jo");
									cenario[aux-1][aux2].setTipo("Pi");
									control++;
								 for(auto linha: cenario){
										for(auto coluna: cenario.at(aux3)){
											cout << coluna.getNome() << coluna.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
											aux3++;
									}
									aux3 = 0;
									getchar();
									// system("CLS"); system("clear");
							 }
						}
						aux2++;
					 }
					 aux2 = 0;
					 aux++;
				 }
		}else if(direction == left){
				for(auto linha: cenario){
					for(auto coluna: cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux2 > 0 and control == 0){
							if(cenario[aux][aux2-1].getNome() != "Pe" and cenario[aux][aux2-1].getNome() != "In" ){
									cenario[aux][aux2].setNome("~~");
									cenario[aux][aux2].setTipo("~~");
									cenario[aux][aux2-1].setNome("Jo");
									cenario[aux][aux2-1].setTipo("Pi");
									for(auto linha: cenario){
										for(auto coluna: cenario.at(aux3)){
											cout << coluna.getNome() << coluna.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
											aux3++;
										}
										aux3 = 0;
									control++;
									getchar();
									// system("CLS"); system("clear");
							 }
						}
						aux2++;
					 }
					 aux2 = 0;
					 aux++;
				 }
		}else if(direction == right){
				for(auto linha: cenario){
					for(auto coluna: cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux2 < (tamanho-1) and control == 0){
							if(cenario[aux][aux2+1].getNome() != "Pe" and cenario[aux][aux2+1].getNome() != "In" ){
									cenario[aux][aux2].setNome("~~");
									cenario[aux][aux2].setTipo("~~");
									cenario[aux][aux2+1].setNome("Jo");
									cenario[aux][aux2+1].setTipo("Pi");
									for(auto linha: cenario){
										for(auto coluna: cenario.at(aux3)){
											cout << coluna.getNome() << coluna.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
												aux3++;
									}
									aux3 = 0;
									control++;
									getchar();
									// system("CLS"); system("clear");
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
