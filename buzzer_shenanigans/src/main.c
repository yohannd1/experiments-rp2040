#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "buzzer.h"

#define BUZZER_PIN 10

// TODO: MML string: octaves
// TODO: MML string: `.` to make the length a little bit bigger
// TODO: MML string: note slide
// TODO: two channels! (two buzzers and always sleep for the shortest duration)
// TODO: precompile MML to avoid realtime playback issues
// TODO: CMaj7 DMaj7 D#Min7 FMaj7
// TODO: try to support lower frequencies...
// TODO: 1-bit PCM using PIO

int charNoteToOffset(char c) {
	if (c >= 'A' && c <= 'Z') c += 'a'-'A';

	switch (c) {
	case 'c': return 0;
	case 'd': return 2;
	case 'e': return 4;
	case 'f': return 5;
	case 'g': return 7;
	case 'a': return 9;
	case 'b': return 11;
	default: return 0;
	}
}

bool isNoteLetter(char c) {
	return (c >= 'a' && c <= 'g') || (c >= 'A' && c <= 'G');
}

int main(void) {
	stdio_init_all();

	buzzer_t bz;
	buzzer_init(&bz, BUZZER_PIN);

	const float c2_pitch = 261.6f / 4.0f;
	const size_t octave_count = 7;
	const size_t table_size = octave_count * 12;

	float pitches[table_size];
	for (int i = 0; i < table_size; i++)
		pitches[i] = c2_pitch * pow(2, (float)i / 12.0f);

	const uint interval = 50;
	const uint bpm = 100;

	// invert b/m to get m/b, then convert m/b to 60k ms/b
	const float ms_per_beat = 1000.0f * 60.0f * (1.0f / (float)bpm);

	const char *song =
		"c4 d4 e4 c16 d16 f4  r8 f8 r8 f8 r8 r4 "
		"c4 d4 c4 c16 c+16 d4 r8 d8 r8 d8 r8 r4 "
		"c4 g4 f4 d16 d+16 e4 r8 e8 r8 e8 r8 r4 "
		"c4 d4 e4 c16 d16 f4  r8 f8 r8 f8 r8 r4 "
		"r2 "
		"c4 < b4 a4 g4 f4 e4 d4 c4"
		;

	int octave = 2; // c-4
	int note = 0;
	int i = 0;
	while (song[i] != '\0') {
		char c = song[i];

#define GET_DURATION_INTO(_duration, _divider) { \
	char *ptr; \
	long number = strtol(&song[i+1], &ptr, 10); \
	int end_index = ptr - song; \
	/* if we got a number, use it - if not, just use 1.0 */ \
	_divider = (end_index > i+1) ? number : 1.0f; \
	_duration = ms_per_beat * (1.0f / _divider); \
	i = end_index; \
}

		if (c == ' ' || c == '\n' || c == '\r') {
			i++;
		} else if (c == '>') {
			if (octave < octave_count - 1) octave++;
			i++;
		} else if (c == '<') {
			if (octave > 0) octave--;
			i++;
		} else if (isNoteLetter(c)) {
			note = 12*octave + charNoteToOffset(c);

			// + and - for detuning
			while (true) {
				char c = song[i+1];

				if (c == '-') {
					if (note > 0) note--;
				} else if (c == '+') {
					if (note < table_size - 1) note++;
				} else {
					break;
				}

				i++;
			}

			float divider;
			uint duration;
			GET_DURATION_INTO(duration, divider);

			printf("Note %c, divider %.1f: pitches[%d] (%.2f) for %dms\n", c, divider, note, pitches[note], duration);
			buzzer_play(&bz, pitches[note], duration);
		} else if (c == 'r' || c == 'R') {
			float divider;
			uint duration;
			GET_DURATION_INTO(duration, divider);

			sleep_ms(duration);
		} else {
			printf("WARNING: SKIPPING UNKNOWN CHAR %c [%d]\n", c, c);
			sleep_ms(500);
			i++;
		}
	}

	buzzer_deinit(&bz);

	printf("Song finished! Now entering infinite loop\n");

	while (true)
		sleep_ms(1000);

	return 0;
}
