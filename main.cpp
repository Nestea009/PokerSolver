#include <iostream>
#include <iomanip>
using namespace std;

bool sonPareja(string a, string b) {
    if (a[0] == b[0]) {
        return true;
    }
    return false;
}

bool mismoPalo(string a, string b) {
    if (a[1] == b[1]) {
        return true;
    }
    return false;
}

// Transforma una mano a valores numéricos para compararlos en una escalera
void transformar(string mano[], int new_hand[]) {
    for(int i = 0; i < 5; i++) {
        if(sonPareja(mano[i], "Ax")) {
            new_hand[i] == -1;
        }
        else if(sonPareja(mano[i], "Tx")) {
            
        }
        else if(sonPareja(mano[i], "Jx")) {
            new_hand[i] == 11;
        }
        else if(sonPareja(mano[i], "Qx")) {
            new_hand[i] == 12;
        }
        else if(sonPareja(mano[i], "Kx")) {
            new_hand[i] == 13;
        }
        else {
            string a = mano[i];
            char b = a[0];
            string str(1,b);
            new_hand[i] = stoi(b);
        }
    }
}

// Checkea si el elemento está en el deck (hecho por chat gpt)
bool estaEnElDeck(string arr[], int size, string item) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == item) {
            return true; // Item found
        }
    }
    return false; // Item not found
}

// Elimina un elemento de un vector de string
void removeElement(string arr[], int &size, string element) {
    int i = 0;
    while (i < size) {
        if (arr[i] == element) {
            // Shift elements left to "erase" the element
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            size--; // Decrease the size of the array
        } else {
            i++;
        }
    }
}


void makeDeck(string deck[], int &DIM, string hand[]) {
    removeElement(deck, DIM, hand[0]);
    removeElement(deck, DIM, hand[1]);
}

// Genera un número random entre 0 y 49
int randomNum(int n) {
    return (rand() % n);
}


/*
    Pre: deck de 52 cartas
    Post: Pregunta al usuario dos cartas válidas y 
*/
void preguntarCartas(string deck[], string hand[], int &DIM) {
    string carta = "";
    do {
        cout << "Escriba una carta válida: "; 
        cin >> carta;
    } while (!estaEnElDeck(deck, DIM, carta));

    hand[0] = carta;

    do {
        cout << "Escriba otra carta válida: "; 
        cin >> carta;
    } while (!estaEnElDeck(deck, DIM, carta) || (carta == hand[0]));

    hand[1] = carta;
}

/*
    Pre: ---
    Post: Pregunta al usuario el número de iteraciones a ejecutar
*/
void preguntarIteraciones(unsigned &n) {
    cout << "Escriba el número de Flops que desea ejecutar: ";
    cin >> n;
    return;
}

bool esPareja(string mano[]) {
    for(int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if(sonPareja(mano[i], mano[j])) {
                return true;
            }
        }
    }
    return false;
}

bool esDoblesParejas(string mano[]) {
    // Primera Pareja
    for(int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if(sonPareja(mano[i], mano[j])) {

                // Segunda Pareja
                for(int a = 0; a < 4; a++) {
                    for (int b = a + 1; b < 5; b++) {
                        if(sonPareja(mano[a], mano[b]) && (mano[a] != mano[i])) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool esTrio(string mano[]) {
    for(int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if(sonPareja(mano[i], mano[j])) {
                for (int k = j+1;k < 5; k++) {
                    if (sonPareja(mano[j], mano[k]) && sonPareja(mano[i], mano[k]) && (k != i) && (k != j)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool esEscalera(string mano[]) {
    bool As = false;
    for(int i = 0; i < 5; i++) {
        if(sonPareja(mano[i], "Ax")) {      // Esto comprueba si estamos en el caso de un As
            As = true;
            break;
        }
    }
    int new_mano[5] = {};
    transformar(mano, new_mano);

    if(As) {

    }
    else {
        for (int j = 0; j > 4; j++) {
            if(!(new_mano[j] + 1 == new_mano[j+1])) {
                return false;
            }
        }
        return true;
    }
}

bool esColor(string mano[]) {
    for(int i = 0; i < 4; i++) {
        if(!mismoPalo(mano[i], mano[i+1])) {
            return false;
        }
    }
    return true;
}

bool esFull(string mano[]) {
    return false;
}

bool esPoker(string mano[]) {
    
    return false;
}

bool esStraightFlush(string mano[]) {
    if(esEscalera(mano)) {
        return true;
    }
    return false;
}

void Flop(string deck[], string hand[], unsigned &numeroParejas, unsigned &numeroDoblesParejas, unsigned &numeroTrios,
          unsigned &numeroEscaleras, unsigned &numeroColores, unsigned &numeroFullHouses,
          unsigned &numeroPokeres, unsigned &numeroStraightFlushes, int &DIM) {

    string flop[3] = {"", "", ""};
    int x = 0;

    // Saca el flop
    for (int i = 0; i < 3; i++) {
        x = randomNum(DIM);
        flop[i] = deck[x];
        removeElement(deck, DIM, flop[i]);
        cout << flop[i] << " ";
    }
    cout << " | " << endl;
    
    string mano5[5] {hand[0], hand[1], flop[0], flop[1], flop[2]};


    if(esColor(mano5)) {
        if(esStraightFlush(mano5)) {
            numeroStraightFlushes++;
        }
        else {
            numeroColores++;
        }
    }
    else if(esEscalera(mano5)) {
        numeroEscaleras++;
    }
    else if(esPareja(mano5)) {
        if(esTrio(mano5)) {
            if (esPoker(mano5)) {
                numeroPokeres++;
            }
            else  {
                numeroTrios++;
            }
        } 
        else if(esDoblesParejas(mano5)) {
            if (esFull(mano5)) {
                numeroFullHouses++;
            }
            else {
                numeroDoblesParejas++;
            }
        }
        else {
            numeroParejas++;
        }
    }

}

int main() {

    int DIM = 52;

    string deck[DIM] = {"2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks", "As",
    "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh", "Ah",
    "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd", "Ad",
    "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc", "Ac"};

    string hand[2] = {"0", "0"};
    preguntarCartas(deck, hand, DIM);
    
    unsigned n = 0; // Número de iteraciones
    preguntarIteraciones(n);

    // Variables a apuntar
    unsigned numeroParejas = 0;
    unsigned numeroDoblesParejas = 0;
    unsigned numeroTrios = 0;
    unsigned numeroEscaleras = 0;
    unsigned numeroColores = 0;
    unsigned numeroFullHouses = 0;
    unsigned numeroPokeres = 0;
    unsigned numeroStraightFlushes = 0;

    for (int i = 0; i < n; i++) { // ES posible que haya un error en el que la misma carta puede salir en el mismo Flop, aunque la eliminamos sigue pasando
        DIM = 52;
        string newDeck[DIM] = {"2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks", "As",
        "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh", "Ah",
        "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd", "Ad",
        "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc", "Ac"};
        makeDeck(newDeck, DIM, hand);
        Flop(newDeck, hand, numeroParejas, numeroDoblesParejas, numeroTrios, numeroEscaleras, numeroColores, numeroFullHouses, numeroPokeres, numeroStraightFlushes, DIM);
    }

    cout << endl << "Hay " << numeroParejas << " parejas." << endl;
    cout << "Hay " << numeroDoblesParejas << " dobles parejas." << endl;
    cout << "Hay " << numeroTrios << " trios." << endl;
    cout << "Hay " << numeroEscaleras << " escaleras." << endl;
    cout << "Hay " << numeroColores << " colores." << endl;
    cout << "Hay " << numeroFullHouses << " full houses." << endl;
    cout << "Hay " << numeroPokeres << " pokeres." << endl;
    cout << "Hay " << numeroStraightFlushes << " straight flushes." << endl;

    return 0;
}