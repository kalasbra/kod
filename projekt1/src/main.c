#include <stdio.h>
#include <pthread.h>
#include <gpiod_utils.h>
#include <semaphore.h>

/********************************************************************************
 * @brief Structure containing thread arguments.
 * 
 * @param led 
 *        Reference to gpiod line connected to a LED.
 * @param button
 *        Reference to gpiod line connected to a button.
 * @param blink_speed_ms
 *        Blink speed of the LED at pressdown of the button.
 ********************************************************************************/
struct thread_args {
    struct gpiod_line* led_a;
    struct gpiod_line* led_b;
    struct gpiod_line* button;
    uint16_t blink_speed_ms;
    bool enabled;
    uint8_t last_input_value;
};

/******************************************************************************
 * @brief Kollar stigande flank på knappen. Om stigande flank,så togglas aktiveringen 
 *        av leds och skriver ut det nya tillståndet. access låses till 
 *        terminalen med en semafor, väntar sen 10 ms innan den släpper till nästa tråd.
 *        Med hjlp av en bool variable så om LEDs är enabled så blinkar LEDs 
 *        Annars släcks båda LEDS.
 * 
 * @param arg
 *        Reference to argument containing all thread parameters.
 * @return
 *        A nullptr, since we have to return something.
 ********************************************************************************/
void* run_thread(void* arg)
{
    struct thread_args* self = (struct thread_args*)(arg);
    while (1) 
    {

        if (gpiod_line_event_detected(self->button, GPIOD_LINE_EDGE_RISING, &self->last_input_value ))
        {
            semaphore_reserve(0);
            
            self->enabled = !self->enabled;
            if (!self->enabled)
            {
                printf("LEDs connected to pin %hu and %hu disabled!\n\n", 
                    gpiod_line_offset(self->led_a), 
                    gpiod_line_offset(self->led_b));         
            }     
            else 
            {
                printf("LEDs connected to pin %hu and %hu enabled!\n\n", 
                    gpiod_line_offset(self->led_a), 
                    gpiod_line_offset(self->led_b));  
            }
            delay_ms(10);
            semaphore_release(0);
        }    
        if (!self->enabled)
        {
            gpiod_line_set_value(self->led_a, 0);
            gpiod_line_set_value(self->led_b, 0);
        }
        else
        {
            gpiod_line_set_value(self->led_a, 1);
            gpiod_line_set_value(self->led_b, 0);
            delay_ms(self->blink_speed_ms);

            gpiod_line_set_value(self->led_a, 0);
            gpiod_line_set_value(self->led_b, 1);
            delay_ms(self->blink_speed_ms);
        }
        
    }
    return 0;
}
    


/********************************************************************************
 * @brief Creates two threads and connects a LED and a button in each thread.
 ********************************************************************************/
int main(void) {
    struct gpiod_line* led1 = gpiod_line_new(17, GPIOD_LINE_DIRECTION_OUT);
    struct gpiod_line* led2 = gpiod_line_new(22, GPIOD_LINE_DIRECTION_OUT);
    struct gpiod_line* led3 = gpiod_line_new(23, GPIOD_LINE_DIRECTION_OUT);
    struct gpiod_line* led4 = gpiod_line_new(24, GPIOD_LINE_DIRECTION_OUT);

    struct gpiod_line* button1 = gpiod_line_new(27, GPIOD_LINE_DIRECTION_IN);
    struct gpiod_line* button2 = gpiod_line_new(25, GPIOD_LINE_DIRECTION_IN);

    struct thread_args args1 = { led1, led3, button1, 100, false, 0 };
    struct thread_args args2 = { led2, led4, button2, 500, false, 0};
    pthread_t t1, t2; 

    pthread_create(&t1, 0, run_thread, &args1);
    pthread_create(&t2, 0, run_thread, &args2);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    return 0;
}