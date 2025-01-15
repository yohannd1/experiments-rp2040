#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 10

void init_pitches(uint64_t *pitches, size_t len, int starting_note) {
	for (int i = 0; i < len; i++) {
		int midi_note = starting_note + i;
		double freq = 440.0 * pow(2, (double)(midi_note - 69) / 12.0);
		printf("MIDI %d, FREQ %lf\n", midi_note, freq);
		pitches[i] = (uint64_t)freq;
	}
}

void pwm_init_buzzer(uint pin) {
	gpio_set_function(pin, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(pin);
	pwm_config config = pwm_get_default_config();
	pwm_config_set_clkdiv(&config, 4.0f); // Ajusta divisor de clock
	pwm_init(slice_num, &config, true);
	pwm_set_gpio_level(pin, 0); // Desliga o PWM inicialmente
}

void play_tone(uint pin, uint32_t frequency, uint duration_ms) {
	uint slice_num = pwm_gpio_to_slice_num(pin);
	uint32_t clock_freq = clock_get_hz(clk_sys);
	uint32_t top = clock_freq / frequency - 1;

	pwm_set_wrap(slice_num, top);
	pwm_set_gpio_level(pin, top / 2);

	sleep_ms(duration_ms);

	pwm_set_gpio_level(pin, 0);
}

int main(void) {
	stdio_init_all();
	pwm_init_buzzer(BUZZER_PIN);

	/* Buzzer bz; */
	/* Buzzer_init(&bz, BUZZER_PIN); */
	/* Buzzer_deinit(&bz); */
	/* Buzzer_play(2090, 1000); */

	double c4_pitch = 2090.0; // WHY THE FUCK

	const size_t octave_count = 5;
	const size_t table_size = octave_count * 12;

	uint32_t pitches[table_size];
	for (int i = 0; i < table_size; i++) {
		double freq = c4_pitch * pow(2, (double)i / 12.0);
		pitches[i] = (uint32_t)freq;
	}

	/* for (int i = 0; i < table_size; i++) { */
	/* 	play_tone(BUZZER_PIN, pitches[i], 100); */
	/* } */

	/* const char *song = "cegb"; */
	const uint interval = 50;

	// I FUCKING LOVE 7TH CHORDS

	for (int i = 0; i < 16; i++) {
		play_tone(BUZZER_PIN, pitches[0], interval);
		play_tone(BUZZER_PIN, pitches[4], interval);
		play_tone(BUZZER_PIN, pitches[7], interval);
		play_tone(BUZZER_PIN, pitches[11], interval);
	}

	for (int i = 0; i < 16; i++) {
		play_tone(BUZZER_PIN, pitches[0+2], interval);
		play_tone(BUZZER_PIN, pitches[4+2], interval);
		play_tone(BUZZER_PIN, pitches[7+2], interval);
		play_tone(BUZZER_PIN, pitches[11+2], interval);
	}

	for (int i = 0; i < 16; i++) {
		play_tone(BUZZER_PIN, pitches[0+3], interval);
		play_tone(BUZZER_PIN, pitches[3+3], interval);
		play_tone(BUZZER_PIN, pitches[7+3], interval);
		play_tone(BUZZER_PIN, pitches[10+3], interval);
	}

	for (int i = 0; i < 16; i++) {
		play_tone(BUZZER_PIN, pitches[0+5], interval);
		play_tone(BUZZER_PIN, pitches[4+5], interval);
		play_tone(BUZZER_PIN, pitches[7+5], interval);
		play_tone(BUZZER_PIN, pitches[11+5], interval);
	}

	/* size_t octave = 4; */
	/* for (int i = 0;; i++) { */
	/* 	if (song[i] == '\0') i = 0; */

	/* 	char ch = song[i]; */

	/* 	/1* if (ch == '>') { *1/ */
	/* 	/1* 	if (octave > 4) *1/ */ 
	/* 	/1* } *1/ */

	/* 	if (ch >= 'a' && ch <= 'g') { */
	/* 		int raw = 'c' - 'a'; */
	/* 		int offset = (ch < 'c') ? (12 - 2 + raw) : (raw - 2); */
	/* 		play_tone(BUZZER_PIN, pitches[(octave - 4) * 4 + offset], interval); */
	/* 	} */
	/* } */

	/* uint64_t pitches[120]; */
	/* printf("Building pitch table...\n"); */
	/* init_pitches(pitches, 120, 12); */

	/* float bpm = 0.0; */

	/* int song[3] = {880, 1000, 2000}; */

	/* for (int i = 0; i < 3; i++) { */
	/* 	play_tone(BUZZER_PIN, song[i], 500); */
	/* } */

	/* int freq = 2000; */
	/* while (true) { */
	/* 	printf("What %d\n", freq); */
	/* 	play_tone(BUZZER_PIN, freq, 250); */
	/* 	sleep_ms(200); */
	/* 	freq += 100; */
	/* } */

	while (true)
		sleep_ms(1000);

	return 0;
}
