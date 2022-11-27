/*---------------------------------------------------------------
  File: settings_ui.h
  Project: DICE REBELS
  Author: Yeo Yi Jia, y.yijia@digipen.edu
  Co-Author: Liew Yeni, yeni.l@digipen.edu
  Co-Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#ifndef SETTINGS_UI_H
#define SETTINGS_UI_H


#include "cprocessing.h"

void settings_init(void);

void settings_update(void);

void settings_shutdown(void);

void RenderAsset(asset render, int opacity);

#endif // !SETTINGS_UI_H

