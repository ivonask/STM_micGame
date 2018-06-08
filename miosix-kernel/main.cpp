
#include "player.h"
#include "mono.h"

int main()
{
	ADPCMSound sound(mono_bin,mono_bin_len);
	Player::instance().play(sound);
}
