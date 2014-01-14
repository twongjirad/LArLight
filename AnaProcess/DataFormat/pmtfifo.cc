#ifndef PMTFIFO_CC
#define PMTFIFO_CC

#include "pmtfifo.hh"

namespace larlight {

  void pmtfifo::clear_data(){
    data_base::clear_data();
    init_vars();
  }
  
  void pmtfifo::init_vars(){
    clear();
    _channel_number=FEM::INVALID_CH;
    _channel_frame_id=FEM::INVALID_WORD;
    _disc_id=FEM::DISC_MAX;
    _timeslice=FEM::INVALID_WORD;
  }
  
  void event_pmtfifo::clear_data(){
    data_base::clear_data();
    init_vars();
  }
  
  void event_pmtfifo::init_vars(){
    clear();
    _event_frame_id=FEM::INVALID_WORD;
    _module_address=FEM::INVALID_WORD;
    _module_id=FEM::INVALID_WORD;
    _channel_header_count=FEM::INVALID_WORD;
    _checksum=FEM::INVALID_WORD;
    _nwords=FEM::INVALID_WORD;
    _trigger_frame_id=FEM::INVALID_WORD;
    _trigger_timeslice=FEM::INVALID_WORD;
  }

}
#endif
