// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of a
//        bit 31~0 - a[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of b
//        bit 31~0 - b[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of result
//        bit 31~0 - result[31:0] (Read)
// 0x24 : Control signal of result
//        bit 0  - result_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONTROL_ADDR_A_DATA      0x10
#define CONTROL_BITS_A_DATA      32
#define CONTROL_ADDR_B_DATA      0x18
#define CONTROL_BITS_B_DATA      32
#define CONTROL_ADDR_RESULT_DATA 0x20
#define CONTROL_BITS_RESULT_DATA 32
#define CONTROL_ADDR_RESULT_CTRL 0x24
