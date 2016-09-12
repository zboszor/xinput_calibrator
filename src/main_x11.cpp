/*
 * Copyright (c) 2009 Tias Guns
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "config.h"

#include <unistd.h> // for pause()
#include "gettext.h"
#include "calibrator.hh"
#include "gui/x11.hpp"

int main(int argc, char** argv)
{
    Calibrator* calibrator;

    setlocale(LC_MESSAGES, "");
    setlocale(LC_CTYPE, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    calibrator = Calibrator::make_calibrator(argc, argv);
    if (calibrator->try_restore())
        return 0;

    GuiCalibratorX11::make_instance( calibrator );

#ifdef HAVE_TIMERFD
    while (1)
    	GuiCalibratorX11::give_timer_signal();
#else
    // wait for timer signal, processes events
    while(1)
        pause();
#endif

    delete calibrator;
    return 0;
}
