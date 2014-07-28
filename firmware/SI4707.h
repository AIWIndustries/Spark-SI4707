/*
  Si4707.h - Arduino library for controling the Silicon Labs Si4707 in I2C mode.
  
  Copyright 2013 by Ray H. Dees
  Copyright 2013 by Richard Vogel
  
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SI4707_h
#define SI4707_h
//
#include "application.h"
//
//  Arduino definitions.
//
#define lowByte(w) ((uint8_t) ((w) & 0xff)) //from Arduino.h
#define highByte(w) ((uint8_t) ((w) >> 8))  //from Arduino.h
//
//
#define WB_CHANNEL_SPACING	           0x0A	     //  25 kHz.
#define WB_MIN_FREQUENCY	           0xFDC0	     //  162.400 mHz.
#define WB_MAX_FREQUENCY	           0xFDFC	     //  162.550 mHz.
//
//  Si4707 Command definitions.
//
#define	POWER_UP	                     0x01 	   //  Powerup device.
#define	GET_REV 	                     0x10 	   //  Returns revision information on the device.
#define	POWER_DOWN	                   0x11 	   //  Powerdown device.
#define	SET_PROPERTY	                 0x12 	   //  Sets the value of a property.
#define	GET_PROPERTY	                 0x13 	   //  Retrieves a property’s value.
#define	GET_INT_STATUS	               0x14 	   //  Read interrupt status bits.
#define	PATCH_ARGS	                   0x15 	   //  Reserved command used for firmware file downloads.
#define	PATCH_DATA	                   0x16 	   //  Reserved command used for firmware file downloads.
#define	WB_TUNE_FREQ	                 0x50 	   //  Selects the WB tuning frequency.
#define	WB_TUNE_STATUS	               0x52 	   //  Queries the status of the previous WB_TUNE_FREQ command.
#define	WB_RSQ_STATUS	                 0x53 	   //  Queries the status of the Received Signal Quality (RSQ) of the current channel.
#define	WB_SAME_STATUS	               0x54 	   //  Returns SAME information for the current channel.
#define	WB_ASQ_STATUS	                 0x55 	   //  Queries the status of the 1050 Hz alert tone.
#define	WB_AGC_STATUS	                 0x57 	   //  Queries the status of the AGC.
#define	WB_AGC_OVERRIDE	               0x58 	   //  Enable or disable the AGC.
#define	GPIO_CTL 	                     0x80 	   //  Configures GPO as output or Hi-Z.
#define	GPIO_SET	                     0X81 	   //  Sets GPO output level (low or high).
//
//  Si4707 Property definitions.
//
#define GPO_IEN		                   0x0001      //  Enables GPO2 interrupt sources.
#define REFCLK_FREQ	                 0x0201      //  Sets frequency of reference clock in Hz.
#define REFCLK_PRESCALE              0x0202      //  Sets the prescaler value for RCLK input.
#define RX_VOLUME		                 0x4000      //  Sets the output volume.
#define RX_HARD_MUTE	               0x4001      //  Mutes the audio output.
#define WB_MAX_TUNE_ERROR 		       0x5108      //  Maximum change from the WB_TUNE_FREQ to which the AFC will lock.
#define WB_RSQ_INT_SOURCE 		       0x5200      //  Configures interrupts related to RSQ metrics.
#define WB_RSQ_SNR_HIGH_THRESHOLD 	 0x5201      //  Sets high threshold for SNR interrupt.
#define WB_RSQ_SNR_LOW_THRESHOLD 	   0x5202      //  Sets low threshold for SNR interrupt.
#define WB_RSQ_RSSI_HIGH_THRESHOLD   0x5203      //  Sets high threshold for RSSI interrupt.
#define WB_RSQ_RSSI_LOW_THRESHOLD 	 0x5204      //  Sets low threshold for RSSI interrupt.
#define WB_VALID_SNR_THRESHOLD       0x5403      //  Sets SNR threshold to indicate a valid channel.
#define WB_VALID_RSSI_THRESHOLD      0x5404      //  Sets RSSI threshold to indicate a valid channel.
#define WB_SAME_INTERRUPT_SOURCE 	   0x5500      //  Configures SAME interrupt sources.
#define WB_ASQ_INT_SOURCE 		       0x5600      //  Configures 1050 Hz alert tone interrupts.
//
//  Si4707 Power Up Command Arguments.
//
#define WB                             0x03      //  Function, 3 = WB receive.
#define QUERY                          0x0F      //  Function, 15 = Query Library ID. 
#define XOSCEN	                       0x10      //  Crystal Oscillator Enable.
#define PATCH	                         0x20      //  Patch Enable.
#define GPO2EN                         0x40      //  GPO2 Output Enable.
#define CTSEN  	                       0x80      //  CTS Interrupt Enable.
//
#define OPMODE                         0x05      //  Application Setting, 5 = Analog L & R outputs. 
//
// Si4707 Returned Interrupt Status Bits.
//
#define STCINT                         0x01      //  Seek/Tune Complete Interrupt.
#define ASQINT                         0x02      //  1050 Hz Alert Tone Interrupt.
#define SAMEINT                        0x04      //  SAME Interrupt.
#define RSQINT                         0x08      //  Received Signal Quality Interrupt.
#define ERRINT                         0x40      //  Error Interrupt.
#define CTSINT                         0x80      //  Clear To Send Interrupt.
//
//  Si4707 Status Register Masks.
//
#define VALID                          0x01      //  Valid Channel.
#define AFCRL                          0x02      //  AFC Rail Indicator.
//
#define RSSILINT                       0x01      //  RSSI was Detected Low.
#define RSSIHINT                       0x02      //  RSSI was Detected High.
#define SNRLINT                        0x04      //  SNR was Detected Low.
#define SNRHINT                        0x08      //  SNR was Detected High.
//
#define HDRRDY                         0x01      //  SAME Header Ready was detected.
#define PREDET                         0x02      //  SAME Preamble was Detected.
#define SOMDET                         0x04      //  SAME Start Of Message was Detected.
#define EOMDET                         0x08      //  SAME End Of Message was Detected.
//
#define ALERTON                        0x01      //  Alert Tone has not been detected on since last WB_TUNE_FREQ.
#define ALERTOF                        0x02      //  Alert Tone has not been detected off since last WB_TUNE_FREQ.
#define ALERT                          0x01      //  Alert Tone is currently present.
//
//  Si4707 Interrupt Acknowledge Commands.
//
#define CHECK                          0x00      //  Allows checking of status without clearing interrupt.
#define INTACK                         0x01      //  If set, this bit clears the current interrupt.
#define CLRBUF                         0x02      //  If set, the SAME buffer is cleared.
//
//  Si4707 Sources for GPO2/INT Interrupt pin.
//
#define STCIEN                       0x0001      //  Seek/Tune Complete Interrupt Enable.
#define ASQIEN                       0x0002      //  ASQ Interrupt Enable.
#define SAMEIEN                      0x0004      //  SAME Interrupt Enable.
#define RSQIEN                       0x0008      //  RSQ Interrupt Enable. 
#define ERRIEN                       0x0040      //  Error Interrupt Enable.
#define CTSIEN 	                     0x0080      //  CTS Interrupt Enable.
#define STCREP                       0X0100      //  Repeat STCINT even if it is already set.
#define ASQREP                       0x0200      //  Repeat ASQINT even if it is already set.
#define SAMEREP                      0x0400      //  Repeat SAMEINT even if it is already set.
#define RSQREP                       0x0800      //  Repeat RSQINT even if it is already set.
//
#define RSSILIEN                     0x0001      //  RSSI detect Low Interrupt Enable.
#define RSSIHIEN                     0x0002      //  RSSI detect High Interrupt Enable.
#define SNRLIEN                      0x0004      //  SNR detect Low Interrupt Enable.
#define SNRHIEN                      0x0008      //  SNR detect High Interrupt Enable.
//
#define HDRRDYIEN                    0x0001      //  SAME Header Ready Interrupt Enable.
#define PREDETIEN                    0x0002      //  SAME Preamble Detected Interrupt Enable.
#define SOMDETIEN                    0x0004      //  SAME Start Of Message Detected Interrupt Enable.
#define EOMDETIEN                    0x0008      //  SAME End Of Message Detected Interrupt Enable.  
//
#define ALERTONIEN                   0x0001      //  Sets 1050 Hz tone on as source of ASQ Interrupt.
#define ALERTOFIEN                   0x0002      //  Sets 1050 Hz tone off as source of ASQ Interrupt. 
//
//  Si4707 GPO Control / Set Functions.
//
#define GPO1OEN                        0x02      //  GPO1 Output Enable.
#define GPO2OEN                        0x04      //  GPO2 Output Enable.  The use of GPO2 as an interrupt pin will override this.
#define GPO3OEN                        0x08      //  GPO3 Output Enable.
#define GPO1LEVEL                      0x02      //  Sets GPO1 High. 
#define GPO2LEVEL                      0x04      //  Sets GPO2 High. 
#define GPO3LEVEL                      0x08      //  Sets GPO3 High.
//
//  SAME Confidence Level Masks and Bit Shift Positions.
//
#define SAME_STATUS_OUT_CONF0          0x03
#define SAME_STATUS_OUT_CONF1          0x0C
#define SAME_STATUS_OUT_CONF2          0x30
#define SAME_STATUS_OUT_CONF3          0xC0
#define SAME_STATUS_OUT_CONF4          0x03
#define SAME_STATUS_OUT_CONF5          0x0C
#define SAME_STATUS_OUT_CONF6          0x30
#define SAME_STATUS_OUT_CONF7          0xC0
#define SAME_STATUS_OUT_CONF0_SHFT        0
#define SAME_STATUS_OUT_CONF1_SHFT        2
#define SAME_STATUS_OUT_CONF2_SHFT        4
#define SAME_STATUS_OUT_CONF3_SHFT        6
#define SAME_STATUS_OUT_CONF4_SHFT        0
#define SAME_STATUS_OUT_CONF5_SHFT        2
#define SAME_STATUS_OUT_CONF6_SHFT        4
#define SAME_STATUS_OUT_CONF7_SHFT        6

#define INT                               D2      //  Arduino Interrupt input pin.
#define RST                               D4      //  Arduino pin used to reset the Si4707.
#define ON 		                         0x01      //  Used for Power/Mute On.
#define OFF 	                         0x00      //  Used for Power/Mute Off.
#define CMD_DELAY	                        2      //  Inter-Command delay (301 usec).
#define PROP_DELAY                       10      //  Set Property Delay (10.001 msec)
#define PUP_DELAY	                      200      //  Power Up Delay.  (110.001 msec)
#define TUNE_DELAY                      250      //  Tune Delay. (250.001 msec)
#define RADIO_ADDRESS                  0x11      //  I2C address of the Si4707, shifted one bit.
#define RADIO_VOLUME                 0x003F      //  Default Volume.
//
//  SAME Definitions.  
//
#define SAME_CONFIDENCE_THRESHOLD         1      //  Must be 1, 2 or 3, nothing else!
#define SAME_BUFFER_SIZE                255      //  The maximum number of receive bytes.
#define SAME_MIN_LENGTH                  36      //  The SAME message minimum acceptable length.
#define SAME_LOCATION_CODES              30      //  Subtract 1, because we count from 0.
#define SAME_TIME_OUT                     6      //  Time before buffers are flushed.
//
//  Program Control Status Bits.
//
#define INTAVL                         0x10      //  A status interrupt is available.  
//
#define MSGAVL                         0x01      //  A SAME message is Available to be printed/parsed.
#define MSGPAR                         0x02      //  The SAME message was successfully Parsed.
#define MSGUSD                         0x04      //  When set, this SAME message has been used. 
#define MSGPUR                         0x08      //  The SAME message should be Purged (Third Header received). 
//
//  Global Status Bytes.
//
extern uint8_t intStatus;
extern uint8_t rsqStatus;
extern uint8_t sameStatus;
extern uint8_t asqStatus;
extern uint8_t agcStatus;
extern uint8_t msgStatus;
//
//  Global Radio Variables.
//
extern uint16_t channel;
extern float frequency;
extern uint16_t volume;
extern uint8_t mute;
extern uint8_t rssi;
extern uint8_t snr;
extern int freqoff;
extern uint8_t power;
//
//  Global SAME Variables.
//
extern char sameOriginatorName[];
extern char sameEventName[];
extern char sameCallSign[];
//
extern uint8_t sameHeaderCount;
extern uint8_t sameLength;
extern uint8_t sameState;
extern uint8_t samePlusIndex;
extern uint8_t sameLocations;
extern uint32_t sameLocationCodes[];
extern uint16_t sameDuration;
extern uint16_t sameDay;
extern uint16_t sameTime;
extern uint8_t sameWat;
//
extern uint8_t response[];
extern volatile uint8_t sreg;
extern volatile uint8_t timer;
//
//  SI4707 Class.
//
class SI4707 
{
  public: 

    void begin(void);
    void on(void);
    void getRevision(void);
    void patch(void);

    void off(void);
    void end(void);
    
    void tune(uint32_t direct);
    void tune(void);
    void scan(void);
    
    uint8_t getIntStatus(void);
    void getTuneStatus(uint8_t mode);
    void getRsqStatus(uint8_t mode);
    void getSameStatus(uint8_t mode);
    void getAsqStatus(uint8_t mode);
    void getAgcStatus(void);

    void setVolume(uint16_t volume);
    void setMute(uint8_t value);

    void setProperty(uint16_t property, uint16_t value);
    uint16_t getProperty(uint16_t property);

    void gpioControl(uint8_t value);
    void gpioSet(uint8_t value);
      
    int  sameAvailable(void);
    char sameRead(void);
    void sameParse(void);
    void sameFlush(void);
    void sameFill(const String &s);
  
  private:

    static uint8_t sameConf[];
    static char sameData[];
    static uint8_t rxConfidence[];
    static char rxBuffer[];  
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;
    
    void writeCommand(uint8_t command);
    void writeByte(uint8_t command, uint8_t value);
    void writeWord(uint8_t command, uint16_t value);
    void writeAddress(uint8_t address, uint8_t mode);
    
    void readStatus(void);
    void readBurst(int quantity);
};

extern SI4707 Radio;

#endif  //  End of SI4707.h
