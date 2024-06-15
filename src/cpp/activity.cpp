#include "activity.h"

activity::activity(QObject *parent)
    : QObject{parent} {
}

QString activity::getActivity(QString Name) {
    if(activeList.contains(Name))
        return activeList[Name];
    return "";
}

void activity::setActivity(QString Name, QString val) {
    activeList[Name] = val;
    emit activeListChanged();
}

QHash<QString, QString> activity::activeList() const {
    return m_activeList;
}
