#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_Dout "../tv/cdatafile/c.uz_FOC_sample.autotvin_Dout.dat"
#define AUTOTB_TVOUT_Dout "../tv/cdatafile/c.uz_FOC_sample.autotvout_Dout.dat"
// wrapc file define:
#define AUTOTB_TVIN_self "../tv/cdatafile/c.uz_FOC_sample.autotvin_self.dat"
#define AUTOTB_TVOUT_self "../tv/cdatafile/c.uz_FOC_sample.autotvout_self.dat"
// wrapc file define:
#define AUTOTB_TVIN_i_reference_Ampere "../tv/cdatafile/c.uz_FOC_sample.autotvin_i_reference_Ampere.dat"
#define AUTOTB_TVOUT_i_reference_Ampere "../tv/cdatafile/c.uz_FOC_sample.autotvout_i_reference_Ampere.dat"
// wrapc file define:
#define AUTOTB_TVIN_i_actual_Ampere "../tv/cdatafile/c.uz_FOC_sample.autotvin_i_actual_Ampere.dat"
#define AUTOTB_TVOUT_i_actual_Ampere "../tv/cdatafile/c.uz_FOC_sample.autotvout_i_actual_Ampere.dat"
// wrapc file define:
#define AUTOTB_TVIN_V_dc_volts "../tv/cdatafile/c.uz_FOC_sample.autotvin_V_dc_volts.dat"
#define AUTOTB_TVOUT_V_dc_volts "../tv/cdatafile/c.uz_FOC_sample.autotvout_V_dc_volts.dat"
// wrapc file define:
#define AUTOTB_TVIN_omega_el_rad_per_sec "../tv/cdatafile/c.uz_FOC_sample.autotvin_omega_el_rad_per_sec.dat"
#define AUTOTB_TVOUT_omega_el_rad_per_sec "../tv/cdatafile/c.uz_FOC_sample.autotvout_omega_el_rad_per_sec.dat"
// wrapc file define:
#define AUTOTB_TVIN_u_output_Volts "../tv/cdatafile/c.uz_FOC_sample.autotvin_u_output_Volts.dat"
#define AUTOTB_TVOUT_u_output_Volts "../tv/cdatafile/c.uz_FOC_sample.autotvout_u_output_Volts.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_Dout "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_Dout.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_self "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_self.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_i_reference_Ampere "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_i_reference_Ampere.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_i_actual_Ampere "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_i_actual_Ampere.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_V_dc_volts "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_V_dc_volts.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_omega_el_rad_per_sec "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_omega_el_rad_per_sec.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_u_output_Volts "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_u_output_Volts.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  Dout_depth = 0;
  self_depth = 0;
  i_reference_Ampere_depth = 0;
  i_actual_Ampere_depth = 0;
  V_dc_volts_depth = 0;
  omega_el_rad_per_sec_depth = 0;
  u_output_Volts_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{Dout " << Dout_depth << "}\n";
  total_list << "{self " << self_depth << "}\n";
  total_list << "{i_reference_Ampere " << i_reference_Ampere_depth << "}\n";
  total_list << "{i_actual_Ampere " << i_actual_Ampere_depth << "}\n";
  total_list << "{V_dc_volts " << V_dc_volts_depth << "}\n";
  total_list << "{omega_el_rad_per_sec " << omega_el_rad_per_sec_depth << "}\n";
  total_list << "{u_output_Volts " << u_output_Volts_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
  public:
    int Dout_depth;
    int self_depth;
    int i_reference_Ampere_depth;
    int i_actual_Ampere_depth;
    int V_dc_volts_depth;
    int omega_el_rad_per_sec_depth;
    int u_output_Volts_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
struct __cosim_sC__ { char data[12]; };
struct __cosim_s1C__ { char data[28]; };
extern "C" void uz_FOC_sample_hw_stub(volatile void *, __cosim_sC__, __cosim_sC__, float, float, volatile void *);

extern "C" void apatb_uz_FOC_sample_hw(volatile void * __xlx_apatb_param_self, __cosim_sC__ __xlx_apatb_param_i_reference_Ampere, __cosim_sC__ __xlx_apatb_param_i_actual_Ampere, float __xlx_apatb_param_V_dc_volts, float __xlx_apatb_param_omega_el_rad_per_sec, volatile void * __xlx_apatb_param_u_output_Volts) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_Dout);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > Dout_pc_buffer(150);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "Dout");
  
            // push token into output port buffer
            if (AESL_token != "") {
              Dout_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {{
            int i = 0;
            for (int j = 0, e = 150; j < e; j += 1, ++i) {
            ((int*)__xlx_apatb_param_u_output_Volts)[j] = Dout_pc_buffer[i].to_int64();
          }}}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_self);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<224> > self_pc_buffer(3);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "self");
  
            // push token into output port buffer
            if (AESL_token != "") {
              self_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {{
            int i = 0;
            for (int j = 0, e = 3; j < e; j += 1, ++i) {((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+0] = self_pc_buffer[i].range(31,0).to_int64();
((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+1] = self_pc_buffer[i].range(63,32).to_int64();
((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+2] = self_pc_buffer[i].range(95,64).to_int64();
((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+3] = self_pc_buffer[i].range(127,96).to_int64();
((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+4] = self_pc_buffer[i].range(159,128).to_int64();
((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+5] = self_pc_buffer[i].range(191,160).to_int64();
((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+6] = self_pc_buffer[i].range(223,192).to_int64();
}}}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//Dout
aesl_fh.touch(AUTOTB_TVIN_Dout);
aesl_fh.touch(AUTOTB_TVOUT_Dout);
//self
aesl_fh.touch(AUTOTB_TVIN_self);
aesl_fh.touch(AUTOTB_TVOUT_self);
//i_reference_Ampere
aesl_fh.touch(AUTOTB_TVIN_i_reference_Ampere);
aesl_fh.touch(AUTOTB_TVOUT_i_reference_Ampere);
//i_actual_Ampere
aesl_fh.touch(AUTOTB_TVIN_i_actual_Ampere);
aesl_fh.touch(AUTOTB_TVOUT_i_actual_Ampere);
//V_dc_volts
aesl_fh.touch(AUTOTB_TVIN_V_dc_volts);
aesl_fh.touch(AUTOTB_TVOUT_V_dc_volts);
//omega_el_rad_per_sec
aesl_fh.touch(AUTOTB_TVIN_omega_el_rad_per_sec);
aesl_fh.touch(AUTOTB_TVOUT_omega_el_rad_per_sec);
//u_output_Volts
aesl_fh.touch(AUTOTB_TVIN_u_output_Volts);
aesl_fh.touch(AUTOTB_TVOUT_u_output_Volts);
CodeState = DUMP_INPUTS;
// print Dout Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_Dout, __xlx_sprintf_buffer.data());
  {  if (__xlx_apatb_param_u_output_Volts) {
    for (int j = 0, e = 150; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv = ((int*)__xlx_apatb_param_u_output_Volts)[j];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_Dout, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(150, &tcl_file.Dout_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_Dout, __xlx_sprintf_buffer.data());
}
// print self Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_self, __xlx_sprintf_buffer.data());
  {  if (__xlx_apatb_param_self) {
    for (int j = 0, e = 3; j != e; ++j) {
sc_bv<224> __xlx_tmp_lv;
__xlx_tmp_lv.range(31,0) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+0];
__xlx_tmp_lv.range(63,32) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+1];
__xlx_tmp_lv.range(95,64) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+2];
__xlx_tmp_lv.range(127,96) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+3];
__xlx_tmp_lv.range(159,128) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+4];
__xlx_tmp_lv.range(191,160) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+5];
__xlx_tmp_lv.range(223,192) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+6];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_self, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(3, &tcl_file.self_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_self, __xlx_sprintf_buffer.data());
}
// print i_reference_Ampere Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_i_reference_Ampere, __xlx_sprintf_buffer.data());
  {
    sc_bv<96> __xlx_tmp_lv;__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_i_reference_Ampere)[0*1+0];
__xlx_tmp_lv.range(95,64) = ((long long*)&__xlx_apatb_param_i_reference_Ampere)[0*1+1];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_i_reference_Ampere, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.i_reference_Ampere_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_i_reference_Ampere, __xlx_sprintf_buffer.data());
}
// print i_actual_Ampere Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_i_actual_Ampere, __xlx_sprintf_buffer.data());
  {
    sc_bv<96> __xlx_tmp_lv;__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_i_actual_Ampere)[0*1+0];
__xlx_tmp_lv.range(95,64) = ((long long*)&__xlx_apatb_param_i_actual_Ampere)[0*1+1];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_i_actual_Ampere, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.i_actual_Ampere_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_i_actual_Ampere, __xlx_sprintf_buffer.data());
}
// print V_dc_volts Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_V_dc_volts, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_V_dc_volts);
    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_V_dc_volts, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.V_dc_volts_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_V_dc_volts, __xlx_sprintf_buffer.data());
}
// print omega_el_rad_per_sec Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_omega_el_rad_per_sec, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_omega_el_rad_per_sec);
    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_omega_el_rad_per_sec, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.omega_el_rad_per_sec_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_omega_el_rad_per_sec, __xlx_sprintf_buffer.data());
}
// print u_output_Volts Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_u_output_Volts, __xlx_sprintf_buffer.data());
  {
    sc_bv<64> __xlx_tmp_lv;
    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_u_output_Volts, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.u_output_Volts_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_u_output_Volts, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
uz_FOC_sample_hw_stub(__xlx_apatb_param_self, __xlx_apatb_param_i_reference_Ampere, __xlx_apatb_param_i_actual_Ampere, __xlx_apatb_param_V_dc_volts, __xlx_apatb_param_omega_el_rad_per_sec, __xlx_apatb_param_u_output_Volts);
CodeState = DUMP_OUTPUTS;
// print Dout Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_Dout, __xlx_sprintf_buffer.data());
  {  if (__xlx_apatb_param_u_output_Volts) {
    for (int j = 0, e = 150; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv = ((int*)__xlx_apatb_param_u_output_Volts)[j];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_Dout, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(150, &tcl_file.Dout_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_Dout, __xlx_sprintf_buffer.data());
}
// print self Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_self, __xlx_sprintf_buffer.data());
  {  if (__xlx_apatb_param_self) {
    for (int j = 0, e = 3; j != e; ++j) {
sc_bv<224> __xlx_tmp_lv;
__xlx_tmp_lv.range(31,0) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+0];
__xlx_tmp_lv.range(63,32) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+1];
__xlx_tmp_lv.range(95,64) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+2];
__xlx_tmp_lv.range(127,96) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+3];
__xlx_tmp_lv.range(159,128) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+4];
__xlx_tmp_lv.range(191,160) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+5];
__xlx_tmp_lv.range(223,192) = ((int*)(((__cosim_s1C__*)__xlx_apatb_param_self) + j))[0*7+6];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_self, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(3, &tcl_file.self_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_self, __xlx_sprintf_buffer.data());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
