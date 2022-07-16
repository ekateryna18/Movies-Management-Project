#pragma once

#include "film.h"
#include "observer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

//class for movie cart
using std::vector;
class CosInch: public Observable{
private:
	vector<Film> inchirieri;
public:
	CosInch() = default;
	/*
	*Adauga un film in lista de inchirireri
	*/
	void addFilmToCart(const Film& f);

	/*
	* Elimina toate flmele din cos
	*/
	void emptyCart();
	/*
	* Adauga un numar random de filme in lista de inchirieri
	*/
	void addRandomFilms(vector<Film> originalFilms, int howManay);
	/*
	* Returneaza un vector care contine toate filmele inchiriate
	*/
	const vector<Film>& getAllFilms();
};