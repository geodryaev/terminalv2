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
            arrJsn.append("Отдел информатизации");
            arrJsn.append("Отдел хещения средств институа");
            arrJsn.append("Отдел посылания \"Иди отсюда\" быстрее дыхания");
            arrJsn.append("Отдел зачем тебе 2НДФЛ");
            arrJsn.append("Отдел научись сам стрелять");
            arrJsn.append("Отдел научной типо деятельности");
            arrJsn.append("Отдел спецБАТАНАЛЬОНА");
            arrJsn.append("Дядки ОТДЕЛ");
            arrJsn.append("Отдел слепых за слежкой (кроме кра... конечно же)учебного процесса");
            arrJsn.append("И еще три пи***, три звезды отделов");
            QJsonObject object;
            object["departaments"] = arrJsn;
            QJsonDocument doc(object);
            d.write(doc.toJson());
            d.close();
        }
    }
    return getListDepartament();
}
