#ifndef VACATIONLISTMODEL_H
#define VACATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QString>

struct Vacation {
    QString date;
    QString valid;
    QString request;
};

class VacationListModel : public QAbstractListModel {
    Q_OBJECT
  public:
    explicit VacationListModel(QObject *parent = nullptr);

    enum VacationListModelRoles {
        DateRole    = Qt::UserRole + 1,
        ValidRole   = Qt::UserRole + 2,
        RequestRole = Qt::UserRole + 3
    };

    int                            rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant                       data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadVacation(QString Name);

  private:
    QVector<Vacation *> vacationList;
};

#endif // VACATIONLISTMODEL_H
