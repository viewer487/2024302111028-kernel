// clang-format off
struct spinlock;
// console.c
void            consoleinit(void);
void            consputc(int);

// printk.c
int             printk(char*, ...) __attribute__ ((format (printf, 1, 2)));
void            panic(char*) __attribute__((noreturn));
void            printkinit(void);

// uart.c
void            uartinit(void);
void            uartintr(void);
void            uartwrite(char [], int);
void            uartputc_sync(int);
// proc.c
int             cpuid(void);
struct cpu*     mycpu(void);

// spinlock.c
void            acquire(struct spinlock*);
int             holding(struct spinlock*);
void            initlock(struct spinlock*, char*);
void            release(struct spinlock*);
void            push_off(void);
void            pop_off(void);
// number of elements in fixed-size array
#define NELEM(x) (sizeof(x) / sizeof((x)[0]))
