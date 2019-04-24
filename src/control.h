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

#ifndef _CONTROL_H_
#define _CONTROL_H_
#define tak 1
#define nie 0


// UWAGA. Podstawową strukturą przechowującą dane w niniejszym programie jest tablica danych (klasa Array).
// Jest to jedyna struktura stosowana w ćwiczeniu 2. W ćwiczeniu 3 stosowana jest zarówna taka tablica, jak i struktury dodatkowe służące do budowy drzew.
// W kodzie dostępne są predefiniowane rekordy, które są umieszczane w tablicy danych:
// ObjectINT       - rekord zawierający klucz typu stałoprzecinkowego (liczba całkowita) - dostępne zarównow obu ćwiczeniach
// ObjectDoubleINT - rekord zawierający dwa klucze typu stałoprzecinkowego (liczby całkowite) - dostępne zarównow obu ćwiczeniach
// HuffmanData     - rekord zawierający dane wykorzystywane w implementacji algorytmów dla drzewa Huffmana – dostępny tylko w ćwiczeniu 3.

// W ramach wykonywania ćwiczeń studenci mogą tworzyć własne typy rekordów. Typy te muszą dziedziczyć po klasie Object, w której znajduje się kilka metod
// czysto wirtualnych, więc klasy nowych rekordów powinny zdefiniować ciała tych metod. Tablicę własnych rekordów należy alokować w pliku main.c
// Nie ma potrzeby modyfikowania implementacji algorytmów (pod warunkiem poprawnego zdefiniowania własnych rekordów).

//===============================================================================
#define NUMER_INDEKSU  302494  // tu wstawić numer indeksu
// można też  "losowo" wybierać liczbę startową dla każdego uruchomienia aplikacji
//#define NUMER_INDEKSU  clock()


//===============================================================================
// Flaga określająca numer ćwiczenia
#define CWICZENIE_2        nie  // tak - ćwiczenie drugie (badanie "standardowych" algorytmów sortowania)
							    // nie - ćwiczenie trzecie (badanie algorytmów bazujących na drzewach binarnych)
// UWAGA: niektóre algorytmy w ćwiczeniu 3 mogą wykorzystywać "standardowe" algorytmy sortowania lub ich elementy,
// więc ustawienie w pliku control_sort-std.h flag sterujących "standardowymi" algorytmami może mieć znaczenie dla parametrów wydajnościowych.


//===============================================================================
// Liczność badanego zbioru
#define LICZNOSC 30

//===============================================================================
// Wypisz tablicę na ekran przed posortowaniem i po nim
#define WYPISZ_NA_KONSOLE tak

//===============================================================================
// Flaga sterująca wyborem rodzaju standardowego rekordu.
#define REKORD_Z_JEDNYM_KLUCZEM       tak  // tak - wykorzystywany jest rekord z jednym klucze, ustawienia wyboru kluczy są ignorowane
									       // nie - wykorzystywany jest rekord z dwoma kluczami. Wybór klucza do sortowania przeprowadzany jest procedurą
										   //       Object::setKeyID(0) (lub Object::setKeyID(1)) i obowiązuje wszystkie algorytmy aż do następnego wyboru

//===============================================================================
// Czy ciąg wejściowy ma być uporządkowany rosnąco lub malejąco?
// W przypadku wyzerowania obu flag uzyskuje się klucze losowane z rozkładu równomiernego.
#define CIAG_WEJSCIOWY_ROSNACY        nie  // tak - wartości kluczy dla standardowych rekordów to kolejno 0, 1, 2,...
#define CIAG_WEJSCIOWY_MALEJACY       nie  // tak - wartości kluczy dla standardowych rekordów to kolejno N-1, N-2,... gdzie N to długość ciągu

//===============================================================================
// Flaga określająca zawartość kluczy rekordów, używana tylko w przypadku braku wstępnego uporządkowania.
#define KLUCZE_UNIKATOWE        nie  // tak - wartości kluczy nie mogą się powtarzać
                                     // nie - wartości kluczy mogą się powtarzać

//===============================================================================
// Maksymalna warość klucza - powinna być >= 0.
// Używana jest tylko dla kluczy całkowitoliczbowych.
// Jest ignorowana przy ustawieniu na tak flagi KLUCZE_UNIKATOWE
// Wartość minimalna jest stała i równa 0.
#define MAX_WARTOSC_KLUCZA        0 // dla wartości == 0 flaga ta przyjmuje wartość liczności tablicy pomniejszonej o 1.

//===============================================================================
// Flagi sterujące raportem
#define ALGORYTM_RAPORT         tak  // tak - zliczane są porównania oraz kopiowania w ramach zamiany rekordów miejscami
#define IMPLEMENTACJA_RAPORT    tak  // tak - zliczane są operacje wykonane na iteratorach


//===============================================================================
// Stała służąca do sztucznego wydłużania czasu kopiowania rekordu.
// Jeżeli wykomentowana - nie ma dodatkowego przedłużania czasu kopiowania
//#define OPOZNIENIE 10

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Koniec obszaru ustawiania parametrów wykonania ćwiczeń
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++









//===============================================================================
#include "control_sort-std.h"
#include "control_drzewa.h"

//===============================================================================
// korekta ustawienia flag

#if not MAX_WARTOSC_KLUCZA
#undef MAX_WARTOSC_KLUCZA
#define MAX_WARTOSC_KLUCZA LICZNOSC-1
#endif

// Dla ćw. 3, bo niektóre algorytmy wymagają określonych wartości flag:
// Implementacja algorytmu Huffmana bazuje na wstawianiu rekordów w kierunku prawej strony tablicy.
// Drzewo poszukiwań wymaga unikatowych wartości kluczy.
// Przy drzewie poszukiwań i Huffmanie nie należy alokować dodatkowego miejsca dla "w miejscu".

#if !CWICZENIE_2
#if !WSTAWIANIE_START_OD_PRAWEJ
#undef WSTAWIANIE_START_OD_PRAWEJ
#define WSTAWIANIE_START_OD_PRAWEJ 1
#endif

#if BADANIE_BST

#if CIAG_WEJSCIOWY_ROSNACY
#undef CIAG_WEJSCIOWY_ROSNACY
#undef CIAG_WEJSCIOWY_ROSNACY 0
#endif

#if CIAG_WEJSCIOWY_MALEJACY
#undef CIAG_WEJSCIOWY_MALEJACY
#undef CIAG_WEJSCIOWY_MALEJACY 0
#endif

#if !KLUCZE_UNIKATOWE
#undef KLUCZE_UNIKATOWE
#define KLUCZE_UNIKATOWE 1
#endif

#if SORTOWANIE_W_MIEJSCU
#undef SORTOWANIE_W_MIEJSCU
#define SORTOWANIE_W_MIEJSCU 0
#endif

#elif BADANIE_HUFFMANA

#if SORTOWANIE_W_MIEJSCU
#undef SORTOWANIE_W_MIEJSCU
#define SORTOWANIE_W_MIEJSCU 0
#endif

#endif

#endif

//===============================================================================
// zmienne globalne
#if defined _MAIN_CPP_
long  licznosc = LICZNOSC;
long  seed = NUMER_INDEKSU;
#else
extern long  licznosc;
extern long  seed;
#endif //_MAIN_CPP_

#endif
