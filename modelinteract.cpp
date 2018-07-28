#include "modelinteract.h"
#include <QDate>
#include <QSqlQuery>
#include <QTemporaryFile>
#include <QTemporaryDir>
ModelInteract::ModelInteract(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    path2db="";

}

bool ModelInteract::OpenDatabase()
{
    Log(path2db);
    bool dbExist = QFile(path2db).exists();

    db.setDatabaseName(path2db);
    if(!db.open())
    {

        Log("open database failed");
        return false;
    }
    if(!dbExist)
    {
        qDebug()<<"dbexist: "<<dbExist;
        QSqlQuery query;
        query.exec("CREATE TABLE `Can` ("
                   "`ID`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                   "`width`	INTEGER,"
                   "`height`	INTEGER,"
                   "`depth`	INTEGER,"
                   "`volume`	INTEGER,"
                   "`weight`	INTEGER,"
                   "`density`	INTEGER,"
                   "`barcode`	TEXT,"
                   "`time`	TEXT"
               ")");
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
    Log("");
    OpenDatabase();
    QString insertQuery = "INSERT INTO Can (width,height,depth,volume,weight,density,barcode, time) "
                          "VALUES ("+QString::number(width)+","+QString::number(height)+","+QString::number(depth)+
            ","+QString::number(volume)+","+QString::number(weight)+","+QString::number(density)+",'"+barcode+"','"+QDate::currentDate().toString("dd-MM-yyyy")+"')";
    Log(insertQuery);
    QSqlQuery query;
    if(!query.exec(insertQuery))
        Log("insert to database failed");
    CloseDatabase();
}

bool ModelInteract::InserRecord(ReceivedData data)
{
//    Log("barcode: "+data.barcode+ " date: "+data.date);
    OpenDatabase();
    QString insertQuery = "INSERT INTO Can (width,height,depth,volume,weight,density,barcode, time) "
                          "VALUES ("+QString::number(data.width)+","+QString::number(data.height)+","+QString::number(data.depth)+
            ","+QString::number(data.volume)+","+QString::number(data.weight)+","+QString::number(data.density)+",'"+data.barcode+"','"+(data.date=QDate::currentDate().toString("dd-MM-yyyy"))+"')";

//    QString insertQuery = "INSERT INTO Can (width,height,depth,volume,weight,density,barcode, time) VALUES (4.5,7.5,5,0,3,0,'\u0000','18-07-2018')";
//    qDebug().noquote()<<insertQuery;
    QSqlQuery query;
    if(!query.exec(insertQuery))
        Log("insert to database failed");
    CloseDatabase();
//    Log("InserRecord done");
    emit InsertNewRecorded(data);
}

bool ModelInteract::UpdateRecord(float width, float height, float depth, float weight, float volume, float density, QString barcode, int id)
{
    Log("");
    OpenDatabase();
    QString insertQuery = "UPDATE Can SET width = "+QString::number(width)+",height= "+QString::number(height)+",depth = "+QString::number(depth)
            +" ,volume = "+QString::number(volume)+",weight="+QString::number(weight)
            +",density="+QString::number(density)+",barcode="+barcode+", time ="+QDate::currentDate().toString("dd-MM-yyyy")+" Where id = "+QString::number(id);
    Log(insertQuery);
    QSqlQuery query(insertQuery);
    if(!query.exec())
        Log("update to database failed");
    CloseDatabase();
}

bool ModelInteract::LoadRecord()
{
    Log("");
    OpenDatabase();
    QString cmdQuery = "SELECT * FROM Can ";
    QSqlQuery query(cmdQuery);
    while(query.next())
    {
        ReceivedData* record = new ReceivedData;
        record->id = query.value("ID").toFloat();
        record->width = query.value("width").toFloat();
        record->height = query.value("height").toFloat();
        record->depth = query.value("depth").toFloat();
        record->weight = query.value("weight").toFloat();
        record->volume = query.value("volume").toFloat();
        record->density = query.value("density").toFloat();
        record->barcode = query.value("barcode").toString();
        record->date = query.value("time").toString();
//        record->toString();
        listRecord.append(record);
    }
    CloseDatabase();
    emit LoadRecorded();
    qDebug()<<listRecord.count();
}

void ModelInteract::setPath2db(const QString &value)
{
    path2db = value;
}

QList<ReceivedData *> ModelInteract::getListRecord() const
{
    return listRecord;
}

void ModelInteract::setListRecord(const QList<ReceivedData *> &value)
{
    listRecord = value;
}

float ModelInteract::GetlastID()
{
    float result=-1;
    OpenDatabase();
    QString cmdQuery = "SELECT MAX(ID) FROM Can";

    QSqlQuery query(cmdQuery);
    while(query.next())
    {
            result = query.value(0).toFloat();
            qDebug()<<"error1";
    }


    Log(QString::number(result));
    CloseDatabase();
    return result;

}
