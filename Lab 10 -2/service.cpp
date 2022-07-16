#include "service.h"
#include "film_repo.h"
#include "film.h"

#include <functional>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>

using std::copy_if;
using std::sort;

/*
Adauga un nou film
*/
void FilmService::addFilm(int id, const string& title, const string& genre, int year, const string& actor) {
	Film f{ id, title, genre, year, actor };
	repo.add(f);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, f));
}

void FilmService::deleteFilm(int id) {
	auto index = repo.find(id);
	Film f = (*index);
	Film film_sters{ f.getId(), f.getTitle(), f.getGenre(), f.getYear(), f.getActor() };
	repo.stergere(id);
	undoActions.push_back(std::make_unique<UndoStergere>(repo, film_sters));

}

void FilmService::modifyFilm(int id, const string& title, const string& genre, int year, const string& actor) {
	Film f{ id, title, genre, year, actor };
	auto index = repo.find(id);
	Film film_vechi = (*index);
	repo.modificare(id, f);
	undoActions.push_back(std::make_unique<UndoModificare>(repo, film_vechi));
}

vector<Film> FilmService::sortbytitle() {
	vector<Film> sorted{ repo.get_all() };
	sort(sorted.begin(), sorted.end(), cmpTitle);
	return sorted;
}

vector<Film> FilmService::sortbyactor() {
	vector<Film> sorted{ repo.get_all() };
	sort(sorted.begin(), sorted.end(), cmpActor);
	return sorted;
}

vector<Film> FilmService::sortbyyear() {
	vector<Film> sorted{ repo.get_all() };
	sort(sorted.begin(), sorted.end(), cmpGen);
	sort(sorted.begin(), sorted.end(), cmpAn);
	return sorted;
}

vector<Film> FilmService::filterByTitle(char litera) {
	vector<Film> all{ repo.get_all() };
	vector<Film> filtered_list{};
	copy_if(all.begin(), all.end(), back_inserter(filtered_list), [litera](const Film& f) {
		return f.getTitle()[0] == litera;
		});
	return filtered_list;
}

vector<Film> FilmService::filterByYear(int an) {
	vector<Film> all{ repo.get_all() };
	vector<Film> filtered_list{};
	copy_if(all.begin(), all.end(), back_inserter(filtered_list), [an](const Film& f) {
		return f.getYear() == an;
		});
	return filtered_list;
}


void FilmService::addToCart(string titlu) {
	auto i = repo.get_by_title(titlu);
	currentCart.adauga((*i));
}

size_t FilmService::addRandomToCart(int howmany) {
	currentCart.umple(howmany);
	return currentCart.lista().size();
}

void FilmService::emptycart() {
	currentCart.goleste();
}

vector<Film> FilmService::getCartFilms() {
	return currentCart.lista();
}

void FilmService::undo() {
	if (undoActions.empty()) {
		throw FilmRepoException{ "No more undo operations to do" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}