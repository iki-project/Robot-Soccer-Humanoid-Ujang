/*
 *   MXDXL.h
 *
 *   Author: ROBOTIS
 *
 */

#ifndef _MX_DXL_H_
#define _MX_DXL_H_


namespace Robot
{
	class MXDXL
	{
		public:
			static const int MIN_VALUE = 0;
			static const int CENTER_VALUE = 2048;
			static const int MAX_VALUE = 4095;
			static const double MIN_ANGLE = -180.0; // degree
			static const double MAX_ANGLE = 180.0; // degree
			static const double RATIO_VALUE2ANGLE = 0.088; // 360 / 4096
			static const double RATIO_ANGLE2VALUE = 11.378; // 4096 / 360

			static const int PARAM_BYTES = 7;


			static int GetMirrorValue(int value)		{ return MAX_VALUE + 1 - value; }
			static double GetMirrorAngle(double angle)	{ return -angle; }
			static int Angle2Value(double angle) { return (int)(angle * RATIO_ANGLE2VALUE) + CENTER_VALUE; }
			static double Value2Angle(int value) { return (double)(value - CENTER_VALUE) * RATIO_VALUE2ANGLE; }

			// Address
			enum
			{
				P_MODEL_NUMBER_L			= 0,
				P_MODEL_NUMBER_H			= 1,
				P_VERSION					= 2,
				P_ID						= 3,
				P_BAUD_RATE					= 4,
				P_RETURN_DELAY_TIME			= 5,
				P_CW_ANGLE_LIMIT_L         	= 6,
				P_CW_ANGLE_LIMIT_H         	= 7,
				P_CCW_ANGLE_LIMIT_L        	= 8,
				P_CCW_ANGLE_LIMIT_H        	= 9,
				P_SYSTEM_DATA2              	= 10,
				P_HIGH_LIMIT_TEMPERATURE    	= 11,
				P_LOW_LIMIT_VOLTAGE         	= 12,
				P_HIGH_LIMIT_VOLTAGE        	= 13,
				P_MAX_TORQUE_L              	= 14,
				P_MAX_TORQUE_H              	= 15,
				P_RETURN_LEVEL					= 16,
				P_ALARM_LED                 	= 17,
				P_ALARM_SHUTDOWN            	= 18,
				P_OPERATING_MODE            	= 19,
				P_LOW_CALIBRATION_L         	= 20,
				P_LOW_CALIBRATION_H         	= 21,
				P_HIGH_CALIBRATION_L        	= 22,
				P_HIGH_CALIBRATION_H        	= 23,
				P_TORQUE_ENABLE             	= 24,
				P_LED                       	= 25,
				P_D_GAIN                    	= 26,
				P_I_GAIN                    	= 27,
				P_P_GAIN                    	= 28,
				P_RESERVED                  	= 29,
				P_GOAL_POSITION_L           	= 30,
				P_GOAL_POSITION_H           	= 31,
				P_MOVING_SPEED_L            	= 32,
				P_MOVING_SPEED_H            	= 33,
				P_TORQUE_LIMIT_L            	= 34,
				P_TORQUE_LIMIT_H            	= 35,
				P_PRESENT_POSITION_L        	= 36,
				P_PRESENT_POSITION_H        	= 37,
				P_PRESENT_SPEED_L           	= 38,
				P_PRESENT_SPEED_H           	= 39,
				P_PRESENT_LOAD_L            	= 40,
				P_PRESENT_LOAD_H            	= 41,
				P_PRESENT_VOLTAGE           	= 42,
				P_PRESENT_TEMPERATURE       	= 43,
				P_REGISTERED_INSTRUCTION	= 44,
				P_PAUSE_TIME                	= 45,
				P_MOVING			= 46,
				P_LOCK				= 47,
				P_PUNCH_L			= 48,
				P_PUNCH_H			= 49,
				P_RESERVED4                 	= 50,
				P_RESERVED5                 	= 51,
				P_POT_L                     	= 52,
				P_POT_H                     	= 53,
				P_PWM_OUT_L                 	= 54,
				P_PWM_OUT_H                 	= 55,
				P_P_ERROR_L                 	= 56,
				P_P_ERROR_H                 	= 57,
				P_I_ERROR_L                 	= 58,
				P_I_ERROR_H                 	= 59,
				P_D_ERROR_L                 	= 60,
				P_D_ERROR_H                 	= 61,
				P_P_ERROR_OUT_L             	= 62,
				P_P_ERROR_OUT_H             	= 63,
				P_I_ERROR_OUT_L             	= 64,
				P_I_ERROR_OUT_H             	= 65,
				P_D_ERROR_OUT_L             	= 66,
				P_D_ERROR_OUT_H             	= 67,
				MAXNUM_ADDRESS
			};

	};
}

#endif
