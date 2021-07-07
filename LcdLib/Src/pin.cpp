/*
 * pin.c
 *
 *  Created on: Apr 27, 2021
 *      Author: tns
 */
#include "LcdLib/Inc/pin.h"

void gpio_set(Pin *pin)
{
#if (!USE_EMULATOR)
	/* Case of HAL */
	if(pin->is_inverted)
	{
		HAL_GPIO_WritePin(pin->port, pin->pin, 0);
	}
	else
	{
		HAL_GPIO_WritePin(pin->port, pin->pin, 1);
	}

	/* TODO: pin_set in case of Emulator */
#endif
}

void gpio_clear(Pin *pin)
{
#if (!USE_EMULATOR)
	/* Case of HAL */
	if(pin->is_inverted)
	{
		HAL_GPIO_WritePin(pin->port, pin->pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(pin->port, pin->pin, 0);
	}

	/* TODO: pin_clear in case of emulator */
#endif
}

void gpio_write(Pin *pin, bool pin_val)
{
#if (!USE_EMULATOR)
	if(pin->is_inverted)
	{
		HAL_GPIO_WritePin(pin->port, pin->pin, !pin_val);
	}
	else
	{
		HAL_GPIO_WritePin(pin->port, pin->pin, pin_val);
	}
#endif
}

void gpio_toggle(Pin *pin)
{
#if (!USE_EMULATOR)
	/* Case of HAL */
	HAL_GPIO_TogglePin(pin->port, pin->pin);

    /* TODO: pin_toggle in case of emulator */
#endif
}
