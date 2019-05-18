#ifndef RC4_H
#define RC4_H

#include <stdio.h>
#include <zconf.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rc4_state {
    u_char perm[256];
    u_char index1;
    u_char index2;
};

extern void rc4_init(struct rc4_state *const state, const u_char *key, int keylen);

extern void rc4_crypt(struct rc4_state *const state,
                      const u_char *inbuf, u_char *outbuf, u_int64_t buflen);

void crypt(const u_char *input, u_char *output, uint64_t size);

#ifdef __cplusplus
}
#endif

#endif /* RC4_H */
