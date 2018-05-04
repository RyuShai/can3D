#ifndef MODELINTERACT_H
#define MODELINTERACT_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QList>
#include "config.h"

class ModelInteract : public QObject
{
    Q_OBJECT
public:
    explicit ModelInteract(QObject *parent = nullptr);
    //call when insert new record
    bool InserRecord(float width, float height, float depth, float weight,float volume, float density, QString barcode);
    bool InserRecord(ReceivedData data);
    //call when save  edited record
    bool UpdateRecord(float width, float height, float depth, float weight,float volume, float density, QString barcode , int id);
    bool LoadRecord();
    void setPath2db(const QString &value);
    QList<ReceivedData *> getListRecord() const;
    void setListRecord(const QList<ReceivedData *> &value);
    float GetlastID();
signals:
    void LoadRecorded();
    void InsertNewRecorded(ReceivedData data);
public slots:
private:
    QSqlDatabase db;
    QString path2db;
    QList<ReceivedData*> listRecord;
    //function
    //open database, call whenver access db
    bool OpenDatabase();
    //call whenver finish touch database
    void CloseDatabase();


};

#endif // MODELINTERACT_H
