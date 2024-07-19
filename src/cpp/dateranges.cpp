#include "dateranges.h"
#include "halfiles.h"
#include <QDebug>
#include <QFile>
#include <QSettings>

DateRanges::DateRanges(QObject *parent)
    : QObject{parent} {
    loadRanges();
}

void DateRanges::loadRanges() {
    HalFiles hf;

    const QString cGroupId            = "AppSettingsGeneral";
    const QString cVacationRangeLower = "vacationRangeLower";
    const QString cVacationRangeUpper = "vacationRangeUpper";

    QSettings settings(hf.getSettingsFilePath(), QSettings::IniFormat, this);
    settings.beginGroup(cGroupId);

    int vacationLowerBound = settings.value(cVacationRangeLower, 0).toInt();
    int vacationUpperBound = settings.value(cVacationRangeUpper, 0).toInt();

    settings.endGroup();

    QDate currentDate = QDate::currentDate();

    m_lowerVacationBound = currentDate.addDays(vacationLowerBound);
    m_upperVacationBound = currentDate.addDays(vacationUpperBound);

    qDebug() << currentDate.addDays(vacationLowerBound);
    qDebug() << currentDate.addDays(vacationUpperBound);

    emit lowerVacationBoundChanged();
    emit upperVacationBoundChanged();
}

QDate DateRanges::lowerVacationBound() const {
    return m_lowerVacationBound;
}

QDate DateRanges::upperVacationBound() const {
    return m_upperVacationBound;
}
