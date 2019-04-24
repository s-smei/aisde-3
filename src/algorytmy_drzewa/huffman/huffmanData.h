/******************************************************************************/
/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
    //
    //  Adam Wojtasik
    //
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#ifndef _huffmanData_h_
#define _huffmanData_h_

#include <iomanip>
#include <cmath>

#include "vertex.h"

#define setByteSize(x) HuffmanByte::setBS(x)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// klasa pomocnicza do przechowywania danych w postaci "bajtu" o zadanym rozmiarze bitowym
class HuffmanByte{
public:
    const static int stdByteSize;
    const static int maxByteSize;
private:
    static int byteSize;
public:
    static void setBS(int x){ if(x < 3 && x > maxByteSize) throw Error(ERR_ByteSize); byteSize = x; }
    static int getByteSize(){ return byteSize; }
//---------------

private:
    unsigned int value;

public:
    HuffmanByte(unsigned int x = 0) : value(x) {}

    void set(unsigned int x){ value = x; }
    unsigned int get(){ return value; }

    void setZero(){ value = 0x00; }
    void setOneToBit (int i){ value |= 0x01 << i; }
    void setZeroToBit(int i){ value = !value; setOneToBit(i); value = !value; }
    void setBit(int value, int index){ value ? setOneToBit(index):setZeroToBit(index); }

    void print(){ for(int i = byteSize-1; i >= 0; i--) cout << ((value&(0x01<<i))>>i); }
    unsigned int getValue() const { return value; }
};
#ifdef _MAIN_CPP_
const int HuffmanByte::stdByteSize = 8;
const int HuffmanByte::maxByteSize = HuffmanByte::stdByteSize*sizeof(unsigned int);
int HuffmanByte::byteSize = HuffmanByte::stdByteSize;
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class HuffmanData : public Vertex{
private:
    HuffmanByte byte;
    long count;          // liczba wystapien obiektu o danym kodzie

public:
    HuffmanData(): byte(0), count(0L) {}
    HuffmanData(const HuffmanData& sec) : Vertex(sec.left, sec.right), count(sec.count), byte(sec.byte) {}
    ~HuffmanData(){}

    static long inSize;
    static long outSize;

    void clear(){ left = right = nullptr; count = 0L; byte.setZero(); }
    void clearTree(){ delete left; left = nullptr; delete right; right = nullptr; }

    void    setByte(unsigned int b){ byte.set(b); }
    unsigned long getCount(){ return count; }
    HuffmanByte&   getByte() { return byte; }

    // przeciazone operatory porownania
    bool    operator >  (Vertex& data) const { return count >  dynamic_cast<HuffmanData&>(data).count; }
    bool    operator <  (Vertex& data) const { return count <  dynamic_cast<HuffmanData&>(data).count; }
    bool    operator >= (Vertex& data) const { return count >= dynamic_cast<HuffmanData&>(data).count; }
    bool    operator <= (Vertex& data) const { return count <= dynamic_cast<HuffmanData&>(data).count; }
	bool    operator == (Vertex& data) const { return count == dynamic_cast<HuffmanData&>(data).count; }
	bool    operator != (Vertex& data) const { return count != dynamic_cast<HuffmanData&>(data).count; }

    // przeciazone operatory de- i inkrementacji
    HuffmanData& operator ++ (int) { count += 1; return *this; }
	HuffmanData& operator -- (int) { count -= 1; return *this; }

    char byteToChar(unsigned int byte) {
        return static_cast<char>(byte);
    }

    static void printSizeDiff() {
        cout << "inSize: " << HuffmanData::inSize;
        cout << "  outSize: " << HuffmanData:: outSize;
        cout << endl;
        cout << static_cast<double>(HuffmanData::outSize) / HuffmanData::inSize << endl;
    }

    void display(string poprzedni, int=0){
        if(left == nullptr){
            if(right == nullptr){
                #if ROZMIAR_BAJTU==8
                cout << "letter: " << byteToChar(byte.getValue()) << "  ";
                #endif
                cout << "byte: "; print(); HuffmanData::inSize += ROZMIAR_BAJTU * count;
                cout << "  licznosc: " << setw(6) << count;
                cout << "  kod: "+ poprzedni << std::endl;
                HuffmanData::outSize += poprzedni.length() * count;
            }
            else right->display(poprzedni+"1");
        }
        else{
            left->display(poprzedni+"0");
            if(right != nullptr) right->display(poprzedni+"1");
        }
    }
    void print(){ byte.print(); }

    void operator = (HuffmanData& source){
        (*(Vertex*)this) = source;
        byte = source.byte;
        count = source.count;
        source.clear();
    }

	bool addNewVertex(Vertex*){ return true; }
	Vertex* createEmptyVertex(){return nullptr; }
	bool isEmpty(){ return false; }

// Przeciazony operator +
// dwa rekordy (węzły) są "dodawane" - stają się potomkami nowego węzła
    void operator+(HuffmanData& prev){
        right = new HuffmanData(*this);
        left = new HuffmanData(prev);
        count += prev.count;
        byte.setZero();
        prev.clear();
    }
};


#endif
