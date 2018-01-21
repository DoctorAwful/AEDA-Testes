#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+(const Documento &doc1) {
	int numPaginasf = doc1.getNumPaginas() + numPaginas;

	float percentagemPreto = doc1.getNumPaginas() * doc1.getPercentagemPreto() + numPaginas * pPreto;
	float percentagemAmarelo =  doc1.getNumPaginas()*doc1.getPercentagemAmarelo() + numPaginas* pAmarelo;
	percentagemPreto = percentagemPreto / numPaginasf;
	percentagemAmarelo = percentagemAmarelo / numPaginasf;

	Documento novo(numPaginasf, percentagemPreto, percentagemAmarelo);

	return novo;
	
	

}



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }


bool Impressora::operator== (const Impressora &impressora) const {
	if ((this->codigo == impressora.codigo) && (this->ano == impressora.ano))
	{
		return true;
	}
	return false;
} 


//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }


bool ImpressoraPB::imprime(Documento doc1){
	
	if(this->numPagImprimir >= doc1.getNumPaginas())
	{
		numPagImprimir = numPagImprimir - doc1.getNumPaginas();
		docsImpressos.push_back(doc1);
		return true;
	}
	else return false; 
	
}



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}
bool ImpressoraCores::imprime(Documento doc1) {
	
	if((this->numPagImprimirPreto >= doc1.getNumPaginas() * doc1.getPercentagemPreto()) && (this->numPagImprimirAmarelo >= doc1.getNumPaginas() * doc1.getPercentagemAmarelo())) {
		imprimepreto(doc1.getNumPaginas(), doc1.getPercentagemPreto());
		imprimeamarelo(doc1.getNumPaginas(), doc1.getPercentagemAmarelo());
		docsImpressos.push_back(doc1);
		return true;
	}
	else return false; 
	return false;

}


//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }



int Escritorio::numImpressorasSemResponsavel() const {

	vector<Impressora*> temp;
	unsigned int contador = 0;

	for (unsigned int i = 0; i < funcionarios.size(); i++)
	{
		for (unsigned int j = 0; j < funcionarios[i].getImpressoras().size(); j++)
		{
			temp.push_back(funcionarios[i].getImpressoras().at(j));
		}
	} 

	for (unsigned int  l = 0; l < this->impressoras.size(); l++)
	{
		
		for (unsigned int j = 0; j < temp.size(); j++)
		{
			if (this->impressoras[l] == temp[j])
				contador++;
		}
	}

	return impressoras.size() - contador;
	
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1) {
	
	vector<Impressora *> retiradas;

	for(unsigned int i = 0; i < impressoras.size(); i++)
	{
		if (impressoras.at(i)->getAno() < ano1)
		{
			retiradas.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin()+i);
			i--;

		}
	}
	return retiradas;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const {
	
	
	ImpressoraPB * inexistente = new ImpressoraPB("inexistente", 0,0);

	for (unsigned int i = 0; i < impressoras.size(); i++)
	{
		if (impressoras[i]->imprime(doc1))
		{
			return impressoras[i];
		}
	}
	return inexistente;
}

vector<Impressora *> Escritorio::tonerBaixo() const {

	vector<Impressora *> tonerbaixo;
	for (unsigned int i = 0; i < impressoras.size(); i++)
	{
		if (impressoras[i]->getPrinterType() == 1)
		{
			if (impressoras[i]->getNumPaginasImprimir() < 30)
				tonerbaixo.push_back(impressoras[i]);
		}
		else if (impressoras[i]->getPrinterType() == 2)
		{
			if (impressoras[i]->getNumPaginasImprimir() < 20)
				tonerbaixo.push_back(impressoras[i]);
		}
	}

	return tonerbaixo;
}

string Escritorio::operator()(string codImpressora) const {

	vector <Impressora*> temp;
	vector <string> codigos;
	string nulo = "nulo";
	string codigo;
	bool none = true;

	for (unsigned int i = 0; i < funcionarios.size(); i++)
	{
		for (unsigned int j = 0; j < funcionarios[i].getImpressoras().size(); j++)
		{
			
			codigos.push_back(funcionarios[i].getCodigo());
			temp.push_back(funcionarios[i].getImpressoras()[j]);
		}
	}


	for (unsigned int j = 0; j < temp.size(); j++)
	{
		if (temp.at(j)->getCodigo() == codImpressora)
		{
			codigo = codigos.at(j);
			return codigo;
		}
	}
	
	
	return nulo;

}