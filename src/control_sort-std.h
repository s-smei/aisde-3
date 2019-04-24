/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
//  Autor: Adam Wojtasik

/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#ifndef _CONTROL_SORTOWANIE_H_
#define _CONTROL_SORTOWANIE_H_

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Flagi sterujące standardowymi algorytmami sortowania
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWAGA: niektóre algorytmy sortowania korzystają z procedur składowych innych algorytmów (lub nawet z całych algorytmów)
// zatem poniższe flagi mogą wpływać na różne algorytmy, nie tylko na algorytmy związane z nazwą danej flagi
// Przykład: sortowanie szybkie dla małych zbiorów korzysta z sortowania przez wstawianie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*******************************************************************************
// Flaga aktywacji/deaktywacji alokacji dodatkowej tablicy
#define SORTOWANIE_W_MIEJSCU     nie   // tak – sortowanie w miejscu: alokowana jest tylko tablica główna dostępna pod wskaźnikiem array
                                       // nie - sortowanie nie w miejscu: alokowana jest druga tablica o takich samych rozmiarach dostępna pod wskaźnikiem arrayBis


//*******************************************************************************
// Flagi sterujące sortowaniem przez selekcję
#define SELEKCJA_START_OD_PRAWEJ          nie   // nie – rozpoczęcie sortowania od najmniejszych kluczy (z "lewej" strony tablicy)
                                                // tak – rozpoczęcie sortowania od największych kluczy (z "prawej" strony tablicy)
#define SELEKCJA_INDEX                    tak   // nie - każdy kolejny rekord spełniający warunek jest od razu przenoszony na "pierwsze" miejsce
                                                // tak - znajdowany jest indeks najlepszego rekordu w całej tablicy i dopiero wtedy ten rekord trafia na "pierwsze" miejsce

//*******************************************************************************
// Flagi sterujące sortowaniem przez wstawianie
#define WSTAWIANIE_START_OD_PRAWEJ        nie   // nie – rozpoczęcie sortowanie od najmniejszych kluczy (z "lewej" strony tablicy)
                                                // tak – rozpoczęcie sortowanie od największych kluczy (z "prawej" strony tablicy)
#define WSTAWIANIE_SHELL                  nie   // nie - zwykłe wstawianie, tak - sortowanie Shella z wstawianiem
#define WSTAWIANIE_BISEKCJA               nie   // szukanie miejsca do wstawienia: nie - przegląd bezpośredni, tak - bisekcja

#endif
