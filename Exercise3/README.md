# ESERCIZIO 3

## Indice:
* compilazione ed esecuzione;
* relazione;
---
## COMPILAZIONE ED ESECUZIONE:
### Test:
Recarsi nella cartella "Exercise3" (./), da terminale digitare `make run_test` per compilare ed eseguire i test di Unity.
### App:
Recarsi nella cartella "Exercise3" (./), fornire nella directory "dataset" un file *.csv, contenente le coppie chiave-valore che si intende testare. Scrivere il path del file nel Makefile e compilare ed eseguire con `make hash_map_app`. 

_make hash_map_app <path_file_csv>_
 
 >Nota 1: Per avere una funzione di rehash in funzione della dimensione dell'array si usa (e si cosiglia fortemente la medesima scelta) una variabile globale che punta al campo size della struct HashMap. La libreria richiede di scrivere una propria funzione di hash.  

 >Nota 2: Si è scelto di scrivere una libreria aggiuntiva per la gesione apposita degli array, che contiene una funzione di ordinamento e una funzione di ricerca.
  
 >Nota 3: Si è scelto di caricare il contenuto del csv nell'array e riordinarlo solo successivamente, utilizzando l'algoritmo quicksort.    
 

---
## RELAZIONE:
 **Stima tempi (secondi):**  

 operazione | Array | Hash Map (Default) | Hash Map (Custom) 
 ----- |------------- | ---------   |---------
caricamento | 2.0 | 4.3 | 3.1
ricerca | 5.5  | 3.5    | 3.5

**Commento:**   
Dai tempi registrati si notano chiaramente i vantaggi delle rispettive strutture dati, tenendo comunque conto che per l'array si è scelto un ordinamento e una ricerca piuttosto efficienti. Rimangono comunque significativi i risultati, perchè il caricamento in una struttura statica (che non ha bisogno di rehash) richiede circa la metà di tempo rispetto a una struttura che varia nel tempo. 
>Nota: Si può comunque notare che il caricamento in una hashmap che parte da una dimensione di 10 (e richiede svariate rehash) e il caricamento di una hash map che parte da una dimensione di 5000000 (che ne richiede solamente una) influisce (per circa un 25%) comunque poco tenendo conto della memoria inizialmente allocata. Nella maggior parte dei casi un dimensione pari a 10 si presta meglio ai fini dell'applicazione evitando di allocare da subito tanta memoria che potrebbe non venire mai utilizzata.

La ricerca richiede meno tempo nell'hash map (anche grazie alle scelta del fattore di carico, che mantiene un bilanciamento tra lunghezza dell'array e lunghezza delle liste di trabocco) poichè l'accesso alla casella dell'array (nell'hash map) richiede tempo O(1) più il tempo necessario a scorrere le liste composte di pochi elementi (supponendo di avere come nel nostro caso un utilizzo sensato della funzione di rehash e sapendo che gli elementi sono estratti da [0...10 <sup>7</sup> ]); nell'array la ricerca binaria ha complessità O(log(n)). 
Su strutture di queste dimensioni (circa 6000000) abbiamo circa 15 confronti nel caso peggiore nell'array, contro i pochi confronti nella lista dell'hash map (le liste sono corte(in media 1-2 elementi)), risultando quindi più efficiente come evidenziato dai tempi in tabella.

Come previsto la quantità di chiavi trovate a quelle estratte randomicmente non è mai la stessa, comunque è sempre circa pari a (1 − 1/e) · 10 <sup>7</sup>.