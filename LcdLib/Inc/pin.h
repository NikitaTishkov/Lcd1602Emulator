/*
 * pin.h
 *
 *  Created on: Apr 27, 2021
 *      Author: tns
 */

#ifndef INC_PIN_H_
#define INC_PIN_H_
#include <stdbool.h>
#include <stdint.h>
#define USE_EMULATOR 1

struct pin{
	uint32_t port;
	uint32_t pin;
	bool is_inverted;
};
typedef struct pin Pin;

void gpio_set(Pin *pin);
void gpio_clear(Pin *pin);
void gpio_write(Pin *pin, bool pin_val);
void gpio_toggle(Pin *pin);


#endif /* INC_PIN_H_ */
