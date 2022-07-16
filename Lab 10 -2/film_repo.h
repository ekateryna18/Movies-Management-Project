#pragma once

#include "film.h"
#include "validator.h"
#include <string>
#include <vector>
#include <algorithm>
using std::vector;

using std::stringstream;
using std::to_string;
using std::cout;
typedef Film Element;
#define INITIAL_CAPACITY 5
#include <ostream>

using std::ostream;

class FilmRepo
{
private:
	vector<Film> allFilms;
public:
	/*
	Constructor default
	Alocam loc pentru 5 elemente
	*/
	FilmRepo() = default;

	/*
	Constructor de copier
	*/
	FilmRepo(const FilmRepo& ot) = delete;

	virtual vector<Film> get_all();

	virtual bool exist(const Film& f);

	virtual void add(const Element& el);

	virtual void modificare(const int id, Film f);
	/*
	Sterge un film din lista dupa id
	*/
	virtual void stergere(const int id);

	virtual auto get_by_title(string title)->vector<Film>::iterator;

	virtual int size();
	/*
	Cauta
	arunca exceptie daca nu exista film
	*/
	virtual auto find(int id)->vector<Film>::iterator;

};

class FilmRepoFile : public FilmRepo {
private:
	string filename;
	/*
	* Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	* Salveaza datele din fisier
	* Format: id, titlu, gen, an, actor
	*/
	void saveToFile();

public:
	FilmRepoFile(string fname) : FilmRepo(), filename{ fname }{
		loadFromFile();
	};
	void add(const  Element& el) override;

	void modificare(const int id, Film f) override;
	/*
	Sterge un film din lista dupa id
	*/
	void stergere(const int id) override;

	vector<Film> get_all() override;

	bool exist(const Film& f) override;

	auto get_by_title(string title)->vector<Film>::iterator override;

	int size() override;
	/*
	Cauta
	arunca exceptie daca nu exista film
	*/
	auto find(int id)->vector<Film>::iterator override;
};