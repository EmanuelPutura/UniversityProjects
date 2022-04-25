#ifndef COATSTABLEMODEL_H
#define COATSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

#include <domain/TrenchCoat/TrenchCoat.h>

#include <business/CoatsService.h>

class CoatsTableModel : public QAbstractTableModel {
private:
    CoatsService& service;
    bool basket_entities;
public:
    explicit CoatsTableModel(CoatsService& service, bool basket_entities = false, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // COATSTABLEMODEL_H
