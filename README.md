# PRAC-PRO2 | Cuenca Fluvial 🏞️
# GENERAL
| TÍTOL | CURS | DIFICULTAT | TESTS | NOTA |
| --- | --- | --- | --- | --- |
| Cuenca Fluvial | 2023-2024 Q2 | 7/10 | 4/4 | x/10 |

<br>

# Explicació
La pràctica tracta de programar un programa modular que permeti a l'usuari definir un arbre de ciutas `Cuenca` on cada node sera una `Ciutat`. Aquest `Cjt_ciutats` tenenen un inventari de productes definits en el `Cjt_productes` on cada `Producte` té un: Id, Pes, Volum associats. <br>
La finalitat és que les ciutats comercïn entre elles intercanviant-se l'excés de productes fins arribar a/intentar cobrir les respectives necessitats. <br>
Finalment hi ha un `Vaixell` que comercia amb totes les ciutats fins que aquest ja no té més productes que intercanviar. Aquest intercanvi només es realitza amb aquelles ciutats que pertanyin al millor `Viatge` on és determina mitjançant els paràmetres: Quantitat > Distància > Ordre. <br>
Per a determinar aquest millor viatge hi ha una `Llantxa` eficientment implementada que calcula la millor ruta. 

# Consells
1. Fes servir `git` per a poder veure passades modificacions.
2. Destina temps a pensar molt bé com ho implementaràs. Recomano fer pseudocodi de totes les funcions.

# Instal·lació
1. Instal·la el compilador de C++ `g++`, l'eina `make` per a fer servir el `Makefile` i `git` per a descarregar-se comodament el codi.
```sh
sudo apt update -y
sudo apt install -y g++ make git
```

2. Descarrega el codi i compila el programa.
```sh
git clone https://github.com/impulsado/PRAC-PRO2.git
cd /path/to/PRAC-PRO2
make
```

3. Executa el codi amb samples predefinits o lliurement.
```
# Lliuremente
./program.exe

# Samples pre-definits
./program.exe < samples/sample.inp
```
