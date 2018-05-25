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

int main() {
	enum Direction{up=1,down,left,right};
	int x,randNumLinha,randNumColuna; // gerador de linhas e colunas
	int var=0; // variavel do while
	elemento objAux; // auxiliar para informação dos objetos
	cout << "Qual o tamanho do cenario?" << endl;
	cin >> x; // tamanho do cenario


	vector<vector<elemento>> cenario(x, vector<elemento>(x)); // vector cenario
	int aux = 0,aux2 = 0,aux3 = 0; // preencher cenario com vazios

	srand(time(NULL));
//----------------------PIRATA-----------------------//
	objAux.setNome("Jo");
	objAux.setTipo("Pi");
	cenario[0][0] = objAux;
//-----------------------ONE PIECE-------------------//
	objAux.setNome("Te");
	objAux.setTipo("One");
	cenario[x-1][x-1] = objAux;
//-----------------------OBSTACULOS----------------- //
  objAux.setNome("Pe");
  objAux.setTipo("Ob");
 for(int pedra=1 ; pedra <= (x/2) ; pedra++){
	randNumLinha = rand() % (x-1) + 1;
	randNumColuna = rand() % (x-1) + 1;
		while(var==0){
			if(randNumLinha == 0 or randNumColuna == 0){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
		}
		var=0;
	while(var==0){
			if(randNumLinha == (x-1) and randNumColuna == (x-1)){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
	}
	var =0;
	while(var==0){
			if(cenario[randNumLinha][randNumColuna].getNome() == "Pe" or 
				cenario[randNumLinha][randNumColuna].getNome() == "In"){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
	}
	while(var==0){
			if(randNumLinha == (x-2) and randNumColuna == (x-2)){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
	}
	var = 0;
	cenario[randNumLinha][randNumColuna] = objAux;
 }
 var = 0;
//----------------------- MARINHA ------------------//
	objAux.setNome("In");
  objAux.setTipo("Ma");
	randNumLinha = rand() % (x-1) + 1;
	randNumColuna = rand() % (x-1) + 1;
		while(var==0){
			if(randNumLinha == 0 or randNumColuna == 0){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
		}
	 var=0;
	while(var==0){
			if(randNumLinha == (x-1) and randNumColuna == (x-1)){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
	}
	 var =0;
	while(var==0){
			if(cenario[randNumLinha][randNumColuna].getNome() == "Pe" or 
				cenario[randNumLinha][randNumColuna].getNome() == "In"){
				randNumLinha = rand() % (x-1) + 1;
				randNumColuna = rand() % (x-1) + 1;
			}else{
				var=1;
			}
	}
	cenario[randNumLinha][randNumColuna] = objAux;

//---------------------ESPAÇOS VAZIOS--------------//

 for(auto a : cenario){
		for(auto b : cenario.at(aux)){
			if(b.getNome() != "Jo" && b.getNome() != "Te" && b.getNome() != "Pe" && b.getNome() != "In" ){
				b.setNome("XX");
				b.setTipo("XX");
				cenario.at(aux).at(aux2) = b;
			}
				aux2++;
		}
		aux2 = 0;
		aux++;
	}
//----------------GERANDO CENARIO-----------------//

	aux=0;

	for(auto i : cenario){
		for(auto j : cenario.at(aux)){
			cout << j.getNome() << j.getTipo() << "\t";
			cout << " ";
		}
		cout << endl;
		aux++;
	}
//----------MOVIMENTO----------------------------//
	fflush(stdin);
	aux = 0;
	aux2 = 0;
  var = 0;
	int control = 0;
	while(var == 0){
  Direction direction = Direction(rand()%4+1);
		if(direction == up){
				for(auto i : cenario){
					for(auto j : cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux < (x-1) and control == 0){
							if(cenario[aux+1][aux2].getNome() != "Pe" and cenario[aux+1][aux2].getNome() != "In" ){
									cenario[aux][aux2].setNome("XX");
									cenario[aux][aux2].setTipo("XX");
									cenario[aux+1][aux2].setNome("Jo");
									cenario[aux+1][aux2].setTipo("Pi");
									for(auto i : cenario){
										for(auto j : cenario.at(aux3)){
											cout << j.getNome() << j.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
											aux3++;
									}
									aux3 = 0;
									control++;
									getchar();
							 }
						}
						aux2++;
					 }
					 aux2 = 0;
					 aux++;
				 }
		}else if(direction == down){
				for(auto i : cenario){
					for(auto j : cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux > 0 and control == 0){
							if(cenario[aux-1][aux2].getNome() != "Pe" and cenario[aux-1][aux2].getNome() != "In" ){
									cenario[aux][aux2].setNome("XX");
									cenario[aux][aux2].setTipo("XX");
									cenario[aux-1][aux2].setNome("Jo");
									cenario[aux-1][aux2].setTipo("Pi");
									control++;
								 for(auto i : cenario){
										for(auto j : cenario.at(aux3)){
											cout << j.getNome() << j.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
											aux3++;
									}
									aux3 = 0;
									getchar();
							 }
						}
						aux2++;
					 }
					 aux2 = 0;
					 aux++;
				 }
		}else if(direction == left){
				for(auto i : cenario){
					for(auto j : cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux2 > 0 and control == 0){
							if(cenario[aux][aux2-1].getNome() != "Pe" and cenario[aux][aux2-1].getNome() != "In" ){
									cenario[aux][aux2].setNome("XX");
									cenario[aux][aux2].setTipo("XX");
									cenario[aux][aux2-1].setNome("Jo");
									cenario[aux][aux2-1].setTipo("Pi");
									for(auto i : cenario){
										for(auto j : cenario.at(aux3)){
											cout << j.getNome() << j.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
											aux3++;
										}
										aux3 = 0;
									control++;
									getchar();
							 }
						}
						aux2++;
					 }
					 aux2 = 0;
					 aux++;
				 }
		}else if(direction == right){
				for(auto i : cenario){
					for(auto j : cenario.at(aux)){
						if (cenario[aux][aux2].getNome() == "Jo" and aux2 < (x-1) and control == 0){
							if(cenario[aux][aux2+1].getNome() != "Pe" and cenario[aux][aux2+1].getNome() != "In" ){
									cenario[aux][aux2].setNome("XX");
									cenario[aux][aux2].setTipo("XX");
									cenario[aux][aux2+1].setNome("Jo");
									cenario[aux][aux2+1].setTipo("Pi");
									for(auto i : cenario){
										for(auto j : cenario.at(aux3)){
											cout << j.getNome() << j.getTipo() << "\t";
											cout << " ";
										}
											cout << endl;
												aux3++;
									}
									aux3 = 0;
									control++;
									getchar();
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