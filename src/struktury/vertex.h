//
//  Created by Adam Wojtasik on 02/04/2017.
//  Copyright © 2017 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef vertex_h
#define vertex_h

#include <cmath>
#include "error.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Klasa abstrakcyjna reprezentująca węzeł w drzewie binarnym
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Vertex{
protected:
    Vertex* left;
    Vertex* right;
	
// Konstruktory, destruktor
public:
    Vertex() : left(nullptr), right(nullptr) {}
    Vertex(Vertex* l, Vertex* r,class TreeHead* org = nullptr) : left(l), right(r) {}
	Vertex(Vertex* l, Vertex* r, Vertex* f, class TreeHead* org = nullptr) : left(l), right(r) {}
    virtual ~Vertex(){ delete left; delete right; }
	virtual void clear(){ left = right = nullptr; }

// Dostęp do potomków i rodzica
	void setLeft(Vertex* l){ left = l; }
	void setRight(Vertex* r){ right = r; }
	Vertex* getLeft(){ return left; }
	Vertex* getRight(){ return right; }

// Klasy pochodne muszą przeciążyć operatory porównań
	virtual bool operator >  (Vertex&) const = 0;
	virtual bool operator >= (Vertex&) const = 0;
	virtual bool operator <  (Vertex&) const = 0;
	virtual bool operator <= (Vertex&) const = 0;
	virtual bool operator == (Vertex&) const = 0;
	virtual bool operator != (Vertex&) const = 0;

// Obliczanie wysokości drzewa
	int calculateHeight(){
		int depthLeft = 0;
		int depthRight = 0;
		if(left != nullptr) depthLeft = left->calculateHeight();
		if(right != nullptr) depthRight = right->calculateHeight();
		return fmax(depthLeft, depthRight)+1.;
	}

// Wymaganie na metody pomocnicze, które trzeba zdefiniować w klasach pochodnych
	virtual bool addNewVertex(Vertex*) = 0;
	virtual Vertex* createEmptyVertex() = 0;
	virtual bool isEmpty() = 0;

	virtual void display(std::string, int=0)=0;

// Metody pomocnicze niezależne od rodzaju węzła (posługują się metodami definiowanymi w węzłach pochodnych)
// "Rysowanie" węzła na konsoli jako elementu drzewa
	void displayTree(int level, int format){
		if(right != nullptr) right->displayTree(level+1,format);
		for(int i = 0; i < level; i++){
			for(int j = 0; j < format; j++) std::cout << " ";
		}
		display("",format);
		std::cout << std::endl;
		if(left != nullptr) left->displayTree(level+1,format);
	}

protected:
// Wstawianie do drzewa "pustych" węzłów, by uzyskać drzewo (formalnie) pełne
	void complete(const int& height, int currDepth){
		if(currDepth < height){
			if(right == nullptr){
				right = createEmptyVertex();
			}
			right->complete(height, currDepth+1);
			if(left == nullptr){
				left = createEmptyVertex();
			}
			left->complete(height, currDepth+1);
		}
	}

// Czyszczenie drzewa z "pustych" węzłów
	void clean(){
		if(right != nullptr){
			if(right->isEmpty()){ delete right; right = nullptr; }
			else right->clean();
		}
		if(left != nullptr){
			if(left->isEmpty()){ delete left; left = nullptr; }
			else left->clean();
		}
	}
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TreeHead{
protected:
	Vertex* root;
	
	TreeHead() : root(nullptr) {}
	~TreeHead(){ delete root; }
	
public:
	void setRoot(Vertex* r){ root = r; }
	Vertex* getRoot(){ return root; }
	
	virtual void testTree() = 0;
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* vertex_h */
