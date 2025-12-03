.syntax unified
.cpu cortex-m3
.thumb

.global _estack
.global _sidata
.global _sdata
.global _edata
.global _sbss
.global _ebss
.extern main

/* ---------------- Vector table ---------------- */
.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object
.balign 4
g_pfnVectors:
  .word _estack           /* 0: Initial SP */
  .word Reset_Handler     /* 1: Reset */
  .word Default_Handler   /* 2: NMI */
  .word Default_Handler   /* 3: HardFault */
  .rept 60
    .word Default_Handler
  .endr
.size g_pfnVectors, .-g_pfnVectors

/* ---------------- Reset_Handler ---------------- */
.section .text.Reset_Handler, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
  ldr r0, =_sidata
  ldr r1, =_sdata
  ldr r2, =_edata
1:
  cmp r1, r2
  bcc 2f
  b   3f
2:
  ldr r3, [r0], #4
  str r3, [r1], #4
  b   1b
3:
  ldr r0, =_sbss
  ldr r1, =_ebss
4:
  cmp r0, r1
  bcc 5f
  b   6f
5:
  movs r2, #0
  str r2, [r0], #4
  b   4b
6:
  bl  main
7:
  b   7b

.section .text.Default_Handler, "ax", %progbits
.global Default_Handler
.type Default_Handler, %function
Default_Handler:
  b .