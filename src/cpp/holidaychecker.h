#ifndef HOLIDAYCHECKER_H
#define HOLIDAYCHECKER_H

#include <QDate>
#include <QHash>
#include <QObject>
#include <QString>

class HolidayChecker : public QObject {
    Q_OBJECT
  public:
    explicit HolidayChecker(QObject *parent = nullptr);

    Q_INVOKABLE QString holiday();

    Q_INVOKABLE bool holidayCheck(QDate date);
    Q_INVOKABLE bool checkString(QString date);
    Q_INVOKABLE void loadHolidays();

  private:
    QHash<QString, bool> m_holidays;
};

#endif // HOLIDAYCHECKER_H
