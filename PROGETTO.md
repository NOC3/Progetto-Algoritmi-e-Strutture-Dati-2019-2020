# INFO PROGETTO:

## Struttura directory esercizi:
Si è deciso di strutturare il progetto in directory separate per esercizio, in maniera differenziata per i due linguaggi utilizzati. Per ogni esercizio vi è un file "README.md" contenente le istruzioni di compilazione ed esecuzione e la relazione relativa all'applicazione da sviluppare. Inoltre, tutti i makefile presentano il comando make clean.
### *C*
Si è deciso di strutturare i file nell'usuale struttura del C (bin, include, src), con l'aggiunta di una cartella "test" (contenente i test di Unity) e una "app" (contenente l'applicazione).

### *Java*
Si è deciso di strutturare la directory in modo che tutti i file relativi all'esercizio fossero all'interno della stessa directory.

## Directory "Dataset"
Come prerequisito di esecuzione delle applicazioni, viene richiesta la creazione di una directory "dataset" all'esterno della cartella contenente il progetto (./../dataset/), in cui è possibile porre i file necessari all'esecuzione delle applicazioni ( *.csv, *.txt) e in cui verranno scritti i file di output. È comunque possibile modificare il path dei file di input nei makefile e cambiare la directory di output all'interno del codice.