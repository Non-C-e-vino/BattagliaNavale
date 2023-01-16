Note di implementazione

Informazioni generali
Nella creazione del progetto si è cercato di applicare le caratteristiche di modularità 
e riutilizzabilità proprie della programazione orientata agli oggetti. E' stata anche inclusa la possibilità
di modificare a piacimento alcune variabili di gioco, quali la grandezza della griglia, la quantità 
di navi in gioco per tipo, il numero di turni, dal file gameVars.h, secondo le restrizioni indicate 
sul suddetto file.

Ottimizzazione
Inizialemente il file di log veniva aperto e chiuso ad ogni turno,
ma e' evidente (grazie al profiler di VS) che questo sia molto inefficiente soprattutto
se si registrano lunghe partite tra Bot, quindi i file rimangono sempre aperti 
durante l'esecuzione (grazie a InLogger e OutLogger).
I messaggi su terminale vengono minimizzati in caso di partite tra bot.

Problemi strutturali
L'idea iniziale era di mentanere separate le classi generatrici di input (che implementano Player) e il GameHandler.
e' pero' diventato sempre piu' evidente che il giocatore computer (Bot) deve accedere
a informazioni di GameHandler che che vanno al di la' dell'incapsulamento di quest'ultimo,
quindi Bot e' stata resa sua classe interna. Per quanto questa soluzione possa avere un senso logico,
sarebbe sicuramente piu' pratico se GameHandler potesse simulare la giocata di Bot, 
senza che quest'ultimo generi effettivamente delle coordinate in forma testuale
che vanno poi riconvertite, passando per i loop di gioco. E' anche vero che in
questo modo si andrebbe a complicare la gestione dei log.
Anche Hull sarebbe dovuta diventare interna a Ship, ma, sinceramente, non mi e' ancora chiaro se
una classe virtuale pura puo' avere in se' classi interne non virtuali pure. Sono quindi
pubblichi dei metodi che sarebbe meglio non lo fossero ( Ship::set_damage(), Ship::heal() ).

Problemi di leggibilita'
L'uso delle convenzioni per i nomi poteva essere migliore (es. distinguere dati
membro con la notazione m_datoMembro) .
Gli oggetti di classe XY non vengono dichiarati sempre sotto lo stesso nome 
(ad es. "c", "ref", "xy"), e la scrittura risulta ambigua in quanto quando si 
accede al membro xy[2] si scrive spesso xy[indiceOggettoXY].xy[IndiceArrayMembro] .
L'intero sistema di gestione delle coordinate in forma testuale risulta inutilmente
complicato per via di mancanza di esperienza e tentativi di microottimizzazione evitabili.
