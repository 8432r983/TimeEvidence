#ifndef NAMELISTMODEL_H
#define NAMELISTMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QStringList>

class NameListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NameRoles {
        NameRole = Qt::UserRole + 1
    };

    explicit NameListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList m_names;

    void loadNamesFromFile();
};

#endif // NAMELISTMODEL_H
