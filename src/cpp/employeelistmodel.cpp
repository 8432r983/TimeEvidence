#include <QDebug>

#include "employeelist.h"
#include "employeelistmodel.h"

EmployeeListModel::EmployeeListModel(QObject *parent)
    : QAbstractListModel{parent} {
}

EmployeeListModel::~EmployeeListModel() {
    qDebug() << "EmployeeListModel to Garbage.....";
}

int EmployeeListModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid() || mlst.isEmpty())
        return 0;
    return mlst.size();
}

int EmployeeListModel::columnCount(const QModelIndex &parent) const {
    if(parent.isValid() || mlst.isEmpty())
        return 0;
    return 1;
}

QVariant EmployeeListModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() > mlst.size())
        return QVariant();
    const Employee *emp = mlst[index.row()];
    switch(role) {
    case NameRole:
        return emp->name;
    case PasswordRole:
        return emp->password;
    case HoursRole:
        return emp->hours;
    case VactationRole:
        return emp->vacation;
    case StatusRole:
        return emp->status;
    }
    return QVariant();
}

QHash<int, QByteArray> EmployeeListModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[NameRole]      = "name";
    names[PasswordRole]  = "password";
    names[HoursRole]     = "hours";
    names[VactationRole] = "vacation";
    names[StatusRole]    = "status";
    return names;
}

void EmployeeListModel::readEmployees() {
    beginResetModel();
    EmployeeList emplst;
    emplst.loadList(this, mlst);
    endResetModel();
}
