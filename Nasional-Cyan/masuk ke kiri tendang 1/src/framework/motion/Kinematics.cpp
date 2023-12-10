/*
 *   Kinematics.cpp
 *
 *   Author: ROBOTIS
 *
 */

#include <math.h>
#include "Kinematics.h"


using namespace Robot;

const double Kinematics::CAMERA_DISTANCE = 34.0; //34mm
const double Kinematics::EYE_TILT_OFFSET_ANGLE = 50.0; //40.0degree // 50.0
const double Kinematics::LEG_SIDE_OFFSET = 55.0; //37.0mm
const double Kinematics::THIGH_LENGTH = 131.0; //93.0mm
const double Kinematics::CALF_LENGTH = 131.0; //93.0mm
const double Kinematics::ANKLE_LENGTH = 42.0; //33.5mm
const double Kinematics::LEG_LENGTH = 300; //303//219.5mm (THIGH_LENGTH + CALF_LENGTH + ANKLE_LENGTH)

Kinematics* Kinematics::m_UniqueInstance = new Kinematics();

Kinematics::Kinematics()
{
}

Kinematics::~Kinematics()
{
}
