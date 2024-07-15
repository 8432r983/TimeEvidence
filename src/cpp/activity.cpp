#include "activity.h"

activity::activity(QObject *parent)
    : QObject{parent} {
}

QString activity::getActivity(QString Name) {
    if(m_activeList.contains(Name))
        return m_activeList[Name];
    return "";
}

void activity::setActivity(QString Name, QString val) {
    m_activeList[Name] = val;
    emit activeListChanged();
}

QHash<QString, QString> activity::activeList() const {
    return m_activeList;
}
