Kalk
====
Il progetto è stato sviluppato da [Timoty Granziero](https://github.com/Vashy) e [Andrea Nalesso](https://github.com/sydernee) per il corso di *Programmazione ad Oggetti* del prof. [Francesco Ranzato](http://www.math.unipd.it/~ranzato/), corso di laurea in [Informatica](http://informatica.math.unipd.it/) dell'Università degli Studi di Padova, a.a. 2017/2018.


<!--- TOC --->
1. [Introduzione](README.md#introduzione)
1. [Specifiche di progetto](README.md#specifiche-di-progetto)
1. [Compilazione ed esecuzione](README.md#compilazione-ed-esecuzione)
   1. [C++](README.md#c)
   1. [Java](README.md#java)
1. [Manuale utente](README.md#manuale-utente)
1. [Feedback del docente e problemi noti](README.md#feedback-del-docente-e-problemi-noti)
1. [Segnalazione malfunzionamenti](README.md#segnalazione-malfunzionamenti)
1. [Licenza](README.md#licenza)


Introduzione
------------
Scopo del progetto didattico è lo sviluppo di una calcolatrice *estendibile*, in grado di gestire i calcoli di diversi tipi di dati, tra cui:
* `Matrix`
* `SquareMatrix`, sottotipo di `Matrix`
* `SparseMatrix`, sottotipo di `Matrix`
* `Network`

Questi tipi di dati sono implementati sia in **C++** che in **Java**: l'implementazione in C++ è fornita di una interfaccia grafica
sviluppata usando il framework Qt, mentre quella in Java è corredata da un esempio di uso (la classe [`Use`](java/dataTypes/Use.java)).

Specifiche di progetto
---------------------
Le specifiche di progetto sono visionabili e scaricabili [dall'omonima cartella](specifica/specificaProgetto.pdf).

Compilazione ed esecuzione
--------------------------
### C++
Per compilare il progetto in *C++*, è stato fornito il file `kalk.pro`
all'interno della cartella [`cpp`](cpp/). Posizionarsi all'interno di quella cartella ed eseguire il comando
`qmake` per generare il Makefile, poi `make` per compilare i sorgenti. A questo punto, sarà presente
un eseguibile denominato `kalk`; è sufficiente eseguirlo con il comando `./kalk` (mentre si è posizionati
all'interno della cartella [`cpp`](cpp/)) per lanciare l'applicativo.

### Java
Per compilare il progetto in *Java*, compilare i sorgenti *java* dalla directory [`java`](java/)
del progetto con il comando 

```bash
    javac kalkException/*.java dataTypes/*.java
```

Dopodiché eseguire lo script della classe *Use* invocando il comando (sempre dalla cartella java)
```bash
    java dataTypes.Use
```
Manuale utente
---------------
Sebbene l'interfaccia sia intuitiva, è stata realizzata una [breve guida utente](usermanual.md).

Feedback del docente e problemi noti
------------------------------------
Il feedback con i problemi riscontrati dal docente in fase di valutazione del progetto è [liberamente disponibile](report.md).

Segnalazione malfunzionamenti
-----------------------------
In caso di problemi o malfunzionamenti, si invita ad aprire una [issue](https://github.com/sydernee/Kalk/issues).

Licenza
-------
Il materiale presente in questa repository, ove non diversamente specificato, è rilasciato con licenza [GNU General Public License v3.0](LICENSE).
