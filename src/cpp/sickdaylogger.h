#ifndef SICKDAYLOGGER_H
#define SICKDAYLOGGER_H

#include <QDate>
#include <QObject>
#include <QString>

class SickdayLogger : public QObject {
    Q_OBJECT
  public:
    explicit SickdayLogger(QObject *parent = nullptr);

    Q_INVOKABLE void addSickdayEntry(QString Name, QDate start, QDate end, QString validity);
    QString          getDay(QDate date);

  signals:
};

#endif // SICKDAYLOGGER_H
