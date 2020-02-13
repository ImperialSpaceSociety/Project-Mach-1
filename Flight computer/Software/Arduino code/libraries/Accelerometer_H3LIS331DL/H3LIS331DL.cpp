/*
 * H3LIS331DL.cpp
 * A library for 3-Axis Digital Accelerometer(±400g)
 *  
 * Copyright (c) 2014 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : lawliet zou
 * Create Time: April 2014
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#include "H3LIS331DL.h"
#include <Wire.h>

void H3LIS331DL::init(H3LIS331DL_ODR_t  odr,H3LIS331DL_Mode_t mode,H3LIS331DL_Fullscale_t fullScale){

    Wire.begin();
    //set output data rate
    setODR(odr);
    //set PowerMode 
    setMode( mode);
    //set Fullscale
    setFullScale( fullScale);
    //set axis Enable
    setAxis( H3LIS331DL_X_ENABLE | H3LIS331DL_Y_ENABLE |  H3LIS331DL_Z_ENABLE);
}

void H3LIS331DL::importPara(int16_t val_x, int16_t val_y, int16_t val_z)
{
    _adjVal[0] = val_x;
    _adjVal[1] = val_y;
    _adjVal[2] = val_z;
}
void H3LIS331DL::readXYZ(int16_t* x, int16_t* y, int16_t* z)
{
    //get Acceleration Raw data  
    AxesRaw_t data;
    status_t response = getAccAxesRaw(&data);
    if(MEMS_SUCCESS == response){
        *x = (data.AXIS_X - _adjVal[0]);
        *y = (data.AXIS_Y - _adjVal[1]);
        *z = (data.AXIS_Z - _adjVal[2]);
    }
}

void H3LIS331DL::getAcceleration(double* xyz)
{
    AxesRaw_t data;
    double gains = 0.003;
    getAccAxesRaw(&data);
    
    xyz[0] = (data.AXIS_X - _adjVal[0]) * gains;
    xyz[1] = (data.AXIS_Y - _adjVal[1]) * gains;
    xyz[2] = (data.AXIS_Z - _adjVal[2]) * gains;
}


/*******************************************************************************
* Function Name  : getWHO_AM_I
* Description    : Read identification code from H3LIS331DL::WHO_AM_I register
* Input          : char to be filled with the Device identification Value
* Output         : None
* Return         : Status [value of FSS]
*******************************************************************************/
status_t H3LIS331DL::getWHO_AM_I(byte* val){
  
    if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_WHO_AM_I, val) )
        return MEMS_ERROR;
  
    return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setODR
* Description    : Sets H3LIS331DL Accelerometer Output Data Rate 
* Input          : Output Data Rate
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setODR(H3LIS331DL_ODR_t dr){
    byte value;
  
    if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG1, &value) )
        return MEMS_ERROR;
  
    value &= 0xE7;
    value |= dr<<H3LIS331DL_DR;
  
    if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG1, value) )
        return MEMS_ERROR;
  
    return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setMode
* Description    : Sets H3LIS331DLH Accelerometer Operating Mode
* Input          : Modality (H3LIS331DL_LOW_POWER, H3LIS331DL_NORMAL, H3LIS331DL_POWER_DOWN...)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setMode(H3LIS331DL_Mode_t pm) {
    byte value;
  
    if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG1, &value) )
        return MEMS_ERROR;
  
    value &= 0x1F;
    value |= (pm<<H3LIS331DL_PM);   
  
    if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG1, value) )
        return MEMS_ERROR;
  
    return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : setAxis
* Description    : Enable/Disable LIS331DLH Axis
* Input          : H3LIS331DL_X_ENABLE/H3LIS331DL_X_DISABLE | H3LIS331DL_Y_ENABLE/H3LIS331DL_Y_DISABLE
                   | H3LIS331DL_Z_ENABLE/H3LIS331DL_Z_DISABLE
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setAxis(H3LIS331DL_Axis_t axis) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG1, &value) )
    return MEMS_ERROR;
  
  value &= 0xF8;
  value |= (0x07 & axis);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG1, value) )
    return MEMS_ERROR;   
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setFullScale
* Description    : Sets the LIS331DLH FullScale
* Input          : H3LIS331DL_FULLSCALE_2/H3LIS331DL_FULLSCALE_4/H3LIS331DL_FULLSCALE_8
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setFullScale(H3LIS331DL_Fullscale_t fs) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, &value) )
    return MEMS_ERROR;
  
  value &= 0xCF;    
  value |= (fs<<H3LIS331DL_FS);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setBDU
* Description    : Enable/Disable Block Data Update Functionality
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setBDU(State_t bdu) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, &value) )
    return MEMS_ERROR;
  
  value &= 0x7F;
  value |= (bdu<<H3LIS331DL_BDU);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setBLE
* Description    : Set Endianess (MSB/LSB)
* Input          : H3LIS331DL_BLE_LSB / H3LIS331DL_BLE_MSB
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setBLE(H3LIS331DL_Endianess_t ble) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, &value) )
    return MEMS_ERROR;
  
  value &= 0xBF;    
  value |= (ble<<H3LIS331DL_BLE);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setFDS
* Description    : Set Filter Data Selection
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setFDS(State_t fds) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, &value) )
    return MEMS_ERROR;
  
  value &= 0xEF;    
  value |= (fds<<H3LIS331DL_FDS);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setBOOT
* Description    : Rebot memory content
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setBOOT(State_t boot) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, &value) )
    return MEMS_ERROR;
  
  value &= 0x7F;    
  value |= (boot<<H3LIS331DL_BOOT);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setSelfTest
* Description    : Set Self Test Modality
* Input          : MEMS_DISABLE/MEMS_ENABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setSelfTest(State_t st) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, &value) )
    return MEMS_ERROR;
  
  value &= 0xFD;
  value |= (st<<H3LIS331DL_ST);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setSelfTestSign
* Description    : Set Self Test Sign (Disable = st_plus, Enable = st_minus)
* Input          : MEMS_DISABLE/MEMS_ENABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setSelfTestSign(State_t st_sign) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, &value) )
    return MEMS_ERROR;
  
  value &= 0xF7;
  value |= (st_sign<<H3LIS331DL_ST_SIGN);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setIntHighLow
* Description    : Set Interrupt active state (Disable = active high, Enable = active low)
* Input          : MEMS_DISABLE/MEMS_ENABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setIntHighLow(State_t ihl) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, &value) )
    return MEMS_ERROR;
  
  value &= 0x7F;
  value |= (ihl<<H3LIS331DL_IHL);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setIntPPOD
* Description    : Set Interrupt Push-Pull/OpenDrain Pad (Disable = Push-Pull, Enable = OpenDrain)
* Input          : MEMS_DISABLE/MEMS_ENABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setIntPPOD(State_t pp_od) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, &value) )
    return MEMS_ERROR;
  
  value &= 0xBF;
  value |= (pp_od<<H3LIS331DL_PP_OD);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt1DataSign
* Description    : Set Data signal Interrupt 1 pad
* Input          : Modality by H3LIS331DL_INT_Conf_t Typedef 
                  (H3LIS331DL_INT_SOURCE, H3LIS331DL_INT_1OR2_SOURCE, H3LIS331DL_DATA_READY, H3LIS331DL_BOOT_RUNNING)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt1DataSign(H3LIS331DL_INT_Conf_t i_cfg) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, &value) )
    return MEMS_ERROR;
  
  value &= 0xFC;
  value |= (i_cfg<<H3LIS331DL_I1_CFG);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt2DataSign
* Description    : Set Data signal Interrupt 2 pad
* Input          : Modality by H3LIS331DL_INT_Conf_t Typedef 
                  (H3LIS331DL_INT_SOURCE, H3LIS331DL_INT_1OR2_SOURCE, H3LIS331DL_DATA_READY, H3LIS331DL_BOOT_RUNNING)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt2DataSign(H3LIS331DL_INT_Conf_t i_cfg) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, &value) )
    return MEMS_ERROR;
  
  value &= 0xE7;
  value |= (i_cfg<<H3LIS331DL_I2_CFG);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setSPI34Wire
* Description    : Set SPI mode 
* Input          : Modality by H3LIS331DL_SPIMode_t Typedef (H3LIS331DL_SPI_4_WIRE, H3LIS331DL_SPI_3_WIRE)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setSPI34Wire(H3LIS331DL_SPIMode_t sim) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, &value) )
    return MEMS_ERROR;
  
  value &= 0xFE;
  value |= (sim<<H3LIS331DL_SIM);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : turnONEnable
* Description    : TurnON Mode selection for sleep to wake function
* Input          : H3LIS331DL_SLEEP_TO_WAKE_DIS/H3LIS331DL_SLEEP_TO_WAKE_ENA
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::turnONEnable(H3LIS331DL_Sleep_To_Wake_Conf_t stw) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG5, &value) )
    return MEMS_ERROR;
  
  value &= 0x00;
  value |= (stw<<H3LIS331DL_TURN_ON);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG5, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}

#if 0
/*******************************************************************************
* Function Name  : HPFilterReset
* Description    : Reading register for reset the content of internal HP filter
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::HPFilterReset(void) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_HP_FILTER_RESET, &value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}
#endif

/*******************************************************************************
* Function Name  : setReference
* Description    : Sets Reference register acceleration value as a reference for HP filter
* Input          : Value of reference acceleration value (0-255)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setReference(int8_t ref) {
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_REFERENCE_REG, ref) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setHPFMode
* Description    : Set High Pass Filter Modality
* Input          : H3LIS331DL_HPM_NORMAL_MODE_RES/H3LIS331DL_HPM_REF_SIGNAL/H3LIS331DL_HPM_NORMAL_MODE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setHPFMode(H3LIS331DL_HPFMode_t hpm) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, &value) )
    return MEMS_ERROR;
  
  value &= 0x9F;
  value |= (hpm<<H3LIS331DL_HPM);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setHPFCutOFF
* Description    : Set High Pass CUT OFF Freq
* Input          : H3LIS331DL_HPFCF [0,3]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setHPFCutOFF(H3LIS331DL_HPFCutOffFreq_t hpf) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, &value) )
    return MEMS_ERROR;
  
  value &= 0xFC;
  value |= (hpf<<H3LIS331DL_HPCF);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
  
}


/*******************************************************************************
* Function Name  : setInt2HPEnable
* Description    : Set Interrupt2 hp filter enable/disable
* Input          : MEMS_ENABLE/MEMS_DISABLE
* example        : H3LIS331DL_SetInt2HPEnable(MEMS_ENABLE)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt2HPEnable(State_t stat) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, &value) )
    return MEMS_ERROR;
  
  value &= 0xF7;
  value |= stat<<H3LIS331DL_HPEN2 ;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}     


/*******************************************************************************
* Function Name  : setInt1HPEnable
* Description    : Set Interrupt1 hp filter enable/disable
* Input          : MEMS_ENABLE/MEMS_DISABLE
* example        : H3LIS331DL_SetInt1HPEnable(MEMS_ENABLE)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt1HPEnable(State_t stat) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, &value) )
    return MEMS_ERROR;
  
  value &= 0xFB;
  value |= stat<<H3LIS331DL_HPEN1 ;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}  


/*******************************************************************************
* Function Name  : int1LatchEnable
* Description    : Enable Interrupt 1 Latching function
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::int1LatchEnable(State_t latch) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, &value) )
    return MEMS_ERROR;
  
  value &= 0xFB;
  value |= latch<<H3LIS331DL_LIR1;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : int2LatchEnable
* Description    : Enable Interrupt 2 Latching function
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::int2LatchEnable(State_t latch) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, &value) )
    return MEMS_ERROR;
  
  value &= 0xDF;
  value |= latch<<H3LIS331DL_LIR2;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : resetInt1Latch
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::resetInt1Latch(void) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_SRC, &value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : resetInt2Latch
* Description    : Reset Interrupt 2 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::resetInt2Latch(void) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_SRC, &value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt1Configuration
* Description    : Interrupt 1 Configuration (without 6D_INT)
* Input          : H3LIS331DL_INT_AND/OR | H3LIS331DL_INT_ZHIE_ENABLE/DISABLE | H3LIS331DL_INT_ZLIE_ENABLE/DISABLE...
* Output         : None
* Note           : You MUST use ALL input variable in the argument, as in example above
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt1Configuration(H3LIS331DL_IntConf_t ic) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_CFG, &value) )
    return MEMS_ERROR;
  
  value &= 0x40; 
  value |= ic;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_CFG, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt2Configuration
* Description    : Interrupt 2 Configuration (without 6D_INT)
* Input          : H3LIS331DL_INT_AND/OR | H3LIS331DL_INT_ZHIE_ENABLE/DISABLE | H3LIS331DL_INT_ZLIE_ENABLE/DISABLE...
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt2Configuration(H3LIS331DL_IntConf_t ic) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_CFG, &value) )
    return MEMS_ERROR;
  
  value &= 0x40; 
  value |= ic;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_CFG, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt1Mode
* Description    : Interrupt 1 Configuration mode (OR, 6D Movement, AND, 6D Position)
* Input          : H3LIS331DL_INT_MODE_OR, H3LIS331DL_INT_MODE_6D_MOVEMENT, H3LIS331DL_INT_MODE_AND, H3LIS331DL_INT_MODE_6D_POSITION
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt1Mode(H3LIS331DL_IntMode_t int_mode) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_CFG, &value) )
    return MEMS_ERROR;
  
  value &= 0x3F; 
  value |= (int_mode<<H3LIS331DL_INT_6D);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_CFG, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt2Mode
* Description    : Interrupt 2 Configuration mode (OR, 6D Movement, AND, 6D Position)
* Input          : H3LIS331DL_INT_MODE_OR, H3LIS331DL_INT_MODE_6D_MOVEMENT, H3LIS331DL_INT_MODE_AND, H3LIS331DL_INT_MODE_6D_POSITION
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt2Mode(H3LIS331DL_IntMode_t int_mode) {
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_CFG, &value) )
    return MEMS_ERROR;
  
  value &= 0x3F; 
  value |= (int_mode<<H3LIS331DL_INT_6D);
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_CFG, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : get6DPositionInt1
* Description    : 6D Interrupt 1 Position Detect
* Input          : Byte to be filled with H3LIS331DL_POSITION_6D_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::get6DPositionInt1(byte* val){
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_SRC, &value) )
    return MEMS_ERROR;
  
  value &= 0x7F;
  
  switch (value){
  case H3LIS331DL_UP_SX:   
    *val = H3LIS331DL_UP_SX;    
    break;
  case H3LIS331DL_UP_DX:   
    *val = H3LIS331DL_UP_DX;    
    break;
  case H3LIS331DL_DW_SX:   
    *val = H3LIS331DL_DW_SX;    
    break;
  case H3LIS331DL_DW_DX:   
    *val = H3LIS331DL_DW_DX;    
    break;
  case H3LIS331DL_TOP:     
    *val = H3LIS331DL_TOP;      
    break;
  case H3LIS331DL_BOTTOM:  
    *val = H3LIS331DL_BOTTOM;  
    break;
  }
  
  return MEMS_SUCCESS;  
}


/*******************************************************************************
* Function Name  : get6DPositionInt2
* Description    : 6D Interrupt 2 Position Detect
* Input          : Byte to be filled with H3LIS331DL_POSITION_6D_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::get6DPositionInt2(byte* val){
  byte value;
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_SRC, &value) )
    return MEMS_ERROR;
  
  value &= 0x7F;
  
  switch (value){
  case H3LIS331DL_UP_SX:   
    *val = H3LIS331DL_UP_SX;    
    break;
  case H3LIS331DL_UP_DX:   
    *val = H3LIS331DL_UP_DX;    
    break;
  case H3LIS331DL_DW_SX:   
    *val = H3LIS331DL_DW_SX;    
    break;
  case H3LIS331DL_DW_DX:   
    *val = H3LIS331DL_DW_DX;    
    break;
  case H3LIS331DL_TOP:     
    *val = H3LIS331DL_TOP;      
    break;
  case H3LIS331DL_BOTTOM:  
    *val = H3LIS331DL_BOTTOM;   
    break;
  }
  
  return MEMS_SUCCESS;  
}


/*******************************************************************************
* Function Name  : setInt1Threshold
* Description    : Sets Interrupt 1 Threshold
* Input          : Threshold = [0,127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt1Threshold(byte ths) {
  if (ths > 127)
    return MEMS_ERROR;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_THS, ths) )
    return MEMS_ERROR;    
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt1Duration
* Description    : Sets Interrupt 1 Duration
* Input          : Duration = [0,127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt1Duration(byte id) {  
  if (id > 127)
    return MEMS_ERROR;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_DURATION, id) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt2Threshold
* Description    : Sets Interrupt 2 Threshold
* Input          : Threshold = [0,127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt2Threshold(byte ths) {
  if (ths > 127)
    return MEMS_ERROR;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_THS, ths) )
    return MEMS_ERROR;    
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : setInt2Duration
* Description    : Sets Interrupt 2 Duration
* Input          : Duration = [0,127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::setInt2Duration(byte id) {  
  if (id > 127)
    return MEMS_ERROR;
  
  if( !writeReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_DURATION, id) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : getStatusReg
* Description    : Read the status register
* Input          : char to empty by Status Reg Value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getStatusReg(byte* val) {
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_STATUS_REG, val) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;  
}

/*******************************************************************************
* Function Name  : getStatusBIT
* Description    : Read the status register BIT
* Input          : H3LIS331DL_STATUS_REG_ZYXOR, H3LIS331DL_STATUS_REG_ZOR, H3LIS331DL_STATUS_REG_YOR, H3LIS331DL_STATUS_REG_XOR,
                   H3LIS331DL_STATUS_REG_ZYXDA, H3LIS331DL_STATUS_REG_ZDA, H3LIS331DL_STATUS_REG_YDA, H3LIS331DL_STATUS_REG_XDA, 
                   H3LIS331DL_DATAREADY_BIT
* Output         : status register BIT
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getStatusBit(byte statusBIT, byte *val) {
  byte value;  
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_STATUS_REG, &value) )
    return MEMS_ERROR;
  
  switch (statusBIT){
  case H3LIS331DL_STATUS_REG_ZYXOR:     
    if(value &= H3LIS331DL_STATUS_REG_ZYXOR){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  case H3LIS331DL_STATUS_REG_ZOR:       
    if(value &= H3LIS331DL_STATUS_REG_ZOR){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  case H3LIS331DL_STATUS_REG_YOR:       
    if(value &= H3LIS331DL_STATUS_REG_YOR){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }                                 
  case H3LIS331DL_STATUS_REG_XOR:       
    if(value &= H3LIS331DL_STATUS_REG_XOR){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  case H3LIS331DL_STATUS_REG_ZYXDA:     
    if(value &= H3LIS331DL_STATUS_REG_ZYXDA){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  case H3LIS331DL_STATUS_REG_ZDA:       
    if(value &= H3LIS331DL_STATUS_REG_ZDA){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  case H3LIS331DL_STATUS_REG_YDA:       
    if(value &= H3LIS331DL_STATUS_REG_YDA){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  case H3LIS331DL_STATUS_REG_XDA:       
    if(value &= H3LIS331DL_STATUS_REG_XDA){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }                                      
  }
  
  return MEMS_ERROR;
}


/*******************************************************************************
* Function Name  : getAccAxesRaw
* Description    : Read the Acceleration Values Output Registers
* Input          : buffer to empty by AccAxesRaw_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getAccAxesRaw(AxesRaw_t* buff) {
    byte valueL = 0,valueH = 0;
    readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_OUT_X_L, &valueL);
    readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_OUT_X_H, &valueH);
    buff->AXIS_X = (valueH<<8)|valueL;
    readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_OUT_Y_L, &valueL);
    readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_OUT_Y_H, &valueH);
    buff->AXIS_Y = (valueH<<8)|valueL;
    readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_OUT_Z_L, &valueL);
    readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_OUT_Z_H, &valueH);
    buff->AXIS_Z = (valueH<<8)|valueL;
    return MEMS_SUCCESS;  
}


/*******************************************************************************
* Function Name  : getInt1Src
* Description    : Reset Interrupt 1 Latching function
* Input          : buffer to empty by Int1 Source Value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getInt1Src(byte* val) {  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_SRC, val) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : getInt2Src
* Description    : Reset Interrupt 2 Latching function
* Input          : buffer to empty by Int2 Source Value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getInt2Src(byte* val) {  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_SRC, val) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : getInt1SrcBit
* Description    : Reset Interrupt 1 Latching function
* Input          : H3LIS331DL_INT1_SRC_IA, H3LIS331DL_INT1_SRC_ZH, H3LIS331DL_INT1_SRC_ZL .....
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getInt1SrcBit(byte statusBIT, byte *val) {
  byte value;  
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT1_SRC, &value) )
    return MEMS_ERROR;
  
  if(statusBIT == H3LIS331DL_INT_SRC_IA){
    if(value &= H3LIS331DL_INT_SRC_IA){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }    
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_ZH){
    if(value &= H3LIS331DL_INT_SRC_ZH){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_ZL){
    if(value &= H3LIS331DL_INT_SRC_ZL){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_YH){
    if(value &= H3LIS331DL_INT_SRC_YH){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_YL){
    if(value &= H3LIS331DL_INT_SRC_YL){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_XH){
    if(value &= H3LIS331DL_INT_SRC_XH){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_XL){
    if(value &= H3LIS331DL_INT_SRC_XL){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }    
  } 
  return MEMS_ERROR;
}


/*******************************************************************************
* Function Name  : getInt2SrcBit
* Description    : Reset Interrupt 2 Latching function
* Input          : H3LIS331DL_INT_SRC_IA, H3LIS331DL_INT_SRC_ZH, H3LIS331DL_INT_SRC_ZL .....
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t H3LIS331DL::getInt2SrcBit(byte statusBIT, byte *val) {
  byte value;  
  
  if( !readReg(H3LIS331DL_MEMS_I2C_ADDRESS, H3LIS331DL_INT2_SRC, &value) )
    return MEMS_ERROR;
  
  if(statusBIT == H3LIS331DL_INT_SRC_IA){
    if(value &= H3LIS331DL_INT_SRC_IA){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_ZH){
    if(value &= H3LIS331DL_INT_SRC_ZH){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_ZL){
    if(value &= H3LIS331DL_INT_SRC_ZL){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_YH){
    if(value &= H3LIS331DL_INT_SRC_YH){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }    
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_YL){
    if(value &= H3LIS331DL_INT_SRC_YL){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }   
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_XH){
    if(value &= H3LIS331DL_INT_SRC_XH){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }  
  }
  
  if(statusBIT == H3LIS331DL_INT_SRC_XL){
    if(value &= H3LIS331DL_INT_SRC_XL){     
      *val = MEMS_SET;
      return MEMS_SUCCESS;
    }
    else{  
      *val = MEMS_RESET;
      return MEMS_SUCCESS;
    }    
  } 
  return MEMS_ERROR;
}

/*******************************************************************************
* Function Name     : readReg
* Description       : Generic Reading function. It must be full filled with either
*                   : I2C or SPI reading functions                  
* Input             : Register Address
* Output            : Data Read
* Return            : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
uint8_t H3LIS331DL::readReg(byte deviceAddr, byte Reg, byte* Data) {
  
  //To be completed with either I2c or SPI reading function
  // i.e. *Data = SPI_Mems_Read_Reg( Reg );
  // i.e. if(!I2C_BufferRead(Data, deviceAddr, Reg, 1)) 
  // return MEMS_ERROR;
  // else  
  // return MEMS_SUCCESS;
// Reads num bytes starting from address register on device in to _buff array
    byte num = 1;
    Wire.beginTransmission(deviceAddr); // start transmission to device 
    Wire.write(Reg);             // sends address to read from
    Wire.endTransmission();         // end transmission
    
    Wire.beginTransmission(deviceAddr); // start transmission to device
    Wire.requestFrom(deviceAddr,num);    // request 6 bytes from device
    
    if(Wire.available()){
        *Data = Wire.read();    // receive a byte
        Wire.endTransmission(); // end transmission
        return MEMS_SUCCESS;        
    }else{
        Wire.endTransmission();
        return MEMS_ERROR;
    }
}

/*******************************************************************************
* Function Name     : writeReg
* Description       : Generic Writing function. It must be full filled with either
*                   : I2C or SPI writing function
* Input             : Register Address, Data to be written
* Output            : None
* Return            : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
uint8_t H3LIS331DL::writeReg(byte deviceAddress, byte WriteAddr, byte Data) {
  
  //To be completed with either I2c or SPI writing function
  // i.e. SPI_Mems_Write_Reg(Reg, Data);
  // i.e. I2C_ByteWrite(&Data,  deviceAddress,  WriteAddr);  
  //  return MEMS_SUCCESS;
  // Writes val to address register on device
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(WriteAddr);             // send register address
    Wire.write(Data);                 // send value to write
    Wire.endTransmission();         // end transmission  
    return MEMS_SUCCESS;
}
