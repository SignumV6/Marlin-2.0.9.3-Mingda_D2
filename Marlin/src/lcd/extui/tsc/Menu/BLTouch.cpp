#include "../TSC_Menu.h"

#if ENABLED(MINGDA_TFT)

#define LEVELING_POINT_MOVE_Z      10.0f  // Z-axis position when nozzle move to next point
#define LEVELING_POINT_HEIGHT_Z		0.2f  // Z-axis position when leveling
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

#if ENABLED(AUTO_BED_LEVELING_BILINEAR) || ENABLED(AUTO_BED_LEVELING_UBL)

#include "../../../../feature/bltouch.h"

const MENUITEMS BLTouchItems = {
// title
LABEL_ABL,
// icon                        label
 {
    {ICON_BLTOUCH_DEPLOY,        LABEL_BLTOUCH_DEPLOY},
    {ICON_BLTOUCH_STOW,          LABEL_BLTOUCH_STOW},
    {ICON_BLTOUCH_TEST,          LABEL_BLTOUCH_TEST},
    {ICON_BLTOUCH_INIT,          LABEL_BLTOUCH_INIT},
    {ICON_BACKGROUND,            LABEL_BACKGROUND},
    {ICON_BACKGROUND,            LABEL_BACKGROUND},
    {ICON_BACKGROUND,            LABEL_BACKGROUND},
    {ICON_BACK,                  LABEL_BACK},
  }
};

void menuCallBackBLTouch(void)
{
  KEY_VALUES key_num = menuKeyGetValue();
  switch(key_num)
  {
    case KEY_ICON_0:
      storeCmd("M280 P0 S10\n");
      break;
    case KEY_ICON_1:
      storeCmd("M280 P0 S90\n");
      break;
    case KEY_ICON_2:
      storeCmd("M280 P0 S120\n");
      break;
    case KEY_ICON_3:
      storeCmd("M280 P0 S160\n");
      break;
    case KEY_ICON_7:
      infoMenu.cur--; break;
    default:break;
  }
}

void menuBLTouch()
{
  menuDrawPage(&BLTouchItems);
  menuSetFrontCallBack(menuCallBackBLTouch);
}

#else

bool manualblRunning = false;

const MENUITEMS manualLevelingItems = {
// title
LABEL_LEVELING,
// icon                        label
 {{ICON_POINT_1,               LABEL_POINT_1},
  {ICON_POINT_2,               LABEL_POINT_2},
  {ICON_POINT_3,               LABEL_POINT_3},
  {ICON_POINT_4,               LABEL_POINT_4},
  {ICON_BACKGROUND,            LABEL_BACKGROUND},
  {ICON_BACKGROUND,            LABEL_BACKGROUND},
  {ICON_BACKGROUND,            LABEL_BACKGROUND},
  {ICON_BACK,                  LABEL_BACK},}
};

void moveToLevelingPoint(uint8_t point)
{
  char buffer [100];
  static const uint16_t pointPosition[][2] = {
    {LEVELING_POINT_1_X, LEVELING_POINT_1_Y},
    {LEVELING_POINT_2_X, LEVELING_POINT_2_Y},
    {LEVELING_POINT_3_X, LEVELING_POINT_3_Y},
    {LEVELING_POINT_4_X, LEVELING_POINT_4_Y},
  };
  if(manualblRunning == false)
  {
    storeCmd("G28\n");
    manualblRunning = true;
  }
  snprintf(buffer, 100, "G0 Z%.3f F%d\n", LEVELING_POINT_MOVE_Z, LEVELING_POINT_Z_FEEDRATE);
  storeCmd(buffer);
  snprintf(buffer, 100, "G0 X%d Y%d F%d\n", pointPosition[point][0], pointPosition[point][1], LEVELING_POINT_XY_FEEDRATE);
  storeCmd(buffer);
  snprintf(buffer, 100, "G0 Z%.3f F%d\n", LEVELING_POINT_HEIGHT_Z, LEVELING_POINT_Z_FEEDRATE);
  storeCmd(buffer);
}

void menuCallBackManualLeveling(void)
{
  KEY_VALUES key_num = menuKeyGetValue();
  switch(key_num)
  {
    case KEY_ICON_0: moveToLevelingPoint(0); break;
    case KEY_ICON_1: moveToLevelingPoint(1); break;
    case KEY_ICON_2: moveToLevelingPoint(2); break;
    case KEY_ICON_3: moveToLevelingPoint(3); break;
    case KEY_ICON_7:
      manualblRunning = false;
      infoMenu.cur--; break;
    default:break;
  }
}

void menuManualLeveling()
{
  menuDrawPage(&manualLevelingItems);
  menuSetFrontCallBack(menuCallBackManualLeveling);
}

#endif

#endif