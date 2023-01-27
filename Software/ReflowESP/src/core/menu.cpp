#include "menu.h"
#include "../main.h"
#include "../config/Config.h"

// Menu library
#include <menu.h>

// Serial IO
#include <menuIO/chainStream.h>
#include <menuIO/serialIO.h>
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>

// TFT
#include <TFT_eSPI.h>
#include <menuIO/TFT_eSPIOut.h>

// Encoder
#include <ClickEncoder.h>
#include <menuIO/clickEncoderIn.h>

using namespace Menu;

// TFT
TFT_eSPI gfx = TFT_eSPI();

// Encoder
ClickEncoder clickEncoder = ClickEncoder(ENCA, ENCB, ENCBTN, ENCSTEPS, 1, INPUT, INPUT_PULLDOWN);
ClickEncoderStream encStream(clickEncoder, 1);

int exitMenuOptions = 0;

result go_pwm() {
  delay(50);
  Serial.println("go_pwm");
  pwmout.set_period(pwmPeriodSec * 1000);
  return proceed;
}

const colorDef<uint16_t> colors[6] MEMMODE = {
  //{{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
  {{(uint16_t)Black, (uint16_t)Black}, {(uint16_t)Black, (uint16_t)Red,   (uint16_t)Red}}, //bgColor
  {{(uint16_t)White, (uint16_t)White},  {(uint16_t)White, (uint16_t)White, (uint16_t)White}},//fgColor
  {{(uint16_t)Red, (uint16_t)Red}, {(uint16_t)Yellow, (uint16_t)Yellow, (uint16_t)Yellow}}, //valColor
  {{(uint16_t)White, (uint16_t)White}, {(uint16_t)White, (uint16_t)White, (uint16_t)White}}, //unitColor
  {{(uint16_t)White, (uint16_t)Gray},  {(uint16_t)Black, (uint16_t)Red,  (uint16_t)White}}, //cursorColor
  {{(uint16_t)White, (uint16_t)Yellow}, {(uint16_t)Black,  (uint16_t)Red,   (uint16_t)Red}}, //titleColor
};

MENU(tempMenu, "Temperature", doNothing, noEvent, wrapStyle,
  FIELD(pwmPeriodSec, "PWM Period", "s", 1, 60, 1, 1, go_pwm, exitEvent, noStyle),
  EXIT("< BACK")
)

MENU(settingsMenu, "Settings", doNothing, noEvent, wrapStyle,
  SUBMENU(tempMenu),
  EXIT("< Back")
)

MENU(mainMenu, MACHINE_NAME, doNothing, noEvent, wrapStyle,
  SUBMENU(settingsMenu),
  FIELD(pwmState, "PWM", "", 0, 1, 0.1, 0.1, doNothing, noEvent, noStyle)
);

serialIn serial(Serial);
MENU_INPUTS(in, &encStream, &serial);
MENU_OUTPUTS(out, MAX_DEPTH,
  TFT_eSPI_OUT(gfx, colors, FONT_WIDTH, FONT_HEIGHT, {0, 0, GFX_WIDTH / FONT_WIDTH, GFX_HEIGHT / FONT_HEIGHT}),
  SERIAL_OUT(Serial),
  NONE
);

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out);
