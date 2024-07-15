#include "activity.h"

activity::activity(QObject *parent)
    : QObject{parent} {
}

bool activity::getActivity(QString Name) {
    if(activeList.contains(Name))
        return activeList[Name];
    return false;
}

void activity::setActivity(QString Name, bool val) {
    activeList[Name] = val;
}
