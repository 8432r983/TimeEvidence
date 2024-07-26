#ifndef SPECIALDAYLOGGER_H
#define SPECIALDAYLOGGER_H

#include <QObject>
#include <QString>

class SpecialDayLogger : public QObject {
    Q_OBJECT
  public:
    explicit SpecialDayLogger(QObject *parent = nullptr);

    void addDay(QString Name, QString date, QString type, QString hours);

  signals:
};

#endif // SPECIALDAYLOGGER_H
