
/********************************************************************************
 * @brief Provides utility functions for the Linux libgpiod library.
 ********************************************************************************/
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <gpiod.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif 

/********************************************************************************
 * @brief Enumeration for selecting the data direction of GPIO lines.
 ********************************************************************************/
enum gpiod_line_direction { GPIOD_LINE_DIRECTION_IN,    /* Input, e.g. buttons. */
                            GPIOD_LINE_DIRECTION_OUT }; /* Output, e.g. LEDs. */

/********************************************************************************
 * @brief Enumeration for selecting edge when performing edge detection.
 ********************************************************************************/
enum gpiod_line_edge { GPIOD_LINE_EDGE_RISING,  /* Rising edge, i.e. low to high. */
                       GPIOD_LINE_EDGE_FALLING, /* Falling edge, i.e. high to low. */
                       GPIOD_LINE_EDGE_BOTH };  /* Both edges. */

/********************************************************************************
 * @brief Provides new GPIO line connected to specified pin.
 *
 * @param pin
 *        Physical pin number of the Raspberry Pi.
 * @param direction
 *        The data direction of the pin, e.g. input or output.
 * @return
 *        Reference to the GPIO line upon success, else a nullptr.
 ********************************************************************************/
struct gpiod_line* gpiod_line_new(const uint8_t pin, 
                                   const enum gpiod_line_direction direction);

/********************************************************************************
 * @brief Toggles the output of specified GPIO line.
 *
 * @param self
 *        Reference to the GPIO line.
 ********************************************************************************/
void gpiod_line_toggle(struct gpiod_line* self);

/********************************************************************************
 * @brief Blinks the output of specified GPIO line with specified blink speed.
 *
 * @param self
 *        Reference to the GPIO line.
 * @param blink_speed_ms
 *        The blink speed measured in milliseconds.
 ********************************************************************************/
void gpiod_line_blink(struct gpiod_line* self, 
                      const uint16_t blink_speed_ms);

/********************************************************************************
 * @brief Detects specified edge on specified GPIO line. A 50 ms delay is used 
 *        to diminish the effects of contact bounces before the edge detection
 *        is performed.
 *
 * @param self
 *        Reference to the GPIO line.
 * @param edge
 *        The edge to detect.
 * @param previous_input
 *        Reference to variable storing the previous input value of the pin.
 * @return 
 *        True if specified edge is detected, else false. 
 ********************************************************************************/
bool gpiod_line_event_detected(struct gpiod_line* self, 
                               const enum gpiod_line_edge edge, 
                               uint8_t* previous_input);

/********************************************************************************
 * @brief Blocks the calling thread with specified delay time.
 * 
 * @param delay_time_ms
 *        The delay time in milliseconds.
 ********************************************************************************/
void delay_ms(const uint16_t delay_time_ms);

#ifdef __cplusplus
}
#endif