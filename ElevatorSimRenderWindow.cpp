/*
 * Copyright (c) 2012, Joseph Max DeLiso
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */

#include "ElevatorSim.hpp"
#include "ElevatorSimRenderWindow.hpp"

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>

namespace elevatorSim {

const int ElevatorSimRenderWindow::LEFT_MARGIN = 120;
const int ElevatorSimRenderWindow::RIGHT_MARGIN = 8;
const int ElevatorSimRenderWindow::TOP_MARGIN = 8;
const int ElevatorSimRenderWindow::BOTTOM_MARGIN = 8;

ElevatorSimRenderWindow::ElevatorSimRenderWindow(int X, int Y, int W, int H, const char* Label) :
   Fl_Gl_Window(X, Y, W, H, Label) {
   /* special initialization code */
}

void ElevatorSimRenderWindow::draw() {
   if(!valid()) {
      /* initialize */
   }

   /* draw */
}

int ElevatorSimRenderWindow::handle(int event) {
   switch(event) {
      case FL_FOCUS:

      return 1;

      case FL_UNFOCUS:

      return 1;

      /* ... handle more events ... */

      default:
         return Fl_Gl_Window::handle(event);
   }
}

} /* namespace elevatorSim */