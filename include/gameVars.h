#ifndef GAMEVARS_H
#define GAMEVARS_H

//modifibabili secondo i limiti indicati

constexpr int GRIDSIZE = 12;    //MAX 23 in quanto i caratteri 'X' 'Y' 'Z' sono riservati
constexpr int CORA = 3 *2;
constexpr int SUPP = 3 *2;
constexpr int ESPL = 2 *2;
constexpr int SHIPSN = CORA + SUPP + ESPL; //da non midificare direttamente. Deve essere pari
constexpr int MAXTURNS = 1000000000; //comprende la fase di schieramneto
constexpr char LOGFILE[] = "log.txt";

#endif