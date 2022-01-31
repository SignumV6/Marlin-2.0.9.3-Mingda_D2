#include "../TSC_Menu.h"

#if ENABLED(MINGDA_TFT)

//1 title, ITEM_PER_PAGE items (icon + label) 
MENUITEMS TrammingItems = {
// title
LABEL_TRAMMING,
// icon                       label
 {
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_ABL,              LABEL_TRAMMING},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACKGROUND,       LABEL_BACKGROUND},
    {ICON_BACK,             LABEL_BACK},}
};

SCROLL     tmsgScroll;
static const uint8_t *tmsgbody;

// text position rectangles for Live icons 

//info rectangle          
const GUI_RECT RectInfo = {START_X,  TITLE_END_Y +  1 * SPACE_Y, START_X + 3 * ICON_WIDTH + 2 * SPACE_X,  TITLE_END_Y +  2 * ICON_HEIGHT + 1 * SPACE_Y};

const  GUI_RECT tmsgRect ={START_X + 2, TITLE_END_Y + STATUS_MSG_BODY_YOFFSET,
                          START_X + 3 * ICON_WIDTH + 2 * SPACE_X - 2,   TITLE_END_Y +  2 * ICON_HEIGHT + 1 * SPACE_Y - STATUS_MSG_BODY_BOTTOM}; 

TRAMMING_MSG trammingMsg;

void trammingMsg_GetCurMsg(TRAMMING_MSG *tmsg)
{
  tmsg->curTool = ExtUI::getActiveTool();
  tmsg->actBed = ExtUI::getActualTemp_celsius(ExtUI::BED);
  tmsg->tagBed = ExtUI::getTargetTemp_celsius(ExtUI::BED),
  tmsg->actHotend = ExtUI::getActualTemp_celsius(tmsg->curTool),
  tmsg->tagHotend = ExtUI::getTargetTemp_celsius(tmsg->curTool);
  tmsg->fanPercent = ExtUI::getTargetFan_percent(ExtUI::FAN0);
  tmsg->feedRatePercent = ExtUI::getFeedrate_percent();
  tmsg->x = ExtUI::getAxisPosition_mm(ExtUI::X),
  tmsg->y = ExtUI::getAxisPosition_mm(ExtUI::Y),
  tmsg->z = ExtUI::getAxisPosition_mm(ExtUI::Z);
} 



static void drawTramming(void)
{
  trammingMsg_GetCurMsg(&trammingMsg);
  GUI_SetTextMode(GUI_TEXTMODE_TRANS);
  GUI_SetColor(VAL_COLOR);
  GUI_SetBkColor(WHITE);
  GUI_RestoreColorDefault();
}

static bool msgNeedUpdate = true;
void trammingScreen_setMsg(const uint8_t *title, const uint8_t *tmsg)
{
  tmsgbody = tmsg;
  msgNeedUpdate = true;
}

void redrawTrammingMsg(void)
{
  GUI_SetBkColor(INFOMSG_BKCOLOR);
  GUI_ClearPrect(&tmsgRect);  
  Scroll_CreatePara(&tmsgScroll, (uint8_t *)tmsgbody, &tmsgRect);
  GUI_SetBkColor(BK_COLOR);
}

void drawTrammingScreenMsg(void)
{
  GUI_SetBkColor(0x4B0D);
  GUI_ClearPrect(&RectInfo);
  GUI_DispString(RectInfo.x0 + STATUS_MSG_TITLE_XOFFSET,RectInfo.y0 + STATUS_MSG_ICON_YOFFSET, textSelect(LABEL_STATUS_FEEDBACK));
  redrawTrammingMsg();
}

void scrollTMsg(void){
  GUI_SetBkColor(INFOMSG_BKCOLOR);
  GUI_SetColor(INFOMSG_COLOR);
  Scroll_DispString(&tmsgScroll, NO);
  GUI_RestoreColorDefault();
}

void menuCallTramming(void)
{
  KEY_VALUES key_num = menuKeyGetValue();
  switch(key_num)
  {
    case KEY_ICON_3:
    ui.reset_status();
      storeCmd("G35\n");
      break;
    case KEY_ICON_7:
      infoMenu.cur--; break;
    default:break;
  }
  if (msgNeedUpdate) {
    msgNeedUpdate = false;
    redrawTrammingMsg();
  }
  scrollTMsg();
}

void menuTramming()
{
  menuDrawPage(&TrammingItems);
  drawTramming();
  drawTrammingScreenMsg();
  msgNeedUpdate = false;

  menuSetFrontCallBack(menuCallTramming);
}

#endif