#include "robot.h"

namespace G8
{
    Robot::Robot(void)
    {
        pButtons = new ButtonBoard(static_cast<FEHIO::FEHIOPort>(CONST.GetVal<int>("BANK_BB", C_TYPE_INT)));

        pRight_encoder = new DigitalEncoder(static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_RENCODE", C_TYPE_INT)));
        pLeft_encoder = new DigitalEncoder(static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_LENCODE", C_TYPE_INT)));

        pRight_motor = new FEHMotor(static_cast<FEHMotor::FEHMotorPort>(CONST.GetVal<int>("MOT_RIGHT", C_TYPE_INT)));
        pLeft_motor  = new FEHMotor(static_cast<FEHMotor::FEHMotorPort>(CONST.GetVal<int>("MOT_LEFT", C_TYPE_INT)));

        pCds_cell = new AnalogInputPin(static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_CDS", C_TYPE_INT)));

        pMob = new Mobility(pRight_encoder, pLeft_encoder, pRight_motor, pLeft_motor);

        pBag_servo = new FEHServo(static_cast<FEHServo::FEHServoPort>(CONST.GetVal<int>("SERVO_BAG_PORT", C_TYPE_INT)));
        pBag_servo->SetMax(CONST.GetVal<int>("SERVO_BAG_MAX", C_TYPE_INT));
        pBag_servo->SetMin(CONST.GetVal<int>("SERVO_BAG_MIN", C_TYPE_INT));

        pNav = new Navigation(pMob);
    }

    Robot::~Robot()
    {
        delete pButtons;
        pButtons = nullptr;

        delete pRight_encoder;
        pRight_encoder = nullptr;

        delete pLeft_encoder;
        pLeft_encoder = nullptr;

        delete pRight_motor;
        pRight_motor = nullptr;

        delete pLeft_motor;
        pLeft_motor = nullptr;

        delete pCds_cell;
        pCds_cell = nullptr;

        delete pBag_servo;
        pBag_servo = nullptr;

        delete pMob;
        pMob = nullptr;

        delete pNav;
        pNav = nullptr;
    }
}
