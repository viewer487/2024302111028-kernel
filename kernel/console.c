#include "types.h"
#include "memlayout.h"

#define LCR 3
#define LSR 5
#define THR 0
#define IER 1
#define FCR 2
#define LCR_EIGHT_BITS (3 << 0)
#define LCR_BAUD_LATCH (1 << 7)
#define LSR_TX_IDLE (1 << 5)
#define FCR_FIFO_ENABLE (1 << 0)
#define FCR_FIFO_CLEAR (3 << 1)

static inline volatile uint8 *
uart_reg(int reg)
{
  return (volatile uint8 *)(UART0 + reg);
}

void
uartputc_sync(int c)
{
  while ((uart_reg(LSR)[0] & LSR_TX_IDLE) == 0)
    ;
  uart_reg(THR)[0] = (uint8)c;
}

void
consputc(int c)
{
  if (c == '\n')
    uartputc_sync('\r');
  uartputc_sync(c);
}

void
consoleinit(void)
{
  volatile uint8 *uart = (volatile uint8 *)UART0;

  uart[IER] = 0x00;
  uart[LCR] = LCR_BAUD_LATCH;
  uart[0] = 0x03;
  uart[1] = 0x00;
  uart[LCR] = LCR_EIGHT_BITS;
  uart[FCR] = FCR_FIFO_ENABLE | FCR_FIFO_CLEAR;
  uart[IER] = 0x00;
}
