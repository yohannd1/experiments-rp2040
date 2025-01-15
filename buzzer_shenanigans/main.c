#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "buzzer.h"

#define BUZZER_PIN 10

int main(void) {
	stdio_init_all();

	Buzzer bz;
	Buzzer_init(&bz, BUZZER_PIN);
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
	/* 	Buzzer_play(&bz, pitches[i], 100); */
	/* } */

	/* const char *song = "cegb"; */
	const uint interval = 50;

	// I FUCKING LOVE 7TH CHORDS

	for (int i = 0; i < 16; i++) {
		Buzzer_play(&bz, pitches[0], interval);
		Buzzer_play(&bz, pitches[4], interval);
		Buzzer_play(&bz, pitches[7], interval);
		Buzzer_play(&bz, pitches[11], interval);
	}

	for (int i = 0; i < 16; i++) {
		Buzzer_play(&bz, pitches[0+2], interval);
		Buzzer_play(&bz, pitches[4+2], interval);
		Buzzer_play(&bz, pitches[7+2], interval);
		Buzzer_play(&bz, pitches[11+2], interval);
	}

	for (int i = 0; i < 16; i++) {
		Buzzer_play(&bz, pitches[0+3], interval);
		Buzzer_play(&bz, pitches[3+3], interval);
		Buzzer_play(&bz, pitches[7+3], interval);
		Buzzer_play(&bz, pitches[10+3], interval);
	}

	for (int i = 0; i < 16; i++) {
		Buzzer_play(&bz, pitches[0+5], interval);
		Buzzer_play(&bz, pitches[4+5], interval);
		Buzzer_play(&bz, pitches[7+5], interval);
		Buzzer_play(&bz, pitches[11+5], interval);
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
	/* 		Buzzer_play(&bz, pitches[(octave - 4) * 4 + offset], interval); */
	/* 	} */
	/* } */

	while (true)
		sleep_ms(1000);

	Buzzer_deinit(&bz);

	return 0;
}
