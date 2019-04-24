//
//  Autor:         Dominik Kasprowicz
//  Modificacje:   Adam Wojtasik
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef stos_h
#define stos_h

#include "error.h"

//******************* Klasa Stack ********************
template <typename T>
class Stack {
    class Element{
        T value;
        Element *next;

        Element(T war, Element* wsk) : value(war), next(wsk) {}
        ~Element() { delete next; }

        void remove(Element** dest){ *dest = next; this->next= nullptr; delete this; }

        T getValue(){ return value; };
        friend class Stack;
    };

private:
    Element* first;

public:
    Stack<T>() : first(nullptr) {}
    virtual ~Stack() { delete first; }

    void operator+=(const T& war){ first = new Element(war, first); }

    T remove(){
        if(first == nullptr) throw Error(ERR_EmptyStack);
        T ret = first->getValue();
        first->remove(&first);
        return ret;
    }
    void reset(){ delete first; first = nullptr; }
};
//******************* End of Stack ********************


#endif // stos_h
