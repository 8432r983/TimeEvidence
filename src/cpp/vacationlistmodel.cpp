#include "vacationlistmodel.h"
#include "halfiles.h"

#include <QDebug>
#include <QFile>
#include <QStringList>
#include <algorithm>

VacationListModel::VacationListModel(QObject *parent)
    : QAbstractListModel{parent} {
}

int VacationListModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid() || vacationList.isEmpty())
        return 0;
    return vacationList.size();
}

QHash<int, QByteArray> VacationListModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[DateRole]    = "date";
    names[ValidRole]   = "valid";
    names[RequestRole] = "request";
    return names;
}

QVariant VacationListModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() > vacationList.size())
        return QVariant();

    const Vacation *vacation = vacationList[index.row()];

    switch(role) {
    case DateRole:
        return vacation->date;
    case ValidRole:
        return vacation->valid;
    case RequestRole:
        return vacation->request;
    }
    return QVariant();
}

void VacationListModel::loadVacation(QString Name) {
    beginResetModel();
    HalFiles hf;
    QString  filePath = hf.getEmployeeVacationPath(Name);

    if(!QFile::exists(filePath)) {
        qDebug() << "file doesnt exist: " << filePath;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "cant open file: " + filePath;
    }
    file.readLine();

    QHash<QString, bool> vacationHash;
    vacationList.clear();

    while(!file.atEnd()) {
        QString     line     = QString(file.readLine()).replace("\n", "");
        QStringList elements = line.split(";");

        if(elements.size() == 3) {
            Vacation *vacation = new Vacation();
            vacation->date     = elements[0].trimmed();
            vacation->valid    = elements[1].trimmed();
            vacation->request  = elements[2].trimmed();

            if(elements[1].trimmed().toLower() != "da") {
                vacation->valid = "Ne";
            } else {
                vacation->valid = "Da";
            }

            if(!vacationHash[vacation->date]) {
                vacationHash[vacation->date] = true;
                vacationList.append(vacation);
            }
        }
    }

    std::sort(vacationList.begin(), vacationList.end(), comp);
    endResetModel();
}

bool VacationListModel::comp(const Vacation *lhs, const Vacation *rhs) {
    QString ld = lhs->date;
    QString rd = rhs->date;

    if(ld.split(".")[1] == rd.split(".")[1]) {
        return ld.split(".")[0] < rd.split(".")[0];
    }
    return ld.split(".")[1] < rd.split(".")[1];
}
