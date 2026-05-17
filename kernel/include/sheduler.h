#ifndef SIMHA_RTOS_SCHEDULER_H
#define SIMHA_RTOS_SCHEDULER_H

#include <stdint.h>
#include <stddef.h>

/* ========================================================================== */
/* 1. ARCHITECTURE PORT ABSTRACTION LAYER                                     */
/* ========================================================================== */
/* This section auto-detects the target platform or relies on your Makefile   */
/* compiler flags (e.g., -DARCH_XTENSA) to configure architecture types.     */

#if defined(ARCH_XTENSA) || defined(__XTENSA__)

    /* ESP32 / Xtensa Specifics */
    typedef uint32_t port_stack_t;
    #define PORT_STACK_GROWTH      (-1)  /* Stack grows downwards */
    #define PORT_DEFAULT_STACK_SZ  2048

#elif defined(ARCH_ARM_CM) || defined(__arm__)
    /* STM32 / ARM Cortex-M Specifics */
    typedef uint32_t port_stack_t;
    #define PORT_STACK_GROWTH      (-1)  /* Stack grows downwards */
    #define PORT_DEFAULT_STACK_SZ  1024

#elif defined(ARCH_8051) || defined(__SDCC_mcs51)
    /* 8051 Specifics */
    typedef uint8_t port_stack_t; 
    #define PORT_STACK_GROWTH      (1)   /* Stack grows upwards on standard 8051 */
    #define PORT_DEFAULT_STACK_SZ  64    /* Extremely constrained! */
#else
    #error "Simha-RTOS: Target architecture not defined or unsupported!"
#endif

/* ========================================================================== */
/* 2. TASK STATE & CONTROL STRUCTURES                                         */
/* ========================================================================== */

typedef enum {
    TASK_STATE_READY = 0,
    TASK_STATE_RUNNING,
    TASK_STATE_BLOCKED,
    TASK_STATE_SUSPENDED
} task_state_t;

/* Task Control Block (TCB) */
typedef struct TCB {
    /* CRITICAL: stack_ptr MUST be the first element. 
     * Low-level assembly context-switching loops rely on a 0-offset 
     * from the TCB structure pointer to find the hardware stack pointer. */
    volatile port_stack_t *stack_ptr; 

    uint32_t              task_id;
    task_state_t          state;
    uint8_t               priority;
    
    #if !defined(ARCH_8051)
    uint8_t               *stack_base; /* For stack overflow tracking (omit on 8051) */
    #endif

    struct TCB            *next;       /* Linked list pointer for scheduler queues */
    struct TCB            *prev;
} TCB_t;

/* Global tracking pointers exported by the scheduler core */
extern volatile TCB_t *current_tcb;
extern volatile TCB_t *next_tcb;

/* ========================================================================== */
/* 3. CORE KERNEL SYSTEM API                                                 */
/* ========================================================================== */

/* Hardware-Independent Lifecycle Functions */
void    simha_kernel_init(void);
void    simha_kernel_start(void);
TCB_t*  native_task_create(void (*task_entry)(void *), void *param, uint32_t stack_size, uint8_t priority);
void    native_task_block(TCB_t *task);
void    native_task_wakeup(TCB_t *task);

/* Hardware-Dependent Functions (Must be implemented individually per architecture port) */
volatile port_stack_t* port_initialize_stack(volatile port_stack_t *stack_top, void (*task_entry)(void *), void *param);
void                   port_yield(void);
void                   port_start_first_task(void);

#endif /* SIMHA_RTOS_SCHEDULER_H */