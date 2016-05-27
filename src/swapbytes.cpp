#ifndef SWAPBYTES_H
#define SWAPBYTES_H

void SwapBytes(void *pv, size_t n)
{
    int a = 0x12345678;
    unsigned char *c = (unsigned char*)(&a);
    if (*c == 0x78) {
        // Little endian
        char *p = (char *) pv;
        size_t lo, hi;
        for(lo=0, hi=n-1; hi>lo; lo++, hi--)
        {
            char tmp=p[lo];
            p[lo] = p[hi];
            p[hi] = tmp;
        }
    }
}
#define BIGENDIAN(x) SwapBytes(&x, sizeof(x));


#endif