#include "entrymanager.h"

EntryManager::EntryManager(QObject *parent)
    : QObject{parent} {
}

void EntryManager::setInOut(QString Name, QString newVal) {
    m_inout[Name] = newVal;
    emit inoutChanged();
}

QString EntryManager::getInOut(QString Name) {
    if(!m_inout.contains(Name))
        return "";
    return m_inout[Name];
}

void EntryManager::setStartTime(QString Name, QString newVal) {
    m_startTimes[Name] = newVal;
    emit startTimesChanged();
}

QString EntryManager::getStartTime(QString Name) {
    if(!m_startTimes.contains(Name))
        return "";
    return m_startTimes[Name];
}

QMap<QString, QString> EntryManager::inout() const {
    return m_inout;
}

QMap<QString, QString> EntryManager::startTimes() const {
    return m_startTimes;
}
