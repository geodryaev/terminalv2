#ifndef WIDGETDELEGATE_H
#define WIDGETDELEGATE_H
#include "QSettings"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonDocument"
#include "QList"

class myWidget
{
public:
    myWidget();
    ~myWidget();

    QString pathToSave();
    void setDefaultSettings();
    QList<QString>getListDepartament();


private:
    QSettings *settings;
    QJsonDocument _objectJSON;
};

#endif // WIDGETDELEGATE_H
