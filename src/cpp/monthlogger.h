#ifndef MONTHLOGGER_H
#define MONTHLOGGER_H

#include "entry.h"
#include <QObject>

class MonthLogger : public QObject {
    Q_OBJECT
  public:
    explicit MonthLogger(QObject *parent = nullptr);

    Q_INVOKABLE void addEntry(QString Name, QString Day, QString Date, QString clockIn, QString clockOut, QString travel,
                              QString holiday, QString sickday, QString vacation, QString sickdayValidity);

  signals:
};

#endif // MONTHLOGGER_H
