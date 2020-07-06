# ESERCIZIO 4

## Indice:
* struttura directory
* compilazione ed esecuzione;
* relazione;

## STRUTTURA DIRECTORY:
La directory "Exercise4" è suddivisa in 3 sotto-directory:
* *first attempt ("brute force")*: cartella contenente il primo tentativo di soluzione del problema con un approccio naive
* *final*: cartella contenente la versione finale della soluzione
* *iterative attempt*: cartella contenente il tentativo di conversione (di `dfs` & `dfsinit`) da ricorsivo a iterativo della versione finale (directory "final") della soluzione



## COMPILAZIONE ED ESECUZIONE:
Per ognuna delle 3 alternative soluzioni la procedura è la medesima: copiare i file `Makefile, Main.java, Graph.java` nella directory contenente le 12 cartelle di test e lo script di test ruby.
Compilare ed eseguire con `make run`.
>Nota: le due versioni final scrivono l'output su file tramite BufferedWriter, mentre la versione "brute force" reindirizza lo stdOut su file. 

## RELAZIONE:

#### Intuizione:
Sostituiamo il problema di avere un albero complessivamente più leggero con il problema di trovare l'arco di peso massimo tra due vertici. Essendo un grafo connesso, aciclico e non orientato con N nodi e N-1 archi si è sicuri che dal nodo A al nodo B vi è un solo percorso senza passare più volte sullo stesso nodo (che può attraversare più nodi): aggiungendo un arco da A a B si hanno due percorsi, quindi si può eliminare un arco qualsiasi del primo percorso ed essere certi che il grafo sia comunque connesso. Per cui per rispondere alla query basta ricercare (se presente) un arco nel percorso tra i nodi della query con peso maggiore del peso dell'arco da aggiungere ed essere certi che sostituendolo il peso complessivo dell'albero sarà minore. 
In tutte le soluzioni viene usato questo approccio, dando come output "YES" nel caso in cui si trovi un arco di peso maggiore, "NO" altrimenti. 

---

### **first attempt ("brute force")**
Crea il grafo, parsificando il file, come una HashMap<Long, Node>. Parsifica una query alla volta, e tramite una `dfs` salva in cima ad uno stack il peso massimo dal nodo di partenza al nodo attuale nell'iterazione, facendo pop nel caso in cui il percorso sia errato. Iterando dal nodo di partenza al nodo di arrivo si ottiene in cima allo stack il peso massimo del path tra il nodo di inizio e il nodo di fine della query. 

test  | tempi (sec) | diff
----- | ----- | ---------  
test1 | 61 | ok
test2 | 256| ok
test3 | 11 | ok
test4 | 13 | ok
test5 | 5  | ok
test6 | NaN | fail
test7 | 762 | ok
test8 | 956 | ok
test9 | Nan| fail
test10 | Nan | fail
test11 | Nan | fail
test12 | Nan | fail

_commento:_
 
Sebbene tutti i test che riescono a terminare sono corretti, è evidentemente una soluzione non efficiente poiche richiede una dfs per ogni query (n*O(|V|+|E|)) che motiva dei tempi così grandi, che ha portato alla ricerca di strutture più adatte alla risoluzione delle query. 

---

### **final**
Crea il grafo, parsificando il file, come un oggetto di tipo Graph, con 3 variabili: 
* vertices = la rappresentazione del grafo tramite una HashMap<K,V>, K=identificatore del nodo, V=adiacenti del nodo rappresentati a loro volta tramite una seconda HashMap<K,V>, K=identificatore del nodo adiacente, V=peso dell'arco tra i due nodi;
*  cenTree[#numeroNodi] = array di nodeUtil contenente informazioni utili alla computazione della decomposizione centroide dell'albero, comprende  il numero di sotto-nodi, il padre e il livello (facenti riferimento alla decomposizione) dell'iesimo nodo;
*  maxW = HashMap<K,V> usata per salvare il peso massimo da un nodo al centroide di un livello, K=Pair<livello, nodo>, V=peso. 

#### Funzionamento:
* **decomposizione del grafo in un albero centroide (ricorsivamente)**:
 Dopo aver creato il grafo viene chiamata la `decompose`, che a sua volta chiama la `dfsinit` che calcola e salva in `cenTree[i].subNodes` il numero di sottonodi del nodo i. Successivamente calcola il centroide al livello x (con `findCentroid`) per poi chiamare `dfs` per inserire in maxW il peso massimo tra i nodi e il centroide del livello. Infine toglie il centroide, ricalcola `decompose` per ogni sottoalbero del centroide e infine riaggiunge il centroide. Questa serie di operazioni calcolano i parent e il peso dell'arco massimo (tra il nodo e i livelli soprastanti) per ogni nodo del grafo.
* **risoluzione query**:
Successivamente si passa alla risoluzione delle query:
si parte dai nodi A e B e si fa una LCA (si risale l'albero tramite i parent di A e B finchè non si trova il primo nodo in comune) ottenendo così il livello del minimo nodo in comune (nel percorso da A e B verso root) per poi cercare in maxW (con `maxW.get(livello, A)`, `maxW.get(livello, B)`) il massimo peso tra A e il nodo in comune e B e il nodo in comune. Confrontando questi due pesi si ottiene il peso massimo nel percorso da A a B(che andrà poi confrontato con il peso della query).


>Nota 1: la costruzione dell'albero centroide richiede tempo O(n*log(n)). Ha un'altezza limitata da O(log(n)) poichè ad ogni livello la dimensione massima dei sottoalberi è dimezzata. Trovare il massimo peso nel path tra due nodi si riduce a trovare il massimo dei pesi tra: {primoNodo-->LCA, secondoNodo-->LCA}, passando al massimo per log(n) livelli.

>Nota 2: con nodo centroide si intende il nodo che, se rimosso dall'albero, produce una foresta in cui ogni albero ha #nodi < n/2

>Nota 3: alla riga 55 di `Main.java` si è deciso di "gestire" l'eccezione di Stack Overflow (discussa in seguito) per permettere un'agevole visualizzazione dei tempi di esecuzione. 

test  | tempi (sec) | diff
----- | ----- | ---------  
test1 | 1.28 | ok
test2 | 2.65(fail) | ok
test3 | 0.48 | ok
test4 | 0.74 | ok
test5 | 0.31 | ok
test6 | NaN | fail
test7 | 0.97 | ok
test8 | 2.84(fail) | ok
test9 | NaN | fail
test10 | NaN | fail
test11 | NaN | fail
test12 | NaN | fail

_commento:_\
Questa soluzione permette l'attraversamento alla ricerca del massimo di 2*log(n) livelli nel caso peggiore, riducendo notevolmente la complessità come si evince dai tempi.

Tuttavia, il codice, da una parte richiede due strutture di n vertici (`vertices`, `cenTree`) e una terza di massimo n*log(n) (`maxW`) occupando in maniera consistente la Heap, e dall'altra attua la decomposizione appoggiandosi esclusivamente su funzioni ricorsive, causando nei casi più critici `Stack Overflow`.   
 
---

### **iterative attempt**

Data l'eccezione sollevata dalla soluzione ricorsiva _final_ si è provato un approccio iterativo, modificando le funzioni critiche nella decomposizione del grafo (`dfsinit`, `dfs`). Tuttavia si è immediatamente notato il peggioramento nei tempi di esecuzione, per cui si è evitato di indigare ulteriormente questa soluzione, lasciandola solo parzialmente corretta, prediligendo la versione ricorsiva come soluzione corretta. 