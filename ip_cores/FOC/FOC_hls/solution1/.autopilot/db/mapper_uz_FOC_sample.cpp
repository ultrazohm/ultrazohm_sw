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
struct __cosim_sC__ { char data[12]; };
struct __cosim_s24__ { char data[36]; };
struct __cosim_s14__ { char data[20]; };
extern "C" void uz_FOC_sample(int*, __cosim_s24__*, volatile void *, volatile void *, __cosim_sC__*, __cosim_sC__*, float, float, int, int);
extern "C" void apatb_uz_FOC_sample_hw(volatile void * __xlx_apatb_param_self, volatile void * __xlx_apatb_param_Controller_id, volatile void * __xlx_apatb_param_Controller_iq, __cosim_sC__ __xlx_apatb_param_i_reference_Ampere, __cosim_sC__ __xlx_apatb_param_i_actual_Ampere, float __xlx_apatb_param_V_dc_volts, float __xlx_apatb_param_omega_el_rad_per_sec, volatile void * __xlx_apatb_param_output_volts_d, volatile void * __xlx_apatb_param_output_volts_q) {
  // Collect __xlx_output_volts_d_output_volts_q__tmp_vec
  vector<sc_bv<32> >__xlx_output_volts_d_output_volts_q__tmp_vec;
  for (int j = 0, e = 50; j != e; ++j) {
    __xlx_output_volts_d_output_volts_q__tmp_vec.push_back(((int*)__xlx_apatb_param_output_volts_d)[j]);
  }
  int __xlx_size_param_output_volts_d = 50;
  int __xlx_offset_param_output_volts_d = 0;
  int __xlx_offset_byte_param_output_volts_d = 0*4;
  for (int j = 0, e = 50; j != e; ++j) {
    __xlx_output_volts_d_output_volts_q__tmp_vec.push_back(((int*)__xlx_apatb_param_output_volts_q)[j]);
  }
  int __xlx_size_param_output_volts_q = 50;
  int __xlx_offset_param_output_volts_q = 50;
  int __xlx_offset_byte_param_output_volts_q = 50*4;
  int* __xlx_output_volts_d_output_volts_q__input_buffer= new int[__xlx_output_volts_d_output_volts_q__tmp_vec.size()];
  for (int i = 0; i < __xlx_output_volts_d_output_volts_q__tmp_vec.size(); ++i) {
    __xlx_output_volts_d_output_volts_q__input_buffer[i] = __xlx_output_volts_d_output_volts_q__tmp_vec[i].range(31, 0).to_uint64();
  }
  // Collect __xlx_self__tmp_vec
  vector<sc_bv<288> >__xlx_self__tmp_vec;
  for (int j = 0, e = 1; j != e; ++j) {
    sc_bv<288> _xlx_tmp_sc;
    _xlx_tmp_sc.range(63, 0) = ((long long*)__xlx_apatb_param_self)[j*5+0];
    _xlx_tmp_sc.range(127, 64) = ((long long*)__xlx_apatb_param_self)[j*5+1];
    _xlx_tmp_sc.range(191, 128) = ((long long*)__xlx_apatb_param_self)[j*5+2];
    _xlx_tmp_sc.range(255, 192) = ((long long*)__xlx_apatb_param_self)[j*5+3];
    _xlx_tmp_sc.range(287, 256) = ((long long*)__xlx_apatb_param_self)[j*5+4];
    __xlx_self__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_self = 1;
  int __xlx_offset_param_self = 0;
  int __xlx_offset_byte_param_self = 0*36;
  __cosim_s24__* __xlx_self__input_buffer= new __cosim_s24__[__xlx_self__tmp_vec.size()];
  for (int i = 0; i < __xlx_self__tmp_vec.size(); ++i) {
    ((long long*)__xlx_self__input_buffer)[i*5+0] = __xlx_self__tmp_vec[i].range(63, 0).to_uint64();
    ((long long*)__xlx_self__input_buffer)[i*5+1] = __xlx_self__tmp_vec[i].range(127, 64).to_uint64();
    ((long long*)__xlx_self__input_buffer)[i*5+2] = __xlx_self__tmp_vec[i].range(191, 128).to_uint64();
    ((long long*)__xlx_self__input_buffer)[i*5+3] = __xlx_self__tmp_vec[i].range(255, 192).to_uint64();
    ((long long*)__xlx_self__input_buffer)[i*5+4] = __xlx_self__tmp_vec[i].range(287, 256).to_uint64();
  }
  // DUT call
  uz_FOC_sample(__xlx_output_volts_d_output_volts_q__input_buffer, __xlx_self__input_buffer, __xlx_apatb_param_Controller_id, __xlx_apatb_param_Controller_iq, &__xlx_apatb_param_i_reference_Ampere, &__xlx_apatb_param_i_actual_Ampere, __xlx_apatb_param_V_dc_volts, __xlx_apatb_param_omega_el_rad_per_sec, __xlx_offset_byte_param_output_volts_d, __xlx_offset_byte_param_output_volts_q);
// print __xlx_apatb_param_output_volts_d
  sc_bv<32>*__xlx_output_volts_d_output_buffer = new sc_bv<32>[__xlx_size_param_output_volts_d];
  for (int i = 0; i < __xlx_size_param_output_volts_d; ++i) {
    __xlx_output_volts_d_output_buffer[i] = __xlx_output_volts_d_output_volts_q__input_buffer[i+__xlx_offset_param_output_volts_d];
  }
  for (int i = 0; i < __xlx_size_param_output_volts_d; ++i) {
    ((int*)__xlx_apatb_param_output_volts_d)[i] = __xlx_output_volts_d_output_buffer[i].to_uint64();
  }
// print __xlx_apatb_param_output_volts_q
  sc_bv<32>*__xlx_output_volts_q_output_buffer = new sc_bv<32>[__xlx_size_param_output_volts_q];
  for (int i = 0; i < __xlx_size_param_output_volts_q; ++i) {
    __xlx_output_volts_q_output_buffer[i] = __xlx_output_volts_d_output_volts_q__input_buffer[i+__xlx_offset_param_output_volts_q];
  }
  for (int i = 0; i < __xlx_size_param_output_volts_q; ++i) {
    ((int*)__xlx_apatb_param_output_volts_q)[i] = __xlx_output_volts_q_output_buffer[i].to_uint64();
  }
// print __xlx_apatb_param_self
  sc_bv<288>*__xlx_self_output_buffer = new sc_bv<288>[__xlx_size_param_self];
  for (int i = 0; i < __xlx_size_param_self; ++i) {
    char* start = (char*)(&(__xlx_self__input_buffer[__xlx_offset_param_self]));
    __xlx_self_output_buffer[i].range(63, 0) = ((long long*)start)[i*5+0];
    __xlx_self_output_buffer[i].range(127, 64) = ((long long*)start)[i*5+1];
    __xlx_self_output_buffer[i].range(191, 128) = ((long long*)start)[i*5+2];
    __xlx_self_output_buffer[i].range(255, 192) = ((long long*)start)[i*5+3];
    __xlx_self_output_buffer[i].range(287, 256) = ((long long*)start)[i*5+4];
  }
  for (int i = 0; i < __xlx_size_param_self; ++i) {
    ((long long*)__xlx_apatb_param_self)[i*5+0] = __xlx_self_output_buffer[i].range(63, 0).to_uint64();
    ((long long*)__xlx_apatb_param_self)[i*5+1] = __xlx_self_output_buffer[i].range(127, 64).to_uint64();
    ((long long*)__xlx_apatb_param_self)[i*5+2] = __xlx_self_output_buffer[i].range(191, 128).to_uint64();
    ((long long*)__xlx_apatb_param_self)[i*5+3] = __xlx_self_output_buffer[i].range(255, 192).to_uint64();
    ((long long*)__xlx_apatb_param_self)[i*5+4] = __xlx_self_output_buffer[i].range(287, 256).to_uint64();
  }
}
