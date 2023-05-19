#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
extern "C" void uz_VSD_6ph_asym(int*, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);
extern "C" void apatb_uz_VSD_6ph_asym_hw(volatile void * __xlx_apatb_param_in, volatile void * __xlx_apatb_param_out_1, volatile void * __xlx_apatb_param_out_2, volatile void * __xlx_apatb_param_out_3, volatile void * __xlx_apatb_param_out_4, volatile void * __xlx_apatb_param_out_5, volatile void * __xlx_apatb_param_out_6) {
  // Collect __xlx_in__tmp_vec
  vector<sc_bv<32> >__xlx_in__tmp_vec;
  for (int j = 0, e = 6; j != e; ++j) {
    __xlx_in__tmp_vec.push_back(((int*)__xlx_apatb_param_in)[j]);
  }
  int __xlx_size_param_in = 6;
  int __xlx_offset_param_in = 0;
  int __xlx_offset_byte_param_in = 0*4;
  int* __xlx_in__input_buffer= new int[__xlx_in__tmp_vec.size()];
  for (int i = 0; i < __xlx_in__tmp_vec.size(); ++i) {
    __xlx_in__input_buffer[i] = __xlx_in__tmp_vec[i].range(31, 0).to_uint64();
  }
  // DUT call
  uz_VSD_6ph_asym(__xlx_in__input_buffer, __xlx_apatb_param_out_1, __xlx_apatb_param_out_2, __xlx_apatb_param_out_3, __xlx_apatb_param_out_4, __xlx_apatb_param_out_5, __xlx_apatb_param_out_6);
// print __xlx_apatb_param_in
  sc_bv<32>*__xlx_in_output_buffer = new sc_bv<32>[__xlx_size_param_in];
  for (int i = 0; i < __xlx_size_param_in; ++i) {
    __xlx_in_output_buffer[i] = __xlx_in__input_buffer[i+__xlx_offset_param_in];
  }
  for (int i = 0; i < __xlx_size_param_in; ++i) {
    ((int*)__xlx_apatb_param_in)[i] = __xlx_in_output_buffer[i].to_uint64();
  }
}
