#ifndef UZ_ADCLTC2311_H
#define UZ_ADCLTC2311_H

// defines
#define UZ_ADCLTC2311_CH1 (1<<0)
#define UZ_ADCLTC2311_CH2 (1<<1)
#define UZ_ADCLTC2311_CH3 (1<<2)
#define UZ_ADCLTC2311_CH4 (1<<3)
#define UZ_ADCLTC2311_CH5 (1<<4)
#define UZ_ADCLTC2311_CH6 (1<<5)
#define UZ_ADCLTC2311_CH7 (1<<6)
#define UZ_ADCLTC2311_CH8 (1<<7)

#define UZ_ADCLTC2311_MASTER1 (1<<0)
#define UZ_ADCLTC2311_MASTER2 (1<<1)

// typedefs
typedef struct uz_adcLtc2311 uz_adcLtc2311;

// function declarations
uz_adcLtc2311* uz_adcLtc2311_init(uz_adcLtc2311* self);

#endif // UZ_ADCLTC2311_H
