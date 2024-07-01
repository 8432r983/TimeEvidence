#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "NameListModel.h"

NameListModel::NameListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    beginResetModel();

    loadNamesFromFile();

    endResetModel();

}

int NameListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_names.count();
}

QVariant NameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_names.size() || role != NameRole)
        return QVariant();

    if (role == NameRole)
        return m_names.at(index.row());

    return QVariant();
}

QHash<int, QByteArray> NameListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

void NameListModel::loadNamesFromFile()
{
    QFile file("C:/Users/leona/OneDrive/Documents/untitled/NameList.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QString line = file.readLine().trimmed();
            if (!line.isEmpty())
                m_names.append(line);
        }
        file.close();
    }
}

