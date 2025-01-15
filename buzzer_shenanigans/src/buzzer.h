#ifndef _BUZZER_H
#define _BUZZER_H

#include <stdint.h>

typedef struct Buzzer {
	uint pin;
} Buzzer;

void Buzzer_init(Buzzer *bz, uint pin);
void Buzzer_deinit(Buzzer *bz);
void Buzzer_play(Buzzer *bz, uint32_t frequency, uint duration_ms);

#endif
