# Octave-Simulator

In fisierul functions.c apelam functiile utilizate in rezolvarea taskurilor,
iar fisierul tasks.c contine functiile care corespund fiecarui task. 

Pentru a evita stocarea unor numere mari in interiorul matricelor, am respectat
conditiile specificate conform carora este necesar doar restul pozitiv al
impartirii la 10007 sau diferenta dintre acesta si 10007, in cazul in care este
negativ. Am definit R in acest sens.

Index nu este valid daca este negativ sau mai mare decat numarul de matrice
alocate pana la momentul respectiv - 1. (diferenta de 1 apare din cauza
indexarii de la 0). Pentru a verifica acest lucru, am utilizat functia
verif_index.

Task 1 - Incarcarea in memorie a unei matrice (L)

Variabila nr_matrix stocheaza numarul de elemente ale vectorului de matrice 
alocat dinamic a, deci trebuie incrementata cu 1 la fiecare operatie ce
solicita adaugarea in memorie a unei noi matrice. Din moment ce elementele sunt
indexate de la 0, accesam matricea cu numar de ordine i pe pozitia i - 1 in
vector. Pentru operatia L, citim nr_lin si nr_col, dimensiunile noii matrice,
apoi le stocam in vectorii alocati dinamic lin si col. Valorile sunt neceasare
pentru executarea urmatoarelor operatii. Pentru prima matrice alocam memorie cu
ajutorul malloc, deoarece nu este nevoie sa le initializam cu 0 (adica sa
folosim calloc), ci vom citi valorile elementelor de la tastatura. Dupa aceea,
este necesar sa alocam un vector de pointeri, in care elementul de pe pozitia i
pointeaza spre linia i a matricei. Citim in mod repetat cele nr_lin * nr_col
valori si le atribuim in matrice. Incepand cu a doua matrice pe care dorim sa
o adaugam in vector, vom realoca memoria cu cate un element in plus pentru
vectorul de matrice, iar lin si col se maresc, de asemenea, fiecare cu o
pozitie, care se completeaza ulterior cu dimensiunile citite. Este important sa
utilizam realloc pentru a mari dimensiunea vectorului cu datele deja introduse,
nu a crea altul.

Task 2 - Determinarea dimensiunilor unei matrice (D)

Dupa cum am precizat in explicatia task-ului anterior, vectorii alocati dinamic
lin si col au rolul de a stoca dimensiunile matricei cu numar de ordine index pe 
pozitia index.

Task 3 - Afisarea dimensiunilor unei matrice (P)
Index reprezinta numarul de ordine al elementului din vectorul de matrice.
Utilizam din nou vectorii lin si col pentru a parcurge matricea si a-i afisa
elementele. 

Task 4 - Redimensionarea unei matrice (C)

Pentru rezolvarea acestui task avem nevoie de 2 vectori auxiliari alocati
dinamic, vl - pentru linii - si vc - pentru coloane, in care stocam indicii
cititi pentru a realiza o parcurgere doar pe liniile si coloanele respective.
In acest mod obtinem elementele aflate la intersectia liniilor si coloanelor
date, deci redimensionarea matricei. Mai intai, stocam elementele intr-un
auxiliar, pentru a redimensiona matricea initiala fara a pierde elementele
cerute. Dupa ce am eliberat vectorii ce pointeaza spre liniile matricei si zona
completa alocata acesteia, putem adauga matricea stocata in aux. De asemenea,
actualizam informatiile in lin si col, inlocuind vechile dimensiuni cu cele
citite de la tastatura: l si c. Este important ca la final sa eliberam memoria
alocata vectorilor de indici vl si vc si matricei auxiliare aux.
 
Task 5 - Inmultirea a doua matrice (M)

Verificam daca numarul de coloane al primei matrice este egal cu numarul de
linii ale primei matrice, proprietate matematica ce asigura realizarea
operatiei de inmultire a 2 matrice. Stim ca algoritmul de rezolvare presupune
ca pentru orice linie i a primei matrice, vom parcurge a doua matrice pe
coloane. Pentru fiecare coloana calculam conform regulilor de calcul impuse* o
suma formata din produsul elementului aflat pe linia i, coloana j in prima
matrice si elementul aflat pe linia j de pe coloana respectiva din cea de a 
doua matrice. Suma obtinuta la finalul parcurgerii unei coloane reprezinta
elementul din matricea rezultat de pe linia cu acelasi indice ca linia din
prima matrice parcursa, respeciv pe coloana cu acelasi indice ca si coloana din
a doua matrice parcursa. In cazul nostru, matricea rezultat se va aloca la
finalul multimii matricelor, ceea ce presupune realocarea vectorului de matrice
cu o dimensiune cu o unitate mai mare si actualizarea vectorilor lin si col.
Utilizam o alta proprietate matematica conform careia matricea produs are
numarul de linii egal cu numarul linii ale primei matrice si numarul de coloane
egal cu numarul de coloane ale celei de a doua matrice.

Task 6 - Sortarea matricelor (O)

Este necesar sa alocam dinamic un vector in care stocam suma elementelor
fiecarei matrice. Sumele sunt calculate prin parcurgerea vectorului de matrice
si calculand pentru matricea de pe pozitia i sum[i], respectand regulile de
calcul impuse*. In continuare, vom sorta vectorul de sume, actualizand la
fiecare pas in cadrul caruia se realizeaza o interschimbare si datele stocate
in vectorii lin si col, respectiv vectorul de matrice a. In caz contrar, dupa
sortare nu am mai putea identifica carui indice ii corespundea initial fiecare
suma. La final trebuie eliberata memoria alocata vectorului de sume.

Task 7 - Transpunerea unei matrice (T)

Transpunerea unei matrice se realizeaza prin transformarea liniilor in coloane.
Daca ne-am propune sa modificam matricea fara auxiliare, datele stocate initial
ar fi actualizate constant si nu ar asigura acuratetea algoritmului. Asadar,
alocam dinamic o matrice auxiliara cu numar de linii egal cu numarul de coloane
al matricei de pe pozitia index si respectiv numar de coloane egal cu numarul de
linii al matricei de pe pozitia index. Este necesar sa parcurgem matricea din
cerinta pe coloane, iar auxiliara pe linii. La fiecare pas atribuim
auxiliarului pozitia curenta din matricea de pe pozitia index pentru a
transpune matricea. La final putem elibera zona de memorie de la index, unde
vom plasa transpusa. Este necesar sa actualizam si vectorii de dimensiuni lin
si col, deoarece dimensiunile au fost inversate odata cu transpunerea.
 
Task 8 - Ridicarea unei matrice la o putere in timp logaritmic (R)

Pentru a ridica matricea de pe pozitia index la putere in mod neeficient,
consideram 3 matrice a, b si c. a si b sunt chiar matricea de pe pozitia index,
iar c reprezinta rezultatul inmultirii celor 2. La fiecare pas, b devine c, iar 
in c se stocheaza noile valori conform algoritmului de inmultire a doua matrice.
Practic, c este a ridicata la puterea pas + 1. Cum in enunt este specificat
faptul ca ridicarea la putere se realizeaza doar pentru matricele patratice, c
va avea mereu dimensiunea n x n, ceea ce asigura corectitudinea inmultirii
dintre a si b dupa ce b primeste valorile stocate in c. Am inclus aceasta parte
in functia power, precum si dezalocarea memoriei pentru matricea auxiliara.
Pentru a ridica la putere in timp logaritmic, ar trebui ca produsul de forma
a * a *...* a sa devina a^2 * a^2 *...* a^2, insa acest lucru este posibil doar
pentru exponenti de forma 2^k. Asadar, la fiecare pas cand exponentul este un
numar de forma 2 * k + 1, inmultim matricea rezultat cu a, pentru a nu "pierde"
unitati din puterea respectiva. Pentru pasii la care exponentul este un numar
par, este necesar sa realizam inmultirea intre a si ea insusi, pentru a asigura
complexitatea logaritmica a algoritmului. Practic, la fiecare pas par puterea
lui a se dubleaza si exponentul se injumatateste, iar la fiecare pas impar se
actualizeaza matricea rezultat prin inmultirea cu a^(2*k) si exponentul se
micsoreaza cu 1.

Task 9 - Eliberarea memoriei unei matrice (F)

Eliberam mai intai vectorii ce pointeaza spre liniile matricei, ca apoi sa
putem elibera intreaga zona de memorie rezervata acesteia. Pentru a nu avea
discontinuitati si a ocupa ineficient memoria, deplasam toate elementele care
urmeaza dupa matricea eliberata cu o pozitie la stanga, pentru a completa zona
ramasa libera. Tinem cont de faptul ca numarul de matrice alocate se micsoreaza
cu o unitate, iar din cauza deplasarii matricelor, valorile stocate in vectorii
de dimensiuni lin si col sunt decalate. Deci este necesar sa deplasam cu o
pozitie spre stanga si pe acestia.

Task 10 - Eliberarea tuturor resurselor (Q)

Parcurgem vectorul de nr_matrix matrice, eliberand mai intai vectorul de
pointeri spre liniile matricei, iar apoi intreaga zona alocata matricei. La
finalul parcurgerii, putem elibera intregul vector de matrice. Nu ne mai raman
decat vectorii de dimensiuni, lin si col.

Task 11 - Alte situatii

In cazul in care este citit un caracter diferit de majustulele mentionate in
task-uri (separatorii nu se iau in considerare), afisam mesajul de eroare
corespunzator.
