# ESERCIZIO 2

## Indice:
* compilazione ed esecuzione;
* relazione;
---
## COMPILAZIONE ED ESECUZIONE:
### Test:
Recarsi nella cartella "Exercise2" (./), da terminale digitare `make RunTest` per compilare ed eseguire i test di JUnit.
### App:
Recarsi nella cartella "Exercise2" (./), fornire nella directory "dataset" un file *.txt da correggere come primo parametro, e come secondo un file *.txt, che verrà utlizzato come dizionario per trovare le edit distance migliori. Scrivere i path dei due file rispettivamente nel Makefile e compilare ed eseguire con `make EditDistanceApp`. 

_make EditDistanceApp <path_file_da_correggere> <path_dizionario>_

>Nota 1: L'esecuzione produce il file "corrected.txt" nella directory "dataset", contenente: la parola, l'intero che rappresenta l'edit distance migliore, le parole con quell'edit distance e il tempo impiegato per ciascuna parola.   

>Nota 2: L'app non è case sensitive e ignora la punteggiatura.   

>Nota 3: Per memorizzare le parole trovate si è scelto di utilizzare la LinkedList nativa di Java.   

>Nota 4: Alla riga 71 in "EditDistance.java" si controlla che l'edit distance minore ("best") sia minore della differenza tra le lunghezze della parola sul dizionario e di quella sul testo; anche se come controllo non è il più stringente (poichè parole con lunghezza simile potrebbero avere comunque edit distance alta), evita i controlli su parole di lunghezza molto diversa (e quindi con edit distance banalmente maggiore).

>Nota 5: Alla riga 80 in "EditDistance.java" viene controllato il valore dell'edit distance trovato all'iterazione x, se è uguale a 0 il ciclo while viene interrotto, dato che se la parola è corretta non esistono parole con edit distance migliore.
---
## RELAZIONE:
 **Stima tempi ricerca(secondi):**

 edit_distance | edit_dystance_dyn
 ------------- | ---------  
2291 | 42

**Commento:**   
Il tempo massimo con la versione edit_distance_dyn per singola parola è circa 2.5 secondi, tempo medio 1 secondo, <1 sec per parole con editdistance = 0 (vedi Nota 5).  
Il tempo massimo con la versione edit_distance per singola parola circa 900  secondi, tempo medio tra i 5 e i 10 secondi (ma che pò arrivare fiono ai 20 secondi), <1 sec per parole con editdistance = 0 (vedi Nota 5).
Si nota chiaramente che la versione con memoizzazione migliora sensibilmente i tempi di esecuzione(da circa 40 minuti a 42 secondi), poichè riduce la complessità evitando di ricalcolare i casi già analizzati riducendola ad un accesso in tabella di costo O(1).