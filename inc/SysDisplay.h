/**************************************************************************//**
 *  @file
 *  @author Steve Lascos
 *  @company Blackaddr Audio
 *
 *  @copyright This software is proprietary and confidential. It may not be
 *  used for any purpose without prior written permission from Blackaddr Audio.
 *  [2020] - [2024] Blackaddr Audio
 *  All Rights Reserved.
 *
 *  NOTICE:  All information contained herein is, and remains the property of
 *  Blackaddr Audio and its suppliers, if any.  The intellectual and technical
 *  concepts contained herein are proprietary to Blackaddr Audio and its
 *  suppliers and may be covered by U.S. and Foreign Patents, patents in
 *  process, and are protected by trade secret or copyright law.
 *  Dissemination of this information or reproduction of this material is
 *  strictly forbidden unless prior written permission is obtained from
 *  Blackaddr Audio.
 *****************************************************************************/

#pragma once

#include <cstdint>
#include <cstdarg>
#include <memory>

namespace SysPlatform {

class SysDisplay {
public:
    enum class Font {
        DEFAULT_SMALL = 0,
        DEFAULT_LARGE,
        TUNER
    };

    SysDisplay();
    virtual ~SysDisplay();

    void begin();

    unsigned getHeight();
    unsigned getWidth();

    void setFont(Font font);
    void setTextColor(uint16_t color);
    void setCursor(int16_t x, int16_t y);
    int16_t getCursorX();
    int16_t getCursorY();
    void getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1,
                     int16_t *y1, uint16_t *w, uint16_t *h);

    int printf(const char* str, const char *fmt, ...);

    void clearDisplay();
    void invertDisplay(bool invert);
    void flipVertical(bool flip);
    void display();
    void fillScreen(uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                        uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
        uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h,
                  uint16_t color);

    static const unsigned SYS_BLACK;
    static const unsigned SYS_WHITE;
    static const unsigned SYS_DISPLAY_HEIGHT;
    static const unsigned SYS_DISPLAY_WIDTH;
protected:
    struct impl;
    std::shared_ptr<impl> m_pimpl;
};

extern SysDisplay sysDisplay;

}
