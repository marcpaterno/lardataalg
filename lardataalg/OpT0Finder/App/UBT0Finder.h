/**
 * \file UBT0Finder.h
 *
 * \ingroup App
 * 
 * \brief Class def header for a class UBT0Finder
 *
 * @author kazuhiro
 */

/** \addtogroup App

    @{*/

#ifndef LARLITE_UBT0FINDER_H
#define LARLITE_UBT0FINDER_H

#include "Analysis/ana_base.h"
#include "MCQCluster.h"
#include "lardataalg/OpT0Finder/Base/FlashMatchManager.h"
#include "larcorealg/Geometry/GeometryCore.h"
#include <TTree.h>
#include <TH2D.h>

namespace larlite {
  /**
     \class UBT0Finder
     User custom analysis class made by SHELL_USER_NAME
   */
  class UBT0Finder : public ana_base{
  
  public:

    UBT0Finder();

    /// Default destructor
    virtual ~UBT0Finder(){_use_mc=false;}

    /** IMPLEMENT in UBT0Finder.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in UBT0Finder.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in UBT0Finder.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

    ::flashana::FlashMatchManager& Manager() { return _mgr;}

    void UseMC(bool doit=true) { _use_mc = doit; }

    void SetROStart(double t) { _RO_start = t; }
    void SetROEnd(double t)   { _RO_end = t; }

    void SetTrigTime(double t) { _Trig_time = t; }

    void SetEDiff(double e) { _e_diff = e ; }

    void UseAbsolutePE(bool tof) { _useAbsPE = tof ; }

    void SetStepLength(double step){ _step_len = step ; }

    void UseLightPathWithMC (bool yesOrNo ){ _use_light_path_w_mc = yesOrNo ; } 

    void UseBNBCorrectnessWindow (bool yesOrNo){ _use_bnb_correctness_window = yesOrNo; }

    void PassGeometry(const ::geo::GeometryCore &PassedGeom) { LArSoftgeom = &PassedGeom; }

    void PassDetectorProp(const ::detinfo::DetectorProperties &PassedDetProp) { detprop = &PassedDetProp; }

  protected:

    ::flashana::FlashMatchManager _mgr;
    ::flashana::MCQCluster _mcqclustering;

    // Geometry Information
    const ::geo::GeometryCore *LArSoftgeom;
    const ::detinfo::DetectorProperties *detprop;

    //Switch -- if set to true, Light path will be used with mctrack
    bool _use_light_path_w_mc;

    // readout start : 
    // time before the trigger when the RO start
    double _RO_start; // us
    // readout end :
    // time after the trigger when the RO ends
    double _RO_end; // us
    // trigger time
    // the time at which, within the TPC readout
    // the trigger should arrive
    // for MC this is generally 0
    double _Trig_time; // us

    // Configurable params
    bool _use_mc;
    bool _useAbsPE ;
    double _step_len ;
    double _e_diff ; //Energy difference cut between start and end of track.  

    TTree* _int_tree;
    double _t0 ;
    double _n_pe ;
    double _int_e ;
    double _n_flash ;

    TTree* _track_tree;
    double _trk_time;
    double _trk_shift;
    double _trk_max_x;
    double _trk_min_x;
    double _trk_x;
    
    TTree* _flashmatch_tree;
    double _npe;
    double _npts;
    double _flash_x;
    double _flash_y;
    double _flash_z;
    double _tpc_x;
    double _tpc_y;
    double _tpc_z;
    double _score;
    double _flash_time;
    double _mc_time;
    double _mc_x;
    double _mc_y;
    double _mc_z;
    double _mc_dx;

    // tree to measure efficiency of matching for MCTracks
    TTree *_eff_tree;
    TTree *_flash_tree;
    int _matched;
    double _mc_edep;
    double _trk_max_abs_x, _trk_min_abs_x;

    TH2D * _nflash_v_nint ;
    TH1D * _time_diff ;
    int _n_bins ;
    int _max_time ;

    int _use_bnb_correctness_window ;

  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
