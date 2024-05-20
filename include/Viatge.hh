#ifndef VIATGE_HH
#define VIATGE_HH

#include <list>
#include <string>
#include <iostream>
#include "Cjt_ciutats.hh"

class Viatge {

private:
	int quant_comerciat;
	int distancia;  // Quantitat de ciutats recorreguda (Optimització)
	std::string ordre;  // 'r' root; 'e' esquerra; 'd' dreta;
	std::string ultima_ciutat;
	Cjt_ciutats snapshot;
	bool tot_comerciat;

public:
	/* CONSTRUCTORS */
	Viatge();

	/* MODIFICADORS */
	void afegirCiutat(std::string id_city, char dir, Cjt_ciutats& conjunt);
	void actQuant(int quant);
	void actTotComerciat();

	/* CONSULTORS */
	std::string consultarOrdre() const;
	int consultarQuant() const;
	int consultarDist() const;
	std::string consultarUltimaCiutat() const;
	Cjt_ciutats consultarSnapshot() const;
	bool estaTotComerciat() const;
};

#endif