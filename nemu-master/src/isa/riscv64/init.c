#include <isa.h>
#include <memory/paddr.h>

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
static const uint32_t img [] = {
  0x00000297,  // auipc t0,0
  0x0002b823,  // sd  zero,16(t0)
  0x0102b503,  // ld  a0,16(t0)
  0x0000006b,  // nemu_trap
  0xdeadbeef,  // some data
};

static void restart() {
  /* Set the initial program counter. */
  //设置PC为RESET_VECTOR，即内存中的指令起始地址。
  cpu.pc = RESET_VECTOR;

  /* The zero register is always 0. */
  //将自定义的CPU的零寄存器的值设为0
  cpu.gpr[0]._64 = 0;
}

void init_isa() {
  /* Load built-in image. */
  //将img数组中的指令和数据加载到内存中的RESET_VECTOR位置。
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
}
