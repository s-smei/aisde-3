/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
//
//  Autor: Grzegorz Janczyk
//  drobne poprawki: Adam Wojtasik
//
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#include "kopiec.h"
#include <stdio.h>
#include <math.h>



//--------------------------------------------------------
void KopiecINT::wypiszNaKonsole(bool flag){
	
	if(flag){
    int Wie,Kol,LiWie,Ods,D,i;

		cout << endl << "Struktura kopcowa:" << endl;
		LiWie = (int)(log((double)this->lastIndex())/log((double)2));
		Ods=D=2;

		for(i=LiWie-1; i>0; i--) Ods=2*Ods+D;
		for(Wie=0; Wie<=LiWie; Wie++){
			for(Kol=1; (Kol <= pow((double)2,Wie)) && (pow((double)2,Wie)-1+Kol<=this->lastIndex()); Kol++){
				for(i=0; i<Ods; i++) printf(" ");
				printf("%2ld",this->array[(Iterator)pow((double)2,Wie)-1+Kol].getKey());
				for(i=0; i<Ods+D; i++) printf(" ");
			}
			cout << endl;
			Ods = (Ods-D)/2;
		};
		cout << "******************************************************************" << endl;
	}
	else{
		for(Iterator i = this->firstIndex(); i <= this->lastIndex(); ++i) { cout << this->array[i].getKey() << " "; }
		cout << endl << endl;
	}
}
//--------------------------------------------------------

