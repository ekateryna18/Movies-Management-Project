#include "CosInchirieri.h"

using std::shuffle;

void CosInch::addFilmToCart(const Film& f) {
	this->inchirieri.push_back(f);
}

void CosInch::emptyCart() {
	this->inchirieri.clear();
}

void CosInch::addRandomFilms(vector<Film> originalFilms, int howMany) {
	shuffle(originalFilms.begin(), originalFilms.end(), std::default_random_engine(std::random_device{}()));
	while (inchirieri.size() < howMany && originalFilms.size() > 0) {
		inchirieri.push_back(originalFilms.back());
		originalFilms.pop_back();
	}
}

const vector<Film>& CosInch::getAllFilms() {
	return this->inchirieri;
}