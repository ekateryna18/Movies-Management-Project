#pragma once
#include "cosGUI.h"
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QListWidget>
#include <QRadioButton>
#include "service.h"

using std::vector;
using std::string;
class FilmStoreGUI : public QWidget {
private:

	FilmService& srv;
	CartGUI guicos{srv};
	//add
	QLabel* lblId = new QLabel{ "Id movie: " };
	QLabel* lblTitlu = new QLabel{ "Title movie: " };
	QLabel* lblGen = new QLabel{ "Movie genre: " };
	QLabel* lblAn = new QLabel{ "Release year: " };
	QLabel* lblActor = new QLabel{ "Main actor: " };

	QLineEdit* editId;
	QLineEdit* editTitlu;
	QLineEdit* editGen;
	QLineEdit* editAn;
	QLineEdit* editActor;

	QPushButton* btnAddFilm;

	//delete
	QPushButton* btn_delete_film;

	//update
	QPushButton* btnModifyFilm;

	//cos
	QPushButton* btnopencart;

	//add forms
	QPushButton* btnPainter;

	//sort
	QGroupBox* groupBox = new QGroupBox(tr("Sort type"));

	QRadioButton* radioSrtTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radioSrtActor = new QRadioButton(QString::fromStdString("Actor"));
	QRadioButton* radioSrtAnGen = new QRadioButton(QString::fromStdString("An+Gen"));

	QPushButton* btnSortFilms;

	//filter
	QLabel* lblFilterTitlu = new QLabel{ "Filter movies(by first letter): " };
	QLabel* lblFilterAn = new QLabel{ "Filtere by release years: " };
	QLineEdit* editFilterTitlu;
	QLineEdit* editFilterAn;
	QPushButton* btnFilterFilmTitlu;
	QPushButton* btnFilterFilmAn;

	QPushButton* btnReloadData;
	QPushButton* btnUndo;

	QTableWidget* tableFilms;
	QListWidget* filmlist;

	void initializeGUIComponents();

	void connectSignalsSlots();
	void ReloadFilmList(vector<Film> films);

	
public:
	FilmStoreGUI(FilmService& filmsrv) : srv{ filmsrv } {
		initializeGUIComponents();
		connectSignalsSlots();
		ReloadFilmList(srv.getAll());
	}
	void guiAddFilm();
	void guiDeleteFilm();
	void guiModify();
	void open_cart();
	void undo();
};