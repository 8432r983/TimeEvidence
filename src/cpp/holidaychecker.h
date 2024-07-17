#ifndef HOLIDAYCHECKER_H
#define HOLIDAYCHECKER_H

#include <QHash>
#include <QObject>
#include <QString>

class HolidayChecker : public QObject {
    Q_OBJECT
  public:
    explicit HolidayChecker(QObject *parent = nullptr);

    Q_INVOKABLE QString holiday();

    bool holidayCheck(QString date);
    void loadHolidays();

  private:
    QHash<QString, bool> m_holidays;
};

#endif // HOLIDAYCHECKER_H
