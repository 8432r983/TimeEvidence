#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H

#include <QObject>

#include "employee.h"

class EmployeeList : public QObject {
    Q_OBJECT
  public:
    explicit EmployeeList(QObject *parent = nullptr);
    void loadList(QObject *parent1, QVector<Employee *> &mlst);

  private:
    int getDeviceId();
};

#endif // EMPLOYEELIST_H
