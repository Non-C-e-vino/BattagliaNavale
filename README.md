# BattagliaNavale
Progetto finale corso Laboratorio di Programmazione

Status: implementate le funzioni principali, in attesa di revisione e aggiunta commenti

## Configurazione

```bash
git clone git@github.com:Non-C-e-vino/BattagliaNavale.git
```
```bash
cd ./BattagliaNavale
cmake -S . -B ./build
```

## Utilizzo
Una volta buildato il progetto, saranno prodotti due eseguibili. Per giocare a battaglia navale:

```bash
cd ./build
```

```bash
./battaglia_navale
```

Il gioco salva tutte le mosse valide effettuate durante l'ultima partita disputata sul file /build/log.txt.

Per riguardare o stampare su di un altro file una partita salvata su di un file log, utilizzare il secondo eseguibile:

```bash
./replay
```
## Note
Allo stato attuale e' possibile modificare alcune variabili di gioco, quali numero navi per tipo, grandezza griglia di gioco, numero massimo turni, modificando il file gameVars.h (sara' necessario un rebuild). Per visualizzare correttamnete un replay, le variabili devono essere nello stesso stato di quando e' stata disputata la partita salvata.
