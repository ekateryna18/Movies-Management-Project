#pragma once
#include <vector>
#include <algorithm>
#include <random>    
#include <chrono> 

#include "film.h"
#include "observer.h"
#include "film_repo.h"
using std::vector;

/*
  Clasa care implementeaza ideea de cos
  Extinde observable, astfel cei interesati se notifica in caz ca s-a schimbat ceva la Cos
*/

class CosFilm : public Observable {
	vector<Film> inCos;
	FilmRepo& rep;
public:
	CosFilm(FilmRepo& rep) : rep{rep} {}

	void adauga(const Film& f) {
		inCos.push_back(f);
		//notificam can se schimba ceva in cos
		notify();
	}

	void addbyttl(string titlu) {
		auto i = rep.get_by_title(titlu);
		adauga((*i));
	}

	auto find(int id) -> vector<Film>::iterator {
		auto f = std::find_if(inCos.begin(), inCos.end(),
			[=](const Film& film) {
				return film.getId() == id;
			});
		return f;
	}

	void sterge(int id) {
		auto poz = find(id);
		inCos.erase(poz);
		notify();
	}

	void goleste() {
		inCos.clear();
		//notificam can se schimba ceva in cos
		notify();
	}
	/*
	Umple cosul aleator
	*/
	void umple(int cate) {
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Film> all = rep.get_all();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
		while (inCos.size() < cate && all.size() > 0) {
			inCos.push_back(all.back());
			all.pop_back();
		}
		//notificam cand se schimba ceva in cos
		notify();
	}

	const vector<Film>& lista() const {
		return inCos;
	}

};