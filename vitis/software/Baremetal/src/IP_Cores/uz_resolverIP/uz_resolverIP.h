#ifndef UZ_RESOLVERIP_H
#define UZ_RESOLVERIP_H
/*********************
 *
 * Includes
 *
 *********************/
#include <stdint.h>
#include <stdbool.h>

/*********************
 *
 * TypeDefs
 *
 *********************/

/**
 * @brief Data type for object resolverIP
 *
 */
typedef struct uz_resolverIP_t uz_resolverIP_t;

/**
 * @brief Configuration struct for resolverIP
 *
 */
struct uz_resolverIP_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core, tested for 100MHz*/
    uint32_t resolution; /**< Resolution setting of AD2S1210. Determined by RES pins, tested for 16bit */
    float freq_clockin; /**< External Clock of AD2S1210. Determined by Crystal Frequency, tested for 8.192MHz */
    float zero_position_mechanical; /**< Mechanical zero position*/
    float pole_pairs_machine; /**< Number of machine pole pairs (for conversion from mechanical to electrical position/velocity)*/
    float pole_pairs_resolver; /**< Number of resolver pole pairs (for conversion of measured to  mechanical velocity)*/
    uint32_t mode_after_init; /**< IP-Core operating mode after init. See enum uz_resolverIP_mode for possible options*/
};

/**
 * @brief struct for returning both position and velocity (in float)
 *
 */

struct uz_resolverIP_position_velocity_t{
  float position;
  float velocity;
};



/**
 * @brief Mode enum for resolverIP
 *
 */
typedef enum
{
  POSITION_MODE,/**< Position Mode of AD2S1210 */
	VELOCITY_MODE,/**< Velocity Mode of AD2S1210 */
	CONFIG_MODE,/**< Config Mode of AD2S1210 */
	POSITION_VELOCITY_MODE/**< Custom Mode for readout of both position and velocity with one trigger*/
} uz_resolverIP_mode;



/*********************
 *
 * LowLevelFunctions
 *
 *********************/

/**
 * @brief Initializes an instance of the resolverIP driver and sets it into Config Mode
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_resolverIP_t* uz_resolverIP_init(struct uz_resolverIP_config_t config);

/**
 * @brief Sets ResolverIP in Config Mode for Register Read/Write Operations
 *
 * @param self instance of uz_resolverIP_t
 */
void uz_resolverIP_setConfigMode(uz_resolverIP_t* self);


/**
 * @brief Sets ResolverIP in Velocity Mode
 *
 * @param self instance of uz_resolverIP_t
 */
void uz_resolverIP_setDataModeVelocity(uz_resolverIP_t* self);

/**
 * @brief Sets ResolverIP in Position Mode
 *
 * @param self instance of uz_resolverIP_t
 */
void uz_resolverIP_setDataModePosition(uz_resolverIP_t* self);

/**
 * @brief Sets ResolverIP in Position and Velocity Mode
 *
 * @param self instance of uz_resolverIP_t
 */
void uz_resolverIP_setDataModePositionVelocity(uz_resolverIP_t* self);


/**
 * @brief Sets Zero Position, mechanical and electrical position values are offset by this value
 *
 * @param self instance of uz_resolverIP_t
 * @param zero_pos zero position, mechanical position between 0 and 2 * PI, this value is subtracted from original value in readMechanicalPosition
 */
void uz_resolverIP_setZeroPosition(uz_resolverIP_t* self, float zero_pos);

/**
 * @brief Returns number of machine pole pairs
 *
 * @param self instance of uz_resolverIP_t
 * @return pole_Pairs, number of machine pole pairs
 */
float uz_resolverIP_getMachinePolePairs(uz_resolverIP_t* self);

/**
 * @brief Sets number of machine pole pairs
 *
 * @param self instance of uz_resolverIP_t
 * @param pole_Pairs number of machine pole pairs
 */
void uz_resolverIP_setMachinePolePairs(uz_resolverIP_t* self, float pole_Pairs);

/**
 * @brief Returns number of resolver pole pairs in  config struct,  measured velocities will be divided by this factor
 *
 * @param self instance of uz_resolverIP_t
 * @return pole_Pairs, number of resolver pole pairs
 */
float uz_resolverIP_getResolverPolePairs(uz_resolverIP_t* self);

/**
 * @brief Sets number of resolver pole pairs in config struct, measured velocities will be divided by this factor
 *
 * @param self instance of uz_resolverIP_t
 * @param pole_Pairs number of resolver pole pairs
 */
void uz_resolverIP_setResolverPolePairs(uz_resolverIP_t* self, float pole_Pairs);


/**
 * @brief Reads Resolver Electrical Velocity, returns after SPI Communication is done and value is read in via AXI. External trigger connected to IPCore is neccessary
 *
 * @param self instance of uz_resolverIP_t
 *
 *  @return Float Electrical Velocity Data in rad per second
 */
float uz_resolverIP_readElectricalVelocity(uz_resolverIP_t* self);

/**
 * @brief  Reads Resolver Mechanical Velocity, returns after SPI Communication is done and value is read in via AXI. External trigger connected to IPCore is neccessary
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return Float Mechanical Velocity Data in rad per second
 */
float uz_resolverIP_readMechanicalVelocity(uz_resolverIP_t* self);

/**
 * @brief Reads Resolver Electrical Position, returns after SPI Communication is done and value is read in via AXI. External trigger connected to IPCore is neccessary
 *
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return Float Electrical Position Data in range 0 .. 2*PI
 */
float uz_resolverIP_readElectricalPosition(uz_resolverIP_t* self);

/**
 * @brief Reads Resolver Mechanical Position, returns after SPI Communication is done and value is read in via AXI. External trigger connected to IPCore is neccessary
 *
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return Float Mechanial Position Data in range 0 .. 2*PI
 */
float uz_resolverIP_readMechanicalPosition(uz_resolverIP_t* self);


/**
 * @brief Reads Resolver Mechanical Position and Velocity, returns after SPI Communication is done and value is read in via AXI. External trigger connected to IPCore is neccessary
 *
 * @param self instance of uz_resolverIP_t
 * 
 * @return Struct of type uz_resolverIP_position_velocity_t with float members for mechanical position (0..2*PI) and velocity in rad per second
 */
struct uz_resolverIP_position_velocity_t uz_resolverIP_readMechanicalPositionAndVelocity(uz_resolverIP_t* self);

/**
  * @brief Reads Resolver Electrical Position and Velocity, returns after SPI Communication is done and value is read in via AXI. External trigger connected to IPCore is neccessary
 *
 * @param self instance of uz_resolverIP_t
 * 
 * @return Struct of type uz_resolverIP_position_velocity_t with float members for electrical position (0..2*PI) and velocity in rad per second
 */
struct uz_resolverIP_position_velocity_t uz_resolverIP_readElectricalPositionAndVelocity(uz_resolverIP_t* self);



/*********************
 *
 * High Level Register Read/Write Functions
 *
 *********************/
/**
 * @brief Reads Resolver Register
 *
 * @param self instance of uz_resolverIP_t
 * @param addr Register address (see Datasheet)
 *
 *  @return int32_t Read Register Data
 */
int32_t uz_resolverIP_readRegister(uz_resolverIP_t* self, int32_t addr);

/**
 * @brief Writes Resolver Register
 *
 * @param self instance of uz_resolverIP_t
 * @param addr Register address
 * @param val Register write value
 */
void uz_resolverIP_writeRegister(uz_resolverIP_t* self, int32_t addr, int32_t val);

/**
 * @brief Sets Loss Of Signal Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The LOS threshold register determines the loss of signal threshold
 * of the AD2S1210. The AD2S1210 allows the user to set the LOS
 * threshold to a value between 0 V and 4.82 V. The resolution of
 * the LOS threshold is seven bits, that is, 38 mV. Note that the MSB,
 * D7, should be set to 0. The default value of the LOS threshold
 * on power-up is 2.2 V.
 *
 * @param self instance of uz_resolverIP_t
 * @param thresh Loss Of Signal Threshold of AD2S1210 in Volts. Valid threshold values are in the range [0V, 4.82V]
 */
void uz_resolverIP_setLOSThresh(uz_resolverIP_t* self, float thresh);

/**
 * @brief Returns Loss Of Signal Threshold of AD2S1210 in Volts.
 * From AD2S1210 Datasheet:
 * The LOS threshold register determines the loss of signal threshold
 * of the AD2S1210. The AD2S1210 allows the user to set the LOS
 * threshold to a value between 0 V and 4.82 V. The resolution of
 * the LOS threshold is seven bits, that is, 38 mV. Note that the MSB,
 * D7, should be set to 0. The default value of the LOS threshold
 * on power-up is 2.2 V.
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Loss Of Signal Threshold of AD2S1210 in Volts
 *
 */
float uz_resolverIP_getLOSThresh(uz_resolverIP_t* self);

/**
 * @brief Sets Degradation Of Signal Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The DOS overrange threshold register determines the degradation
 * of signal threshold of the AD2S1210. The AD2S1210 allows the
 * user to set the DOS overrange threshold to a value between 0 V
 * and 4.82 V. The resolution of the DOS overrange threshold is
 * 7 bits, that is, 38 mV. The MSB, D7, must be set to 0. The default
 * value of the DOS overrange threshold on power-up is 4.1 V.
 *
 * @param self instance of uz_resolverIP_t
 * @param thresh Degradation Of Signal Threshold of AD2S1210 in Volts. Valid threshold values are in the range [0V, 4.82V]
 */
void uz_resolverIP_setDOSOverrangeThresh(uz_resolverIP_t* self, float thresh);
/**
 * @brief Returns Degradation Of Signal Threshold of AD2S1210 in Volts.
 * From AD2S1210 Datasheet:
 * The DOS overrange threshold register determines the degradation
 * of signal threshold of the AD2S1210. The AD2S1210 allows the
 * user to set the DOS overrange threshold to a value between 0 V
 * and 4.82 V. The resolution of the DOS overrange threshold is
 * 7 bits, that is, 38 mV. The MSB, D7, must be set to 0. The default
 * value of the DOS overrange threshold on power-up is 4.1 V. *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Degradation Of Signal Threshold of AD2S1210 in Volts
 *
 */
float uz_resolverIP_getDOSOverrangeThresh(uz_resolverIP_t* self);

/**
 * @brief Sets Degradation Of Signal Mismatch Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The DOS mismatch threshold register determines the signal
 * mismatch threshold of the AD2S1210. The AD2S1210 allows
 * the user to set the DOS mismatch threshold to a value between
 * 0 V and 4.82 V. The resolution of the DOS mismatch threshold
 * is seven bits, that is, 38 mV. Note that the MSB, D7, should be
 * set to 0.The default value of the DOS mismatch threshold on
 * power-up is 380 mV.
 *
 * @param self instance of uz_resolverIP_t
 * @param thresh Degradation Of Signal Mismatch Threshold of AD2S1210 in Volts. Valid threshold values are in the range [0V, 4.82V]
 */
void uz_resolverIP_setDOSMismatchThresh(uz_resolverIP_t* self, float thresh);

/**
 * @brief Returns Degradation Of Signal Mismatch Threshold of AD2S1210 in Volts.
 * From AD2S1210 Datasheet:
 * The DOS mismatch threshold register determines the signal
 * mismatch threshold of the AD2S1210. The AD2S1210 allows
 * the user to set the DOS mismatch threshold to a value between
 * 0 V and 4.82 V. The resolution of the DOS mismatch threshold
 * is seven bits, that is, 38 mV. Note that the MSB, D7, should be
 * set to 0.The default value of the DOS mismatch threshold on
 * power-up is 380 mV.
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Degradation Of Signal Mismatch Threshold of AD2S1210 in Volts
 *
 */
float uz_resolverIP_getDOSMismatchThresh(uz_resolverIP_t* self);


/**
 * @brief Sets Degradation Of Signal Reset Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The AD2S1210 continuously stores the minimum and maximum
 * magnitude of the monitor signal in internal registers. The difference
 * between the minimum and maximum is calculated to determine if
 * a DOS mismatch has occurred. The initial values for the minimum
 * and maximum internal registers must be defined by the user.
 * When the fault register is cleared, the registers that store the
 * maximum and minimum amplitudes of the monitor signal
 * are reset to the values stored in the DOS reset maximum and
 * minimum threshold registers. The resolution of the DOS reset
 * maximum and minimum thresholds is seven bits each, that is,
 * 38 mV. Note that the MSB, D7, should be set to 0. To ensure
 * correct operation, it is recommended that the DOS reset
 * minimum threshold register be set to at least 1 LSB less than the
 * DOS overrange threshold, and the DOS reset maximum threshold
 * register be set to at least 1 LSB greater than the LOS threshold
 * register. The default value of the DOS reset minimum threshold
 * register and the DOS reset maximum threshold register are 3.99 V
 * and 2.28 V, respectively.
 *
 * @param self instance of uz_resolverIP_t
  * @param max Degradation Of Signal Reset Maximum Threshold of AD2S1210 in Volts. Valid threshold values are in the range [0V, 4.82V]
 */
void uz_resolverIP_setDOSResetMax(uz_resolverIP_t* self, float max);

/**
 * @brief Sets Degradation Of Signal Reset Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The AD2S1210 continuously stores the minimum and maximum
 * magnitude of the monitor signal in internal registers. The difference
 * between the minimum and maximum is calculated to determine if
 * a DOS mismatch has occurred. The initial values for the minimum
 * and maximum internal registers must be defined by the user.
 * When the fault register is cleared, the registers that store the
 * maximum and minimum amplitudes of the monitor signal
 * are reset to the values stored in the DOS reset maximum and
 * minimum threshold registers. The resolution of the DOS reset
 * maximum and minimum thresholds is seven bits each, that is,
 * 38 mV. Note that the MSB, D7, should be set to 0. To ensure
 * correct operation, it is recommended that the DOS reset
 * minimum threshold register be set to at least 1 LSB less than the
 * DOS overrange threshold, and the DOS reset maximum threshold
 * register be set to at least 1 LSB greater than the LOS threshold
 * register. The default value of the DOS reset minimum threshold
 * register and the DOS reset maximum threshold register are 3.99 V
 * and 2.28 V, respectively.
 *
 * @param self instance of uz_resolverIP_t
 * @param min Degradation Of Signal Reset Maximum Threshold of AD2S1210 in Volts. Valid threshold values are in the range [0V, 4.82V]
 */
void uz_resolverIP_setDOSResetMin(uz_resolverIP_t* self, float min);

/**
 * @brief Returns Degradation Of Signal Reset Minimum Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The AD2S1210 continuously stores the minimum and maximum
 * magnitude of the monitor signal in internal registers. The difference
 * between the minimum and maximum is calculated to determine if
 * a DOS mismatch has occurred. The initial values for the minimum
 * and maximum internal registers must be defined by the user.
 * When the fault register is cleared, the registers that store the
 * maximum and minimum amplitudes of the monitor signal
 * are reset to the values stored in the DOS reset maximum and
 * minimum threshold registers. The resolution of the DOS reset
 * maximum and minimum thresholds is seven bits each, that is,
 * 38 mV. Note that the MSB, D7, should be set to 0. To ensure
 * correct operation, it is recommended that the DOS reset
 * minimum threshold register be set to at least 1 LSB less than the
 * DOS overrange threshold, and the DOS reset maximum threshold
 * register be set to at least 1 LSB greater than the LOS threshold
 * register. The default value of the DOS reset minimum threshold
 * register and the DOS reset maximum threshold register are 3.99 V
 * and 2.28 V, respectively.
 *
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Degradation Of Signal Reset Minimum Threshold of AD2S1210 in Volts
 *
 */
float uz_resolverIP_getDOSResetMin(uz_resolverIP_t* self);

/**
 * @brief Returns Degradation Of Signal Reset Maximum Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The AD2S1210 continuously stores the minimum and maximum
 * magnitude of the monitor signal in internal registers. The difference
 * between the minimum and maximum is calculated to determine if
 * a DOS mismatch has occurred. The initial values for the minimum
 * and maximum internal registers must be defined by the user.
 * When the fault register is cleared, the registers that store the
 * maximum and minimum amplitudes of the monitor signal
 * are reset to the values stored in the DOS reset maximum and
 * minimum threshold registers. The resolution of the DOS reset
 * maximum and minimum thresholds is seven bits each, that is,
 * 38 mV. Note that the MSB, D7, should be set to 0. To ensure
 * correct operation, it is recommended that the DOS reset
 * minimum threshold register be set to at least 1 LSB less than the
 * DOS overrange threshold, and the DOS reset maximum threshold
 * register be set to at least 1 LSB greater than the LOS threshold
 * register. The default value of the DOS reset minimum threshold
 * register and the DOS reset maximum threshold register are 3.99 V
 * and 2.28 V, respectively.
 *
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Degradation Of Signal Reset Maximum Threshold of AD2S1210 in Volts
 *
 */
float uz_resolverIP_getDOSResetMax(uz_resolverIP_t* self);

/**
 * @brief Sets Loss Of Tracking High Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The LOT high threshold register determines the loss of position
 * tracking threshold for the AD2S1210. The LOT high threshold is a
 * 7-bit word. The MSB, D7, must be set to 0. The range of the LOT
 * high threshold, the LSB size, and the default value of the LOT
 * high threshold on power-up are dependent on the resolution
 * setting of the AD2S1210, and are outlined in Table 19.
 *
 * @param self instance of uz_resolverIP_t
 * @param thresh Loss Of Tracking High Threshold of AD2S1210 in degrees
 */
void uz_resolverIP_setLOTHighThresh(uz_resolverIP_t* self, float thresh);
/**
 * @brief Returns Loss Of Tracking High Threshold of AD2S1210 in Volts.
 * From AD2S1210 Datasheet:
 * The LOT high threshold register determines the loss of position
 * tracking threshold for the AD2S1210. The LOT high threshold is a
 * 7-bit word. The MSB, D7, must be set to 0. The range of the LOT
 * high threshold, the LSB size, and the default value of the LOT
 * high threshold on power-up are dependent on the resolution
 * setting of the AD2S1210, and are outlined in Table 19.
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Loss Of Tracking High Threshold of AD2S1210 in Degrees
 *
 */
float uz_resolverIP_getLOTHighThresh(uz_resolverIP_t* self);

/**
 * @brief Sets Loss Of Tracking Low Threshold of AD2S1210.
 * From AD2S1210 Datasheet:
 * The LOT low threshold register determines the level of hysteresis
 * on the loss of position tracking fault detection. Loss of tracking
 * (LOT) occurs when the internal error signal of the AD2S1210
 * exceeds the LOT high threshold. LOT has hysteresis and is not
 * cleared until the internal error signal is less than the value defined
 * in the LOT low threshold register. The LOT low threshold is a
 * 7-bit word. The MSB, D7, must be set to 0. The range of the
 * LOT low threshold, the LSB size, and the default value of the
 * LOT low threshold on power-up are dependent on the resolution
 * setting of the AD2S1210 and are outlined in Table 19
 *
 * @param self instance of uz_resolverIP_t
 * @param thresh Loss Of Tracking High Threshold of AD2S1210 in degrees
 */
void uz_resolverIP_setLOTLowThresh(uz_resolverIP_t* self, float thresh);

/**
 * @brief Returns Loss Of Tracking Low Threshold of AD2S1210 in Volts.
 * From AD2S1210 Datasheet:
 * The LOT low threshold register determines the level of hysteresis
 * on the loss of position tracking fault detection. Loss of tracking
 * (LOT) occurs when the internal error signal of the AD2S1210
 * exceeds the LOT high threshold. LOT has hysteresis and is not
 * cleared until the internal error signal is less than the value defined
 * in the LOT low threshold register. The LOT low threshold is a
 * 7-bit word. The MSB, D7, must be set to 0. The range of the
 * LOT low threshold, the LSB size, and the default value of the
 * LOT low threshold on power-up are dependent on the resolution
 * setting of the AD2S1210 and are outlined in Table 19
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float Loss Of Tracking High Threshold of AD2S1210 in Degrees
 *
 */
float uz_resolverIP_getLOTLowThresh(uz_resolverIP_t* self);
/**
 * @brief Sets Excitation Frequency Register of AD2S1210.
 * From AD2S1210 Datasheet:
 * The excitation frequency register determines the frequency of
 * the excitation outputs of the AD2S1210. A 7-bit frequency control
 * word is written to the register to set the excitation frequency.
 * The MSB, D7, must be set to 0.
 * fCW = (Excitation frquency * 2^15) / fCLKIN
 * where fCW is the frequency control word and fCLKIN is the clock
 * frequency of the AD2S1210. The specified range of the excitation
 * frequency is from 2 kHz to 20 kHz and can be set in increments
 * of 250 Hz. To ensure that the AD2S1210 is operated within the
 * specified frequency range, the frequency control word should
 * be a value between 0x4 and 0x50.
 *
 * @param self instance of uz_resolverIP_t
 * @param excFreq Excitation Frequency AD2S1210 in Herz.
 */
void uz_resolverIP_setExcitationFrequency(uz_resolverIP_t* self, float excFreq);

/**
 * @brief Returns Excitation Frequency Register of AD2S1210.
 * From AD2S1210 Datasheet:
 * The excitation frequency register determines the frequency of
 * the excitation outputs of the AD2S1210. A 7-bit frequency control
 * word is written to the register to set the excitation frequency.
 * The MSB, D7, must be set to 0.
 * fCW = (Excitation frequency * 2^15) / fCLKIN
 * where fCW is the frequency control word and fCLKIN is the clock
 * frequency of the AD2S1210. The specified range of the excitation
 * frequency is from 2 kHz to 20 kHz and can be set in increments
 * of 250 Hz. To ensure that the AD2S1210 is operated within the
 * specified frequency range, the frequency control word should
 * be a value between 0x4 and 0x50.
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return float ExcitationFrequency of AD2S1210 in Herz
 */
float uz_resolverIP_getExcitationFrequency(uz_resolverIP_t* self);

/**
 * @brief Sets Control Register of AD2S1210.
 * From AD2S1210 Datasheet:
 * The control register is an 8-bit register that sets the AD2S1210
 * control modes. The default value of the control register on
 * power-up is 0x7E
 *
 * @param self instance of uz_resolverIP_t
 * @param register_value Control Register Value
 */
void uz_resolverIP_setCTRLReg(uz_resolverIP_t* self, int32_t register_value);
/**
 * @brief Returns Control Register of AD2S1210.
 * From AD2S1210 Datasheet:
 * The control register is an 8-bit register that sets the AD2S1210
 * control modes. The default value of the control register on
 * power-up is 0x7E
 *
 * @param self instance of uz_resolverIP_t
 *
 * @return int32_t Control Register Value
 *
 */
int32_t uz_resolverIP_getCTRLReg(uz_resolverIP_t* self);

/**
 * @brief Resets Software of AD2S1210
 * From AD2S1210 Datasheet:
 * Addressing the software reset register, that is writing the 8-bit
 * address, 0xF0, of the software reset register to the AD2S1210
 * while in configuration mode, allows the user to initiate a software
 * reset of the AD2S1210. The software reset reinitializes the
 * excitation frequency outputs and the internal Type II tracking loop.
 * The data stored in the configuration registers is not overwritten
 * by a software reset. However, note that the data in the fault register
 * is reset. In an application that uses two or more resolver-to-digital
 * converters, which are both driven from the same clock source,
 * the software reset can be used to synchronize the phase of the
 * excitation frequencies across the converters
 *
 * @param self instance of uz_resolverIP_t

 *
 */
void uz_resolverIP_resetSoftware(uz_resolverIP_t* self);

/**
 * @brief Reads Fault Register of AD2S1210
 * From AD2S1210 Datasheet:
 * The AD2S1210 has the ability to detect eight separate fault condi-
 * tions. When a fault occurs, the DOS and/or the LOT output
 * pins are taken low. By reading the fault register, the user can
 * determine the cause of the triggering of the fault detection output
 * pins. Note that the fault register bits are active high, that is, the
 * fault bits are taken high to indicate that a fault has occurred
 *
 * @param self instance of uz_resolverIP_t
 *
 *@return int32_t Fault Register Value
 */
int32_t uz_resolverIP_getFLTRegister(uz_resolverIP_t* self);




#endif // UZ_RESOLVERIP_H
