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

#ifndef _BUILDING_H
#define _BUILDING_H

#include "ElevatorSim.hpp"
#include "Floor.hpp"
#include "Elevator.hpp"
#include "SimulationTerminal.hpp"

#include <GL/glut.h>

namespace elevatorSim{
class Floor;
class Elevator;

class Building : public SimulationTerminal {

   /* friends */

   /* private static constants */
   const unsigned int m_nStory;
   const unsigned int m_nElevator;

   /* private static methods */

   /* private instance members */
   Floor** m_Floors;
   Elevator** m_Elevators;

   /* private methods */

public:

   /* public static constants */

   /* public instanced constants */
   const GLfloat gfxScaleHeight;
   const GLfloat gfxScaleWidth;
   const GLfloat gfxEachFloorHeight;
   const GLfloat gfxEachElevWidth;

   /* constructors */
   Building(unsigned int _nStory = 20, unsigned int _nElevator = 5);
   Building(const Building& buildingCopy);
   ~Building();

   /* public methods inherited from SimulationTerminal */
   void init();
   void render();
   void update();
   
   /* inline const accessors */
   inline unsigned int getStories() const {
      return m_nStory;
   }
   
   inline unsigned int getElevators() const {
      return m_nElevator;
   }
   
   int getMaxElevHeight() const;
   int getMinElevHeight() const;
};

} /* namespace elevatorSim */

#endif
