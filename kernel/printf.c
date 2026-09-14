#include <stdarg.h>

#include "types.h"

void consputc(int c);
void panic(char *s) __attribute__((noreturn));

static char digits[] = "0123456789abcdef";

static void
printint(long long x, int base, int sign)
{
  char buf[32];
  int i = 0;
  unsigned long long u;

  if (sign && x < 0) {
    consputc('-');
    u = (unsigned long long)(-(x + 1)) + 1;
  } else {
    u = (unsigned long long)x;
  }

  do {
    buf[i++] = digits[u % base];
    u /= base;
  } while (u != 0);

  while (i-- > 0)
    consputc(buf[i]);
}

static void
printstr(char *s)
{
  for (; *s; s++)
    consputc(*s);
}

int
printk(char *fmt, ...)
{
  va_list ap;
  char *s;
  int c;

  va_start(ap, fmt);
  for (char *p = fmt; *p; p++) {
    if (*p != '%') {
      consputc(*p);
      continue;
    }
    p++;
    switch (*p) {
    case 'd':
      printint(va_arg(ap, int), 10, 1);
      break;
    case 'x':
      printint(va_arg(ap, unsigned int), 16, 0);
      break;
    case 's':
      s = va_arg(ap, char *);
      if (s == 0)
        s = "(null)";
      printstr(s);
      break;
    case 'c':
      c = va_arg(ap, int);
      consputc(c);
      break;
    case '%':
      consputc('%');
      break;
    default:
      consputc('%');
      consputc(*p);
      break;
    }
  }
  va_end(ap);
  return 0;
}

void
panic(char *s)
{
  printk("panic: %s\n", s);
  for (;;)
    ;
}

void
printkinit(void)
{
}
