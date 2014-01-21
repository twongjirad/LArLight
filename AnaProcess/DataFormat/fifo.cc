#ifndef FIFO_CC
#define FIFO_CC

#include "fifo.hh"

namespace larlight {

  fifo::fifo(DATA::DATA_TYPE type) : std::vector<UShort_t>(),
				     data_base(type)
  {
    clear_data();
  }

  void fifo::clear_data(){
    data_base::clear_data();
    clear();
    init_vars();
  }
  
  void fifo::init_vars(){
    _channel_number=FEM::INVALID_CH;
    _readout_frame_number=FEM::INVALID_WORD;
    _readout_sample_number=FEM::INVALID_WORD;
    _disc_id=FEM::DISC_MAX;
  }

  ////////////////////////////////////////////////////////

  event_fifo::event_fifo(DATA::DATA_TYPE type) : std::vector<larlight::fifo>(), data_base(type)
  { 
    clear_data();
  }
  
  void event_fifo::clear_data(){
    data_base::clear_data();
    clear();
    init_vars();
  }
  
  void event_fifo::init_vars(){
    _event_frame_number=FEM::INVALID_WORD;
    _module_address=FEM::INVALID_WORD;
    _module_id=FEM::INVALID_WORD;
    _checksum=FEM::INVALID_WORD;
    _nwords=FEM::INVALID_WORD;
    _fem_trig_frame_number=FEM::INVALID_WORD;
    _fem_trig_sample_number=FEM::INVALID_WORD;
  }

}
#endif
