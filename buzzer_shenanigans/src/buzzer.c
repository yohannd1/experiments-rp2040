#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "buzzer.h"

static void Buzzer_init_pwm(Buzzer *bz);

void Buzzer_init(Buzzer *bz, uint pin) {
	bz->pin = pin;
	Buzzer_init_pwm(bz);
}

void Buzzer_deinit(Buzzer *bz) {
	bz->pin = 0;
}

static void Buzzer_init_pwm(Buzzer *bz) {
	gpio_set_function(bz->pin, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(bz->pin);

	pwm_config config = pwm_get_default_config();
	pwm_config_set_clkdiv(&config, 4.0f);
	pwm_init(slice_num, &config, true);

	pwm_set_gpio_level(bz->pin, 0); // initially turn off PWM
}

void Buzzer_play(Buzzer *bz, uint32_t frequency, uint duration_ms) {
	uint slice_num = pwm_gpio_to_slice_num(bz->pin);
	uint32_t clock_freq = clock_get_hz(clk_sys);
	uint32_t top = clock_freq / frequency - 1;

	pwm_set_wrap(slice_num, top);
	pwm_set_gpio_level(bz->pin, top / 2);

	sleep_ms(duration_ms);

	pwm_set_gpio_level(bz->pin, 0);
}
