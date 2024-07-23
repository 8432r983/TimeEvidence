#ifndef ENTRY_H
#define ENTRY_H

#include <QObject>
#include <QString>

class Entry : public QObject {
    Q_OBJECT
  public:
    explicit Entry(QObject *parent = nullptr);

    void fromEntry(Entry *val);

    int calcTotal();
    int calcDifference();

    void setTotal();
    void setDifference();

    void reset();

    int     timeToInt(QString time);
    QString intToTime(int time);

    QString day;
    QString date;
    QString clockIn;
    QString clockOut;
    QString total;
    QString difference;
    QString travel;
    QString vacation;
    QString holiday;
    QString sickday;
    QString sickdayValidity;
    bool    daychanged;
};

#endif // ENTRY_H
