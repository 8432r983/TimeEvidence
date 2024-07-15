#ifndef ENTRY_H
#define ENTRY_H

#include <QObject>
#include <QString>

class Entry : public QObject {
    Q_OBJECT
  public:
    explicit Entry(QObject *parent = nullptr);

    void fromEntry(Entry *val);

    void calcTotal();
    void calcDifference();

    int     timeToInt(QString time);
    QString intToTime(int time);

    QString day;
    QString date;
    QString clockIn;
    QString clockOut;
    QString total;
    QString difference;
    QString travel;
};

#endif // ENTRY_H
