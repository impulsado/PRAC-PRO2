# PRAC-PRO2
## Preguntes
### leer_rio
- [ ] El vaixell reinicia el registre d'últimes ciutats visitades o el manté? (Donat que és farà una nova disposició del mapa)

### leer_inventario / leer_inventarios
- [ ] Que passa si la ciutat ja té el producte? Es sobre escriu la informació o es passa al següent producte?
- [ ] Que passa si el producte no existeix? Continua al següent?

### hacer_viaje
- [ ] Classe `Viaje` i `Cjt_viajes` és una bona idea?

## TEMP
# Viatge
```c++
#ifndef VIATGE_HH
#define VIATGE_HH

#include <list>
#include <string>
#include <iostream>

class Viatge {

private:
	std::list<string> ruta;
	int quant_comerciat;

public:
	/* CONSTRUCTORS */
	Viatge();
	Viatge(const Viatge& v);

	/* MODIFICADORS */
	void afegirCiutat(string id_city);
	void eliminarCiutat();
	void actQuant(int quant);

	/* CONSULTORS */
	list<string> consultarRuta();
	string consultarUltimaCiutat();
	int consultarQuant();
};

#endif
```

# Cjt_viatges
```c++
#ifndef CJT_VIATGES_HH
#define CJT_VIATGES_HH

#include "Viatge.hh"
#include <vector>
#include <iostream>

class Cjt_viatges {

private:
	std::vector<Viatge> histo;
	
public:
	/* CONSTRUCTORS */
	Cjt_viatges();

	/* MODIFICADORS */
	void afegirViatge(Viatge v);
	
	/* CONSULTORS */
	Viatge consultarMillorViatge();
};

#endif
```