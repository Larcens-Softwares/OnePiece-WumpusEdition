#include <iostream>
#include <vector>
#include "models.h"
using namespace std;

Elemento::Elemento(string nome, TipoElemento tipo){
    this->nome = nome;
    this->tipo = tipo;
}
Elemento::~Elemento(){}
//////////////////////////////////////////////////////////
Pessoa::Pessoa(int hp):Elemento(nome,tipo){
    this->hp = hp;
}
Pessoa::~Pessoa(){}
//////////////////////////////////////////////////////////
OnePiece::OnePiece(float peso):Elemento(nome,tipo){
    this->peso = peso;
}
void OnePiece::set_peso(float peso){
    this->peso = peso;
}
float OnePiece::get_peso(){
    return peso;
}
OnePiece::~OnePiece(){}

//////////////////////////////////////////////////////////
Pirata::Pirata(float peso):Pessoa(hp){
    this->peso = peso;
    peso_adicional = 0;
}
void Pirata::set_peso_adicional(float peso_adicional){
    this->peso_adicional = peso_adicional;
}
float Pirata::get_peso_adicional(){
    return peso_adicional;
}
void Pirata::set_peso(float peso){
    this->peso = peso;
}
float Pirata::get_peso(){
    return peso;
}
Pirata::~Pirata(){}

//////////////////////////////////////////////////////////
Marinha::Marinha(bool estado):Pessoa(hp){
    this->estado = estado;
}
void Marinha::set_estado(bool estado){
    this->estado = estado;
}
bool Marinha::get_estado(){
    return estado;
}
Marinha::~Marinha(){}
//////////////////////////////////////////////////////////
GrandLine::GrandLine(vector<vector<Elemento> > init_cenario){
    cenario = init_cenario;
}
void GrandLine::set_grand_line(vector<vector<Elemento> > cenar){
    cenario = cenar;
}
vector<vector<Elemento> > GrandLine::get_grand_line(){
    return cenario;
}
GrandLine::~GrandLine(){}


int main(){

	return 0;
}
