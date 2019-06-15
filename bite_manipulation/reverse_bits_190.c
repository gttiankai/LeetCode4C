//
// Created by Tiankai on 2019-06-15.
//


#include <stdlib.h>
#include <stdio.h>



/**
 *  Runtime: 0 ms, faster than 100.00% of C online submissions for Reverse Bits.
 *  Memory Usage: 6.6 MB, less than 33.54% of C online submissions for Reverse Bits.
 *
 * */
uint32_t reverseBits(uint32_t n) {
    // 此处有 bug，应该讲 int 类型改成 uint32_t类型，如果不改的话，会遇到溢出的问题
    int ans = 0;
    for (int i = 0; i < 32; ++i) {
        ans += n & 0x1;
        n = n >> 1;
        if (i < 31) {
            ans = ans << 1;
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    int n = 0b11111111111111111111111111111101;
    printf(" the value %x", reverseBits(n));
    return 0;
}


