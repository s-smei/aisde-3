//
//  Created by Adam Wojtasik on 10/04/2018.
//  Copyright © 2018 Politechnika Warszawska. All rights reserved.
//

// Uwaga: zawartość tego pliku to część definicji klasy BstHead reprezentującej "głowę" drzewa BST

// Przykładowy test operacji na drzewie BST
void testTree(){
	cout << "------- Drzewo oryginalne -------" << endl;
	wypiszNaKonsole(false);

	getRoot()->rotateLeft(getRootHandle());
	cout << "------- Drzewo po rotacji korzenia w lewo -------" << endl;
	wypiszNaKonsole(false);

	getRoot()->getLeft()->rotateRight(getRoot()->getLeftHandle());
	cout << "------- Drzewo po rotacji prawego potomka korzenia w lewo -------" << endl;
	wypiszNaKonsole(false);
}



