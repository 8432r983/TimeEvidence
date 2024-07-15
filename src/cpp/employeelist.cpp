#include <QDebug>
#include <QFile>
#include <QSettings>

#include "employeelist.h"
#include "halfiles.h"

EmployeeList::EmployeeList(QObject *parent)
    : QObject{parent} {
}

void EmployeeList::loadList(QObject *parent1, QVector<Employee *> &mlst) {
    HalFiles hf;
    QString  filepath = hf.getEmployeesFilePath();
    qDebug() << "zaposlenici file=" << filepath;
    if(!QFile::exists(filepath))
        return;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    file.readLine(); // skip first line
    int devId = getDeviceId();
    qDebug() << "devId=" << devId;
    if(devId == -1)
        return;

    qDeleteAll(mlst);
    mlst.clear();

    while(!file.atEnd()) {
        QString     line     = QString(file.readLine());
        QStringList elements = line.split(";");

        if(elements.size() == 6) {
            bool ok;
            int  empid = elements[5].toInt(&ok);
            if(ok) {
                if(empid == devId) {
                    Employee *emp = new Employee(parent1);
                    emp->device   = empid;
                    emp->name     = elements[0].trimmed();
                    emp->password = elements[1].trimmed();
                    emp->hours    = elements[2].toDouble();
                    emp->vacation = elements[3].toInt();
                    emp->status   = elements[4].trimmed();
                    mlst.append(emp);
                }
            }
        }
    }
}

int EmployeeList::getDeviceId() {
    HalFiles      hf;
    const QString cGroupId  = "AppSettingsGeneral";
    const QString cDeviceId = "deviceId";
    QSettings     settings(hf.getSettingsFilePath(), QSettings::IniFormat, this);
    settings.beginGroup(cGroupId);
    int deviceid = settings.value(cDeviceId, -1).toInt();
    settings.endGroup();
    return deviceid;
}
