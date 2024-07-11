#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "employee.h"

class EmployeeListModel : public QAbstractListModel {
    Q_OBJECT
  public:
    explicit EmployeeListModel(QObject *parent = nullptr);
    ~EmployeeListModel();

    enum EmployeeListModelRoles {
        NameRole      = Qt::UserRole + 1,
        PasswordRole  = Qt::UserRole + 2,
        HoursRole     = Qt::UserRole + 3,
        VactationRole = Qt::UserRole + 4,
        StatusRole    = Qt::UserRole + 5,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int                role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void readEmployees();

  private:
    QVector<Employee *> mlst;
};

#endif // EMPLOYEELISTMODEL_H
