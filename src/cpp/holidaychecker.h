#ifndef HOLIDAYLOGGER_H
#define HOLIDAYLOGGER_H

#include <QHash>
#include <QObject>
#include <QString>

class HolidayLogger : public QObject {
    Q_OBJECT
  public:
    explicit HolidayLogger(QObject *parent = nullptr);

    Q_INVOKABLE bool holidayCheck(QString date);

    void loadHolidays();

  signals:

  private:
    QHash<QString, bool> m_holidays;
};

#endif // HOLIDAYLOGGER_H
