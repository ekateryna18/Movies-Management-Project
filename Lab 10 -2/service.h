#pragma once

#include "film.h"
#include "film_repo.h"
#include "CosInchirieri.h"
#include "undo.h"

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <vector>
#include "cosfilm.h"

using std::function;
using std::unique_ptr;

class FilmService {
	FilmRepo& repo;
	//CosInch currentCart;
	CosFilm currentCart{repo} ;
private:
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	FilmService(FilmRepo& repo) : repo{ repo } {}
	//nu permitem copierea de obiecte FilmService
	FilmService(const FilmService& ot) = delete;

	/*
	returneaza toate filmele
	*/
	vector<Film> getAll() {
		return repo.get_all();
	}

	/*
	Adauga un film nou
	*/
	void addFilm(int id, const string& title, const string& genre, int year, const string& actor);
	/*
	sterge un film dupa id
	*/
	void deleteFilm(int id);

	/*
	modifica datele despre un film, in afara de id
	*/
	void modifyFilm(int id, const string& title, const string& genre, int year, const string& actor);

	/*
	* filtreaza dupa prima litera a titlului filmului
	*/
	vector<Film> filterByTitle(char litera);
	/*
	* filtreaza dupa anul filmului
	*/
	vector<Film> filterByYear(int an);
	/*
	sorteaza dupa titlu
	*/
	vector<Film> sortbytitle();
	/*
	sorteaza dupa an
	*/
	vector<Film> sortbyyear();
	/*
	sorteaza dupa actor
	*/
	vector<Film> sortbyactor();
	/*
	* Adauga un film in cosul de inchirieri
	*/
	void addToCart(string titlu);
	/*
	* adauga un numar random de filme in playlist
	*/
	size_t addRandomToCart(int howmany);
	/*
	* elimina toate filmele din cos
	*/
	void emptycart();
	/*
	* Returneaza un vector cu toate filmele din cos
	*/
	vector<Film> getCartFilms();

	CosFilm& getCos() {
		return currentCart;
	}

	void undo();

};