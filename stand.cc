// Implementatie van klasse Stand.

#include <iostream>
#include <iomanip>
#include "stand.h"
#include "standaard.h"
using namespace std;

//*************************************************************************

Stand::Stand()
{

}

//*************************************************************************
// Constructor Stand
// waardeM - aantal rijen
// waardeN - aantal kolommen
Stand::Stand (int waardeM, int waardeN)
{
    m = waardeM;
    n = waardeN;
    x = 1;
}

//*************************************************************************

Stand::~Stand ()
{
  // eventueel TODO: implementeren

}  // ~Stand

//*************************************************************************
int Stand::getM ()
{
  return m;
}

//*************************************************************************
int Stand::getN ()
{
  return n;
}

//*************************************************************************

// Drukt de huidige stand van het bord af.
void Stand::drukaf ()
{
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << bord[i][j] << " ";
        }
        cout << endl;
    }
}  // drukaf

//*************************************************************************
// Doet een zet op het bord, als de zet geldig is.
// rij - rijnummer bord
// kolom - kolomnummer bord
// steennr - steennummer
bool Stand::legsteenneer (int rij, int kolom, int steennr)
{
    switch (steennr)
    {
    case 0:
        if(bord[rij][kolom] != 0 || bord[rij+1][kolom] != 0 || bord[rij][kolom+1] != 0){
            return false;
        }
        bord[rij][kolom] = x;
        bord[rij+1][kolom] = x;
        bord[rij][kolom+1] = x;
        break;
    case 1:
        if(bord[rij][kolom] != 0 || bord[rij][kolom+1] != 0 || bord[rij+1][kolom+1] != 0){
            return false;
        }
        bord[rij][kolom] = x;
        bord[rij][kolom+1] = x;
        bord[rij+1][kolom+1] = x;
        break;
    case 2:
        if(bord[rij+1][kolom] != 0 || bord[rij][kolom+1] != 0 || bord[rij+1][kolom+1] != 0){
            return false;
        }
        bord[rij+1][kolom] = x;
        bord[rij][kolom+1] = x;
        bord[rij+1][kolom+1] = x;
        break;
    case 3:
        if(bord[rij][kolom] != 0 || bord[rij+1][kolom] != 0 || bord[rij+1][kolom+1] != 0){
            return false;
        }
        bord[rij][kolom] = x;
        bord[rij+1][kolom] = x;
        bord[rij+1][kolom+1] = x;
        break;
    }
    x++;
    return true;
}  // legsteenneer

// Maakt een zet ongedaan, als er een zet is gedaan.
// rij - rijnummer bord
// kolom - kolomnummer bord
// steennr - steennummer
void Stand::ontdoezet (int rij, int kolom, int steennr)
{
    if(x != 0){
    switch (steennr)
    {
    case 0:
        bord[rij][kolom] = 0;
        bord[rij+1][kolom] = 0;
        bord[rij][kolom+1] = 0;
        break;
    case 1:
        bord[rij][kolom] = 0;
        bord[rij][kolom+1] = 0;
        bord[rij+1][kolom+1] = 0;
        break;
    case 2:
        bord[rij+1][kolom] = 0;
        bord[rij][kolom+1] = 0;
        bord[rij+1][kolom+1] = 0;
        break;
    case 3:
        bord[rij][kolom] = 0;
        bord[rij+1][kolom] = 0;
        bord[rij+1][kolom+1] = 0;
        break;
    }
    x--;
    }
}  // legsteenneer

//*************************************************************************

// Checkt of het bord een eindstand heeft
// returns true - als er geen mogelijke zetten zijn
//         false - als er nog zetten kunnen worden gedaan.
bool Stand::eindstand ()
{
    if(zettenMogelijk() == 0){
        return true;
    }
    return false;
}  // eindstand

//*************************************************************************

// Doet een random zet
void Stand::doerandomzet ()
{
    int aantzetten = 0;
    aantzetten = zettenMogelijk();
    int zet = randomGetal(1, aantzetten);
    for(int i = 0; i < m-1; i++){
        for(int j = 0; j < n-1; j++){
            for(int z = 0; z <= 3; z++){
                if(legsteenneer(i,j,z)){
                    zet--;
                    if(zet == 0){
                        return;
                    }
                    ontdoezet(i,j,z);
                }

            }
        }
    }
}  // doerandomzet

//*************************************************************************
// Checkt of er een winnende zet mogelijk is.
// returns true - als er een winnende zet is
// en de winnende zet in wrij, wkolom, wsteennr.
// aantal - Het aantal zetten die er worden gecheckt
// wrij - het rijnummer van de winnende zet
// wkolom - het kolomnummer van de winnende zet
// wsteennr - het steennummer van de winnende zet
//
bool Stand::winnend (int &aantal, int &wrij, int &wkolom, int &wsteennr)
{
    if(eindstand()){
        return false;
    }

    for(int i = 0; i < m-1; i++){
        for(int j = 0; j < n-1; j++){
            for(int z = 0; z <= 3; z++){
                if(legsteenneer(i,j,z)){
                    aantal++;
                    if(!winnend(aantal, wrij, wkolom, wsteennr)){
                        ontdoezet(i,j,z);
                        wrij = i;
                        wkolom = j;
                        wsteennr = z;
                        return true;
                    }
                    ontdoezet(i,j,z);
                }
            }
        }
    }
    return false;
}  // winnend

//*************************************************************************
// Telt het aantal zetten die er in de huidige stand van het bord mogelijk zijn.
int Stand::zettenMogelijk(){
    int aantzetten = 0;
    for(int i = 0; i < m-1; i++){
        for(int j = 0; j < n-1; j++){
            for(int z = 0; z <= 3; z++){
                if(legsteenneer(i,j,z)){
                    aantzetten++;
                    ontdoezet(i,j,z);
                }
            }
        }
    }
    return aantzetten;
}

// Zoekt naar de beste zet voor de speler (zet met hoogste winkans),
// Als er geen winnende zet is,
// wordt de bestezet in grij, gkolom, gsteennr opgeslagen.
// anders wordt de winnende zet in grij, gkolom, gsteennr opgeslagen.
// returns true, als de huidige stand geen eindstand is.
// anders false.
bool Stand::goedezet (int &grij, int &gkolom, int &gsteennr)
{
    int aantal = 0;
    if(eindstand()){
        return false;
    }
    if(winnend(aantal, grij, gkolom, gsteennr)){
        return true;
    }
    goedezet_p(0, grij, gkolom, gsteennr);
    return true;
}  // goedezet

// Zoekt naar de beste zet voor de speler (zet met hoogste winkans),
// beste zet wordt opgeslagen in grij, gkolom, gsteenr.
// depth wordt opgehoogd na elke recursieve oproep.
double Stand::goedezet_p(int depth, int &grij, int &gkolom, int &gsteennr){
    double winp = 0; // beste winpercentage
    double aantalm = (double) zettenMogelijk(); // aantal mogelijke zetten
    double totwin = 0; // totale winpercentage

    if(eindstand() && (depth % 2 != 0)){
        return 1;
    }
    else if(eindstand()){
        return 0;
    }
    for(int i = 0; i < m-1; i++){
        for(int j = 0; j < n-1; j++){
            for(int z = 0; z <= 3; z++){
                if(legsteenneer(i,j,z)){
                    depth++;
                    double winperc = goedezet_p(depth, grij, gkolom, gsteennr);
                    depth--;
                    totwin += winperc;
                    if(winperc >= winp){
                        winp = winperc;
                        grij = i;
                        gkolom = j;
                        gsteennr = z;
                    }
                    ontdoezet(i,j,z);
                }
            }
        }
    }
    return totwin/aantalm;
}
