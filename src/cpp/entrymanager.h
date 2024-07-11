#ifndef ENTRYMANAGER_H
#define ENTRYMANAGER_H

#include <QHash>
#include <QObject>
#include <QString>

class EntryManager : public QObject {
    Q_OBJECT
  public:
    explicit EntryManager(QObject *parent = nullptr);

    Q_PROPERTY(
        QHash<QString, QString> inout READ inout NOTIFY inoutChanged FINAL)
    Q_PROPERTY(QHash<QString, QString> startTimes READ startTimes NOTIFY
                   startTimesChanged FINAL)

    Q_INVOKABLE void    setInOut(QString Name, QString newVal);
    Q_INVOKABLE QString getInOut(QString Name);

    Q_INVOKABLE void    setStartTime(QString Name, QString newVal);
    Q_INVOKABLE QString getStartTime(QString Name);

    QHash<QString, QString> inout() const;

    QHash<QString, QString> startTimes() const;

  signals:
    void inoutChanged();
    void startTimesChanged();

  private:
    QHash<QString, QString> m_inout;
    QHash<QString, QString> m_startTimes;
};

#endif // ENTRYMANAGER_H
