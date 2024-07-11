#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>

class Employee : public QObject {
  public:
    explicit Employee(QObject *parent)
        : QObject(parent)
        , name("")
        , password("1")
        , hours(0)
        , vacation(0)
        , status("Z")
        , device(1) {
    }
    ~Employee() {
    }

    QString name;
    QString password;
    double  hours;
    int     vacation;
    QString status;
    int     device;
};
#endif // EMPLOYEE_H
