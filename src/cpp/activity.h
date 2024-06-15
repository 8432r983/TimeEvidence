#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QHash>
#include <QObject>
#include <QString>

class activity : public QObject {
    Q_OBJECT

    Q_PROPERTY(QHash<QString, QString> activeList READ activeList NOTIFY
                   activeListChanged FINAL)

  public:
    explicit activity(QObject *parent = nullptr);

    Q_INVOKABLE QString getActivity(QString Name);
    Q_INVOKABLE void    setActivity(QString Name, QString val);
    QHash<QString, QString> activeList() const;
  signals:
    void activeListChanged();
  private:
    QHash<QString, QString> m_activeList;
};

#endif // ACTIVITY_H
