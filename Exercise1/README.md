# ESERCIZIO 1

## Indice:
* compilazione ed esecuzione;
* relazione;
---
## COMPILAZIONE ED ESECUZIONE:
### Test:
Recarsi nella cartella "Exercise1", da terminale digitare `make run_test` per compilare ed eseguire i test di Unity.
### App:
Recarsi nella cartella "Exercise1", fornire un file *.csv (le righe del csv devono avere la seguente struttura:  "_id: < int >, field1: < char * >, field2: < int >, field3: < float >\n_" )nella directory "Dataset", scrivere il path del file (nel Makefile) come primo argomento di esecuzione, seguito da un parametro (il campo da ordinare), e una lettera (q=quicksort | i=insertionsort).

_sorting_lib_app  <file_esempio> < 1 | 2 | 3 > < q | s >_

Da terminale digitare `make sorting_lib_app` per compilare ed eseguire l'app.

>Nota: L'esecuzione produce un file "sorted_record.csv" (contiene il file "records.csv" ordinato in maniera crscente secondo i parametri) nella directory "dataset".
---
## RELAZIONE:
 **Stima tempi ordinamento(secondi):**
 
campi | insertionsort | quicksort
----- | ------------- | ---------  
field1 (char *)| N\A | 13
field2 (int)| N\A | 23
field3 (float)| N\A | 25

**Commento:**

L'insertionsort non termina in tempi accettabili (>10min) per tutti e 3 i campi come previsto, data la complessità O(n<sup>2</sup>) e la dimensione dell'input.


Il quicksort termina in tempi brevi, nonostante la complessità O(n<sup>2</sup>) (che però è nlogn nel caso medio), anche grazie alla struttura del `partition`, che tripartisce l'array in elementi minori, uguali e maggiori al pivot; è grazie a questa struttura che l'ordinamento sulle stringhe impiega meno tempo (sebbene la comparazione di stringhe sia più esosa in termini di calcolo) poichè vi sono parecchie stringhe uguali.
