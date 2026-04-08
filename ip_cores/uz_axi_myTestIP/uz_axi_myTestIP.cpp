#include <stdint.h>

void uz_axi_myTestIP(int32_t a, int32_t b, int32_t *result) {

   #pragma HLS INTERFACE ap_ctrl_none port=return
   #pragma HLS INTERFACE s_axilite port=a bundle=control
   #pragma HLS INTERFACE s_axilite port=b bundle=control
   #pragma HLS INTERFACE s_axilite port=result bundle=control

   *result = a * b;
}
