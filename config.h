#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QDebug>

namespace Config {
//object size
//unit pixel
static int WINDOW_HEIGHT = 600 ;
static int WINDO_WIDTH = 1068 ;

//upper left group
static int LEFT_GROUP_WIDTH = 300;
static int LEFT_GROUP_HEIGHT = 200;

//uper mid group
static int MID_GROUP_WIDTH = 300;
static int MID_GROUP_HEIGHT = 300;

static  int LOGO_WIDTH = 80;
static  int LOGO_HEIGHT = 80;
static int BARCODE_WIDTH = 160;
static int BARCODE_HEIGHT = 40;




//object position


//object display text
static QString MAIN_WINDOW_TITLE = "MAIN TITLE" ;
static QString MENU_TEXT ="File" ;
static QString MENU_TEXT_EXIT = "Exit";

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

}



#endif // CONFIG_H


