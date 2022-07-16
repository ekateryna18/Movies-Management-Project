#include "Lab102.h"
#include "FilmStoreGUI.h"
#include "film_repo.h"
#include "service.h"
#include "cosGUI2.h"

#include <QLabel>
#include <iostream>
#include <fstream>
using std::cout;
using std::ofstream;
#include <QtWidgets/QApplication>

void adaugactv() {
	ofstream ofs;
	ofs.open("films.txt", ofstream::out, ofstream::trunc);
	ofs << "100,Venom,horror,2021,tom hardy\n";
	ofs << "200,La La Land,musical,2016,Ryan Gosling\n";
	ofs << "300,Tabara,comedie,2021,Selly\n";
	ofs << "400,Black Panther,actiune,2018,Chadwick Boseman\n";
	ofs << "500,The conjouring,horror,2013,Vera Farmiga\n";
	ofs.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	adaugactv();
    FilmRepoFile repo{"films.txt"};
    FilmService srv{ repo };
    FilmStoreGUI gui{ srv };
    gui.show();

    return a.exec();
}
