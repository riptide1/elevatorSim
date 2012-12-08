/*
 * Copyright (c) 2012, Joseph Max DeLiso
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
#include "Person.hpp"
#include "Location.hpp"
#include "Logger.hpp"
#include "SimulationState.hpp"

#include <algorithm>
#include <vector>

double totalwait = 0;
int totalpass = 0;

namespace elevatorSim {

/* constructors */
Person::Person(
   Location startLoc,
   Location dest,
   enum PRIORITY p) {
      start = startLoc;
      destination = dest;
      priority = p;

   m_dwrequest = boost::posix_time::second_clock::local_time();
  // m_dwpickup = boost::posix_time::second_clock::local_time();
  // wait = m_dwrequest - m_dwpickup;

      /* print debug info */
      if(isDebugBuild()) {
         std::stringstream dbgSS;
         dbgSS << "with person @ " << this
            << " start " << start.getYVal()
            << ", dest " << destination.getYVal()
            << ", pri = " << (int)priority << std::endl;

         LOG_INFO( Logger::SUB_MEMORY, sstreamToBuffer( dbgSS ));
      }
}

Person::~Person() {
   /* print debug info */
   if(isDebugBuild()) {
      std::stringstream dbgSS;
      dbgSS << "destructing person @ " << this << std::endl;
      LOG_INFO( Logger::SUB_MEMORY, sstreamToBuffer( dbgSS ));
   }
}

void Person::init() {
   /* TODO */
}

void Person::render() {
   /* TODO */
}

void Person::update() {
   /* Check to see if we've reached a movement condition. If so,
   * either move from floor to elevator or from elevator to floor.
   */

   IPersonCarrier* container = locateContainer();
   std::vector<Elevator*> elevators = SimulationState::acquire().getBuilding().getElevators();
   std::vector<Floor*> floors = SimulationState::acquire().getBuilding().getFloors();

   /* we're waiting at floor, so check if there are any elevators currently on this floor,
   * check to see if an elevator has arrived, and get on if it has
   */
   if( container->getCarrierType() == IPersonCarrier::FLOOR_CARRIER ) {
      Floor* floorContainer = static_cast<Floor*> (container);
      std::set<Elevator*> candidateElevators;

      /* iterate over all of the elevators and compare their positions to this person's
      * starting location */
      std::for_each(
         elevators.begin(),
         elevators.end(),
         [this, &candidateElevators] ( Elevator* thisElevator ) {
            if( thisElevator -> getYVal() == start.getYVal() * Floor::YVALS_PER_FLOOR ) {
               /* we've found a candidate elevator, so add it to the set */ 
               candidateElevators.insert(thisElevator);
            }
      });

      /* if there are candidate elevators */
      if( candidateElevators.size() > 0 ) {
         /* just pick the first one (for now) */

         /* TODO: choose randomly among available elevators,
         * (in preparation for making this a scriptable choice) */
         Elevator * elevatorToBoard  = *candidateElevators.begin();
		 
		 setPickuptime(); 
		 totalpass++;
		 setWaittime();
		 totalwait += getWaittime();

		 printf("totalpass = %d,	totalwait = %f \n", totalpass, totalwait);

         /* move ourselves to this elevator */
         elevatorToBoard -> addPerson( this );

         /* remove ourselves from our containing floor */
         assert( floorContainer -> removePerson( this ) );
		 
      }
   } else if( container->getCarrierType() == IPersonCarrier::ELEVATOR_CARRIER) {
      Elevator* elevatorContainer = static_cast<Elevator*> (container);

      /* if our container elevator has got the same yVal as our destination,
      * we've arrived */
      if( elevatorContainer->getYVal() == destination.getYVal() ) {
         int floorIndex = destination.getYVal() / Floor::YVALS_PER_FLOOR;

         /* move ourselves to this floor */
         floors[floorIndex] -> addPerson( this );

         if(isDebugBuild()) {
            std::stringstream dbgSS;
            dbgSS << "removing self from elevator container, "
               << "num occupants before: " << elevatorContainer -> numPeopleContained()
               << " ..."
               << std::endl;
            LOG_INFO( Logger::SUB_ELEVATOR_LOGIC, sstreamToBuffer( dbgSS ));
         }

         /* remove ourselves from our containing elevator */
         assert( elevatorContainer -> removePerson( this ) );

         if(isDebugBuild()) {
            std::stringstream dbgSS;
            dbgSS << "removed self from elevator container, "
               << "num occupants after: " << elevatorContainer -> numPeopleContained()
               << std::endl;
            LOG_INFO( Logger::SUB_ELEVATOR_LOGIC, sstreamToBuffer( dbgSS ));
         }
      }
   }
}

IPersonCarrier* Person::locateContainer() const {
   /* find parent by searching over all floors and elevators,
    * this operation's worst case runs in linear time, O(E+F),
    * where E is number of elevators and F is number of Floors.
    */
   Building& building = SimulationState::acquire().getBuilding();

   std::vector<Floor*> floors = building.getFloors();
   std::vector<Elevator*> elevators = building.getElevators();

   IPersonCarrier* container = NULL;

   for(std::vector<Floor*>::const_iterator it = floors.begin();
      container == NULL && it != floors.end();
      ++it) {
         container =
            ( (Floor*)(*it) -> containsPerson(this) )
            ? ( (Floor*)(*it) ) : ( NULL );
   }

   for(std::vector<Elevator*>::const_iterator it = elevators.begin();
      container == NULL && it != elevators.end();
      ++it) {
         container =
            ( (Elevator*)(*it) -> containsPerson(this) )
            ? ( (Elevator*)(*it) ) : ( NULL );
   }

   /* TODO: add std::set<IPeopleCarrier*> building.getPersonCarriers */

   assert( container != NULL );
   return container;
}

boost::posix_time::ptime Person::getRequesttime(){
	   return m_dwrequest;
}
boost::posix_time::ptime Person::getPickuptime(){
	   return m_dwpickup;

}
double Person::getWaittime(){
	
	return wait.total_seconds();
}
   
void Person::setRequesttime(){
	  m_dwrequest = boost::posix_time::second_clock::local_time();
}
void Person::setPickuptime(){
	   m_dwpickup = boost::posix_time::second_clock::local_time();
}
void Person::setWaittime(){
	 wait = getPickuptime() - getRequesttime();
}

} /* namespace ElevatorSim */
