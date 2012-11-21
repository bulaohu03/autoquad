/*
    This file is part of AutoQuad.

    AutoQuad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AutoQuad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with AutoQuad.  If not, see <http://www.gnu.org/licenses/>.

    Copyright � 2011, 2012  Bill Nesbitt
*/

#include "aq.h"
#include "config.h"
#include "flash.h"
#include "filer.h"
#include "notice.h"
#include "supervisor.h"
#include "util.h"
#include CONFIG_HEADER
#include <string.h>
#include <stdio.h>
#include <math.h>

float p[CONFIG_NUM_PARAMS] __attribute__((section(".ccm")));

const char *configParameterStrings[] = {
    "CONFIG_VERSION",
    "RADIO_TYPE",
    "RADIO_THRO_CH",
    "RADIO_ROLL_CH",
    "RADIO_PITC_CH",
    "RADIO_RUDD_CH",
    "RADIO_GEAR_CH",
    "RADIO_FLAP_CH",
    "RADIO_AUX2_CH",
    "RADIO_AUX3_CH",
    "RADIO_AUX4_CH",
    "RADIO_AUX5_CH",
    "RADIO_AUX6_CH",
    "RADIO_AUX7_CH",
    "PPM_SCALER",
    "PPM_THROT_LOW",
    "PPM_CHAN_MID",
    "CTRL_PID_TYPE",
    "CTRL_FACT_THRO",
    "CTRL_FACT_PITC",
    "CTRL_FACT_ROLL",
    "CTRL_FACT_RUDD",
    "CTRL_DEAD_BAND",
    "CTRL_DBAND_THRO",
    "CTRL_MIN_THROT",
    "CTRL_MAX",
    "CTRL_NAV_YAW_RT",
    "CTRL_TLT_RTE_P",
    "CTRL_TLT_RTE_I",
    "CTRL_TLT_RTE_D",
    "CTRL_TLT_RTE_F",
    "CTRL_TLT_RTE_PM",
    "CTRL_TLT_RTE_IM",
    "CTRL_TLT_RTE_DM",
    "CTRL_TLT_RTE_OM",
    "CTRL_YAW_RTE_P",
    "CTRL_YAW_RTE_I",
    "CTRL_YAW_RTE_D",
    "CTRL_YAW_RTE_F",
    "CTRL_YAW_RTE_PM",
    "CTRL_YAW_RTE_IM",
    "CTRL_YAW_RTE_DM",
    "CTRL_YAW_RTE_OM",
    "CTRL_TLT_ANG_P",
    "CTRL_TLT_ANG_I",
    "CTRL_TLT_ANG_D",
    "CTRL_TLT_ANG_F",
    "CTRL_TLT_ANG_PM",
    "CTRL_TLT_ANG_IM",
    "CTRL_TLT_ANG_DM",
    "CTRL_TLT_ANG_OM",
    "CTRL_YAW_ANG_P",
    "CTRL_YAW_ANG_I",
    "CTRL_YAW_ANG_D",
    "CTRL_YAW_ANG_F",
    "CTRL_YAW_ANG_PM",
    "CTRL_YAW_ANG_IM",
    "CTRL_YAW_ANG_DM",
    "CTRL_YAW_ANG_OM",
    "GPS_BAUD_RATE",
    "GPS_RATE",
    "MOT_FRAME",
    "MOT_START",
    "MOT_MIN",
    "MOT_MAX",
    "MOT_HOV_THROT",
    "MOT_EXP_FACT",
    "MOT_EXP_MIN",
    "MOT_EXP_MAX",
    "MOT_PWRD_01_T",
    "MOT_PWRD_01_P",
    "MOT_PWRD_01_R",
    "MOT_PWRD_01_Y",
    "MOT_PWRD_02_T",
    "MOT_PWRD_02_P",
    "MOT_PWRD_02_R",
    "MOT_PWRD_02_Y",
    "MOT_PWRD_03_T",
    "MOT_PWRD_03_P",
    "MOT_PWRD_03_R",
    "MOT_PWRD_03_Y",
    "MOT_PWRD_04_T",
    "MOT_PWRD_04_P",
    "MOT_PWRD_04_R",
    "MOT_PWRD_04_Y",
    "MOT_PWRD_05_T",
    "MOT_PWRD_05_P",
    "MOT_PWRD_05_R",
    "MOT_PWRD_05_Y",
    "MOT_PWRD_06_T",
    "MOT_PWRD_06_P",
    "MOT_PWRD_06_R",
    "MOT_PWRD_06_Y",
    "MOT_PWRD_07_T",
    "MOT_PWRD_07_P",
    "MOT_PWRD_07_R",
    "MOT_PWRD_07_Y",
    "MOT_PWRD_08_T",
    "MOT_PWRD_08_P",
    "MOT_PWRD_08_R",
    "MOT_PWRD_08_Y",
    "MOT_PWRD_09_T",
    "MOT_PWRD_09_P",
    "MOT_PWRD_09_R",
    "MOT_PWRD_09_Y",
    "MOT_PWRD_10_T",
    "MOT_PWRD_10_P",
    "MOT_PWRD_10_R",
    "MOT_PWRD_10_Y",
    "MOT_PWRD_11_T",
    "MOT_PWRD_11_P",
    "MOT_PWRD_11_R",
    "MOT_PWRD_11_Y",
    "MOT_PWRD_12_T",
    "MOT_PWRD_12_P",
    "MOT_PWRD_12_R",
    "MOT_PWRD_12_Y",
    "MOT_PWRD_13_T",
    "MOT_PWRD_13_P",
    "MOT_PWRD_13_R",
    "MOT_PWRD_13_Y",
    "MOT_PWRD_14_T",
    "MOT_PWRD_14_P",
    "MOT_PWRD_14_R",
    "MOT_PWRD_14_Y",
    "DOWNLINK_BAUD",
    "TELEMETRY_RATE",
    "NAV_MAX_SPEED",
    "NAV_MAX_DECENT",
    "NAV_CEILING",
    "NAV_SPEED_P",
    "NAV_SPEED_I",
    "NAV_SPEED_PM",
    "NAV_SPEED_IM",
    "NAV_SPEED_OM",
    "NAV_DIST_P",
    "NAV_DIST_I",
    "NAV_DIST_PM",
    "NAV_DIST_IM",
    "NAV_DIST_OM",
    "NAV_ATL_SPED_P",
    "NAV_ATL_SPED_I",
    "NAV_ATL_SPED_PM",
    "NAV_ATL_SPED_IM",
    "NAV_ATL_SPED_OM",
    "NAV_ALT_POS_P",
    "NAV_ALT_POS_I",
    "NAV_ALT_POS_PM",
    "NAV_ALT_POS_IM",
    "NAV_ALT_POS_OM",
    "IMU_ROT",
    "IMU_ACC_BIAS_X",
    "IMU_ACC_BIAS_Y",
    "IMU_ACC_BIAS_Z",
    "IMU_ACC_BIAS1_X",
    "IMU_ACC_BIAS1_Y",
    "IMU_ACC_BIAS1_Z",
    "IMU_ACC_BIAS2_X",
    "IMU_ACC_BIAS2_Y",
    "IMU_ACC_BIAS2_Z",
    "IMU_ACC_BIAS3_X",
    "IMU_ACC_BIAS3_Y",
    "IMU_ACC_BIAS3_Z",
    "IMU_ACC_SCAL_X",
    "IMU_ACC_SCAL_Y",
    "IMU_ACC_SCAL_Z",
    "IMU_ACC_SCAL1_X",
    "IMU_ACC_SCAL1_Y",
    "IMU_ACC_SCAL1_Z",
    "IMU_ACC_SCAL2_X",
    "IMU_ACC_SCAL2_Y",
    "IMU_ACC_SCAL2_Z",
    "IMU_ACC_SCAL3_X",
    "IMU_ACC_SCAL3_Y",
    "IMU_ACC_SCAL3_Z",
    "IMU_ACC_ALGN_XY",
    "IMU_ACC_ALGN_XZ",
    "IMU_ACC_ALGN_YX",
    "IMU_ACC_ALGN_YZ",
    "IMU_ACC_ALGN_ZX",
    "IMU_ACC_ALGN_ZY",
    "IMU_MAG_BIAS_X",
    "IMU_MAG_BIAS_Y",
    "IMU_MAG_BIAS_Z",
    "IMU_MAG_BIAS1_X",
    "IMU_MAG_BIAS1_Y",
    "IMU_MAG_BIAS1_Z",
    "IMU_MAG_BIAS2_X",
    "IMU_MAG_BIAS2_Y",
    "IMU_MAG_BIAS2_Z",
    "IMU_MAG_BIAS3_X",
    "IMU_MAG_BIAS3_Y",
    "IMU_MAG_BIAS3_Z",
    "IMU_MAG_SCAL_X",
    "IMU_MAG_SCAL_Y",
    "IMU_MAG_SCAL_Z",
    "IMU_MAG_SCAL1_X",
    "IMU_MAG_SCAL1_Y",
    "IMU_MAG_SCAL1_Z",
    "IMU_MAG_SCAL2_X",
    "IMU_MAG_SCAL2_Y",
    "IMU_MAG_SCAL2_Z",
    "IMU_MAG_SCAL3_X",
    "IMU_MAG_SCAL3_Y",
    "IMU_MAG_SCAL3_Z",
    "IMU_MAG_ALGN_XY",
    "IMU_MAG_ALGN_XZ",
    "IMU_MAG_ALGN_YX",
    "IMU_MAG_ALGN_YZ",
    "IMU_MAG_ALGN_ZX",
    "IMU_MAG_ALGN_ZY",
    "IMU_GYO_BIAS_X",
    "IMU_GYO_BIAS_Y",
    "IMU_GYO_BIAS_Z",
    "IMU_GYO_BIAS1_X",
    "IMU_GYO_BIAS1_Y",
    "IMU_GYO_BIAS1_Z",
    "IMU_GYO_BIAS2_X",
    "IMU_GYO_BIAS2_Y",
    "IMU_GYO_BIAS2_Z",
    "IMU_GYO_BIAS3_X",
    "IMU_GYO_BIAS3_Y",
    "IMU_GYO_BIAS3_Z",
    "IMU_GYO_SCAL_X",
    "IMU_GYO_SCAL_Y",
    "IMU_GYO_SCAL_Z",
    "IMU_GYO_ALGN_XY",
    "IMU_GYO_ALGN_XZ",
    "IMU_GYO_ALGN_YX",
    "IMU_GYO_ALGN_YZ",
    "IMU_GYO_ALGN_ZX",
    "IMU_GYO_ALGN_ZY",
    "IMU_MAG_INCL",
    "IMU_MAG_DECL",
    "IMU_PRESS_SENSE",
    "GMBL_PITCH_PORT",
    "GMBL_ROLL_PORT",
    "GMBL_PWM_MAX_RL",
    "GMBL_PWM_MIN_RL",
    "GMBL_PWM_MAX_PT",
    "GMBL_PWM_MIN_PT",
    "GMBL_PWM_FREQ",
    "GMBL_NTRL_PITCH",
    "GMBL_NTRL_ROLL",
    "GMBL_SCAL_PITCH",
    "GMBL_SCAL_ROLL",
    "GMBL_SLEW_RATE",
    "GMBL_ROLL_EXPO",
    "SPVR_LOW_BAT1",
    "SPVR_LOW_BAT2",
    "SPVR_BAT_CRV1",
    "SPVR_BAT_CRV2",
    "SPVR_BAT_CRV3",
    "SPVR_BAT_CRV4",
    "SPVR_BAT_CRV5",
    "SPVR_BAT_CRV6",
    "SPVR_FS_RAD_ST1",
    "SPVR_FS_RAD_ST2",
    "UKF_VEL_Q",
    "UKF_VEL_ALT_Q",
    "UKF_POS_Q",
    "UKF_POS_ALT_Q",
    "UKF_ACC_BIAS_Q",
    "UKF_GYO_BIAS_Q",
    "UKF_QUAT_Q",
    "UKF_PRES_ALT_Q",
    "UKF_ACC_BIAS_V",
    "UKF_GYO_BIAS_V",
    "UKF_RATE_V",
    "UKF_PRES_ALT_V",
    "UKF_POS_V",
    "UKF_VEL_V",
    "UKF_ALT_POS_V",
    "UKF_ALT_VEL_V",
    "UKF_GPS_POS_N",
    "UKF_GPS_POS_M_N",
    "UKF_GPS_ALT_N",
    "UKF_GPS_ALT_M_N",
    "UKF_GPS_VEL_N",
    "UKF_GPS_VEL_M_N",
    "UKF_GPS_VD_N",
    "UKF_GPS_VD_M_N",
    "UKF_ALT_N",
    "UKF_ACC_N",
    "UKF_DIST_N",
    "UKF_MAG_N",
    "UKF_POS_DELAY",
    "UKF_VEL_DELAY",
    "VN100_MAG_BIAS_X",
    "VN100_MAG_BIAS_Y",
    "VN100_MAG_BIAS_Z",
    "VN100_MAG_SCAL_X",
    "VN100_MAG_SCAL_Y",
    "VN100_MAG_SCAL_Z",
    "VN100_MAG_ALGN_XY",
    "VN100_MAG_ALGN_XZ",
    "VN100_MAG_ALGN_YX",
    "VN100_MAG_ALGN_YZ",
    "VN100_MAG_ALGN_ZX",
    "VN100_MAG_ALGN_ZY",
    "L1_ATT_J_ROLL",
    "L1_ATT_J_PITCH",
    "L1_ATT_J_YAW",
    "L1_ATT_AM1",
    "L1_ATT_AM2",
    "L1_ATT_T2R_A1",
    "L1_ATT_T2R_A2",
    "L1_ATT_PROP_K1",
    "L1_ATT_M_TLT_RT",
    "L1_ATT_M_YAW_RT",
    "L1_ATT_MAX_OUT",
    "L1_ATT_QUAT_TAU",
    "L1_ATT_L1_ASP",
    "L1_ATT_L1_K1",
    "L1_ATT_PWM_LO",
    "L1_ATT_PWM_HI",
    "L1_ATT_PWM_SCALE",
    "L1_ATT_AM1_KNOB",
    "L1_ATT_AM2_KNOB",
    "L1_ATT_K1_KNOB",
    "L1_ATT_PT_KNOB",
    "L1_ATT_MM_R01",
    "L1_ATT_MM_P01",
    "L1_ATT_MM_Y01",
    "L1_ATT_MM_R02",
    "L1_ATT_MM_P02",
    "L1_ATT_MM_Y02",
    "L1_ATT_MM_R03",
    "L1_ATT_MM_P03",
    "L1_ATT_MM_Y03",
    "L1_ATT_MM_R04",
    "L1_ATT_MM_P04",
    "L1_ATT_MM_Y04",
    "L1_ATT_MM_R05",
    "L1_ATT_MM_P05",
    "L1_ATT_MM_Y05",
    "L1_ATT_MM_R06",
    "L1_ATT_MM_P06",
    "L1_ATT_MM_Y06",
    "L1_ATT_MM_R07",
    "L1_ATT_MM_P07",
    "L1_ATT_MM_Y07",
    "L1_ATT_MM_R08",
    "L1_ATT_MM_P08",
    "L1_ATT_MM_Y08",
    "L1_ATT_MM_R09",
    "L1_ATT_MM_P09",
    "L1_ATT_MM_Y09",
    "L1_ATT_MM_R10",
    "L1_ATT_MM_P10",
    "L1_ATT_MM_Y10",
    "L1_ATT_MM_R11",
    "L1_ATT_MM_P11",
    "L1_ATT_MM_Y11",
    "L1_ATT_MM_R12",
    "L1_ATT_MM_P12",
    "L1_ATT_MM_Y12",
    "L1_ATT_MM_R13",
    "L1_ATT_MM_P13",
    "L1_ATT_MM_Y13",
    "L1_ATT_MM_R14",
    "L1_ATT_MM_P14",
    "L1_ATT_MM_Y14"
};

void configLoadDefault(void) {
    p[CONFIG_VERSION] = DEFAULT_CONFIG_VERSION;
    p[RADIO_TYPE] = DEFAULT_RADIO_TYPE;
    p[RADIO_THRO_CH] = DEFAULT_RADIO_THRO_CH;
    p[RADIO_ROLL_CH] = DEFAULT_RADIO_ROLL_CH;
    p[RADIO_PITC_CH] = DEFAULT_RADIO_PITC_CH;
    p[RADIO_RUDD_CH] = DEFAULT_RADIO_RUDD_CH;
    p[RADIO_GEAR_CH] = DEFAULT_RADIO_GEAR_CH;
    p[RADIO_FLAP_CH] = DEFAULT_RADIO_FLAP_CH;
    p[RADIO_AUX2_CH] = DEFAULT_RADIO_AUX2_CH;
    p[RADIO_AUX3_CH] = DEFAULT_RADIO_AUX3_CH;
    p[RADIO_AUX4_CH] = DEFAULT_RADIO_AUX4_CH;
    p[RADIO_AUX5_CH] = DEFAULT_RADIO_AUX5_CH;
    p[RADIO_AUX6_CH] = DEFAULT_RADIO_AUX6_CH;
    p[RADIO_AUX7_CH] = DEFAULT_RADIO_AUX7_CH;
    p[PPM_SCALER] = DEFAULT_PPM_SCALER;
    p[PPM_THROT_LOW] = DEFAULT_PPM_THROT_LOW;
    p[PPM_CHAN_MID] = DEFAULT_PPM_CHAN_MID;
    p[CTRL_PID_TYPE] = DEFAULT_CTRL_PID_TYPE;
    p[CTRL_FACT_THRO] = DEFAULT_CTRL_FACT_THRO;
    p[CTRL_FACT_PITC] = DEFAULT_CTRL_FACT_PITC;
    p[CTRL_FACT_ROLL] = DEFAULT_CTRL_FACT_ROLL;
    p[CTRL_FACT_RUDD] = DEFAULT_CTRL_FACT_RUDD;
    p[CTRL_DEAD_BAND] = DEFAULT_CTRL_DEAD_BAND;
    p[CTRL_DBAND_THRO] = DEFAULT_CTRL_DBAND_THRO;
    p[CTRL_MIN_THROT] = DEFAULT_CTRL_MIN_THROT;
    p[CTRL_MAX] = DEFAULT_CTRL_MAX;
    p[CTRL_NAV_YAW_RT] = DEFAULT_CTRL_NAV_YAW_RT;
    p[CTRL_TLT_RTE_P] = DEFAULT_CTRL_TLT_RTE_P;
    p[CTRL_TLT_RTE_I] = DEFAULT_CTRL_TLT_RTE_I;
    p[CTRL_TLT_RTE_D] = DEFAULT_CTRL_TLT_RTE_D;
    p[CTRL_TLT_RTE_F] = DEFAULT_CTRL_TLT_RTE_F;
    p[CTRL_TLT_RTE_PM] = DEFAULT_CTRL_TLT_RTE_PM;
    p[CTRL_TLT_RTE_IM] = DEFAULT_CTRL_TLT_RTE_IM;
    p[CTRL_TLT_RTE_DM] = DEFAULT_CTRL_TLT_RTE_DM;
    p[CTRL_TLT_RTE_OM] = DEFAULT_CTRL_TLT_RTE_OM;
    p[CTRL_YAW_RTE_P] = DEFAULT_CTRL_YAW_RTE_P;
    p[CTRL_YAW_RTE_I] = DEFAULT_CTRL_YAW_RTE_I;
    p[CTRL_YAW_RTE_D] = DEFAULT_CTRL_YAW_RTE_D;
    p[CTRL_YAW_RTE_F] = DEFAULT_CTRL_YAW_RTE_F;
    p[CTRL_YAW_RTE_PM] = DEFAULT_CTRL_YAW_RTE_PM;
    p[CTRL_YAW_RTE_IM] = DEFAULT_CTRL_YAW_RTE_IM;
    p[CTRL_YAW_RTE_DM] = DEFAULT_CTRL_YAW_RTE_DM;
    p[CTRL_YAW_RTE_OM] = DEFAULT_CTRL_YAW_RTE_OM;
    p[CTRL_TLT_ANG_P] = DEFAULT_CTRL_TLT_ANG_P;
    p[CTRL_TLT_ANG_I] = DEFAULT_CTRL_TLT_ANG_I;
    p[CTRL_TLT_ANG_D] = DEFAULT_CTRL_TLT_ANG_D;
    p[CTRL_TLT_ANG_F] = DEFAULT_CTRL_TLT_ANG_F;
    p[CTRL_TLT_ANG_PM] = DEFAULT_CTRL_TLT_ANG_PM;
    p[CTRL_TLT_ANG_IM] = DEFAULT_CTRL_TLT_ANG_IM;
    p[CTRL_TLT_ANG_DM] = DEFAULT_CTRL_TLT_ANG_DM;
    p[CTRL_TLT_ANG_OM] = DEFAULT_CTRL_TLT_ANG_OM;
    p[CTRL_YAW_ANG_P] = DEFAULT_CTRL_YAW_ANG_P;
    p[CTRL_YAW_ANG_I] = DEFAULT_CTRL_YAW_ANG_I;
    p[CTRL_YAW_ANG_D] = DEFAULT_CTRL_YAW_ANG_D;
    p[CTRL_YAW_ANG_F] = DEFAULT_CTRL_YAW_ANG_F;
    p[CTRL_YAW_ANG_PM] = DEFAULT_CTRL_YAW_ANG_PM;
    p[CTRL_YAW_ANG_IM] = DEFAULT_CTRL_YAW_ANG_IM;
    p[CTRL_YAW_ANG_DM] = DEFAULT_CTRL_YAW_ANG_DM;
    p[CTRL_YAW_ANG_OM] = DEFAULT_CTRL_YAW_ANG_OM;
    p[GPS_BAUD_RATE] = DEFAULT_GPS_BAUD_RATE;
    p[GPS_RATE] = DEFAULT_GPS_RATE;
    p[MOT_FRAME] = DEFAULT_MOT_FRAME;
    p[MOT_START] = DEFAULT_MOT_START;
    p[MOT_MIN] = DEFAULT_MOT_MIN;
    p[MOT_MAX] = DEFAULT_MOT_MAX;
    p[MOT_HOV_THROT] = DEFAULT_MOT_HOV_THROT;
    p[MOT_EXP_FACT] = DEFAULT_MOT_EXP_FACT;
    p[MOT_EXP_MIN] = DEFAULT_MOT_EXP_MIN;
    p[MOT_EXP_MAX] = DEFAULT_MOT_EXP_MAX;
    p[MOT_PWRD_01_T] = DEFAULT_MOT_PWRD_01_T;
    p[MOT_PWRD_01_P] = DEFAULT_MOT_PWRD_01_P;
    p[MOT_PWRD_01_R] = DEFAULT_MOT_PWRD_01_R;
    p[MOT_PWRD_01_Y] = DEFAULT_MOT_PWRD_01_Y;
    p[MOT_PWRD_02_T] = DEFAULT_MOT_PWRD_02_T;
    p[MOT_PWRD_02_P] = DEFAULT_MOT_PWRD_02_P;
    p[MOT_PWRD_02_R] = DEFAULT_MOT_PWRD_02_R;
    p[MOT_PWRD_02_Y] = DEFAULT_MOT_PWRD_02_Y;
    p[MOT_PWRD_03_T] = DEFAULT_MOT_PWRD_03_T;
    p[MOT_PWRD_03_P] = DEFAULT_MOT_PWRD_03_P;
    p[MOT_PWRD_03_R] = DEFAULT_MOT_PWRD_03_R;
    p[MOT_PWRD_03_Y] = DEFAULT_MOT_PWRD_03_Y;
    p[MOT_PWRD_04_T] = DEFAULT_MOT_PWRD_04_T;
    p[MOT_PWRD_04_P] = DEFAULT_MOT_PWRD_04_P;
    p[MOT_PWRD_04_R] = DEFAULT_MOT_PWRD_04_R;
    p[MOT_PWRD_04_Y] = DEFAULT_MOT_PWRD_04_Y;
    p[MOT_PWRD_05_T] = DEFAULT_MOT_PWRD_05_T;
    p[MOT_PWRD_05_P] = DEFAULT_MOT_PWRD_05_P;
    p[MOT_PWRD_05_R] = DEFAULT_MOT_PWRD_05_R;
    p[MOT_PWRD_05_Y] = DEFAULT_MOT_PWRD_05_Y;
    p[MOT_PWRD_06_T] = DEFAULT_MOT_PWRD_06_T;
    p[MOT_PWRD_06_P] = DEFAULT_MOT_PWRD_06_P;
    p[MOT_PWRD_06_R] = DEFAULT_MOT_PWRD_06_R;
    p[MOT_PWRD_06_Y] = DEFAULT_MOT_PWRD_06_Y;
    p[MOT_PWRD_07_T] = DEFAULT_MOT_PWRD_07_T;
    p[MOT_PWRD_07_P] = DEFAULT_MOT_PWRD_07_P;
    p[MOT_PWRD_07_R] = DEFAULT_MOT_PWRD_07_R;
    p[MOT_PWRD_07_Y] = DEFAULT_MOT_PWRD_07_Y;
    p[MOT_PWRD_08_T] = DEFAULT_MOT_PWRD_08_T;
    p[MOT_PWRD_08_P] = DEFAULT_MOT_PWRD_08_P;
    p[MOT_PWRD_08_R] = DEFAULT_MOT_PWRD_08_R;
    p[MOT_PWRD_08_Y] = DEFAULT_MOT_PWRD_08_Y;
    p[MOT_PWRD_09_T] = DEFAULT_MOT_PWRD_09_T;
    p[MOT_PWRD_09_P] = DEFAULT_MOT_PWRD_09_P;
    p[MOT_PWRD_09_R] = DEFAULT_MOT_PWRD_09_R;
    p[MOT_PWRD_09_Y] = DEFAULT_MOT_PWRD_09_Y;
    p[MOT_PWRD_10_T] = DEFAULT_MOT_PWRD_10_T;
    p[MOT_PWRD_10_P] = DEFAULT_MOT_PWRD_10_P;
    p[MOT_PWRD_10_R] = DEFAULT_MOT_PWRD_10_R;
    p[MOT_PWRD_10_Y] = DEFAULT_MOT_PWRD_10_Y;
    p[MOT_PWRD_11_T] = DEFAULT_MOT_PWRD_11_T;
    p[MOT_PWRD_11_P] = DEFAULT_MOT_PWRD_11_P;
    p[MOT_PWRD_11_R] = DEFAULT_MOT_PWRD_11_R;
    p[MOT_PWRD_11_Y] = DEFAULT_MOT_PWRD_11_Y;
    p[MOT_PWRD_12_T] = DEFAULT_MOT_PWRD_12_T;
    p[MOT_PWRD_12_P] = DEFAULT_MOT_PWRD_12_P;
    p[MOT_PWRD_12_R] = DEFAULT_MOT_PWRD_12_R;
    p[MOT_PWRD_12_Y] = DEFAULT_MOT_PWRD_12_Y;
    p[MOT_PWRD_13_T] = DEFAULT_MOT_PWRD_13_T;
    p[MOT_PWRD_13_P] = DEFAULT_MOT_PWRD_13_P;
    p[MOT_PWRD_13_R] = DEFAULT_MOT_PWRD_13_R;
    p[MOT_PWRD_13_Y] = DEFAULT_MOT_PWRD_13_Y;
    p[MOT_PWRD_14_T] = DEFAULT_MOT_PWRD_14_T;
    p[MOT_PWRD_14_P] = DEFAULT_MOT_PWRD_14_P;
    p[MOT_PWRD_14_R] = DEFAULT_MOT_PWRD_14_R;
    p[MOT_PWRD_14_Y] = DEFAULT_MOT_PWRD_14_Y;
    p[DOWNLINK_BAUD] = DEFAULT_DOWNLINK_BAUD;
    p[TELEMETRY_RATE] = DEFAULT_TELEMETRY_RATE;
    p[NAV_MAX_SPEED] = DEFAULT_NAV_MAX_SPEED;
    p[NAV_MAX_DECENT] = DEFAULT_NAV_MAX_DECENT;
    p[NAV_CEILING] = DEFAULT_NAV_CEILING;
    p[NAV_SPEED_P] = DEFAULT_NAV_SPEED_P;
    p[NAV_SPEED_I] = DEFAULT_NAV_SPEED_I;
    p[NAV_SPEED_PM] = DEFAULT_NAV_SPEED_PM;
    p[NAV_SPEED_IM] = DEFAULT_NAV_SPEED_IM;
    p[NAV_SPEED_OM] = DEFAULT_NAV_SPEED_OM;
    p[NAV_DIST_P] = DEFAULT_NAV_DIST_P;
    p[NAV_DIST_I] = DEFAULT_NAV_DIST_I;
    p[NAV_DIST_PM] = DEFAULT_NAV_DIST_PM;
    p[NAV_DIST_IM] = DEFAULT_NAV_DIST_IM;
    p[NAV_DIST_OM] = DEFAULT_NAV_DIST_OM;
    p[NAV_ATL_SPED_P] = DEFAULT_NAV_ATL_SPED_P;
    p[NAV_ATL_SPED_I] = DEFAULT_NAV_ATL_SPED_I;
    p[NAV_ATL_SPED_PM] = DEFAULT_NAV_ATL_SPED_PM;
    p[NAV_ATL_SPED_IM] = DEFAULT_NAV_ATL_SPED_IM;
    p[NAV_ATL_SPED_OM] = DEFAULT_NAV_ATL_SPED_OM;
    p[NAV_ALT_POS_P] = DEFAULT_NAV_ALT_POS_P;
    p[NAV_ALT_POS_I] = DEFAULT_NAV_ALT_POS_I;
    p[NAV_ALT_POS_PM] = DEFAULT_NAV_ALT_POS_PM;
    p[NAV_ALT_POS_IM] = DEFAULT_NAV_ALT_POS_IM;
    p[NAV_ALT_POS_OM] = DEFAULT_NAV_ALT_POS_OM;
    p[IMU_ROT] = DEFAULT_IMU_ROT;
    p[IMU_ACC_BIAS_X] = DEFAULT_IMU_ACC_BIAS_X;
    p[IMU_ACC_BIAS_Y] = DEFAULT_IMU_ACC_BIAS_Y;
    p[IMU_ACC_BIAS_Z] = DEFAULT_IMU_ACC_BIAS_Z;
    p[IMU_ACC_BIAS1_X] = DEFAULT_IMU_ACC_BIAS1_X;
    p[IMU_ACC_BIAS1_Y] = DEFAULT_IMU_ACC_BIAS1_Y;
    p[IMU_ACC_BIAS1_Z] = DEFAULT_IMU_ACC_BIAS1_Z;
    p[IMU_ACC_BIAS2_X] = DEFAULT_IMU_ACC_BIAS2_X;
    p[IMU_ACC_BIAS2_Y] = DEFAULT_IMU_ACC_BIAS2_Y;
    p[IMU_ACC_BIAS2_Z] = DEFAULT_IMU_ACC_BIAS2_Z;
    p[IMU_ACC_BIAS3_X] = DEFAULT_IMU_ACC_BIAS3_X;
    p[IMU_ACC_BIAS3_Y] = DEFAULT_IMU_ACC_BIAS3_Y;
    p[IMU_ACC_BIAS3_Z] = DEFAULT_IMU_ACC_BIAS3_Z;
    p[IMU_ACC_SCAL_X] = DEFAULT_IMU_ACC_SCAL_X;
    p[IMU_ACC_SCAL_Y] = DEFAULT_IMU_ACC_SCAL_Y;
    p[IMU_ACC_SCAL_Z] = DEFAULT_IMU_ACC_SCAL_Z;
    p[IMU_ACC_SCAL1_X] = DEFAULT_IMU_ACC_SCAL1_X;
    p[IMU_ACC_SCAL1_Y] = DEFAULT_IMU_ACC_SCAL1_Y;
    p[IMU_ACC_SCAL1_Z] = DEFAULT_IMU_ACC_SCAL1_Z;
    p[IMU_ACC_SCAL2_X] = DEFAULT_IMU_ACC_SCAL2_X;
    p[IMU_ACC_SCAL2_Y] = DEFAULT_IMU_ACC_SCAL2_Y;
    p[IMU_ACC_SCAL2_Z] = DEFAULT_IMU_ACC_SCAL2_Z;
    p[IMU_ACC_SCAL3_X] = DEFAULT_IMU_ACC_SCAL3_X;
    p[IMU_ACC_SCAL3_Y] = DEFAULT_IMU_ACC_SCAL3_Y;
    p[IMU_ACC_SCAL3_Z] = DEFAULT_IMU_ACC_SCAL3_Z;
    p[IMU_ACC_ALGN_XY] = DEFAULT_IMU_ACC_ALGN_XY;
    p[IMU_ACC_ALGN_XZ] = DEFAULT_IMU_ACC_ALGN_XZ;
    p[IMU_ACC_ALGN_YX] = DEFAULT_IMU_ACC_ALGN_YX;
    p[IMU_ACC_ALGN_YZ] = DEFAULT_IMU_ACC_ALGN_YZ;
    p[IMU_ACC_ALGN_ZX] = DEFAULT_IMU_ACC_ALGN_ZX;
    p[IMU_ACC_ALGN_ZY] = DEFAULT_IMU_ACC_ALGN_ZY;
    p[IMU_MAG_BIAS_X] = DEFAULT_IMU_MAG_BIAS_X;
    p[IMU_MAG_BIAS_Y] = DEFAULT_IMU_MAG_BIAS_Y;
    p[IMU_MAG_BIAS_Z] = DEFAULT_IMU_MAG_BIAS_Z;
    p[IMU_MAG_BIAS1_X] = DEFAULT_IMU_MAG_BIAS1_X;
    p[IMU_MAG_BIAS1_Y] = DEFAULT_IMU_MAG_BIAS1_Y;
    p[IMU_MAG_BIAS1_Z] = DEFAULT_IMU_MAG_BIAS1_Z;
    p[IMU_MAG_BIAS2_X] = DEFAULT_IMU_MAG_BIAS2_X;
    p[IMU_MAG_BIAS2_Y] = DEFAULT_IMU_MAG_BIAS2_Y;
    p[IMU_MAG_BIAS2_Z] = DEFAULT_IMU_MAG_BIAS2_Z;
    p[IMU_MAG_BIAS3_X] = DEFAULT_IMU_MAG_BIAS3_X;
    p[IMU_MAG_BIAS3_Y] = DEFAULT_IMU_MAG_BIAS3_Y;
    p[IMU_MAG_BIAS3_Z] = DEFAULT_IMU_MAG_BIAS3_Z;
    p[IMU_MAG_SCAL_X] = DEFAULT_IMU_MAG_SCAL_X;
    p[IMU_MAG_SCAL_Y] = DEFAULT_IMU_MAG_SCAL_Y;
    p[IMU_MAG_SCAL_Z] = DEFAULT_IMU_MAG_SCAL_Z;
    p[IMU_MAG_SCAL1_X] = DEFAULT_IMU_MAG_SCAL1_X;
    p[IMU_MAG_SCAL1_Y] = DEFAULT_IMU_MAG_SCAL1_Y;
    p[IMU_MAG_SCAL1_Z] = DEFAULT_IMU_MAG_SCAL1_Z;
    p[IMU_MAG_SCAL2_X] = DEFAULT_IMU_MAG_SCAL2_X;
    p[IMU_MAG_SCAL2_Y] = DEFAULT_IMU_MAG_SCAL2_Y;
    p[IMU_MAG_SCAL2_Z] = DEFAULT_IMU_MAG_SCAL2_Z;
    p[IMU_MAG_SCAL3_X] = DEFAULT_IMU_MAG_SCAL3_X;
    p[IMU_MAG_SCAL3_Y] = DEFAULT_IMU_MAG_SCAL3_Y;
    p[IMU_MAG_SCAL3_Z] = DEFAULT_IMU_MAG_SCAL3_Z;
    p[IMU_MAG_ALGN_XY] = DEFAULT_IMU_MAG_ALGN_XY;
    p[IMU_MAG_ALGN_XZ] = DEFAULT_IMU_MAG_ALGN_XZ;
    p[IMU_MAG_ALGN_YX] = DEFAULT_IMU_MAG_ALGN_YX;
    p[IMU_MAG_ALGN_YZ] = DEFAULT_IMU_MAG_ALGN_YZ;
    p[IMU_MAG_ALGN_ZX] = DEFAULT_IMU_MAG_ALGN_ZX;
    p[IMU_MAG_ALGN_ZY] = DEFAULT_IMU_MAG_ALGN_ZY;
    p[IMU_GYO_BIAS_X] = DEFAULT_IMU_GYO_BIAS_X;
    p[IMU_GYO_BIAS_Y] = DEFAULT_IMU_GYO_BIAS_Y;
    p[IMU_GYO_BIAS_Z] = DEFAULT_IMU_GYO_BIAS_Z;
    p[IMU_GYO_BIAS1_X] = DEFAULT_IMU_GYO_BIAS1_X;
    p[IMU_GYO_BIAS1_Y] = DEFAULT_IMU_GYO_BIAS1_Y;
    p[IMU_GYO_BIAS1_Z] = DEFAULT_IMU_GYO_BIAS1_Z;
    p[IMU_GYO_BIAS2_X] = DEFAULT_IMU_GYO_BIAS2_X;
    p[IMU_GYO_BIAS2_Y] = DEFAULT_IMU_GYO_BIAS2_Y;
    p[IMU_GYO_BIAS2_Z] = DEFAULT_IMU_GYO_BIAS2_Z;
    p[IMU_GYO_BIAS3_X] = DEFAULT_IMU_GYO_BIAS3_X;
    p[IMU_GYO_BIAS3_Y] = DEFAULT_IMU_GYO_BIAS3_Y;
    p[IMU_GYO_BIAS3_Z] = DEFAULT_IMU_GYO_BIAS3_Z;
    p[IMU_GYO_SCAL_X] = DEFAULT_IMU_GYO_SCAL_X;
    p[IMU_GYO_SCAL_Y] = DEFAULT_IMU_GYO_SCAL_Y;
    p[IMU_GYO_SCAL_Z] = DEFAULT_IMU_GYO_SCAL_Z;
    p[IMU_GYO_ALGN_XY] = DEFAULT_IMU_GYO_ALGN_XY;
    p[IMU_GYO_ALGN_XZ] = DEFAULT_IMU_GYO_ALGN_XZ;
    p[IMU_GYO_ALGN_YX] = DEFAULT_IMU_GYO_ALGN_YX;
    p[IMU_GYO_ALGN_YZ] = DEFAULT_IMU_GYO_ALGN_YZ;
    p[IMU_GYO_ALGN_ZX] = DEFAULT_IMU_GYO_ALGN_ZX;
    p[IMU_GYO_ALGN_ZY] = DEFAULT_IMU_GYO_ALGN_ZY;
    p[IMU_MAG_INCL] = DEFAULT_IMU_MAG_INCL;
    p[IMU_MAG_DECL] = DEFAULT_IMU_MAG_DECL;
    p[IMU_PRESS_SENSE] = DEFAULT_IMU_PRESS_SENSE;
    p[GMBL_PITCH_PORT] = DEFAULT_GMBL_PITCH_PORT;
    p[GMBL_ROLL_PORT] = DEFAULT_GMBL_ROLL_PORT;
    p[GMBL_PWM_MAX_RL] = DEFAULT_GMBL_PWM_MAX_RL;
    p[GMBL_PWM_MIN_RL] = DEFAULT_GMBL_PWM_MIN_RL;
    p[GMBL_PWM_MAX_PT] = DEFAULT_GMBL_PWM_MAX_PT;
    p[GMBL_PWM_MIN_PT] = DEFAULT_GMBL_PWM_MIN_PT;
    p[GMBL_PWM_FREQ] = DEFAULT_GMBL_PWM_FREQ;
    p[GMBL_NTRL_PITCH] = DEFAULT_GMBL_NTRL_PITCH;
    p[GMBL_NTRL_ROLL] = DEFAULT_GMBL_NTRL_ROLL;
    p[GMBL_SCAL_PITCH] = DEFAULT_GMBL_SCAL_PITCH;
    p[GMBL_SCAL_ROLL] = DEFAULT_GMBL_SCAL_ROLL;
    p[GMBL_SLEW_RATE] = DEFAULT_GMBL_SLEW_RATE;
    p[GMBL_ROLL_EXPO] = DEFAULT_GMBL_ROLL_EXPO;
    p[SPVR_LOW_BAT1] = DEFAULT_SPVR_LOW_BAT1;
    p[SPVR_LOW_BAT2] = DEFAULT_SPVR_LOW_BAT2;
    p[SPVR_BAT_CRV1] = DEFAULT_SPVR_BAT_CRV1;
    p[SPVR_BAT_CRV2] = DEFAULT_SPVR_BAT_CRV2;
    p[SPVR_BAT_CRV3] = DEFAULT_SPVR_BAT_CRV3;
    p[SPVR_BAT_CRV4] = DEFAULT_SPVR_BAT_CRV4;
    p[SPVR_BAT_CRV5] = DEFAULT_SPVR_BAT_CRV5;
    p[SPVR_BAT_CRV6] = DEFAULT_SPVR_BAT_CRV6;
    p[SPVR_FS_RAD_ST1] = DEFAULT_SPVR_FS_RAD_ST1;
    p[SPVR_FS_RAD_ST2] = DEFAULT_SPVR_FS_RAD_ST2;
    p[UKF_VEL_Q] = DEFAULT_UKF_VEL_Q;
    p[UKF_VEL_ALT_Q] = DEFAULT_UKF_VEL_ALT_Q;
    p[UKF_POS_Q] = DEFAULT_UKF_POS_Q;
    p[UKF_POS_ALT_Q] = DEFAULT_UKF_POS_ALT_Q;
    p[UKF_ACC_BIAS_Q] = DEFAULT_UKF_ACC_BIAS_Q;
    p[UKF_GYO_BIAS_Q] = DEFAULT_UKF_GYO_BIAS_Q;
    p[UKF_QUAT_Q] = DEFAULT_UKF_QUAT_Q;
    p[UKF_PRES_ALT_Q] = DEFAULT_UKF_PRES_ALT_Q;
    p[UKF_ACC_BIAS_V] = DEFAULT_UKF_ACC_BIAS_V;
    p[UKF_GYO_BIAS_V] = DEFAULT_UKF_GYO_BIAS_V;
    p[UKF_RATE_V] = DEFAULT_UKF_RATE_V;
    p[UKF_PRES_ALT_V] = DEFAULT_UKF_PRES_ALT_V;
    p[UKF_POS_V] = DEFAULT_UKF_POS_V;
    p[UKF_VEL_V] = DEFAULT_UKF_VEL_V;
    p[UKF_ALT_POS_V] = DEFAULT_UKF_ALT_POS_V;
    p[UKF_ALT_VEL_V] = DEFAULT_UKF_ALT_VEL_V;
    p[UKF_GPS_POS_N] = DEFAULT_UKF_GPS_POS_N;
    p[UKF_GPS_POS_M_N] = DEFAULT_UKF_GPS_POS_M_N;
    p[UKF_GPS_ALT_N] = DEFAULT_UKF_GPS_ALT_N;
    p[UKF_GPS_ALT_M_N] = DEFAULT_UKF_GPS_ALT_M_N;
    p[UKF_GPS_VEL_N] = DEFAULT_UKF_GPS_VEL_N;
    p[UKF_GPS_VEL_M_N] = DEFAULT_UKF_GPS_VEL_M_N;
    p[UKF_GPS_VD_N] = DEFAULT_UKF_GPS_VD_N;
    p[UKF_GPS_VD_M_N] = DEFAULT_UKF_GPS_VD_M_N;
    p[UKF_ALT_N] = DEFAULT_UKF_ALT_N;
    p[UKF_ACC_N] = DEFAULT_UKF_ACC_N;
    p[UKF_DIST_N] = DEFAULT_UKF_DIST_N;
    p[UKF_MAG_N] = DEFAULT_UKF_MAG_N;
    p[UKF_POS_DELAY] = DEFAULT_UKF_POS_DELAY;
    p[UKF_VEL_DELAY] = DEFAULT_UKF_VEL_DELAY;
    p[VN100_MAG_BIAS_X] = DEFAULT_VN100_MAG_BIAS_X;
    p[VN100_MAG_BIAS_Y] = DEFAULT_VN100_MAG_BIAS_Y;
    p[VN100_MAG_BIAS_Z] = DEFAULT_VN100_MAG_BIAS_Z;
    p[VN100_MAG_SCAL_X] = DEFAULT_VN100_MAG_SCAL_X;
    p[VN100_MAG_SCAL_Y] = DEFAULT_VN100_MAG_SCAL_Y;
    p[VN100_MAG_SCAL_Z] = DEFAULT_VN100_MAG_SCAL_Z;
    p[VN100_MAG_ALGN_XY] = DEFAULT_VN100_MAG_ALGN_XY;
    p[VN100_MAG_ALGN_XZ] = DEFAULT_VN100_MAG_ALGN_XZ;
    p[VN100_MAG_ALGN_YX] = DEFAULT_VN100_MAG_ALGN_YX;
    p[VN100_MAG_ALGN_YZ] = DEFAULT_VN100_MAG_ALGN_YZ;
    p[VN100_MAG_ALGN_ZX] = DEFAULT_VN100_MAG_ALGN_ZX;
    p[VN100_MAG_ALGN_ZY] = DEFAULT_VN100_MAG_ALGN_ZY;
    p[L1_ATT_J_ROLL] = DEFAULT_L1_ATT_J_ROLL;
    p[L1_ATT_J_PITCH] = DEFAULT_L1_ATT_J_PITCH;
    p[L1_ATT_J_YAW] = DEFAULT_L1_ATT_J_YAW;
    p[L1_ATT_AM1] = DEFAULT_L1_ATT_AM1;
    p[L1_ATT_AM2] = DEFAULT_L1_ATT_AM2;
    p[L1_ATT_T2R_A1] = DEFAULT_L1_ATT_T2R_A1;
    p[L1_ATT_T2R_A2] = DEFAULT_L1_ATT_T2R_A2;
    p[L1_ATT_PROP_K1] = DEFAULT_L1_ATT_PROP_K1;
    p[L1_ATT_M_TLT_RT] = DEFAULT_L1_ATT_M_TLT_RT;
    p[L1_ATT_M_YAW_RT] = DEFAULT_L1_ATT_M_YAW_RT;
    p[L1_ATT_MAX_OUT] = DEFAULT_L1_ATT_MAX_OUT;
    p[L1_ATT_QUAT_TAU] = DEFAULT_L1_ATT_QUAT_TAU;
    p[L1_ATT_L1_ASP] = DEFAULT_L1_ATT_L1_ASP;
    p[L1_ATT_L1_K1] = DEFAULT_L1_ATT_L1_K1;
    p[L1_ATT_PWM_LO] = DEFAULT_L1_ATT_PWM_LO;
    p[L1_ATT_PWM_HI] = DEFAULT_L1_ATT_PWM_HI;
    p[L1_ATT_PWM_SCALE] = DEFAULT_L1_ATT_PWM_SCALE;
    p[L1_ATT_AM1_KNOB] = DEFAULT_L1_ATT_AM1_KNOB;
    p[L1_ATT_AM2_KNOB] = DEFAULT_L1_ATT_AM2_KNOB;
    p[L1_ATT_K1_KNOB] = DEFAULT_L1_ATT_K1_KNOB;
    p[L1_ATT_PT_KNOB] = DEFAULT_L1_ATT_PT_KNOB;
    p[L1_ATT_MM_R01] = DEFAULT_L1_ATT_MM_R01;
    p[L1_ATT_MM_P01] = DEFAULT_L1_ATT_MM_P01;
    p[L1_ATT_MM_Y01] = DEFAULT_L1_ATT_MM_Y01;
    p[L1_ATT_MM_R02] = DEFAULT_L1_ATT_MM_R02;
    p[L1_ATT_MM_P02] = DEFAULT_L1_ATT_MM_P02;
    p[L1_ATT_MM_Y02] = DEFAULT_L1_ATT_MM_Y02;
    p[L1_ATT_MM_R03] = DEFAULT_L1_ATT_MM_R03;
    p[L1_ATT_MM_P03] = DEFAULT_L1_ATT_MM_P03;
    p[L1_ATT_MM_Y03] = DEFAULT_L1_ATT_MM_Y03;
    p[L1_ATT_MM_R04] = DEFAULT_L1_ATT_MM_R04;
    p[L1_ATT_MM_P04] = DEFAULT_L1_ATT_MM_P04;
    p[L1_ATT_MM_Y04] = DEFAULT_L1_ATT_MM_Y04;
    p[L1_ATT_MM_R05] = DEFAULT_L1_ATT_MM_R05;
    p[L1_ATT_MM_P05] = DEFAULT_L1_ATT_MM_P05;
    p[L1_ATT_MM_Y05] = DEFAULT_L1_ATT_MM_Y05;
    p[L1_ATT_MM_R06] = DEFAULT_L1_ATT_MM_R06;
    p[L1_ATT_MM_P06] = DEFAULT_L1_ATT_MM_P06;
    p[L1_ATT_MM_Y06] = DEFAULT_L1_ATT_MM_Y06;
    p[L1_ATT_MM_R07] = DEFAULT_L1_ATT_MM_R07;
    p[L1_ATT_MM_P07] = DEFAULT_L1_ATT_MM_P07;
    p[L1_ATT_MM_Y07] = DEFAULT_L1_ATT_MM_Y07;
    p[L1_ATT_MM_R08] = DEFAULT_L1_ATT_MM_R08;
    p[L1_ATT_MM_P08] = DEFAULT_L1_ATT_MM_P08;
    p[L1_ATT_MM_Y08] = DEFAULT_L1_ATT_MM_Y08;
    p[L1_ATT_MM_R09] = DEFAULT_L1_ATT_MM_R09;
    p[L1_ATT_MM_P09] = DEFAULT_L1_ATT_MM_P09;
    p[L1_ATT_MM_Y09] = DEFAULT_L1_ATT_MM_Y09;
    p[L1_ATT_MM_R10] = DEFAULT_L1_ATT_MM_R10;
    p[L1_ATT_MM_P10] = DEFAULT_L1_ATT_MM_P10;
    p[L1_ATT_MM_Y10] = DEFAULT_L1_ATT_MM_Y10;
    p[L1_ATT_MM_R11] = DEFAULT_L1_ATT_MM_R11;
    p[L1_ATT_MM_P11] = DEFAULT_L1_ATT_MM_P11;
    p[L1_ATT_MM_Y11] = DEFAULT_L1_ATT_MM_Y11;
    p[L1_ATT_MM_R12] = DEFAULT_L1_ATT_MM_R12;
    p[L1_ATT_MM_P12] = DEFAULT_L1_ATT_MM_P12;
    p[L1_ATT_MM_Y12] = DEFAULT_L1_ATT_MM_Y12;
    p[L1_ATT_MM_R13] = DEFAULT_L1_ATT_MM_R13;
    p[L1_ATT_MM_P13] = DEFAULT_L1_ATT_MM_P13;
    p[L1_ATT_MM_Y13] = DEFAULT_L1_ATT_MM_Y13;
    p[L1_ATT_MM_R14] = DEFAULT_L1_ATT_MM_R14;
    p[L1_ATT_MM_P14] = DEFAULT_L1_ATT_MM_P14;
    p[L1_ATT_MM_Y14] = DEFAULT_L1_ATT_MM_Y14;
}

void configFlashRead(void) {
    memcpy(&p, (char *)flashStartAddr(), sizeof(p));
}

unsigned char configFlashWrite(void) {
    return flashAddress(flashStartAddr(), (uint32_t *)&p, sizeof(p));
}

void configInit(void) {
    float ver;

    // start with what's in flash
    configFlashRead();

    // try to load any config params from uSD card
    if (configReadFile(0) < 0)
	// clear config if read error
	memset(p, 0, sizeof(p));
    else
	supervisorConfigRead();

    // get flash version
    ver = *(float *)flashStartAddr();
    if (isnan(ver))
	ver = 0.0f;

    // if compiled defaults are greater than flash version and loaded version
    if (DEFAULT_CONFIG_VERSION > ver && DEFAULT_CONFIG_VERSION > p[CONFIG_VERSION])
	configLoadDefault();
    // if flash version greater than or equal to currently loaded version
    else if (ver >= p[CONFIG_VERSION])
	configFlashRead();

    // if loaded version greater than flash version
    if (p[CONFIG_VERSION] > ver)
	configFlashWrite();
}

unsigned int configParameterRead(void *data) {
    paramStruct_t *par = (paramStruct_t *)data;

    if (par->paramId + par->num > CONFIG_NUM_PARAMS)
	par->num = CONFIG_NUM_PARAMS - par->paramId;

    memcpy((char *)par->values, (char *)&p[par->paramId], par->num * sizeof(float));

    return par->num * sizeof(float);
}

unsigned int configParameterWrite(void *data) {
    paramStruct_t *par = (paramStruct_t *)data;

    memcpy((char *)&p[par->paramId], (char *)par->values, par->num * sizeof(float));

    return configParameterRead(data);
}

// read config from uSD
int8_t configReadFile(char *fname) {
    char *lineBuf;
    char *fileBuf;
    char param[16];
    float value;
    int8_t fh;
    int ret;
    char c;
    int i, j, p1, p2;
    int n;

    if (fname == 0)
	fname = CONFIG_FILE_NAME;

    if ((fh = filerGetHandle(fname)) < 0) {
	AQ_NOTICE("config: cannot get read file handle\n");
	return -1;
    }

    fileBuf = (char *)aqCalloc(CONFIG_FILE_BUF_SIZE, sizeof(char));
    lineBuf = (char *)aqCalloc(CONFIG_LINE_BUF_SIZE, sizeof(char));

    p1 = 0;
    do {
	ret = filerRead(fh, fileBuf, -1, CONFIG_FILE_BUF_SIZE);

	p2 = 0;
	for (i = 0; i < ret; i++) {
	    c = fileBuf[p2++];
	    if (c == '\n' || p1 == (CONFIG_LINE_BUF_SIZE-1)) {
		lineBuf[p1] = 0;

		n = sscanf(lineBuf, "#define DEFAULT_%15s %f", param, &value);
		if (n != 2) {
		    n = sscanf(lineBuf, "%15s %f", param, &value);
		    if (n != 2) {
			n = sscanf(lineBuf, "#define %15s %f", param, &value);
		    }
		}

		if (n == 2) {
		    for (j = 0; j < CONFIG_NUM_PARAMS; j++) {
			if (!strncasecmp(param, configParameterStrings[j], sizeof(param)))
			    p[j] = value;
		    }
		}
		p1 = 0;
	    }
	    else {
		lineBuf[p1++] = c;
	    }
	}

    } while (ret > 0);

    filerClose(fh);

    if (lineBuf)
	aqFree(lineBuf, CONFIG_LINE_BUF_SIZE, sizeof(char));
    if (fileBuf)
	aqFree(fileBuf, CONFIG_FILE_BUF_SIZE, sizeof(char));

    return ret;
}

// write config to uSD
int8_t configWriteFile(char *fname) {
    char buf[128];
    int8_t fh;
    int8_t ret;
    int n;
    int i;

    if (fname == 0)
	fname = CONFIG_FILE_NAME;

    if ((fh = filerGetHandle(fname)) < 0) {
	AQ_NOTICE("config: cannot get write file handle\n");
	return -1;
    }

    for (i = 0; i < CONFIG_NUM_PARAMS; i++) {
	n = sprintf(buf, "%-15s\t\t%+.10e\n", configParameterStrings[i], p[i]);
	ret = filerWrite(fh, buf, -1, n);

	if (ret < n) {
	    AQ_NOTICE("config: file write error\n");
	    ret = -1;
	    break;
	}
    }

    filerClose(fh);

    return ret;
}
