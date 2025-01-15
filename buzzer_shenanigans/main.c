#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "buzzer.h"

#define BUZZER_PIN 10

// TODO: MML string: notes
// TODO: MML string: octaves
// TODO: MML string: note lengths
// TODO: MML string: `.` to make the length a little bit bigger
// TODO: MML string: pitch slide
// TODO: two channels! (two buzzers and always sleep for the shortest duration)
// TODO: precompile MML to avoid realtime playback issues

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
	const uint bpm = 120;

	// invert b/m to get m/b, then convert m/b to 60k ms/b
	const double ms_per_beat = 1000.0 * 60.0 * (1.0 / (double)bpm);

	Buzzer_play(&bz, pitches[0], (uint)ms_per_beat);
	Buzzer_play(&bz, pitches[1], (uint)ms_per_beat);
	Buzzer_play(&bz, pitches[2], (uint)ms_per_beat);
	Buzzer_play(&bz, pitches[3], (uint)ms_per_beat);

	// I FUCKING LOVE 7TH CHORDS
	// CMaj7 DMaj7 D#Min7 FMaj7

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
