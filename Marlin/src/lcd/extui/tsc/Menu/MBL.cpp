#include "../TSC_Menu.h"

#if ENABLED(MINGDA_TFT)

#define LEVELING_POINT_MOVE_Z      10.0f // Z-axis position when nozzle move to next point
#define LEVELING_POINT_HEIGHT_Z		  0.1f  // Z-axis position when leveling
#define LEVELING_POINT_Z_FEEDRATE    600  // (mm/min) Z axis move feedrate
#define LEVELING_POINT_XY_FEEDRATE  6000  // (mm/min) X and Y axes move feedrate
#define LEVELING_POINT_1_X         (X_MIN_POS + 30)
#define LEVELING_POINT_1_Y         (Y_MIN_POS + 30)
#define LEVELING_POINT_2_X         (X_MAX_POS - 30)
#define LEVELING_POINT_2_Y         (Y_MIN_POS + 30)
#define LEVELING_POINT_3_X         (X_MAX_POS - 30)
#define LEVELING_POINT_3_Y         (Y_MAX_POS - 30)
#define LEVELING_POINT_4_X         (X_MIN_POS + 30)
#define LEVELING_POINT_4_Y         (Y_MAX_POS - 30)

char cmd[MAX_CMD_SIZE+16], str_1[16], str_2[16], str_3[16];


//#include "../../../../feature/bltouch.h"

const MENUITEMS MBLItems = {
// title
LABEL_MBL,
// icon                        label
 {
    {ICON_POINT_1,          LABEL_POINT_1},
    {ICON_POINT_2,          LABEL_POINT_2},
    {ICON_POINT_3,          LABEL_POINT_3},
    {ICON_POINT_4,          LABEL_POINT_4},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACK,             LABEL_BACK},
  }
};

void menuCallBackMBL(void)
{
  KEY_VALUES key_num = menuKeyGetValue();
  switch(key_num)
  {
    case KEY_ICON_0:
      if (!ExtUI::isPositionKnown()) {
        storeCmd("G28\n");
      }
      sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_MOVE_Z);
        storeCmd(cmd); 
      sprintf_P(cmd, PSTR("G0 X%i Y%i\n"), LEVELING_POINT_1_X, LEVELING_POINT_1_Y);
        storeCmd(cmd);
      sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_HEIGHT_Z);
        storeCmd(cmd); 
      break;
    case KEY_ICON_1:
    if (!ExtUI::isPositionKnown()) {
        storeCmd(PSTR("G28\n"));
    }
    sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_MOVE_Z);
        storeCmd(cmd); 
    sprintf_P(cmd, PSTR("G0 X%i Y%i\n"), LEVELING_POINT_2_X, LEVELING_POINT_2_Y);
        storeCmd(cmd); 
    sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_HEIGHT_Z);
        storeCmd(cmd); 
      break;
    case KEY_ICON_2:
    if (!ExtUI::isPositionKnown()) {
        storeCmd(PSTR("G28\n"));
    }
    sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_MOVE_Z);
        storeCmd(cmd);
    sprintf_P(cmd, PSTR("G0 X%i Y%i\n"), LEVELING_POINT_3_X, LEVELING_POINT_3_Y);
        storeCmd(cmd);
    sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_HEIGHT_Z);
        storeCmd(cmd);
      break;
    case KEY_ICON_3:
    if (!ExtUI::isPositionKnown()) {
        storeCmd(PSTR("G28\n"));
    }
    sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_MOVE_Z);
        storeCmd(cmd);
    sprintf_P(cmd, PSTR("G0 X%i Y%i\n"), LEVELING_POINT_4_X, LEVELING_POINT_4_Y);
        storeCmd(cmd);
    sprintf_P(cmd, PSTR("G0 Z%1.2f\n"), LEVELING_POINT_HEIGHT_Z);
        storeCmd(cmd);
      break;
    case KEY_ICON_7:
      infoMenu.cur--; break;
    default:break;
  }
}

void menuMBL ()
{
  menuDrawPage(&MBLItems);
  menuSetFrontCallBack(menuCallBackMBL);
}



#endif