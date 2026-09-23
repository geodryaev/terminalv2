#include "widgetdelegate.h"
#include "QSettings"
#include "QDebug"
#include "QFile"

myWidget::myWidget()
{
}

myWidget::~myWidget()
{
}

void myWidget::setDefaultSettings()
{
    QSettings settings ("settings.ini", QSettings::IniFormat);
    settings.beginGroup("AboutApp");
    settings.setValue("Autor","Легенда отделения, помешанный на ЗВ, типо самый умный после Козуба - Джони, чернйы прапор Дряев");
    settings.setValue("Version", "v.01beta.NOTEST");
    settings.setValue("pathToSave","C:\\");
    settings.endGroup();
    settings.sync();
}

static QJsonArray defaultDepartaments()
{
    QJsonArray arrJsn;
    arrJsn.append("Отделение информатизации");
    arrJsn.append("Отдел МТО");
    arrJsn.append("Отдел Кдаров");
    arrJsn.append("Отдел НДФЛ");
    arrJsn.append("Отдел ствола");
    arrJsn.append("Отдел науки");
    arrJsn.append("Отдел спецназа за кавказа");
    arrJsn.append("Дядки ОТДЕЛ");
    arrJsn.append("Отдел мне реально лень писать, сами в JSON запишите лентяи");
    return arrJsn;
}

QList<QString> myWidget::getListDepartament()
{
    QList<QString> list;
    QJsonArray arrJson;

    QFile f("data_list.json");
    if (!f.exists())
    {
        QJsonObject object;
        object["departaments"] = defaultDepartaments();
        if (f.open(QIODevice::WriteOnly))
        {
            f.write(QJsonDocument(object).toJson());
            f.close();
        }
    }

    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        _objectJSON = QJsonDocument::fromJson(f.readAll());
        f.close();
        arrJson = _objectJSON.object()["departaments"].toArray();
    }
    else
    {
        qWarning() << "Could not read data_list.json, using default list";
        arrJson = defaultDepartaments();
    }

    for (const auto &elem: arrJson)
    {
        list.append(elem.toString());
    }
    return list;
}
