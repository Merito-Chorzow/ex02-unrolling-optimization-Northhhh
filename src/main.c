#include <stdint.h>

static void semi_write0(const char *str) {
    asm volatile (
        "mov r0, #0x04\n"
        "mov r1, %0\n"
        "bkpt #0xAB\n"
        : : "r" (str) : "r0", "r1", "memory"
    );
}

static void semi_print_u32(unsigned val) {
    char buf[16];
    int i = 14;
    buf[15] = 0; 
    
    if (val == 0) {
        semi_write0("0");
        return;
    }
    while (val > 0 && i >= 0) {
        buf[i--] = '0' + (val % 10);
        val /= 10;
    }
    semi_write0(&buf[i+1]);
}

static void semi_exit(void) {
    volatile unsigned block[2];
    block[0] = 0x20026;
    block[1] = 0; 

    asm volatile (
        "mov r0, #0x18\n"
        "mov r1, %0\n"
        "bkpt #0xAB\n"
        : : "r" (block) : "r0", "r1", "memory"
    );
}

static unsigned sum8_c(const uint8_t* p, unsigned n) {
  unsigned acc=0;
  for (unsigned i=0;i<n;i++) acc += p[i];
  return acc;
}

unsigned sum8_unroll4(const uint8_t* p, unsigned n) {
  unsigned acc = 0;
  unsigned i = 0;

  for (; i + 3 < n; i += 4) {
    acc += p[i+0];
    acc += p[i+1];
    acc += p[i+2];
    acc += p[i+3];
  }
  for (; i < n; ++i) {
    acc += p[i];
  }
  return acc;
}

int main(void) {
  const unsigned S = 123; 
  const unsigned N = 500u + (S % 200u);
  static uint8_t buf[1024];
  
  for (unsigned i=0;i<N;i++) buf[i]=(uint8_t)((i*11u+5u)&0xFF);

  unsigned a = sum8_c(buf, N);
  unsigned b = sum8_unroll4(buf, N);

  semi_write0("ex02: sum8_c=");
  semi_print_u32(a);
  semi_write0(" sum8_unroll4=");
  semi_print_u32(b);
  semi_write0("\n");

  if (a==b) semi_write0("OK [ex02]\n");
  else      semi_write0("FAIL [ex02]\n");

  volatile unsigned sink=0;
  for (unsigned k=0;k<100;k++) sink += sum8_unroll4(buf, N);
  
  semi_write0("ex02: metric=");
  semi_print_u32(sink & 0xFFFF);
  semi_write0("\n");

  semi_exit();

  return 0;
}