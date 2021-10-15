//==============================================================================
//
//  This file is part of GNSSTk, the GNSS Toolkit.
//
//  The GNSSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GNSSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GNSSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//  
//  This software was developed by Applied Research Laboratories at the 
//  University of Texas at Austin.
//  Copyright 2004-2021, The Board of Regents of The University of Texas System
//
//==============================================================================


//==============================================================================
//
//  This software was developed by Applied Research Laboratories at the 
//  University of Texas at Austin, under contract to an agency or agencies 
//  within the U.S. Department of Defense. The U.S. Government retains all 
//  rights to use, duplicate, distribute, disclose, or release this software. 
//
//  Pursuant to DoD Directive 523024 
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public 
//                            release, distribution is unlimited.
//
//==============================================================================
#include <iterator>
#include "SP3NavDataFactory.hpp"
#include "SP3Stream.hpp"
#include "SP3Header.hpp"
#include "SP3Data.hpp"
#include "OrbitDataSP3.hpp"
#include "Rinex3ClockStream.hpp"
#include "Rinex3ClockHeader.hpp"
#include "Rinex3ClockData.hpp"
#include "TimeString.hpp"
#include "MiscMath.hpp"

using namespace std;

namespace gnsstk
{
   const ObsID SP3NavDataFactory::oidGPS(ObservationType::NavMsg,
                                         CarrierBand::L1,TrackingCode::CA);
   const ObsID SP3NavDataFactory::oidGalileo(ObservationType::NavMsg,
                                             CarrierBand::L5,
                                             TrackingCode::E5aI);
   const ObsID SP3NavDataFactory::oidQZSS(ObservationType::NavMsg,
                                          CarrierBand::L1,TrackingCode::CA);
   const ObsID SP3NavDataFactory::oidGLONASS(ObservationType::NavMsg,
                                             CarrierBand::G1,
                                             TrackingCode::Standard);
   const ObsID SP3NavDataFactory::oidBeiDou(ObservationType::NavMsg,
                                            CarrierBand::B1,TrackingCode::B1I);
   const NavType SP3NavDataFactory::ntGPS(NavType::GPSLNAV);
   const NavType SP3NavDataFactory::ntGalileo(NavType::GalFNAV);
   const NavType SP3NavDataFactory::ntQZSS(NavType::GPSLNAV);
   const NavType SP3NavDataFactory::ntGLONASS(NavType::GloCivilF);
   const NavType SP3NavDataFactory::ntBeiDou(NavType::BeiDou_D1);

      /// A clock bias >= this is considered bad.
   const double maxBias = 999999.0;

   SP3NavDataFactory ::
   SP3NavDataFactory()
         : storeTimeSystem(TimeSystem::Any),
           checkDataGapPos(false),
           gapIntervalPos(0.0),
           checkDataGapClk(false),
           gapIntervalClk(0.0),
           checkIntervalPos(false),
           maxIntervalPos(0.0),
           checkIntervalClk(false),
           maxIntervalClk(0.0),
           useSP3clock(true),
           rejectBadPosFlag(true),
           rejectBadClockFlag(true),
           rejectPredPosFlag(false),
           rejectPredClockFlag(false),
           interpType(ClkInterpType::Lagrange),
           halfOrderClk(5),
           halfOrderPos(5)
   {
      supportedSignals.insert(NavSignalID(SatelliteSystem::BeiDou,
                                          CarrierBand::B1,
                                          TrackingCode::B1I,
                                          NavType::BeiDou_D1));
      supportedSignals.insert(NavSignalID(SatelliteSystem::BeiDou,
                                          CarrierBand::B1,
                                          TrackingCode::B1I,
                                          NavType::BeiDou_D2));
      supportedSignals.insert(NavSignalID(SatelliteSystem::BeiDou,
                                          CarrierBand::B3,
                                          TrackingCode::B3I,
                                          NavType::BeiDou_D1));
      supportedSignals.insert(NavSignalID(SatelliteSystem::BeiDou,
                                          CarrierBand::B3,
                                          TrackingCode::B3I,
                                          NavType::BeiDou_D2));
      supportedSignals.insert(NavSignalID(SatelliteSystem::BeiDou,
                                          CarrierBand::B2,
                                          TrackingCode::B2I,
                                          NavType::BeiDou_D1));
      supportedSignals.insert(NavSignalID(SatelliteSystem::BeiDou,
                                          CarrierBand::B2,
                                          TrackingCode::B2I,
                                          NavType::BeiDou_D2));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::CA,
                                          NavType::GPSLNAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::L1CD,
                                          NavType::GPSCNAV2));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::NSCA,
                                          NavType::GPSLNAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::Y,
                                          NavType::GPSLNAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::L2CML,
                                          NavType::GPSCNAVL2));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::L2CM,
                                          NavType::GPSCNAVL2));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::Y,
                                          NavType::GPSLNAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L5,
                                          TrackingCode::L5I,
                                          NavType::GPSCNAVL5));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::MD,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::MDP,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::MPA,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::Mprime,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L1,
                                          TrackingCode::MprimePA,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::MD,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::MDP,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::MPA,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::Mprime,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::GPS,
                                          CarrierBand::L2,
                                          TrackingCode::MprimePA,
                                          NavType::GPSMNAV, 0, 0));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Galileo,
                                          CarrierBand::L5,
                                          TrackingCode::E5aI,
                                          NavType::GalFNAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Galileo,
                                          CarrierBand::E5b,
                                          TrackingCode::E5bI,
                                          NavType::GalINAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Galileo,
                                          CarrierBand::L1,
                                          TrackingCode::E1B,
                                          NavType::GalINAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Glonass,
                                          CarrierBand::G1,
                                          TrackingCode::Standard,
                                          NavType::GloCivilF));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Glonass,
                                          CarrierBand::G2,
                                          TrackingCode::Standard,
                                          NavType::GloCivilF));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Glonass,
                                          CarrierBand::G3,
                                          TrackingCode::G3TestData,
                                          NavType::GloCivilC));
      supportedSignals.insert(NavSignalID(SatelliteSystem::Glonass,
                                          CarrierBand::G3,
                                          TrackingCode::L3OCD,
                                          NavType::GloCivilC));
      supportedSignals.insert(NavSignalID(SatelliteSystem::QZSS,
                                          CarrierBand::L1,
                                          TrackingCode::CA,
                                          NavType::GPSLNAV));
      supportedSignals.insert(NavSignalID(SatelliteSystem::QZSS,
                                          CarrierBand::L5,
                                          TrackingCode::L5I,
                                          NavType::GPSCNAVL5));
   }


   bool SP3NavDataFactory ::
   find(const NavMessageID& nmid, const CommonTime& when,
        NavDataPtr& navOut, SVHealth xmitHealth, NavValidityType valid,
        NavSearchOrder order)
   {
      bool rv;
      NavMessageID genericID;
      if (nmid.messageType != NavMessageType::Ephemeris)
      {
         return false;
      }
         // ignore the return code of transNavMsgID, find might still work.
      transNavMsgID(nmid, genericID);
      rv = findGeneric(NavMessageType::Ephemeris, genericID, when, navOut);
      if (rv == false)
      {
         return false;
      }
         /** @todo If someone attempts to use SP3 but sets the type
          * filter to exclude clock, no clock data will be stored and
          * this will end up returning false.  I'm not sure if this is
          * valid behavior. */
      return findGeneric(NavMessageType::Clock, genericID, when, navOut);
   }


      // This method is roughly equivalent to the deprecated
      // TabularSatStore::getTableInterval.
      // Implementation notes:
      // * iterator ti3 is used as an "end"-type quantity, meaning the
      //   interpolation methods will iterate from ti1 (inclusive) to
      //   ti3 (exclusive).  This differs from the deprecated
      //   TabularSatStore which iterates from it1 to it2 inclusive.
   bool SP3NavDataFactory ::
   findGeneric(NavMessageType nmt, const NavSatelliteID& nsid,
               const CommonTime& when, NavDataPtr& navData)
   {
      unsigned halfOrder;
      bool checkDataGap, checkInterval;
      double gapInterval, maxInterval;
      if (nmt == NavMessageType::Ephemeris)
      {
         halfOrder = halfOrderPos;
         checkDataGap = checkDataGapPos;
         gapInterval = gapIntervalPos;
         checkInterval = checkIntervalPos;
         maxInterval = maxIntervalPos;
      }
      else if (nmt == NavMessageType::Clock)
      {
         halfOrder = halfOrderClk;
         checkDataGap = checkDataGapClk;
         gapInterval = gapIntervalClk;
         checkInterval = checkIntervalClk;
         maxInterval = maxIntervalClk;
      }
      else
         return false;
      // cerr << __PRETTY_FUNCTION__ << " nmt=" << StringUtils::asString(nmt)
      //      << endl;
      bool giveUp = false;
      auto dataIt = data.find(nmt);
      if (dataIt == data.end())
      {
         // cerr << "  no data for nav message type" << endl;
         return false;
      }
         // To support wildcard signals, we need to do a linear search.
      for (auto& sati : dataIt->second)
      {
         if (sati.first != nsid)
            continue; // skip non matches
            // This is not the entry we want, but it is instead the first
            // entry we probably (depending on order) *don't* want.
         auto ti2 = sati.second.upper_bound(when);
         auto ti1 = ti2, ti3 = ti2;
         // cerr << printTime(ti2->first,"  ti2 has been set to %F/%g") << endl;
         if (ti2 == sati.second.end())
         {
               // Since we're at the end we can't do interpolation,
               // but we can still check for an exact match.
            // cerr << "  probably giving up because we're at the end" << endl;
            giveUp = true;
         }
         else
         {
               // I wouldn't have done this except that I'm trying to
               // match the behavior of SP3EphemerisStore.  Basically,
               // for exact matches, the interpolation interval is
               // shifted "left" by one, but not when the time match
               // is not exact.
            auto tiTmp = std::prev(ti2);
            unsigned offs = 0;
            if ((tiTmp != sati.second.end()) &&
                (tiTmp->second->timeStamp == when))
            {
               offs = 1;
            }
            // cerr << "gap = " << (ti2->first - tiTmp->first) << endl;
            if (checkDataGap && (tiTmp != sati.second.end()) &&
                ((ti2->first - tiTmp->first) > gapInterval))
            {
               // cerr << "  giving up because the gap interval is too big"<< endl;
               giveUp = true;
            }
               // This is consistent with SP3EphemerisStore for exact match
               // Check to see if we can do interpolation.
            giveUp |=
               (std::distance(sati.second.begin(), ti2) < (halfOrder+offs)) |
               (std::distance(ti2, sati.second.end()) < (halfOrder-offs));
            // cerr << "  distance from begin = "
            //      << std::distance(sati.second.begin(), ti2) << endl
            //      << "  distance to end = "
            //      << std::distance(ti2, sati.second.end()) << endl;
            if (!giveUp)
            {
                  // we can do interpolation so set up iterators
               ti1 = std::prev(ti2,halfOrder+offs);
               ti3 = std::next(ti2,halfOrder-offs);
               // cerr << printTime(ti1->first,"  ti1 has been set to %F/%g") << endl << printTime(ti3->first,"  ti3 has been set to %F/%g") << endl;
            }
            else
            {
                  // We're on the edge of available and can't interpolate.
               // cerr << "  probably giving up because we're near the bound" << endl;
            }
         }
            // always back up one which allows us to check for exact match.
         ti2 = std::prev(ti2);
         // cerr << printTime(ti1->first,"  ti1 has been set to %F/%g") << endl;
         if (ti2 == sati.second.end())
         {
            // cerr << "ti2 is now end?" << endl;
               // Nothing available that's even close.
            return false;
         }
         if (!giveUp)
         {
               // Need a copy of ti3 to move it back 1, as otherwise
               // the interval check will give the wrong results since
               // it's 1 beyond the actual last interpolated item.
            auto iti3 = std::prev(ti3);
            // cerr << "  distance from ti1 to ti2 = " << std::distance(ti1,ti2)
            //      << endl
            //      << "  distance from ti2 to ti3 = " << std::distance(ti2,ti3)
            //      << endl
            //      << "  interval = " << (iti3->first - ti1->first) << endl;
            if (checkInterval && ((iti3->first - ti1->first) > maxInterval))
            {
               // cerr << "  giving up because the interpolation interval is too"
               //      << " big" << endl;
               giveUp = true;
            }
         }
         if (ti2->second->timeStamp == when)
         {
               // Even though it's an exact match, we still need to
               // make a new object so that we can fill in clock
               // information without affecting the internal store.
            if (!navData)
            {
               OrbitDataSP3 *stored = dynamic_cast<OrbitDataSP3*>(
                  ti2->second.get());
               navData = std::make_shared<OrbitDataSP3>(*stored);
               // ti2->second->dump(std::cerr, DumpDetail::Full);
               // navData->dump(std::cerr, DumpDetail::Full);
                  // If giveUp is not set, then we can do some
                  // interpolation to fill in any missing data.
               if (!giveUp)
               {
                  if (nmt == NavMessageType::Ephemeris)
                  {
                     // cerr << "  interpolating ephemeris for exact match" << endl;
                     interpolateEph(ti1, ti3, when, navData);
                  }
                  else if (nmt == NavMessageType::Clock)
                  {
                     // cerr << "  interpolating clock for exact match" << endl;
                     interpolateClk(ti1, ti3, when, navData);
                  }
               }
               // cerr << "  found an exact match" << endl;
               return true;
            }
            else
            {
               OrbitDataSP3 *stored = dynamic_cast<OrbitDataSP3*>(
                  ti2->second.get());
               OrbitDataSP3 *navOut = dynamic_cast<OrbitDataSP3*>(
                  navData.get());
               if (nmt == NavMessageType::Ephemeris)
               {
                  navOut->copyXV(*stored);
                     // fill in missing data if we can
                  if (!giveUp)
                  {
                     // cerr << "  interpolating ephemeris for exact match (2)" << endl;
                     interpolateEph(ti1, ti3, when, navData);
                  }
               }
               else if (nmt == NavMessageType::Clock)
               {
                  navOut->copyT(*stored);
                     // fill in missing data if we can
                  if (!giveUp)
                  {
                     // cerr << "  interpolating clock for exact match (2)" << endl;
                     interpolateClk(ti1, ti3, when, navData);
                  }
               }
               // stored->dump(std::cerr, DumpDetail::Full);
               // navOut->dump(std::cerr, DumpDetail::Full);
               // cerr << "  found an exact match with existing data" << endl;
               return true;
            }
         }
         else if (giveUp)
         {
               // not an exact match and no data available for interpolation.
            // cerr << "  giving up, insufficient data for interpolation" << endl;
            return false;
         }
         else
         {
            // cerr << "  faking interpolation" << endl;
            if (!navData)
            {
               // cerr << "  creating new empty navData" << endl;
               OrbitDataSP3 *stored = dynamic_cast<OrbitDataSP3*>(
                  ti2->second.get());
               navData = std::make_shared<OrbitDataSP3>(*stored);
               navData->timeStamp = when;
            }
            // else
            // {
            //    cerr << "  already have valid navData" << endl;
            // }
            // std::cerr << "OK, have interval " << printTime(ti1->first,"%F/%g") <<
            //       " <= " <<printTime(when,"%F/%g")<< " < " <<printTime(ti3->first,"%F/%g");
            if (nmt == gnsstk::NavMessageType::Ephemeris)
            {
               interpolateEph(ti1, ti3, when, navData);
               return true;
            }
            else if (nmt == gnsstk::NavMessageType::Clock)
            {
               interpolateClk(ti1, ti3, when, navData);
               return true;
            }
         } // else (do interpolation)
      } // for (auto& sati : dataIt->second)
      // cerr << "  giving up at the end" << endl;
      return false;
   }


   bool SP3NavDataFactory ::
   addDataSource(const std::string& source)
   {
      bool rv = true;
      bool processEph = (procNavTypes.count(NavMessageType::Ephemeris) > 0);
      bool processClk = (procNavTypes.count(NavMessageType::Clock) > 0);
         // When either of these two change, we store the existing
         // NavDataPtr and create a new one.
      CommonTime lastTime;
      SatID lastSat;
      NavDataPtr eph, clk;
      try
      {
         SP3Stream is(source.c_str(), ios::in);
         SP3Header head;
         SP3Data data;
         if (!is)
         {
            return false;
         }
         is >> head;
         if (!is)
         {
            return addRinexClock(source);
         }

            // know whether to look for the extra info contained in SP3c
         bool isC = (head.version==SP3Header::SP3c);
            // check/save TimeSystem to storeTimeSystem
         if ((head.timeSystem != TimeSystem::Any) &&
             (head.timeSystem != TimeSystem::Unknown))
         {
               // if store time system has not been set, do so
            if (storeTimeSystem == TimeSystem::Any)
            {
                  /// @note store TimeSystem must be consistent.
               storeTimeSystem = head.timeSystem;
            }
            else if (storeTimeSystem != head.timeSystem)
            {
                  // Don't load an SP3 file with a differing time system
               cerr << "Time system mismatch in SP3 data, "
                    << gnsstk::StringUtils::asString(storeTimeSystem)
                    << " (store) != "
                    << gnsstk::StringUtils::asString(head.timeSystem)
                    << " (file)" << endl;
               return false;
            }
         }

         while (is)
         {
            is >> data;
            if (!is)
            {
               if (is.eof())
                  break;
               else
                  return false; // some other error
            }
            if ((lastSat != data.sat) || (lastTime != data.time))
            {
               // cerr << "time or satellite change, storing" << endl;
               lastSat = data.sat;
               lastTime = data.time;
               // cerr << "storing eph" << endl;
               if (!store(processEph, eph))
                  return false;
               // cerr << "storing clk" << endl;
               if (!store(processClk && useSP3clock, clk))
                  return false;
            }
               // Don't process time records otherwise we'll end up
               // storing junk in the store that has a time stamp and
               // a bogus satellite ID.
            if (data.RecType != '*')
            {
               if (rejectBadPosFlag &&
                   (data.x[0] == 0.0) ||
                   (data.x[1] == 0.0) ||
                   (data.x[2] == 0.0))
               {
                     // don't add this record with a bad position
                  continue;
               }
               else if (rejectBadClockFlag && (fabs(data.clk) >= maxBias))
               {
                     // don't add this record with a bad clock
                  continue;
               }
               if (processEph)
               {
                     // If the orbit data are predictions and we've
                     // been asked to ignore position predictions, do
                     // so. Otherwise, add the data to the store.
                  if ((!rejectPredPosFlag || data.orbitPredFlag) &&
                      !convertToOrbit(head, data, isC, eph))
                  {
                     return false;
                  }
               }
               if (processClk)
               {
                     // If the clock data are predictions and we've
                     // been asked to ignore clock predictions, do
                     // so. Otherwise, add the data to the store.
                  if ((!rejectPredClockFlag || data.clockPredFlag) &&
                      !convertToClock(head, data, isC, clk))
                  {
                     return false;
                  }
               }
            }
         }
            // store the final record(s)
         // cerr << "storing last eph" << endl;
         if (!store(processEph, eph))
            return false;
         // cerr << "storing last clk" << endl;
         if (!store(processClk, clk))
            return false;
      }
      catch (gnsstk::Exception& exc)
      {
         rv = false;
         cerr << exc << endl;
      }
      catch (std::exception& exc)
      {
         rv = false;
         cerr << exc.what() << endl;
      }
      catch (...)
      {
         rv = false;
         cerr << "Unknown exception" << endl;
      }
      return rv;
   }


   bool SP3NavDataFactory ::
   addRinexClock(const std::string& source)
   {
      bool rv = true;
         // We have to handle this a bit carefully.  If we're not
         // processing clock data, we still need to at least identify
         // the data, otherwise NavLibrary/MultiFormatNavDataFactory
         // might incorrectly handle the processing of the file.
      bool processClk = (procNavTypes.count(NavMessageType::Clock) > 0);
      try
      {
         Rinex3ClockStream is(source.c_str(), ios::in);
         Rinex3ClockHeader head;
         Rinex3ClockData data;
         if (!is)
         {
            return false;
         }
         is >> head;
         if (!is)
         {
            return false;
         }

            // At this point, we have valid RINEX clock.  Probably.
         if (!processClk)
            return true; // ...but the user doesn't want it.

            // check/save TimeSystem to storeTimeSystem
         if(head.timeSystem != TimeSystem::Any &&
            head.timeSystem != TimeSystem::Unknown)
         {
               // if store time system has not been set, do so
            if(storeTimeSystem == TimeSystem::Any)
            {
                  /// @note store TimeSystem must be consistent.
               storeTimeSystem = head.timeSystem;
            }
            else if (storeTimeSystem != head.timeSystem)
            {
                  // Don't load a RINEX clock file with a differing time system
               cerr << "Time system mismatch in SP3/RINEX clock data "
                    << gnsstk::StringUtils::asString(storeTimeSystem)
                    << " (store) != "
                    << gnsstk::StringUtils::asString(head.timeSystem)
                    << " (file)" << endl;
               return false;
            }
         }
         else
         {
            head.timeSystem = TimeSystem::GPS;
            storeTimeSystem = head.timeSystem;
         }

            // Valid RINEX clock data with appropriate time system, go
            // ahead and switch to using RINEX clock instead of SP3
            // clock.
         useRinexClockData();

         while (is)
         {
            is >> data;
            if (!is)
            {
               if (is.eof())
                  break;
               else
                  return false; // some other error
            }
            if(data.datatype == std::string("AS"))
            {
               data.time.setTimeSystem(head.timeSystem);
               OrbitDataSP3 *gps;
               NavDataPtr clk = std::make_shared<OrbitDataSP3>();
                  // Force the message type to clock because
                  // OrbitDataSP3 defaults to Ephemeris.
               clk->signal.messageType = NavMessageType::Clock;
               setSignal(data.sat, clk->signal);
               gps = dynamic_cast<OrbitDataSP3*>(clk.get());
               gps->timeStamp = data.time;
                  // apparently the time system isn't set in
                  // Rinex3ClockData, only in the header.
               gps->timeStamp.setTimeSystem(head.timeSystem);
               gps->clkBias = data.bias * 1e6; // seconds to us
               gps->biasSig = data.sig_bias;
               gps->clkDrift = data.drift * 1e-6;
               gps->driftSig = data.sig_drift;
               gps->clkDrRate = data.accel;
               gps->drRateSig = data.sig_accel;
               if (!store(processClk, clk))
                  return false;
            }
         }
      }
      catch (gnsstk::Exception& exc)
      {
         rv = false;
         cerr << exc << endl;
      }
      catch (std::exception& exc)
      {
         rv = false;
         cerr << exc.what() << endl;
      }
      catch (...)
      {
         rv = false;
         cerr << "Unknown exception" << endl;
      }
      return rv;
   }


   std::string SP3NavDataFactory ::
   getFactoryFormats() const
   {
      if (procNavTypes.empty() ||
          (procNavTypes.count(NavMessageType::Ephemeris) > 0) ||
          (procNavTypes.count(NavMessageType::Clock) > 0))
      {
         return "SP3a, SP3c";
      }
      return "";
   }


   bool SP3NavDataFactory ::
   convertToOrbit(const SP3Header& head, const SP3Data& navIn, bool isC,
                  NavDataPtr& navOut)
   {
      // cerr << __PRETTY_FUNCTION__ << endl;
      OrbitDataSP3 *gps;
         // SP3 needs to merge multiple records, position and
         // velocity, so we only create new objects as needed.
      if (!navOut)
      {
         // cerr << "  creating OrbitDataSP3" << endl;
         navOut = std::make_shared<OrbitDataSP3>();
      }
      gps = dynamic_cast<OrbitDataSP3*>(navOut.get());
      // cerr << "  navIn.RecType=" << navIn.RecType << endl
      //      << "  navIn.correlationFlag=" << navIn.correlationFlag << endl;
      switch (navIn.RecType)
      {
         case 'P':
            gps->timeStamp = navIn.time;
            for (unsigned i = 0; i < 3; i++)
            {
               gps->pos[i] = navIn.x[i];
                  /** @todo the ::pow statement was pulled from
                   * SP3EphemerisStore.  I'm not 100% sure it's
                   * possible to get sigma this way.  We should
                   * determine if it is possible and if so write tests
                   * for this case.  Look for all uses of isC and
                   * correlationFlag. */
               if (navIn.correlationFlag)
               {
                  gps->posSig[i] = navIn.sdev[i];
                  // cerr << "navIn.sdev[" << i << "] = " << gps->posSig[i] << endl;
               }
               else if (isC && (navIn.sig[i] >= 0))
               {
                  gps->posSig[i] = ::pow(head.basePV, navIn.sig[i]);
                  // cerr << "pow(head.basePV,navIn.sig[" << i << "] = " << gps->posSig[i] << endl;
               }
            }
            setSignal(navIn.sat, navOut->signal);
            break;
         case 'V':
            gps->timeStamp = navIn.time;
            for (unsigned i = 0; i < 3; i++)
            {
                  // Yes, x.  Because SP3Data stores position and
                  // velocity in separate records and the data from
                  // both goes into x.
               gps->vel[i] = navIn.x[i];
               if (navIn.correlationFlag)
                  gps->velSig[i] = navIn.sdev[i];
               else if (isC && (navIn.sig[i] >= 0))
                  gps->velSig[i] = ::pow(head.basePV, navIn.sig[i]);
            }
            break;
      }
      return true;
   }


   bool SP3NavDataFactory ::
   convertToClock(const SP3Header& head, const SP3Data& navIn, bool isC,
                  NavDataPtr& clkOut)
   {
      bool rv = true;
      OrbitDataSP3 *gps;
         // SP3 needs to merge multiple records, position and
         // velocity, so we only create new objects as needed.
      if (!clkOut)
      {
         clkOut = std::make_shared<OrbitDataSP3>();
            // Force the message type to clock because OrbitDataSP3
            // defaults to Ephemeris.
         clkOut->signal.messageType = NavMessageType::Clock;
      }
      gps = dynamic_cast<OrbitDataSP3*>(clkOut.get());
      switch (navIn.RecType)
      {
         case 'P':
            gps->timeStamp = navIn.time;
            gps->clkBias = navIn.clk;
            if (navIn.correlationFlag)
               gps->biasSig = navIn.sdev[3] * 1e-6;
            else if (isC && (navIn.sig[3] >= 0))
               gps->biasSig = ::pow(head.baseClk, navIn.sig[3]) * 1e-6;
            setSignal(navIn.sat, clkOut->signal);
            break;
         case 'V':
            gps->timeStamp = navIn.time;
            gps->clkDrift = navIn.clk * 1e-4;
            if (navIn.correlationFlag)
               gps->driftSig = navIn.sdev[3] * 1e-10;
            else if (isC && (navIn.sig[3] >= 0))
               gps->driftSig = ::pow(head.baseClk, navIn.sig[3]) * 1e-10;
            break;
      }
      return rv;
   }


   bool SP3NavDataFactory ::
   store(bool process, NavDataPtr& obj)
   {
      // cerr << __PRETTY_FUNCTION__ << endl;
         // only process if we have something to process.
      if (obj)
      {
         // cerr << "  store storing " << obj.get() << endl;
            // check the validity
         bool check = false;
         bool expect = false;
         switch (navValidity)
         {
            case NavValidityType::ValidOnly:
               check = true;
               expect = true;
               break;
            case NavValidityType::InvalidOnly:
               check = true;
               expect = false;
               break;
                  // Just treat everything else like All, which is to
                  // say, no checks.
            default:
               break;
         }
         if (check)
         {
            if (process)
            {
               if (obj->validate() == expect)
               {
                  if (!addNavData(obj))
                  {
                     // cerr << "  store failed to add nav data" << endl;
                     return false;
                  }
               }
            }
         }
         else
         {
            if (process)
            {
               if (!addNavData(obj))
               {
                  // cerr << "  store failed to add nav data" << endl;
                  return false;
               }
            }
         }
            // Clear the shared_ptr so the next time
            // convertToOrbit is called, it creates a new one.
         // cerr << "  store resetting obj ptr, use_count=" << obj.use_count() << endl;
         // NavData *ptr = obj.get();
         // cerr << "DUMP BEFORE:" << endl;
         // ptr->dump(cerr, DumpDetail::Full);
         obj.reset();
         // cerr << "DUMP AFTER:" << endl;
         // ptr->dump(cerr, DumpDetail::Full);
      }
      return true;
   }


      // This method is roughly equivalent to the deprecated
      // PositionSatStore::getValue().
   void SP3NavDataFactory ::
   interpolateEph(const NavMap::iterator& ti1, const NavMap::iterator& ti3,
                  const CommonTime& when, NavDataPtr& navData)
   {
      // cerr << "  start interpolating ephemeris, distance = " << std::distance(ti1,ti3) << endl;
      std::vector<double> tdata(2*halfOrderPos);
      std::vector<std::vector<double>> posData(3), posSigData(3), velData(3),
         velSigData(3), accData(3), accSigData(3);
      CommonTime firstTime(ti1->second->timeStamp);
         // This flag is only used to decide whether to compute sigmas
         // or use existing ones.  It is expected that for exact time
         // matches, navData will already have any sigma data filled
         // in.
      bool isExact = false;
      unsigned idx = 0;
         // posData etc are 2D arrays, where the first dimension
         // is positional, x=0,y=1,z=2 and the 2nd dimension is
         // the data index for the fit.
      for (unsigned i = 0; i < 3; i++)
      {
         posData[i].resize(2*halfOrderPos);
         posSigData[i].resize(2*halfOrderPos);
         velData[i].resize(2*halfOrderPos);
         velSigData[i].resize(2*halfOrderPos);
         accData[i].resize(2*halfOrderPos);
         accSigData[i].resize(2*halfOrderPos);
      }
      // cerr << "  resized" << endl;
      bool haveVel = false, haveAcc = false;
      NavMap::iterator ti2;
      for (ti2 = ti1, idx=0; ti2 != ti3; ++ti2, ++idx)
      {
         // cerr << "  idx=" << idx << endl;
         tdata[idx] = ti2->second->timeStamp - firstTime;
         if ((idx == halfOrderPos) && (ti2->second->timeStamp == when))
            isExact = true;
         OrbitDataSP3 *nav = dynamic_cast<OrbitDataSP3*>(
            ti2->second.get());
         // cerr << "  nav=" << nav << endl;
         // ti2->second->dump(cerr, DumpDetail::Full);
         for (unsigned i = 0; i < 3; i++)
         {
            // cerr << "  i=" << i << endl
            //      << posData.size() << " " << velData.size() << " "
            //      << accData.size() << endl
            //      << nav->pos.size() << " " << nav->vel.size() << " "
            //      << nav->acc.size() << endl;
            posData[i][idx] = nav->pos[i];
            velData[i][idx] = nav->vel[i];
            accData[i][idx] = nav->acc[i];
            posSigData[i][idx] = nav->posSig[i];
            velSigData[i][idx] = nav->velSig[i];
            accSigData[i][idx] = nav->accSig[i];
            haveVel |= (nav->vel[i] != 0.0);
            haveAcc |= (nav->acc[i] != 0.0);
         }
      }
      double dt = when - firstTime, err;
      OrbitDataSP3 *osp3 = dynamic_cast<OrbitDataSP3*>(navData.get());
      // cerr << printTime(when, "  when=%Y/%02m/%02d %02H:%02M:%02S")
      //      << endl
      //      << printTime(firstTime, "  firstTime=%Y/%02m/%02d %02H:%02M:%02S")
      //      << endl << setprecision(20) << "  dt=" << dt << endl;
      // for (unsigned i = 0; i < tdata.size(); i++)
      // {
      //    cerr << "  i=" << i << " times=" << tdata[i] << endl
      //         << "  P=" << posData[0][i] << " " << posData[1][i] << " "
      //         << posData[2][i] << endl
      //         << "  V=" << velData[0][i] << " " << velData[1][i] << " "
      //         << velData[2][i] << endl
      //         << "  A=" << accData[0][i] << " " << accData[1][i] << " "
      //         << accData[2][i] << endl;
      // }
      // cerr << "  haveVelocity=" << haveVel << "  haveAcceleration="
      //      << haveAcc << endl;
         // Interpolate XYZ position/velocity/acceleration.
      for (unsigned i = 0; i < 3; i++)
      {
         if (haveVel && haveAcc)
         {
            osp3->pos[i] = LagrangeInterpolation(tdata,posData[i],dt,err);
            osp3->vel[i] = LagrangeInterpolation(tdata,velData[i],dt,err);
            osp3->acc[i] = LagrangeInterpolation(tdata,accData[i],dt,err);
            unsigned Nhi = halfOrderPos, Nlow=halfOrderPos-1;
            // cerr << "!isExact sigP[" << i << "][" << Nhi << "] = " << posSigData[i][Nhi] << endl
            //      << "         sigP[" << i << "][" << Nlow << "] = " << posSigData[i][Nlow] << endl
            //      << "         sigV[" << i << "][" << Nhi << "] = " << velSigData[i][Nhi] << endl
            //      << "         sigV[" << i << "][" << Nlow << "] = " << velSigData[i][Nlow] << endl
            //      << "         sigA[" << i << "][" << Nhi << "] = " << accSigData[i][Nhi] << endl
            //      << "         sigA[" << i << "][" << Nlow << "] = " << accSigData[i][Nlow] << endl;
            if (!isExact)
            {
               osp3->posSig[i] = RSS(posSigData[i][halfOrderPos-1],
                                     posSigData[i][halfOrderPos]);
               osp3->velSig[i] = RSS(velSigData[i][halfOrderPos-1],
                                     velSigData[i][halfOrderPos]);
               osp3->accSig[i] = RSS(accSigData[i][halfOrderPos-1],
                                     accSigData[i][halfOrderPos]);
               // cerr << "1 RSS(posSigData[" << i << "][" << (halfOrderPos-1)
               //      << "],posSigData[" << i << "][" << halfOrderPos << "]) = "
               //      << osp3->posSig[i] << endl;
            }
         }
         else if (haveVel && !haveAcc)
         {
            osp3->pos[i] = LagrangeInterpolation(tdata,posData[i],dt,err);
            LagrangeInterpolation(tdata, velData[i], dt, osp3->vel[i],
                                  osp3->acc[i]);
            osp3->acc[i] *= 0.1;
            unsigned Nhi = halfOrderPos, Nlow=halfOrderPos-1;
            // cerr << "!isExact sigP[" << i << "][" << Nhi << "] = " << posSigData[i][Nhi] << endl
            //      << "         sigP[" << i << "][" << Nlow << "] = " << posSigData[i][Nlow] << endl
            //      << "         sigV[" << i << "][" << Nhi << "] = " << velSigData[i][Nhi] << endl
            //      << "         sigV[" << i << "][" << Nlow << "] = " << velSigData[i][Nlow] << endl
            //      << "         sigA[" << i << "][" << Nhi << "] = " << accSigData[i][Nhi] << endl
            //      << "         sigA[" << i << "][" << Nlow << "] = " << accSigData[i][Nlow] << endl;
            if (!isExact)
            {
               osp3->posSig[i] = RSS(posSigData[i][halfOrderPos-1],
                                     posSigData[i][halfOrderPos]);
               osp3->velSig[i] = RSS(velSigData[i][halfOrderPos-1],
                                     velSigData[i][halfOrderPos]);
            }
            // cerr << "2 RSS(posSigData[" << i << "][" << (halfOrderPos-1)
            //      << "],posSigData[" << i << "][" << halfOrderPos << "]) = "
            //      << osp3->posSig[i] << endl;
         }
         else
         {
               // have position, must derive velocity and acceleration
            LagrangeInterpolation(tdata, posData[i], dt, osp3->pos[i],
                                  osp3->vel[i]);
            osp3->vel[i] *= 10000.; // km/sec to dm/sec
               // PositionSatStore doesn't derive
               // acceleration in this case, near as I can
               // tell.
            if (!isExact)
            {
               osp3->posSig[i] = RSS(posSigData[i][halfOrderPos-1],
                                     posSigData[i][halfOrderPos]);
            }
            // cerr << "3 RSS(posSigData[" << i << "][" << (halfOrderPos-1)
            //      << "],posSigData[" << i << "][" << halfOrderPos << "]) = "
            //      << osp3->posSig[i] << endl;
         }
      } // for (unsigned i = 0; i < 3; i++)
      // for (unsigned i = 0; i < 3; i++)
      // {
      //    cerr << "  pos[" << i << "]=" << osp3->pos[i] << endl
      //         << "  vel[" << i << "]=" << osp3->vel[i] << endl
      //         << "  acc[" << i << "]=" << osp3->acc[i] << endl;
      // }
   }


   void SP3NavDataFactory ::
   interpolateClk(const NavMap::iterator& ti1, const NavMap::iterator& ti3,
                  const CommonTime& when, NavDataPtr& navData)
   {
      // cerr << "  start interpolating clock, distance = " << std::distance(ti1,ti3) << endl;
      unsigned Nhi = halfOrderClk, Nlow = halfOrderClk-1;
      std::vector<double> tdata(2*halfOrderClk),
         biasData(2*halfOrderClk), biasSigData(2*halfOrderClk),
         driftData(2*halfOrderClk), driftSigData(2*halfOrderClk),
         drRateData(2*halfOrderClk), drRateSigData(2*halfOrderClk);
      CommonTime firstTime(ti1->second->timeStamp);
         // This flag is only used to decide whether to compute sigmas
         // or use existing ones.  It is expected that for exact time
         // matches, navData will already have any sigma data filled
         // in.
      bool isExact = false;
      unsigned idx = 0;
      bool haveDrift = false, haveDriftRate = false;
      NavMap::iterator ti2;
      for (ti2 = ti1, idx=0; ti2 != ti3; ++ti2, ++idx)
      {
         // cerr << "  idx=" << idx << endl;
         tdata[idx] = ti2->second->timeStamp - firstTime;
         if ((idx == halfOrderClk) && (ti2->second->timeStamp == when))
            isExact = true;
         OrbitDataSP3 *nav = dynamic_cast<OrbitDataSP3*>(
            ti2->second.get());
         // cerr << "  nav=" << nav << endl;
         // ti2->second->dump(cerr, DumpDetail::Full);
         biasData[idx] = nav->clkBias;
         driftData[idx] = nav->clkDrift;
         drRateData[idx] = nav->clkDrRate;
         biasSigData[idx] = nav->biasSig;
         driftSigData[idx] = nav->driftSig;
         drRateSigData[idx] = nav->drRateSig;
         haveDrift |= (nav->clkDrift != 0.0);
         haveDriftRate |= (nav->clkDrRate != 0.0);
      }
      double dt = when - firstTime, err, slope,
         slopedt = tdata[Nhi]-tdata[Nlow];
      OrbitDataSP3 *osp3 = dynamic_cast<OrbitDataSP3*>(navData.get());
      // cerr << setprecision(20) << "  dt=" << dt << endl;
      gnsstk::InvalidRequest unkType(
         "Clock interpolation type " +
         StringUtils::asString(static_cast<int>(interpType)) +
         " is not supported");
      if (haveDrift)
      {
         switch (interpType)
         {
            case ClkInterpType::Lagrange:
               osp3->clkBias = LagrangeInterpolation(tdata,biasData,dt,err);
               osp3->clkDrift = LagrangeInterpolation(tdata,driftData,dt,err);
               break;
            case ClkInterpType::Linear:
               slope = (biasData[Nhi]-biasData[Nlow]) / slopedt;
               osp3->clkBias = biasData[Nlow] + slope*(dt-tdata[Nlow]);
               slope = (driftData[Nhi]-driftData[Nlow]) / slopedt;
               osp3->clkDrift = driftData[Nlow] + slope*(dt-tdata[Nlow]);
               break;
            default:
               GNSSTK_THROW(unkType);
               break;
         }
            // if isExact, we just use the already populated values.
         if (!isExact)
         {
            osp3->biasSig = RSS(biasSigData[Nlow], biasSigData[Nhi]);
            // cerr << " biasSig = " << osp3->biasSig << endl
            //      << " driftSig = " << osp3->driftSig << endl
            //      << " drRateSig = " << osp3->drRateSig << endl;
         }
         osp3->driftSig = RSS(driftSigData[Nlow], driftSigData[Nhi]);
      }
      else
      {
            // No drift, we have to derive it numerically
         switch (interpType)
         {
            case ClkInterpType::Lagrange:
               LagrangeInterpolation(tdata, biasData, dt, osp3->clkBias,
                                     osp3->clkDrift);
               break;
            case ClkInterpType::Linear:
               slope = (biasData[Nhi]-biasData[Nlow]) / slopedt;
               osp3->clkDrift = slope;
               osp3->clkBias = biasData[Nlow] + slope*(dt-tdata[Nlow]);
               break;
            default:
               GNSSTK_THROW(unkType);
               break;
         }
            // if isExact, we just use the already populated values.
         if (!isExact)
         {
            osp3->biasSig = RSS(biasSigData[Nlow], biasSigData[Nhi]);
            // cerr << " biasSig = " << osp3->biasSig << endl;
         }
            // linear interpolation of drift
            /** @todo this doesn't look right to me because it
             * seems like it should be
             * biasSigData[Nhi]-biasSigData[low] but this is how
             * it is in SP3EphemerisStore. */
         osp3->driftSig = osp3->biasSig / slopedt;
      }

      if (haveDriftRate)
      {
         switch (interpType)
         {
            case ClkInterpType::Lagrange:
               osp3->clkDrRate = LagrangeInterpolation(tdata,drRateData,dt,err);
               break;
            case ClkInterpType::Linear:
               slope = (drRateData[Nhi]-drRateData[Nlow]) / slopedt;
               osp3->clkDrRate = drRateData[Nlow] + slope*(dt-tdata[Nlow]);
               break;
            default:
               GNSSTK_THROW(unkType);
               break;
         }
            // if isExact, we just use the already populated values.
         if (!isExact)
         {
            osp3->drRateSig = RSS(drRateSigData[Nlow], drRateSigData[Nhi]);
         }
      }
      else if (haveDrift)
      {
            // must interpolate drift to get drift rate
         switch (interpType)
         {
            case ClkInterpType::Lagrange:
               LagrangeInterpolation(tdata,driftData,dt,err,osp3->clkDrRate);
               break;
            case ClkInterpType::Linear:
               osp3->clkDrRate = (driftData[Nhi]-driftData[Nlow]) / slopedt;
               break;
            default:
               GNSSTK_THROW(unkType);
               break;
         }
         osp3->drRateSig = osp3->driftSig / slopedt;
      }
   }


   bool SP3NavDataFactory ::
   setSignal(const SatID& sat, NavMessageID& signal)
   {
      bool rv = true;
      signal.sat = sat;
      signal.xmitSat = sat;
      signal.system = sat.system;
         // make our best guess.
      switch (sat.system)
      {
         case SatelliteSystem::GPS:
            signal.obs = oidGPS;
            signal.nav = ntGPS;
            break;
         case SatelliteSystem::Galileo:
            signal.obs = oidGalileo;
            signal.nav = ntGalileo;
            break;
         case SatelliteSystem::QZSS:
            signal.obs = oidQZSS;
            signal.nav = ntQZSS;
            break;
         case SatelliteSystem::Glonass:
            signal.obs = oidGLONASS;
            signal.nav = ntGLONASS;
            break;
         case SatelliteSystem::BeiDou:
            signal.obs = oidBeiDou;
            signal.nav = ntBeiDou;
            break;
         default:
               /// @todo add more systems as needed.
            signal.obs = ObsID(ObservationType::NavMsg,
                                       CarrierBand::Unknown,
                                       TrackingCode::Unknown);
            signal.nav = NavType::Unknown;
            rv = false;
            break;
      }
      return rv;
   }


   bool SP3NavDataFactory ::
   transNavMsgID(const NavMessageID& nmidIn, NavMessageID& nmidOut)
   {
      nmidOut = nmidIn; // copy all the original data first.
      return setSignal(nmidIn.sat, nmidOut);
   }


   void SP3NavDataFactory ::
   useRinexClockData(bool useRC)
   {
      if (useRC == !useSP3clock)
         return;
      useSP3clock = !useRC;
      clearClock();
   }


   void SP3NavDataFactory ::
   setClockInterpOrder(unsigned int order)
   {
      if (interpType == ClkInterpType::Lagrange)
         halfOrderClk = (order+1)/2;
      else
         halfOrderClk = 1;
   }


   void SP3NavDataFactory ::
   setClockLagrangeInterp()
   {
      interpType = ClkInterpType::Lagrange;
      halfOrderClk = 5;
   }


   void SP3NavDataFactory ::
   setClockLinearInterp()
   {
      interpType = ClkInterpType::Linear;
      halfOrderClk = 2;
   }


   double SP3NavDataFactory ::
   getPositionTimeStep(const SatID& sat) const
   {
      NavMessageID key(NavSatelliteID(sat), NavMessageType::Ephemeris);
      return nomTimeStep(key);
   }


   double SP3NavDataFactory ::
   getClockTimeStep(const SatID& sat) const
   {
      NavMessageID key(NavSatelliteID(sat), NavMessageType::Clock);
      return nomTimeStep(key);
   }


   double SP3NavDataFactory ::
   nomTimeStep(const NavMessageID& nmid) const
   {
      // cerr << __PRETTY_FUNCTION__ << "  nmid=" << nmid << endl;
      auto dataIt = data.find(nmid.messageType);
         // map delta time * 100 to a count
      std::map<long,unsigned long> stepCount;
         // reverse of stepCount
      std::map<unsigned long,long> countStep;
      if (dataIt == data.end())
      {
         // cerr << "  no data for nav message type" << endl;
         return false;
      }
         // To support wildcard signals, we need to do a linear search.
      for (const auto& sati : dataIt->second)
      {
         if (sati.first != nmid)
            continue; // skip non matches
         // cerr << "  found a match" << endl;
         auto ti1 = sati.second.begin();
         auto ti2 = std::next(ti1);
         while (ti2 != sati.second.end())
         {
            double diff = ti2->first - ti1->first;
            // cerr << "  diff=" << diff << endl;
            stepCount[(long)(diff*100)]++;
            ++ti1;
            ++ti2;
         }
      }
         // Remap stepCount to countStep, which puts the steps in
         // order of how common they are.  May result in overwrites,
         // but we don't really care.
      for (const auto& sci : stepCount)
      {
         countStep[sci.second] = sci.first;
      }
      // cerr << "countStep.empty()=" << countStep.empty() << endl;
      if (!countStep.empty())
      {
            // change the scale back to seconds.
         return countStep.begin()->second / 100.0;
      }
      return 0.0;
   }


   void SP3NavDataFactory ::
   dumpConfig(std::ostream& s) const
   {
         // Not sure why initialTime is being set to time system any
         // and final time is not, but that's how the original code in
         // TabularSatStore was.
      CommonTime initialTime(getInitialTime());
      CommonTime finalTime(getFinalTime());
      initialTime.setTimeSystem(TimeSystem::Any);
      static const std::string fmt(
         "%4F %w %10.3g %4Y/%02m/%02d %2H:%02M:%02S %P");
      s << "Dump SP3NavDataFactory:" << endl
        << (rejectBadPosFlag ? " Reject":" Do not reject")
        << " bad positions." << endl
        << (rejectBadClockFlag ? " Reject":" Do not reject")
        << " bad clocks." << endl
        << (rejectPredPosFlag ? " Reject":" Do not reject")
        << " predicted positions." << endl
        << (rejectPredClockFlag ? " Reject":" Do not reject")
        << " predicted clocks." << endl
        << "Position data:" << endl
        << " Interpolation is Lagrange, of order " << getPositionInterpOrder()
        << " (" << halfOrderPos << " points on each side)" << endl
        << "  Data stored for " << numSatellites() << " satellites" << endl
        << "  Time span of data: "
        << "  Initial time is " << printTime(initialTime,fmt) << endl;
      if ((initialTime == CommonTime::END_OF_TIME) ||
          (finalTime == CommonTime::BEGINNING_OF_TIME))
      {
         s << "(there are no time limits)" << endl;
      }
      else
      {
         s << " FROM " << printTime(initialTime,fmt) << " TO "
           << printTime(finalTime,fmt) << endl;
      }
         // The original TabularSatStore determined whether it had
         // position, velocity, clock bias and drift at load time, but
         // SP3NavDataFactory delays that determination until it's
         // ready to interpolate the data.  The reason for this is
         // that it's possible to load one file that has the data and
         // another that does not.  As such, we don't dump the flags
         // we don't have.
      s << "  Checking for data gaps? ";
      if (checkDataGapPos)
      {
         s << "yes; gap interval is " << fixed << setprecision(2)
           << gapIntervalPos;
      }
      else
      {
         s << "no";
      }
      s << endl << "  Checking data interval? ";
      if (checkIntervalPos)
      {
         s << "yes; max interval is " << fixed << setprecision(2)
           << maxIntervalPos;
      }
      else
      {
         s << "no";
      }
      s << endl
        << "Clock data:" << endl
        << " Interpolation is ";
      switch (interpType)
      {
         case ClkInterpType::Linear:
            s << "Linear." << endl;
            break;
         case ClkInterpType::Lagrange:
            s << "Lagrange, of order " << getClockInterpOrder() << " ("
              << halfOrderClk << " points on each side)" << endl;
            break;
         default:
            s << "???" << endl;
            break;
      }
      s << "  Checking for data gaps? ";
      if (checkDataGapClk)
      {
         s << "yes; gap interval is " << fixed << setprecision(2)
           << gapIntervalClk;
      }
      else
      {
         s << "no";
      }
      s << endl << "  Checking data interval? ";
      if (checkIntervalClk)
      {
         s << "yes; max interval is " << fixed << setprecision(2)
           << maxIntervalClk;
      }
      else
      {
         s << "no";
      }
      s << endl
        << "End dump SP3NavDataFactory." << endl;
   }

} // namespace gnsstk
