#include "Settings.h"
#include "../TSC_Menu.h"

#if ENABLED(MINGDA_TFT)

SETTINGS infoSettings, // Settings para
         lastSettings; // Last Settings para
extern uint32_t TSC_Para[7]; 
uint32_t lastTSC_Para[7];


#ifdef FIL_RUNOUT_PIN
  #define ITEM_RUNOUT_NUM 2
  const ITEM itemRunout[ITEM_RUNOUT_NUM] = {
  // icon                       label
    {ICON_RUNOUT,               LABEL_RUNOUT_OFF},
    {ICON_RUNOUT,               LABEL_RUNOUT_ON},
  };
  const  uint8_t item_runout[ITEM_RUNOUT_NUM] = {FILAMENT_RUNOUT_OFF, FILAMENT_RUNOUT_ON};
  static uint8_t item_runout_i = 0;
#endif


// Reset settings data
void infoSettingsReset(void)
{
  infoSettings.baudrate = 115200;
  infoSettings.language = TFT_ENGLISH;
  infoSettings.mode = SERIAL_TSC;
  infoSettings.runout = 1;
  infoSettings.rotate_ui = 0;
 // infoSettings.bg_color = ST7920_BKCOLOR;
 // infoSettings.font_color = ST7920_FNCOLOR;
  infoSettings.silent = 0;
  infoSettings.auto_off = 0;
}

void loopCheckSettings(void)
{
  static uint32_t lastTime = 0;
  if (millis() - lastTime > 1000)
  {
    lastTime = millis();
    if (memcmp(&infoSettings, &lastSettings, sizeof(SETTINGS))
     || memcmp(lastTSC_Para, TSC_Para, sizeof(TSC_Para)))
    {
      memcpy(&lastSettings, &infoSettings, sizeof(SETTINGS));
      memcpy(lastTSC_Para, TSC_Para, sizeof(TSC_Para));
      storePara();
      //MYSERIAL1.println("Settings stored!");
    }
  }
}

// Version infomation
GUI_RECT lcdFullRect = {0, 0, LCD_WIDTH_PIXEL, LCD_HEIGHT_PIXEL};
void menuCallBackInfo(void)
{
  KEY_VALUES key_num = (KEY_VALUES)KEY_GetValue(1, &lcdFullRect);
  if (key_num != KEY_IDLE)
  {
   infoMenu.cur--;
  }
}

void menuInfo(void)
{
  //char buffer[22];
  char longestprint[50], printtime [50], prints[50], filament[50], str_1[16], buf[50];
  printStatistics ps = print_job_timer.getStats();
  const char* hardware = "Board   : " BOARD_INFO_NAME;
  const char* firmware = "Firmware: " SHORT_BUILD_VERSION " " __DATE__;
  const char* autor = "Autor: " STRING_CONFIG_H_AUTHOR;  // MNi GST
  duration_t(print_job_timer.getStats().printTime).toString(buf);              
  sprintf_P(printtime, PSTR("Total Printtime: %s"), buf);
  duration_t(print_job_timer.getStats().longestPrint).toString(buf);
  sprintf_P(longestprint, PSTR("Longest Print: %s"), buf);
  sprintf_P(prints, PSTR("Total Prints: %i prints, %i finished"), ps.totalPrints, ps.finishedPrints); // GST
  sprintf_P(filament, PSTR("Total Filament: %s m"), dtostrf(ps.filamentUsed / 1000, 1, 2, str_1)); // GST

  uint16_t HW_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)hardware))/2;
  uint16_t FW_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)firmware))/2;
  uint16_t AU_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)autor))/2; // MNi GST
  uint16_t PT_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)printtime))/2; // GST
  uint16_t LP_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)longestprint))/2; // GST
  uint16_t  P_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)prints))/2; // GST
  uint16_t FI_X = (LCD_WIDTH_PIXEL - GUI_StrPixelWidth((uint8_t *)filament))/2; // GST
  uint16_t centerY = 50; // GST LCD_HEIGHT_PIXEL/2;
  uint16_t  startX = min(HW_X, FW_X);
  uint16_t  startY = min(HW_X, AU_X);  // GST
  uint16_t startPT = min(HW_X, PT_X);  // GST
  uint16_t startLP = min(HW_X, LP_X);  // GST
  uint16_t  startP = min(HW_X,  P_X);  // GST
  uint16_t startFI = min(HW_X, FI_X);  // GST
  GUI_Clear(BK_COLOR);
  GUI_DispString(startX, centerY - BYTE_HEIGHT, (uint8_t *)hardware);
  GUI_DispString(startX, centerY, (uint8_t *)firmware);
  GUI_DispString(startY, centerY + BYTE_HEIGHT, (uint8_t *)autor); // GST
  GUI_DispString(startPT, centerY + 3 * BYTE_HEIGHT, (uint8_t *)printtime); // GST
  GUI_DispString(startLP, centerY + 4 * BYTE_HEIGHT, (uint8_t *)longestprint); // GST
  GUI_DispString(startP, centerY + 5 * BYTE_HEIGHT, (uint8_t *)prints); // GST
  GUI_DispString(startFI, centerY + 6 * BYTE_HEIGHT, (uint8_t *)filament); // GST
  GUI_DispStringInRect(20, LCD_HEIGHT_PIXEL - (BYTE_HEIGHT*2), LCD_WIDTH_PIXEL-20, LCD_HEIGHT_PIXEL, textSelect(LABEL_TOUCH_TO_EXIT));

  TSC_ReDrawIcon = 0; // invalid icon redraw function
  menuSetFrontCallBack(menuCallBackInfo);
}


 MENUITEMS settingsItems = {
 // title
 LABEL_SETTINGS,
 // icon                       label
  {{ICON_SCREEN_SETTINGS,      LABEL_SCREEN_SETTINGS},
  {ICON_MACHINE_SETTINGS,     LABEL_MACHINE_SETTINGS}, //GST
  {ICON_RGB_SETTINGS,         LABEL_RGB_SETTINGS}, // GST
  {ICON_SCREEN_INFO,          LABEL_SCREEN_INFO},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  // {ICON_FEATURE_SETTINGS,     LABEL_FEATURE_SETTINGS}, // GST
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACK,                 LABEL_BACK},}
 };

/*MENUITEMS settingsItems = {
// title
LABEL_SETTINGS,
// icon                       label
 {{ICON_SCREEN_SETTINGS,      LABEL_SCREEN_SETTINGS},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_SCREEN_INFO,          LABEL_SCREEN_INFO},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACK,                 LABEL_BACK},}
}; */



void menuCallBackSettings(void)
{
  KEY_VALUES key_num = menuKeyGetValue();
  switch(key_num)
  {
    case KEY_ICON_0:
      infoMenu.menu[++infoMenu.cur] = menuScreenSettings;
      break;
    
     case KEY_ICON_2: 
       infoMenu.menu[++infoMenu.cur] = menuRGBSettings;
       break;
    
     case KEY_ICON_4:
       infoMenu.menu[++infoMenu.cur] = menuFeatureSettings;
       break;

    #ifdef FIL_RUNOUT_PIN
    case KEY_ICON_1:
      item_runout_i = (item_runout_i + 1) % ITEM_RUNOUT_NUM;                
      settingsItems.items[key_num] = itemRunout[item_runout_i];
      menuDrawItem(&settingsItems.items[key_num], key_num);
      infoSettings.runout = item_runout[item_runout_i];
      ExtUI::setFilamentRunoutEnabled(infoSettings.runout);
      break;
    #endif
    
    case KEY_ICON_3:
      infoMenu.menu[++infoMenu.cur] = menuInfo;
      break;

    case KEY_ICON_7:
      infoMenu.cur--;
      break;
    
    default:
      break;
  }
}

void menuSettings(void)
{

  #ifdef FIL_RUNOUT_PIN
  for(uint8_t i=0; i<ITEM_RUNOUT_NUM; i++)
  {
    if(infoSettings.runout == item_runout[i])
    {
      item_runout_i = i;
      settingsItems.items[KEY_ICON_1] = itemRunout[item_runout_i];
    }
  }
  #endif  

  menuDrawPage(&settingsItems);
  menuSetFrontCallBack(menuCallBackSettings);
}

#endif