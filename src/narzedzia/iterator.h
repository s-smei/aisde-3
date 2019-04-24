//
//  Created by Adam Wojtasik on 19/03/2017.
//  Copyright © 2017 Wojtasik Adam. All rights reserved.
//

#ifndef Iterator_h
#define Iterator_h

#include <iostream>
using namespace std;
#include "control.h"


#if IMPLEMENTACJA_RAPORT

#define POROWNANIE liczbaPorownan++;
#define DODAWANIE  liczbaDodawan++;
#define DZIELENIE  liczbaDzielen++;
#define MNOZENIE   liczbaMnozen++;
#define IMPLEMENTACJA_RESET  Iterator::reset();
#define IMPLEMENTACJA_START  Iterator::start();
#define IMPLEMENTACJA_STOP   Iterator::stop();
#define RAPORT_IMPLEMENTACJA Iterator::raport();

#else

#define POROWNANIE
#define DODAWANIE
#define DZIELENIE
#define MNOZENIE
#define IMPLEMENTACJA_RESET
#define IMPLEMENTACJA_START
#define IMPLEMENTACJA_STOP
#define RAPORT_IMPLEMENTACJA

#endif

class Iterator{

#if IMPLEMENTACJA_RAPORT
    static unsigned long liczbaDodawan;
    static unsigned long liczbaMnozen;
    static unsigned long liczbaDzielen;
    static unsigned long liczbaPorownan;

	static unsigned long liczbaDodawanBak;
	static unsigned long liczbaMnozenBak;
	static unsigned long liczbaDzielenBak;
	static unsigned long liczbaPorownanBak;

public:
    static void reset(){
		liczbaDodawan = liczbaMnozen = liczbaDzielen = liczbaPorownan = 0L;
		liczbaDodawanBak = liczbaMnozenBak = liczbaDzielenBak = liczbaPorownanBak = 0L;
	}

	static void start(){
		liczbaDodawan  = liczbaDodawanBak;
		liczbaMnozen   = liczbaMnozenBak;
		liczbaDzielen  = liczbaDzielenBak;
		liczbaPorownan = liczbaPorownanBak;
	}
	static void stop(){
		liczbaDodawanBak  = liczbaDodawan;
		liczbaMnozenBak   = liczbaMnozen;
		liczbaDzielenBak  = liczbaDzielen;
		liczbaPorownanBak = liczbaPorownan;
	}

	static void raport(){
        cout << "Implementacja: " << endl;
        cout << "   porownania: " << liczbaPorownanBak << endl;
        cout << "   dodawania:  " << liczbaDodawanBak << endl;
        cout << "   mnozenia:   " << liczbaMnozenBak << endl;
        cout << "   dzielenia:  " << liczbaDzielenBak << endl;
    }
#endif

private:
    long value;
public:

    operator long(){ return value; }

    Iterator() : value(0L) {}
    Iterator(long i) : value(i) {}

    bool isOdd(){ DZIELENIE return value%2; }

    Iterator& operator =  (long i) { value =       i;   return *this; }
    Iterator& operator =  (int  i) { value = (long)i;   return *this; }

    bool operator >  (long i) { POROWNANIE return value >        i; }
    bool operator >  (int  i) { POROWNANIE return value >  (long)i; }
    bool operator >= (long i) { POROWNANIE return value >=       i; }
    bool operator >= (int  i) { POROWNANIE return value >= (long)i; }
    bool operator <  (long i) { POROWNANIE return value <        i; }
    bool operator <  (int  i) { POROWNANIE return value <  (long)i; }
    bool operator <= (long i) { POROWNANIE return value <=       i; }
    bool operator <= (int  i) { POROWNANIE return value <= (long)i; }
    bool operator == (long i) { POROWNANIE return value ==       i; }
    bool operator == (int  i) { POROWNANIE return value == (long)i; }
    bool operator != (long i) { POROWNANIE return value !=       i; }
    bool operator != (int  i) { POROWNANIE return value != (long)i; }

    bool operator >  (const Iterator& i) { POROWNANIE return value >  i.value; }
    bool operator >= (const Iterator& i) { POROWNANIE return value >= i.value; }
    bool operator <  (const Iterator& i) { POROWNANIE return value <  i.value; }
    bool operator <= (const Iterator& i) { POROWNANIE return value <= i.value; }
    bool operator == (const Iterator& i) { POROWNANIE return value == i.value; }
    bool operator != (const Iterator& i) { POROWNANIE return value != i.value; }

	Iterator& operator++()                          { DODAWANIE value++; return *this; }
	Iterator  operator++(int)                       { Iterator bufor = *this; DODAWANIE ++value; return bufor; }
	Iterator& operator--()                          { DODAWANIE value--; return *this; }
	Iterator  operator--(int)                       { Iterator bufor = *this; DODAWANIE --value; return bufor; }

	Iterator& operator+ (const Iterator& two) const { static Iterator bufor; DODAWANIE bufor.value = value + two.value; return bufor; }
    Iterator& operator+ (long x)              const { static Iterator bufor; DODAWANIE bufor.value = value + x;         return bufor; }
    Iterator& operator+ (int  x)              const { static Iterator bufor; DODAWANIE bufor.value = value + (long)x;   return bufor; }
    Iterator& operator+=(const Iterator& two)       {                        DODAWANIE value += two.value;              return *this; }
    Iterator& operator+=(long x)                    {                        DODAWANIE value +=       x;                return *this; }
    Iterator& operator+=(int  x)                    {                        DODAWANIE value += (long)x;                return *this; }
    Iterator& operator- (const Iterator& two) const { static Iterator bufor; DODAWANIE bufor.value = value - two.value; return bufor; }
    Iterator& operator- (long x)              const { static Iterator bufor; DODAWANIE bufor.value = value - x;         return bufor; }
    Iterator& operator- (int  x)              const { static Iterator bufor; DODAWANIE bufor.value = value - (long)x;   return bufor; }
    Iterator& operator-=(const Iterator& two)       {                        DODAWANIE value -= two.value;              return *this; }
    Iterator& operator-=(long x)                    {                        DODAWANIE value -=       x;                return *this; }
    Iterator& operator-=(int  x)                    {                        DODAWANIE value -= (long)x;                return *this; }
    Iterator& operator/ (const Iterator& two) const { static Iterator bufor; DZIELENIE bufor.value = value/two.value;   return bufor; }
    Iterator& operator/ (long x)              const { static Iterator bufor; DZIELENIE bufor.value = value/x;           return bufor; }
    Iterator& operator/ (int  x)              const { static Iterator bufor; DZIELENIE bufor.value = value/(long)x;     return bufor; }
    Iterator& operator* (const Iterator& two) const { static Iterator bufor; MNOZENIE  bufor.value = value*two.value;   return bufor; }
    Iterator& operator* (long x)              const { static Iterator bufor; MNOZENIE  bufor.value = value*x;           return bufor; }
    Iterator& operator* (int  x)              const { static Iterator bufor; MNOZENIE  bufor.value = value*(long)x;     return bufor; }
};
#if IMPLEMENTACJA_RAPORT
#ifdef _MAIN_CPP_
unsigned long Iterator::liczbaDodawan = 0L;
unsigned long Iterator::liczbaMnozen = 0L;
unsigned long Iterator::liczbaDzielen = 0L;
unsigned long Iterator::liczbaPorownan = 0L;
unsigned long Iterator::liczbaDodawanBak = 0L;
unsigned long Iterator::liczbaMnozenBak = 0L;
unsigned long Iterator::liczbaDzielenBak = 0L;
unsigned long Iterator::liczbaPorownanBak = 0L;
#endif
#endif

#endif /* Iterator_h */
