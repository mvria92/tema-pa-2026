# Board-Game Simulation — Proiectarea Algoritmilor

Proiectul implementează simularea completă a unui joc de tip *board-game*, împărțit în trei etape principale: gestiunea datelor inițiale (jucători, hartă, misiuni), turneul de lupte 1v1 și parcurgerea optimă a hărții folosind algoritmul A*.

---

## 📋 Cerințele Temei

### 1. Înscrierea și organizarea datelor
* **1.1 Jucători:** Citirea din fișierul `jucatori.csv` (nume, energie, abilitate) și stocarea într-o **coadă** (listă simplu înlănțuită), asignând fiecărui jucător un ID unic incremental.
* **1.2 Harta jocului:** Citirea din `harta.txt` și descompunerea acesteia în 3 matrici alocate dinamic:
  * Matricea valorilor căsuțelor (0 pentru liber, 1 pentru obstacol);
  * Matricea costurilor de deplasare pe linii (orizontală);
  * Matricea costurilor de deplasare pe coloane (verticală).
* **1.3 Misiuni:** Citirea coordonatelor de start $(X_i, Y_i)$ și destinație $(X_f, Y_f)$ din `misiuni.csv` și stocarea lor într-o **stivă** (listă simplu înlănțuită).

---

### 2. Turneul de lupte între jucători
* **2.1 Arbore Binar de Căutare (BST) & Arbore de Concurs:**
  * Inserarea jucătorilor din coadă într-un BST pe baza nivelului de energie.
  * Conversia de jos în sus (bottom-up) a BST-ului într-un **arbore de concurs** cu noduri de luptă (`><`), conform celor 4 cazuri din cerință.
* **2.2 Desfășurarea luptelor & Top k:**
  * Simularea luptelor de la frunze spre rădăcină. Câștigătorul fiecărui meci își mărește energia conform formulei:  
    $$E_{jc} = \max(E_{j1}, E_{j2}) + \vert{}E_{j1} - E_{j2}\vert{}$$
  * Determinarea primilor $k$ jucători câștigători (unde $k = 2^p \le n$, cu $p$ maxim).

---

### 3. Deplasarea pe hartă (Algoritmul A*)
* Atribuirea fiecărui jucător câștigător din Top $k$ a unei misiuni extrase din stivă.
* Rularea algoritmului **A\*** pentru determinarea drumului de cost minim între start și destinație, folosind:
  * O coadă cu priorități (Min-Heap);
  * Euristica Manhattan: $h(n) = \vert{}n.x - d.x\vert{} + \vert{}n.y - d.y\vert{}$;
  * Funcția de cost: $f(n) = g(n) + \text{min\_cost} \cdot h(n)$.
* La fiecare pas, energia jucătorului scade cu costul tranziției. Dacă energia devine $\le 0$, misiunea este considerată eșuată.

---

## 🛠️ Detalii de Implementare și Complexități

* **Structuri de date alese:**
  * Coadă și Stivă pentru parsarea rapidă $\mathcal{O}(1)$ la inserare/extragere.
  * Arbori binari pentru organizarea ierarhică a luptelor.
  * Min-Heap pentru extragerea nodului cu cost minim în A* în timp $\mathcal{O}(\log V)$.
* **Managementul memoriei:** Toate alocările dinamice sunt verificate împotriva scurgerilor de memorie (fără erori Valgrind).

---

## 🚀 Compilare și Rulare

Compilarea proiectului se realizează cu `make`:
```bash
make
./main
