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

    #define STEP_UP_TIME    SPINDLE_LASER_FANPWM_POWERUP_DELAY / 255
    #define STEP_DOWN_TIME  SPINDLE_LASER_FANPWM_POWERDOWN_DELAY / 255

    void GcodeSuite::M916() {
        #if ENABLED(SPINDLE_LASER_FANPWM)
            planner.spindle_laser_fanpwm_on = true;

            const uint8_t s = parser.ushortval('S', 255); // requested pwm duty
            const uint8_t s_last = fan_speed[SPINDLE_LASER_FANPWM_FAN]; // fan_speed[p] = the last pwm value set
            const int16_t num_steps = s - s_last;

            millis_t ms_next = 0;
            int16_t i = 0;
            // increment/decrement pwm duty until it is at requested duty
            if(num_steps > 0) { // if we are increasing the PWM
                while (i < num_steps) {
                    watchdog_reset();
                    const millis_t ms = millis();
                    if (ELAPSED(ms, ms_next)) {
                        ms_next = ms + STEP_UP_TIME;
                        i += 1;
                        thermalManager.set_pwm_duty(SPINDLE_LASER_FANPWM_PIN, s_last + i, 255, SPINDLE_LASER_FANPWM_INVERT);
                    }
                }
            }
            else if(num_steps < 0) { // if we are decreasing the PWM
                while (i > num_steps) {
                    watchdog_reset();
                    const millis_t ms = millis();
                    if (ELAPSED(ms, ms_next)) {
                        ms_next = ms + STEP_DOWN_TIME;
                        i -= 1;
                        thermalManager.set_pwm_duty(SPINDLE_LASER_FANPWM_PIN, s_last + i, 255, SPINDLE_LASER_FANPWM_INVERT);
                    }
                }
            }

            fan_speed[SPINDLE_LASER_FANPWM_FAN] = MIN(s, 255U);
        #endif
    }

    void GcodeSuite::M917() {
        #if ENABLED(SPINDLE_LASER_FANPWM)
            planner.spindle_laser_fanpwm_on = false;        // disable pwm writes in planner.cpp
            fan_speed[SPINDLE_LASER_FANPWM_FAN] = 0;        // reset pwm duty to 0
            digitalWrite(SPINDLE_LASER_FANPWM_PIN, LOW);    // disable PWM timer
        #endif
    }
#endif // FAN_COUNT > 0