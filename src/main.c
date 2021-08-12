#include "stdbool.h"
#include "STC89xx.h"
#include "compiler.h"
#include "lint.h"

// 单片机晶振频率
#define FOSC 11059200
// 定时器初始值计算
#define T_1ms (65536 - FOSC/12/1000)
#define _P0 0x80
#define _KEY 0x90

#define RAND_MAX 0x7FFF

SBIT(KEY0, _KEY, 0);

unsigned int count = 0;

// 数码管段选定义
SBIT(DU, _P0, 6);
// 数码管位选定义
SBIT(WE, _P0, 7);

int number = 0;

// 共阴型(0~9,A,b,C,d,E,F,全亮)
unsigned char table_D[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E,
                           0x79, 0x71, 0xFF};
// 位选数组,对应数码管位1,2,3,4
unsigned char table_W[] = {0xFE, 0xFD, 0xFB, 0xF7};

static unsigned long s = 0x80000001;
static unsigned char flag = 0;

int rand(void) {
    register unsigned long t = s;

    t ^= t >> 10;
    t ^= t << 9;
    t ^= t >> 25;

    s = t;

    return (t & RAND_MAX);
}

void sRand(unsigned int seed) {
    s = seed | 0x80000000; /* s shall not become 0 */
}

int main() {
    // 设置定时模式为模式1
    TMOD = 0x01;
    // 设置初始值
    TL0 = T_1ms;
    TH0 = T_1ms >> 8;
    // 启动定时器
    TR0 = 1;

    // 中断相关
    ET0 = 1;
    EA = 1;
    while (1) {}
}

void timer0() __interrupt(1) {
    TL0 = T_1ms;
    TH0 = T_1ms >> 8;
    count++;
    if (KEY0 == 0) {
        sRand(count);
        number = rand() % 10000 + 1;
    }
    if (count % 2 == 0) {
        if (count == 1000) {
            count = 0;
        }
        // 消影
        P2 = 0x00;
        DU = 1;
        DU = 0;
        // 选择数码管
        P2 = table_W[flag];
        WE = 1;
        WE = 0;
        // 设置数字
        switch (flag) {
            case 0:
                P2 = table_D[(number % 10000) / 1000];
                break;
            case 1:
                P2 = table_D[(number % 1000) / 100];
                break;
            case 2:
                P2 = table_D[(number % 100) / 10];
                break;
            case 3:
                P2 = table_D[number % 10];
                break;
        }
        DU = 1;
        DU = 0;
        flag++;
        if (flag > 3) {
            flag = 0;
        }
    }
}
