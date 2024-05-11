#ifndef VIATGE_HH
#define VIATGE_HH

#include <list>
#include <string>
#include <iostream>

class Viatge {

private:
	std::list<std::string> ruta;
	int quant_comerciat;
	std::string ordre;  // 'r' root; 'e' esquerra; 'd' dreta;
	void eliminarCiutat();

public:
	/* CONSTRUCTORS */
	Viatge();

	/* MODIFICADORS */
	void afegirCiutat(std::string id_city, char dir);
	void actQuant(int quant);

	/* CONSULTORS */
	std::list<std::string> consultarRuta() const;
	std::string consultarOrdre() const;
	std::string consultarProxCiutat();  // No és const perquè elimina la ciutat actual.
	int consultarQuant() const;
	std::string consultarUltimaCiutat() const;
};

#endif