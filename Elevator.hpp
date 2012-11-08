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

#ifndef _ELEVATOR_H
#define _ELEVATOR_H

#include "ElevatorSim.hpp"
#include "Location.hpp"
#include "Person.hpp"
#include "SimulationTerminal.hpp"
#include "cRenderObjs.hpp"
#include "Building.hpp"

#include <vector>

namespace elevatorSim {

class Location;
class Building;
struct SimulationTerminal;

class Elevator : public Location, public SimulationTerminal {

   /* friends */


   /* private static constants */


   /* private static methods */


   /* private instance members */
   const Building& owner;
   const int maxVel;
   const int maxAccel;
   const int maxOccupants;
   int currentVel;
   int currentAccel;
   int destFloor;
   bool* floorsSignaled;
   std::vector<Person> occupants;

   /* private methods */

public:

   /* public static constants */
   static const int DEFAULT_MAX_VEL;
   static const int DEFAULT_MAX_ACCEL;
   static const int DEFAULT_MAX_OCCUPANTS; 

   /* public instance members */

   /* constructors & destructors */
   Elevator(
      const Building& _owner,
      int _yVal = 0, 
      const int _maxVel = DEFAULT_MAX_VEL, 
      const int _maxAccel = DEFAULT_MAX_ACCEL, 
      const int _maxOccupants = DEFAULT_MAX_OCCUPANTS);
   ~Elevator();

   /* public methods */
   bool canStopAtNextFloor();
   
   /* inherited from SimulationTerminal */
   void init();
   void render();
   void update();
   void generateRandomDest();

};

} /* namespace elevatorSim */

#endif
