/*
 * Copyright (c) 2012, Joseph Max DeLiso, Daniel Gilbert
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are 
 * those of the authors and should not be interpreted as representing official 
 * policies, either expressed or implied, of the FreeBSD Project.
 */

#include "ElevatorSim.hpp"
#include "ElevatorSimWelcomeWindow.hpp"

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Enumerations.H>
#include <FL/names.h>

namespace elevatorSim {

/* public static member initializers */
const char ElevatorSimWelcomeWindow::WINDOW_TITLE[] = "Welcome";
const int ElevatorSimWelcomeWindow::WINDOW_WIDTH = 300;
const int ElevatorSimWelcomeWindow::WINDOW_HEIGHT = 200;

void ElevatorSimWelcomeWindow::buildDialogs()
{
   confirmDialog = new Fl_Window(350, 160, "");
   Wel_Label = new Fl_Box(10,10,330,50,"This Welcome window will not be shown again.\nClose it?"); 
   OK_Button = new Fl_Button(100, 70, 150, 40, "OK");
   Cancel_Button = new Fl_Button(100, 110, 150, 40, "Cancel");
      
   OK_Button->callback((Fl_Callback*) quitConfirmedCB, this);
   Cancel_Button->callback((Fl_Callback*) quitCancelledCB, this);

   confirmDialog->add(Wel_Label);
   confirmDialog->add(OK_Button);
   confirmDialog->add(Cancel_Button);
   confirmDialog->end();
}

void ElevatorSimWelcomeWindow::quitConfirmedCB(Fl_Button* OK_Button, void* userData) 
{
   (void) OK_Button;

   ElevatorSimWelcomeWindow* thisWin = (ElevatorSimWelcomeWindow*) userData;

   thisWin->confirmDialog->hide();
   thisWin->hide();
}

void ElevatorSimWelcomeWindow::quitCancelledCB(Fl_Button* Cancel_Button, void* userData) 
{
   (void) Cancel_Button;

   ElevatorSimWelcomeWindow* thisWin = (ElevatorSimWelcomeWindow*) userData;
   thisWin->confirmDialog->hide();
}

void ElevatorSimWelcomeWindow::windowCloseCB(Fl_Window* win, void* userData) 
{
   (void) win;

   ElevatorSimWelcomeWindow* thisWin = (ElevatorSimWelcomeWindow*) userData;
   thisWin->confirmDialog->hotspot(15, 15);
   thisWin->confirmDialog->show();
}

/* public methods */
ElevatorSimWelcomeWindow::ElevatorSimWelcomeWindow() :
   Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) {
   /* add more widgets to main window here */

	firstRun = true;

   buildDialogs();
   end();

   callback((Fl_Callback*)windowCloseCB, this);
}

ElevatorSimWelcomeWindow::~ElevatorSimWelcomeWindow() {
   delete confirmDialog;
}

} /* namespace elevatorSim */

