#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QHash>
#include <QObject>

class activity : public QObject {
    Q_OBJECT
  public:
    explicit activity(QObject *parent = nullptr);

    Q_INVOKABLE bool getActivity(QString Name);
    Q_INVOKABLE void setActivity(QString Name, bool val);

  private:
    QHash<QString, bool> activeList;
};

#endif // ACTIVITY_H
