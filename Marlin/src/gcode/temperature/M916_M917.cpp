/** PoshCube
 *
 * M916: Enables fan PWM analogWrites on SPINDLE_LASER_FANPWM_PIN
 *       ready for control with M106/M107
 *
 *  I    Ignore bit for protected pins
 *
 * M917: Disables fan PWM analogWrites on SPINDLE_LASER_FANPWM_PIN
 *       so it can be used elsewhere again
 *
 * M918: Soft speed change
 *
 */
#include "../gcode.h"
#include "../../Marlin.h"
#include "../../inc/MarlinConfig.h"
#include "../../module/temperature.h"
#include "../../module/planner.h"

#if FAN_COUNT > 0

void GcodeSuite::M916() {
    #if ENABLED(SPINDLE_LASER_FANPWM)
        planner.spindle_laser_fanpwm_on = true; // enable pwm writes in planner.cpp
    #endif
}

void GcodeSuite::M917() {
    #if ENABLED(SPINDLE_LASER_FANPWM)
        planner.spindle_laser_fanpwm_on = false; // disable pwm writes in planner.cpp
        digitalWrite(SPINDLE_LASER_FANPWM_PIN, LOW); // disable PWM timer
    #endif
}

void GcodeSuite::M918() {
    #if ENABLED(SPINDLE_LASER_FANPWM)
        for(uint8_t i = 0; i < steps; i++){
            thermalManager.set_pwm_duty(SPINDLE_LASER_FANPWM_PIN, );


        }


}

#endif // FAN_COUNT > 0