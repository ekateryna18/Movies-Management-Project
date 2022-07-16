#pragma once
#include<QAbstractListModel>
#include <QBrush>
#include "film.h"
#include <vector>

using std::vector;

//class for my own table model design
class MyTableModel :public QAbstractTableModel {
	//the list containing the movies that will be put in the table
	vector<Film> films;
public:
	MyTableModel(const std::vector<Film>& films) :films{ films } {
	}
	//number of rows
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return films.size();
	}
	//number of columns
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		//if there are movies that have the year >2020, they will be coloured with red
		if (role == Qt::ForegroundRole) {
			Film f = films[index.row()];
			if (f.getYear() > 2020) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::DisplayRole) {

			Film f = films[index.row()];
			if (index.column() == 0) {
				return QString::number(f.getId());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(f.getTitle());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(f.getGenre());
			}
			else if (index.column() == 3) {
				return QString::number(f.getYear());
			}
			else if (index.column() == 4) {
				return QString::fromStdString(f.getActor());
			}
		}

		return QVariant{};
	}
	//setting the movie list after making changes to it
	void setFilms(const vector<Film>& films) {
		this->films = films;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}
};