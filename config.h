#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QDebug>
#define Log(text) qDebug()<<Q_FUNC_INFO<<" "<<text;
struct ReceivedData
{
    ReceivedData(float id =0,float width=0, float height=0, float depth=0, float weight=0,float volume=0, float density=0, QString barcode="", QString date=""){
        id=id;
        width = width;
        height = height;
        depth = depth;
        weight = weight;
        volume = volume;
        density = density;
        barcode = barcode;
        date = date;
    }
    float id=0;
    float width=0;
    float height=0;
    float depth=0;
    float weight=0;
    float volume=0;
    float density=0;
    QString barcode="barcode";
    QString date="";
    void Clear(){
        width=height=depth=weight=volume=density=0;
        barcode = date ="";
    }
    void toString()
    {
        Log("width: "<<width <<" height: "<<height<<" depth: "<<depth<<"\nvolume: "<<volume<<" density: "<<density<<"\nbarcode: "<<" date: "<<date);
    }
};
namespace Config {

//object size
//unit pixel
static int WINDOW_HEIGHT = 600 ;
static int WINDO_WIDTH = 1300 ;

//upper left group
static int LEFT_GROUP_WIDTH = 800;
static int LEFT_GROUP_HEIGHT = 600;

//uper mid group
static int MID_GROUP_WIDTH = 300;
static int MID_GROUP_HEIGHT = 300;

static  int LOGO_WIDTH = 80;
static  int LOGO_HEIGHT = 80;
static int BARCODE_WIDTH = 160;
static int BARCODE_HEIGHT = 80;




//object position


//object display text
static QString MAIN_WINDOW_TITLE = "MAIN TITLE" ;
static QString MENU_TEXT_FILE ="File" ;
static QString MENU_TEXT_EXIT = "Exit";
static QString MENU_TEXT_PORT = "Port";

static QString FORM_TEXT_HEIGHT = "Height";
static QString FORM_TEXT_WIDTH  = "Width";
static QString FORM_TEXT_DEPTH = "Depth";
static QString FORM_TEXT_WEIGHT = "Weight";
static QString FORM_TEXT_VOLUME = "Volume";
static QString FORM_TEXT_DENSITY = "Density";

static QString UNIT_LENGTH = "cm";
static QString UNIT_WEIGHT = "gam";
static QString UNIT_VOLUME = "cm^3";
static QString UNIT_DENSITY = "gam/cm3";

//enum
static QString WIDTH="Width";
static QString HEIGHT="Height";
static QString DEPTH="Length";
static QString WEIGHT="Weight";
static QString VOLUME="Volume";
static QString DENSITY="density";
static QString BARCODE="Barcode";

}



#endif // CONFIG_H


