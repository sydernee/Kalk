Feedback sul progetto
===================== 
In seguito si riporta il feedback(commentato ove ritenuto necessario) lasciato dal professor Ranzato sul progetto.

Correttezza
-----------
> Nelle classi c'è un puntatore a `MatrixController` che viene impostato al tipo giusto 
(`MatrixController`, `SquareMatrixController`, etc) che richiama a sua volta i metodi `sum` e
subtract di `MatrixController` (non ridefiniti) che loro volta chiamano il metodo
`operator+` e `operator-` di `Matrix`. Perché ridefinire tali metodi in `SquareMatrix` e `SparseMatrix`?

TODO

Orientazione agli oggetti
-------------------------
> La classe `Network` ha vari metodi virtuali, ma nemmeno una classe derivata

La scelta di dichiarare, ove sensato, virtuali i metodi deriva dalla 
[open-world assumption](https://en.wikipedia.org/wiki/Open-world_assumption).

>`operator+` e `operator-` sono definite direttamente, ma non utilizzano logica virtuale: come
può funzionare il polimorfismo su di esse?

TODO

> Oltre a questo, c'è molta duplicazione di codice tra le diverse implementazioni di queste funzioni

Da rivedere la costruzione della [vista di Network](cpp/view/NetworkManager.cpp)
e i metodi insiemistici in [NetworkController](cpp/controller/NetworkController.cpp).

Funzionalità
------------
Nessuna osservazione a riguardo.

GUI
---
> gui sufficiente

Relazione
---------
> relazione discreta
