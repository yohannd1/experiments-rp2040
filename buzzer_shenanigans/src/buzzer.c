#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "buzzer.h"

// current strategy: when the clock is at 125MHz, a 250 divisor makes it so the
// frequency is 500KHz/(wrap+1), and since the max wrap+1 value is 65536, our
// range is 7Hz to 500KHz.
const float clock_div = 250.0f;

static void buzzer_init_pwm(buzzer_t *bz);

void buzzer_init(buzzer_t *bz, uint pin) {
	bz->pin = pin;
	buzzer_init_pwm(bz);
}

void buzzer_deinit(buzzer_t *bz) {
	bz->pin = 0;
}

static void buzzer_init_pwm(buzzer_t *bz) {
	gpio_set_function(bz->pin, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(bz->pin);

	pwm_config config = pwm_get_default_config();
	pwm_config_set_clkdiv(&config, clock_div);
	pwm_init(slice_num, &config, true);

	pwm_set_gpio_level(bz->pin, 0); // initially turn off PWM
}

void buzzer_play(buzzer_t *bz, float frequency, uint duration_ms) {
	uint slice_num = pwm_gpio_to_slice_num(bz->pin);

	/* uint32_t clock_freq = clock_get_hz(clk_sys); */
	/* uint32_t top = clock_freq / frequency - 1; */

	// let's assume the clock is 125MHz for now
	// freq = 500KHz/(wrap+1) -> wrap = 500KHz/freq - 1
	uint32_t wrap = (uint32_t)(500000.0f / frequency - 1.0f);

	pwm_set_wrap(slice_num, wrap);
	pwm_set_gpio_level(bz->pin, wrap / 2);

	sleep_ms(duration_ms);

	pwm_set_gpio_level(bz->pin, 0);
}
