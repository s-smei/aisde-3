//
//  Autor:         Dominik Kasprowicz
//  Modifications: Adam Wojtasik
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef generator_h
#define generator_h

#include <cmath>
#include "stos.h"

//***************** Klasa SequenceGenerator ******************
class SequenceGenerator : public Stack<Iterator> {
public:
    // Funkcje obliczające wartość kolejnego elementu ciągu sterującego
    // dla sortowania Shella. Argumentem może być indeks poprzedniego (!) elementu.
    virtual Iterator nextHvalue(Iterator) const = 0;

    // Funkcja pozwalająca generować różne ciągi sterujące dla sortowania Shella.
    // Kolejne elementy ciągu są odkładane na stos.
    // Argumentem funkcji jest wartość, której nie może przekroczyć ostatni element ciągu.
protected:
    void generate(Iterator maksIndex);
};
//*********** Koniec klasy SequenceGenerator *************

//*********** Klasy wyprowadzone z klasy SequenceGenerator *************
class KnuthSequenceGenerator : public SequenceGenerator {
public:
    KnuthSequenceGenerator(const Iterator maksIndex) { generate(maksIndex); }

protected:
    Iterator nextHvalue(Iterator i) const {
        return (pow(3, (long)i) - 1)/2;
    }
};

class SedgewickSequenceGenerator : public SequenceGenerator
{
public:
    SedgewickSequenceGenerator(const Iterator maksIndex) { generate(maksIndex); }

protected:
    Iterator nextHvalue(Iterator i) const {
        return (1<<(2*(long)i)) + 3*(1<<((long)i-1)) + 1;
    }
};

class TokudaSequenceGenerator : public SequenceGenerator
{
public:
    TokudaSequenceGenerator(const Iterator maksIndex) { generate(maksIndex); }

protected:
    Iterator nextHvalue(Iterator i) const {
        return ceil((pow(9,(long)i) - pow(4,(long)i)) / (5*pow(4,(long)i-1)));
    }
};

/* TA KLASA CZEKA NA IMPLEMENTACJĘ FUNKCJI GENERUJĄCEJ CIĄG */
/* W RAZIE POTRZEBY MOŻNA UTWORZYĆ WIĘCEJ PODOBNYCH KLAS */
class CustomSequenceGenerator : public SequenceGenerator {
protected:
    Iterator nextHvalue(const Iterator i) const {
        /* ZAMIAST "1" MUSIMY ZWRÓCIĆ i-TY ELEMENT CIĄGU! */
        return 1;
    }
};
//*********** Koniec klas wyprowadzonych z klasy SequenceGenerator *************

inline void SequenceGenerator::generate(Iterator maksIndex){
    Iterator i = 1;    // Indeks elementu
    Iterator elem = 1; // Wartosc elementu - pierwszy to zawsze 1

    while(elem <= maksIndex){
        (*this) += elem;
        elem = this->nextHvalue(i++);
    };
}


#endif /* generator_h */
