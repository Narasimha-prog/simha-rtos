#include "kernel/include/nexus_config.h"
#include <stdint.h>
#include <stddef.h>

// ESP32 UART0 Data Register Address (from our .repl)
#define UART0_DR (volatile uint32_t *)0x3FF40000

void print_uart(const char *str) {
    while (*str) {
        *UART0_DR = *str++;
    }
}

void app_main(void) {
    print_uart("\n--- NEXUS-OS KERNEL BOOTING ---\n");
    print_uart("Simulating on Renode Platform...\n");
    
    // Start the system heart
    while(1) {
        // Kernel Idle Loop
    }
}
