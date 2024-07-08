#include "NameListModel.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

NameListModel::NameListModel(QObject *parent) : QAbstractListModel(parent) {

  beginResetModel();
  loadEmployees();
  endResetModel();
}

QVector<Employee> NameListModel::employees() const { return m_employees; }

bool NameListModel::verified() const { return m_verified; }

int NameListModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return m_employees.size();
}

QHash<int, QByteArray> NameListModel::roleNames() const {
  QHash<int, QByteArray> res;
  res[NameRole] = "name";
  res[PasswordRole] = "password";
  res[HoursRole] = "hours";
  res[VacationRole] = "vacation";
  res[DeviceRole] = "device";
  res[EmployeeStatusRole] = "employeeStatus";
  return res;
}

QVariant NameListModel::data(const QModelIndex &index, int role) const {
  if (!hasIndex(index.row(), index.column(), index.parent()))
    return QVariant();

  const Employee employeeItem = m_employees[index.row()];
  // MAR should be case...

  switch (role) {
  case NameRole:
    return QVariant(employeeItem.name);
  case PasswordRole:
    return QVariant(employeeItem.password);
  case HoursRole:
    return QVariant(employeeItem.hours);
  case VacationRole:
    return QVariant(employeeItem.vacation);
  case DeviceRole:
    return QVariant(employeeItem.device);
  case EmployeeStatusRole:
    return QVariant(employeeItem.employeeStatus);
  }

  return QVariant();
}

void NameListModel::loadEmployees() {
  // qDebug() << cPath + cEmployees;
  QFile file(cPath + cEmployees);

  if (file.exists()) {

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

    int c = 0;
    while (!file.atEnd()) {
      QString line = QString(file.readLine()); // MAR no need ...

      if (c >= 1) {
        QStringList elements = line.split(";");

        QString name = elements[0];
        QString password = elements[1].replace(" ", "");
        double hours = elements[2].toDouble();
        int vacation = elements[3].toInt();
        QString employeeStatus = elements[4].replace(" ", "");
        int device = elements[5].toInt();

        m_employees.append(
            {name, password, hours, vacation, device, employeeStatus});
      }
      c++;
    }
  } else {
    qDebug() << "file doesnt exist";
  }
  // MAR add if file does not exists make pop up with msg to check server
  // path....
}

bool NameListModel::verifyEmployee(QString password, QString name) {
  for (int i = 0; i < m_employees.size(); i++) {
    if (m_employees[i].password == password && m_employees[i].name == name) {
      qDebug() << password << name;
      m_verified = true;
      emit verifiedChanged();
    }
  }

  return m_verified;
}

QString NameListModel::getName(int index) {
  if (index >= 0 && index < m_employees.size())
    return m_employees[index].name;
  return QString();
}

QString NameListModel::getStatus(int index) {
  if (index >= 0 && index < m_employees.size())
    return m_employees[index].employeeStatus;
  return QString();
}

void NameListModel::popupExited() {
  m_verified = false;
  emit verifiedChanged();
}
