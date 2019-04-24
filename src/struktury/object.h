//
//  Created by Wojtasik Adam on 20/03/2017.
//  Copyright © 2017 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef object_h
#define object_h

#include "control.h"

#include <iostream>
using namespace std;
#include "control.h"

#if ALGORYTM_RAPORT

#define POROWNANIE_KLUCZ   liczbaPorownan++;
#define KOPIOWANIE_REKORD  liczbaZamian++;

#define ALGORYTM_RESET     Object::reset();
#define ALGORYTM_START     Object::start();
#define ALGORYTM_STOP      Object::stop();

#define RAPORT_ALGORYTM    Object::raport();

#else

#define POROWNANIE_KLUCZ
#define KOPIOWANIE_REKORD

#define ALGORYTM_RESET
#define ALGORYTM_START
#define ALGORYTM_STOP

#define RAPORT_ALGORYTM

#endif

#ifdef OPOZNIENIE
#define DELAY    Object::delay(OPOZNIENIE);
#else
#define DELAY
#endif

class Object{
protected:
	static unsigned int currKeyID;
	bool empty;

#if ALGORYTM_RAPORT
protected:
    static unsigned long liczbaPorownan;
    static unsigned long liczbaZamian;
	static unsigned long liczbaPorownanBak;
	static unsigned long liczbaZamianBak;

public:
    static void reset(){
		liczbaPorownan = liczbaZamian = 0L;
		liczbaPorownanBak = liczbaZamianBak = 0L;
	}
	static void start(){
		liczbaPorownan = liczbaPorownanBak;
		liczbaZamian = liczbaZamianBak;
	}
	static void stop(){
		liczbaPorownanBak = liczbaPorownan;
		liczbaZamianBak = liczbaZamian;
	}
	static void raport(){
        cout << "Algorytm: " << endl;
        cout << "   porownania: " << liczbaPorownanBak << endl;
        cout << "   kopiowania: " << liczbaZamianBak << endl;
    }
#endif

public:
	static void setKeyID(int num){ currKeyID = num; }
	Object(bool emp = false) : empty(emp) {}
	virtual ~Object(){}
	
	bool isEmpty(){ return empty; }

    static void delay(long x) {
        double d = 0.; for(long i = 0; i < x; i++){ for(long j = 0; j < x; j++){for(long k = 0; k < x; k++){ d += 1.; }}}
    }

	virtual bool operator >  (Object& source) const = 0;
	virtual bool operator >= (Object& source) const = 0;
	virtual bool operator <  (Object& source) const = 0;
	virtual bool operator <= (Object& source) const = 0;
	virtual bool operator == (Object& source) const = 0;
	virtual bool operator != (Object& source) const = 0;

	virtual void randomDataFill(Iterator) = 0;
	virtual void uniqueDataFill(Iterator) = 0;

	virtual void display(int){}
};

#if ALGORYTM_RAPORT
#ifdef _MAIN_CPP_
unsigned long Object::liczbaZamian = 0L;
unsigned long Object::liczbaPorownan = 0L;
unsigned long Object::liczbaZamianBak = 0L;
unsigned long Object::liczbaPorownanBak = 0L;

unsigned int Object::currKeyID = 0;
#endif
#endif


class ObjectINT : public Object {
protected:
	long value;

public:
    virtual long getKey() { return value; }
    virtual void setKey(long x) { value = x; }
   
    ObjectINT() : value(0) {}
	ObjectINT(bool emp) : Object(true), value(0) {}
    ObjectINT(long x) : value(x) {}

    virtual void randomDataFill(Iterator maxValue){ value = (long)(((double)rand()/(double)RAND_MAX)*(double)maxValue); }
    virtual void uniqueDataFill(Iterator theValue){ value = theValue; }

    bool operator >  (Object& source) const { POROWNANIE_KLUCZ return value >  dynamic_cast<ObjectINT&>(source).value; }
    bool operator >= (Object& source) const { POROWNANIE_KLUCZ return value >= dynamic_cast<ObjectINT&>(source).value; }
    bool operator <  (Object& source) const { POROWNANIE_KLUCZ return value <  dynamic_cast<ObjectINT&>(source).value; }
    bool operator <= (Object& source) const { POROWNANIE_KLUCZ return value <= dynamic_cast<ObjectINT&>(source).value; }
    bool operator == (Object& source) const { POROWNANIE_KLUCZ return value == dynamic_cast<ObjectINT&>(source).value; }
    bool operator != (Object& source) const { POROWNANIE_KLUCZ return value != dynamic_cast<ObjectINT&>(source).value; }

    ObjectINT& operator = (const ObjectINT& source){ KOPIOWANIE_REKORD value = source.value; DELAY return *this; }
	
	virtual void display(int form){
		if(form <= 0) cout << value << " ";
		else{
			int s = 1;
				if(!empty){
				long rob = value;
				if(rob < 0){ rob = -rob; s=2; }
				while(true){
					rob/=10;
					if(rob > 0) s++;
					else break;
				}
			}
			
			if(s > form) throw Error(ERR_LargePrint);
			int i = 0;
			for(; i < (form-s)/2-1; i++) cout << " ";
			if(empty) cout << "-";
			else cout << value;
			i += s;
			for(; i < form; i++) cout << " ";
		}
	}
};

class ObjectDoubleINT : public ObjectINT {
	long value1;
public:
	long getKey() { return (currKeyID?value1:value); }
	void setKey(long x) { currKeyID?value1=x:value=x; }
	
	ObjectDoubleINT() : value1(0) {}
	ObjectDoubleINT(long x1, long x2) : ObjectINT(x1), value1(x2) {}
	
	void randomDataFill(Iterator maxValue){ value1 = (long)(((double)rand()/(double)RAND_MAX)*(double)maxValue); ObjectINT::randomDataFill(maxValue); }
	void uniqueDataFill(Iterator theValue){ value1 = theValue; ObjectINT::uniqueDataFill(theValue); }
	
	bool operator >  (Object& source) const { POROWNANIE_KLUCZ return (currKeyID?value1:value) >  (currKeyID?dynamic_cast<ObjectDoubleINT&>(source).value1:dynamic_cast<ObjectDoubleINT&>(source).value); }
	bool operator >= (Object& source) const { POROWNANIE_KLUCZ return (currKeyID?value1:value) >= (currKeyID?dynamic_cast<ObjectDoubleINT&>(source).value1:dynamic_cast<ObjectDoubleINT&>(source).value); }
	bool operator <  (Object& source) const { POROWNANIE_KLUCZ return (currKeyID?value1:value) <  (currKeyID?dynamic_cast<ObjectDoubleINT&>(source).value1:dynamic_cast<ObjectDoubleINT&>(source).value); }
	bool operator <= (Object& source) const { POROWNANIE_KLUCZ return (currKeyID?value1:value) <= (currKeyID?dynamic_cast<ObjectDoubleINT&>(source).value1:dynamic_cast<ObjectDoubleINT&>(source).value); }
	bool operator == (Object& source) const { POROWNANIE_KLUCZ return (currKeyID?value1:value) == (currKeyID?dynamic_cast<ObjectDoubleINT&>(source).value1:dynamic_cast<ObjectDoubleINT&>(source).value); }
	bool operator != (Object& source) const { POROWNANIE_KLUCZ return (currKeyID?value1:value) != (currKeyID?dynamic_cast<ObjectDoubleINT&>(source).value1:dynamic_cast<ObjectDoubleINT&>(source).value); }
	
	ObjectDoubleINT& operator = (const ObjectDoubleINT& source){ KOPIOWANIE_REKORD value = source.value; value1 = source.value1; DELAY return *this; }
	
	virtual void display(int){
		cout << " " << value << "-" << value1;
	}
};

#endif /* object_h */



