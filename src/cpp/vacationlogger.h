#ifndef VACATIONLOGGER_H
#define VACATIONLOGGER_H

#include <QDate>
#include <QObject>

class VacationLogger : public QObject {
    Q_OBJECT
  public:
    explicit VacationLogger(QObject *parent = nullptr);

    Q_INVOKABLE void addVacation(QString Name, QDate startDate, QDate endDate);

  signals:
};

#endif // VACATIONLOGGER_H
