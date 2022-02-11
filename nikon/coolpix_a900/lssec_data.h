#ifndef _LSSEC_DATA_H_
#define _LSSEC_DATA_H_

#include <stdint.h>

// DATA XREF:
// sub_8C0+0x81
// sub_8C0+0x0206
extern char byte_3180[4096+128];

// DATA XREF:
// LsSec2ndStage+0x73
// LsSec4thStage+0x38
extern uint32_t byte_4200[16];

// DATA XREF:
// sub_1620+0xAB
extern char byte_4240[4096];

// DATA XREF:
// sub_1620+0x99
extern char byte_5240[72];

extern char version[];

#endif /* !_LSSEC_DATA_H_ */
