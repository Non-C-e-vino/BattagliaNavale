# BattagliaNavale
Progetto finale corso Laboratorio di Programmazione

Status: terminate funzioni principali, revisione e aggiunta commenti

## Configurazione

```bash
git clone git@github.com:Non-C-e-vino/BattagliaNavale.git
```
```bash
cd ./BattagliaNavale
cmake -S . -B ./Build
```

## Utilizzo
Una volta buildato il progetto, saranno prodotti due eseguibili. Per giocare a battaglia navale:
```bash
./<percorso dove e' stato salvato l'eseguibile>/battaglia_navale.exe
```
L'estensione puo' essere diversa

Per riguardare le partite:
```bash
./<percorso dove e' stato salvato l'eseguibile>/replay.exe
```
## Note
Allo stato attuale e' possibile modificare alcune variabili di gioco, quali numero navi per tipo, grandezza griglia di gioco, numero massimo turni, modificando il file gameVars.h (sara' necessario un rebuild). Per visualizzare correttamnete un replay, le variabili devono essere nello stesso stato di quando e' stata disputata la partita salvata.
