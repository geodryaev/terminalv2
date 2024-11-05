#include "widgetdelegate.h"
#include "QSettings"
#include "QDebug"

myWidget::myWidget()
{   
}

myWidget::~myWidget()
{
}

void myWidget::setDefaultSettings()
{
    settings = new QSettings ("settings.ini", QSettings::IniFormat);
    settings->beginGroup("AboutApp");
    settings->setValue("Autor","Легенда отделения, ебанно в рот помешанный на ЗВ, мистер похуй или нихуя не будем делать, типо самый умный после Козуба - Джони, мать его чернйы прапор Дряев");
    settings->setValue("Version", "v.01beta.NOTEST");
    settings->setValue("pathToSave","C:\\");
    settings->endGroup();
}

QList<QString> myWidget::getListDepartament()
{
    QList<QString> list;

    QFile f("data_list.json");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray all = f.readAll();
        _objectJSON = QJsonDocument::fromJson(all);
        f.close();
        QJsonObject object = _objectJSON.object();
        QJsonArray arrJson = object["departaments"].toArray();
        for ( auto elem: arrJson)
        {
            list.append(elem.toString());
        }
        return list;
    }
    else
    {
        QFile d("data_list.json");
        if (d.open(QIODevice::WriteOnly))
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
            QJsonObject object;
            object["departaments"] = arrJsn;
            QJsonDocument doc(object);
            d.write(doc.toJson());
            d.close();
        }
    }
    return getListDepartament();
}
