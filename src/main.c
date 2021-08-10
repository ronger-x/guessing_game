#include "STC89xx.h"
#include "compiler.h"
#include "lint.h"

// 单片机晶振频率
#define FOSC 11059200
// 定时器初始值计算
#define T_1ms (65536 - FOSC/12/1000)
#define RAND_MAX    0x7FFF

static unsigned s = 0x80000001;

unsigned int count = 0;

int rand(void) {
    register unsigned long t = s;

    t ^= t >> 10;
    t ^= t << 9;
    t ^= t >> 25;

    s = t;

    return (t & RAND_MAX);
}

void srand(unsigned int seed) {
    s = seed | 0x80000000; /* s shall not become 0 */
}

int main() {
    while (1) {}
}

void timer0() __interrupt(1) {

}
