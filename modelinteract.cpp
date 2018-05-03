#include "modelinteract.h"
#include <QDate>
#include <QSqlQuery>
ModelInteract::ModelInteract(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    path2db="";
}

bool ModelInteract::OpenDatabase()
{
    Log(path2db);
    db.setDatabaseName(path2db);
    if(!db.open())
    {
        Log("open database failed");
        return false;
    }
    return true;
}

void ModelInteract::CloseDatabase()
{
    if(db.isOpen())
        db.close();
}

bool ModelInteract::InserRecord(float width, float height, float depth, float weight, float volume, float density, QString barcode)
{
    OpenDatabase();
    QString insertQuery = "INSERT INTO Can (width,height,depth,volume,weigh,density,barcode, time) "
                          "VALUES ("+QString::number(width)+","+QString::number(height)+","+QString::number(depth)+
            ","+QString::number(volume)+","+QString::number(weight)+","+QString::number(density)+",'"+barcode+"',"+QDate::currentDate().toString("dd-MM-yyyy")+")";
    Log(insertQuery);
    QSqlQuery query(insertQuery);
    if(!query.exec())
        Log("insert to database failed");
    CloseDatabase();

}

bool ModelInteract::UpdateRecord(float width, float height, float depth, float weight, float volume, float density, QString barcode, int id)
{
    OpenDatabase();
    QString insertQuery = "UPDATE Can SET width = "+QString::number(width)+",height= "+QString::number(height)+",depth = "+QString::number(depth)
            +" ,volume = "+QString::number(volume)+",weigh="+QString::number(weight)
            +",density="+QString::number(density)+",barcode="+barcode+", time ="+QDate::currentDate().toString("dd-MM-yyyy")+" Where id = "+QString::number(id);
    QSqlQuery query(insertQuery);
    if(!query.exec())
        Log("update to database failed");
    CloseDatabase();
}

void ModelInteract::setPath2db(const QString &value)
{
    path2db = value;
}
