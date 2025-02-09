#ifndef _BUZZER_H
#define _BUZZER_H

#include <stdint.h>

typedef struct buzzer_t {
	uint pin;
} buzzer_t;

void buzzer_init(buzzer_t *bz, uint pin);
void buzzer_deinit(buzzer_t *bz);
void buzzer_play(buzzer_t *bz, uint32_t frequency, uint duration_ms);

#endif
