


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>



template <typename T>
struct Wezel {
	T data;
	Wezel<T>* nastepny;
	Wezel<T>* poprzedni;

};

template <typename T>
struct lista {
	Wezel<T>* glowa;
	Wezel<T>* ogon;
	int wielkosc;

	lista<T>() {
		glowa = nullptr;
		ogon = nullptr;
		wielkosc = 0;
	}



	void dodawanie_na_koncu(T dane) {
		// tworzymy nowy w�ze�
		Wezel<T>* nowy_wezel = new Wezel<T>;
		nowy_wezel->data = dane;

		if (wielkosc == 0) {   //sprawdzam czy jest pusta
			glowa = nowy_wezel;  //no jak jest to ustawiam glowe i ogonek na adres tego nowego
			ogon = nowy_wezel;
			nowy_wezel->nastepny = nullptr; //jak jest pusta to nastepny to null
			nowy_wezel->poprzedni = nullptr;
		}
		else {
			nowy_wezel->nastepny = nullptr;   ///bo ogonek
			nowy_wezel->poprzedni = ogon; //poprzedni ustawia na ten co teraz jest ogon
			ogon->nastepny = nowy_wezel; //lacze stary z nowym
			ogon = nowy_wezel;   //daje do ogona adres nowego, co jest koniec listy
		}

		wielkosc += 1;
	}
	void dodawanie_na_poczatku(T dane) {
		Wezel<T>* nowy_wezel = new Wezel<T>; //alo pamieci dla nwzl//schowac do funkcji
		nowy_wezel->data = dane;
		if (wielkosc == 0) {
			glowa = nowy_wezel;
			ogon = nowy_wezel;
			nowy_wezel->nastepny = nullptr;
			nowy_wezel->poprzedni = nullptr;

		}
		else {
			nowy_wezel->nastepny = glowa;
			nowy_wezel->poprzedni = nullptr;
			glowa->poprzedni = nowy_wezel;
			glowa = nowy_wezel;

		}
		wielkosc += 1;
	}

	void usuwanie_ostatniego() {
		if (wielkosc == 0) {
			return;
		}
		else if (wielkosc == 1) {
			Wezel<T>* do_usuniecia = glowa;
			glowa = nullptr;
			ogon = nullptr;
			delete do_usuniecia;
			wielkosc -= 1;

		}
		else {
			Wezel<T>* do_usuniecia = ogon;
			Wezel<T>* nowy_ogon = ogon->poprzedni;//*  //nowy ogon to poprzedni wezel
			nowy_ogon->nastepny = nullptr;
			ogon = nowy_ogon;
			wielkosc -= 1;
			delete do_usuniecia;
		}
	}

	void usuwanie_pierwszego() {
		if (wielkosc == 0) {
			return;
		}
		else if (wielkosc == 1) {
			Wezel<T>* do_usuniecia = glowa;
			glowa = nullptr;
			ogon = nullptr;
			delete do_usuniecia;
		}
		else {
			Wezel<T>* do_usuniecia = glowa;
			Wezel<T>* nowa_glowa = glowa->nastepny;
			nowa_glowa->poprzedni = nullptr;
			glowa = nowa_glowa;
			wielkosc -= 1;
			delete do_usuniecia;
		}
	}
	void zwracanie_i_ele(int i) {
			if (0 <= i && i < wielkosc) {
				Wezel<T>* pomocnik = glowa;
				for (int j = 0; j < i; j++) {
					pomocnik = pomocnik->nastepny;
				}
				std::cout << pomocnik->data;
			}
			else
			{
				std::cout << "zly indeks";
			}
			
	}
	void podmiana_elementu(int i,T nowe_dane) {
		if (0 <= i && i < wielkosc) {
			Wezel<T>* pomocnik = glowa;
			for (int j = 0; j < i; j++) {
				pomocnik = pomocnik->nastepny;
			}
			pomocnik->data = nowe_dane;
		}
		else
		{
			std::cout << "zly indeks";
		}
	}
	void wyswietlanie_listy() {
		Wezel<T>* pomocnik = glowa;
		while (pomocnik != nullptr) {
			std::cout << pomocnik->data << std::endl;
			pomocnik = pomocnik->nastepny;
		}
	}
	void czysczenie_listy() {
		Wezel<T>* pomocnik = glowa;
		while (pomocnik!=nullptr) {
			Wezel<T>* nastepny = pomocnik->nastepny;
			delete pomocnik;
			pomocnik = nastepny;
		}
		glowa = nullptr;
		ogon = nullptr;
		wielkosc = 0;
	}
	
};


//int stary_main() {
//	lista<double> l;
//	l.dodawanie_na_koncu(7.3);
//	l.dodawanie_na_koncu(3.4);
//	l.dodawanie_na_koncu(2.3);
//	l.wyswietlanie_listy();
//
//}

 int main()
 {
 	int tablica[4];

 	srand(time(0));
 	lista<int> l;

 	
 	const int Maxo = 6; //maks rzad wielkosci
	for (int o = 1; o <= Maxo; o++) {  //po rz wielkosci
		const int N = pow(10, o);
		clock_t t1 = clock();
		//dodawanie elementow
		for (int i = 0; i < N; i++) {
			l.dodawanie_na_koncu(rand() % 1000); ///no i dodanie do listy
		}
		clock_t t2 = clock();
		double czas_dodwania = (double)t2 - (double)t1;
		czas_dodwania/= CLOCKS_PER_SEC;//przeliczam z cykli na sekundy
		double sredni_dodawania = czas_dodwania / N;
		std::cout << "Dla N " << N << std::endl;
		std::cout << "Czas dodawania: " << czas_dodwania << std::endl;
		std::cout << "�redni czas dodania: " << sredni_dodawania << std::endl;
		//wyszukiwanie elementow

		t1 = clock();
		for (int i = 0; i < N; i++) {
			l.usuwanie_ostatniego();
		}
		t2 = clock();
		double czas_usuwania = (double)t2 - (double)t1;
		czas_usuwania/= CLOCKS_PER_SEC;
		double sredni_usuwania = czas_usuwania / N;
		std::cout << "Czas usuwania:  " << czas_usuwania << std::endl;
		std::cout << "Sredni czas usuwania elemmentu: " << sredni_usuwania << std::endl;
		l.czysczenie_listy();
	}
 	return 0;
 }















