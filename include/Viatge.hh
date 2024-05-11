#ifndef VIATGE_HH
#define VIATGE_HH

#include <list>
#include <string>
#include <iostream>

class Viatge {

private:
	std::list<std::string> ruta;
	int quant_comerciat;
	void eliminarCiutat();

public:
	/* CONSTRUCTORS */
	Viatge();

	/* MODIFICADORS */
	void afegirCiutat(std::string id_city);
	void actQuant(int quant);

	/* CONSULTORS */
	std::list<std::string> consultarRuta() const;
	std::string consultarProxCiutat();  // No és const perquè elimina la ciutat actual.
	int consultarQuant() const;
	std::string consultarUltimaCiutat() const;
};

#endif