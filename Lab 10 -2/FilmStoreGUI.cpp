#include "FilmStoreGUI.h"
#include "cosGUI2.h"
#include "CartGUIModel.h"

using std::to_string;

void FilmStoreGUI::initializeGUIComponents() {
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editId = new QLineEdit;
	editTitlu = new QLineEdit;
	editGen = new QLineEdit;
	editAn = new QLineEdit;
	editActor = new QLineEdit;

	lyForm->addRow(lblId, editId);
	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblGen, editGen);
	lyForm->addRow(lblAn, editAn);
	lyForm->addRow(lblActor, editActor);
	btnAddFilm = new QPushButton("Adauga film");
	lyForm->addWidget(btnAddFilm);

	btn_delete_film = new QPushButton("Sterge film dupa ID");
	lyForm->addWidget(btn_delete_film);

	btnModifyFilm = new QPushButton("Modifica film dupa ID");
	lyForm->addWidget(btnModifyFilm);

	lyLeft->addWidget(form);


	//sortare filme
	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtActor);
	lyRadioBox->addWidget(radioSrtTitlu);
	lyRadioBox->addWidget(radioSrtAnGen);

	btnSortFilms = new QPushButton("Sorteaza filme");
	lyRadioBox->addWidget(btnSortFilms);

	lyLeft->addWidget(groupBox);

	//filtrare
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterTitlu = new QLineEdit();
	lyFormFilter->addRow(lblFilterTitlu, editFilterTitlu);
	btnFilterFilmTitlu = new QPushButton("Filtreaza filme dupa titlu");
	lyFormFilter->addWidget(btnFilterFilmTitlu);

	editFilterAn = new QLineEdit();
	lyFormFilter->addRow(lblFilterAn, editFilterAn);
	btnFilterFilmAn = new QPushButton("Filtreaza filme dupa an");
	lyFormFilter->addWidget(btnFilterFilmAn);

	lyLeft->addWidget(formFilter);

	//buton undo
	btnUndo = new QPushButton("Undo");
	lyLeft->addWidget(btnUndo);

	//buton deschidere cos
	btnopencart = new QPushButton("Open cart");
	lyLeft->addWidget(btnopencart);

	//buton pentru a reincarca datele
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);

	//btn pt painter
	btnPainter = new QPushButton("Open cart painter");
	lyLeft->addWidget(btnPainter);

	//componenta right-tabelul cu filme
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	this->filmlist = new QListWidget;

	//int noLines = 10;
	//int noColumns = 5;
	//this->tableFilms = new QTableWidget(noLines, noColumns);

	////header-ul tabelului
	//QStringList tblHeaderList;
	//tblHeaderList << "Id" << "Titlu" << "Gen" << "An" << "Actor";
	//QListWidgetItem* Id = new QListWidgetItem(QString::fromStdString("Id"));
	//
	//this->tableFilms->setHorizontalHeaderLabels(tblHeaderList);

	////optiune pentru a se redimensiona celulele din tabel in functie de continut
	//this->tableFilms->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//lyRight->addWidget(tableFilms);
	lyRight->addWidget(filmlist);

	

	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void FilmStoreGUI::ReloadFilmList(vector<Film> films) {
	/*this->tableFilms->clearContents();
	this->tableFilms->setRowCount(films.size());

	int lineNumber = 0;
	for (auto& film : films) {
		this->tableFilms->setItem(lineNumber, 0, new QTableWidgetItem(QString::number(film.getId())));
		this->tableFilms->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.getTitle())));
		this->tableFilms->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(film.getGenre())));
		this->tableFilms->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(film.getYear())));
		this->tableFilms->setItem(lineNumber, 4, new QTableWidgetItem(QString::fromStdString(film.getActor())));
		lineNumber++;
	}*/
	this->filmlist->clear();

	for (auto& film : films) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(to_string(film.getId()) + "--" + film.getTitle() + "--" + film.getGenre() + "--" + to_string(film.getYear()) + "--" + film.getActor()));
		this->filmlist->addItem(item);
	}
}

void FilmStoreGUI::connectSignalsSlots() {
	//adauga filme
	QObject::connect(btnAddFilm, &QPushButton::clicked, this, &FilmStoreGUI::guiAddFilm);

	//stergere
	QObject::connect(btn_delete_film, &QPushButton::clicked, this, &FilmStoreGUI::guiDeleteFilm);

	//update
	QObject::connect(btnModifyFilm, &QPushButton::clicked, this, &FilmStoreGUI::guiModify);

	//undo
	QObject::connect(btnUndo, &QPushButton::clicked, this, &FilmStoreGUI::undo);

	QObject::connect(btnPainter, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new CartDraw{ srv.getCos()};
		drawWindow->show();
		});

	//cart
	//QObject::connect(btnopencart, &QPushButton::clicked, this, &FilmStoreGUI::open_cart);

	QObject::connect(btnopencart, &QPushButton::clicked, this, [&]() {
		//auto listWnd = new CosGUIcuLista{ srv.getCos() };
		auto listWnd = new CosGUIcuListaModel{ srv.getCos() };
		listWnd->show();
		});
	//sortare 
	QObject::connect(btnSortFilms, &QPushButton::clicked, [&]() {
		if (this->radioSrtActor->isChecked())
			this->ReloadFilmList(srv.sortbyactor());
		else if (this->radioSrtTitlu->isChecked())
			this->ReloadFilmList(srv.sortbytitle());
		else if (this->radioSrtAnGen->isChecked())
			this->ReloadFilmList(srv.sortbyyear());
		});

	//filtrare dupa titlu
	QObject::connect(btnFilterFilmTitlu, &QPushButton::clicked, [&]() {
		string title = this->editFilterTitlu->text().toStdString();
		this->ReloadFilmList(srv.filterByTitle(title[0]));
		});

	QObject::connect(btnFilterFilmAn, &QPushButton::clicked, [&]() {
		int an = this->editFilterAn->text().toInt();
		this->ReloadFilmList(srv.filterByYear(an));
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->ReloadFilmList(srv.getAll());
		});

}

void FilmStoreGUI::guiAddFilm() {
	try {
		//preluare info din QLineEdit-uri
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		string actor = editActor->text().toStdString();
		int id = editId->text().toInt();
		int an = editAn->text().toInt();

		editId->clear();
		editTitlu->clear();
		editGen->clear();
		editAn->clear();
		editActor->clear();

		this->srv.addFilm(id, titlu, gen, an, actor);
		this->ReloadFilmList(this->srv.getAll());

		QMessageBox::information(this, "INFO", QString::fromStdString("Film adaugat cu succes!"));
	}
	catch (FilmRepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void FilmStoreGUI::guiDeleteFilm() {
	try {
		int id = editId->text().toInt();
		editId->clear();

		this->srv.deleteFilm(id);
		this->ReloadFilmList(srv.getAll());

		QMessageBox::information(this, "INFO", QString::fromStdString("Film sters!"));
	}
	catch (FilmRepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void FilmStoreGUI::guiModify() {
	try {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		string actor = editActor->text().toStdString();
		int id = editId->text().toInt();
		int an = editAn->text().toInt();

		editId->clear();
		editTitlu->clear();
		editGen->clear();
		editAn->clear();
		editActor->clear();

		this->srv.modifyFilm(id, titlu, gen, an, actor);
		this->ReloadFilmList(srv.getAll());

		QMessageBox::information(this, "INFO", QString::fromStdString("Film modificat!"));
	}
	catch (FilmRepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void FilmStoreGUI::undo() {
	this->srv.undo();
	this->ReloadFilmList(srv.getAll());
	QMessageBox::information(this, "INFO", QString::fromStdString("Undo efectuat cu succes!"));
}

void FilmStoreGUI::open_cart() {
	guicos.show();
}