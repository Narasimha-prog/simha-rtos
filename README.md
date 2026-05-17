# Nexus-OS: Distributed Microkernel

**Nexus-OS** is a headless, real-time operating system designed for microcontrollers (ESP32). It features a modular architecture that separates **hard real-time execution** from **heavyweight visualization**, allowing remote control and monitoring via a Command-Line Interface (CLI) or a Remote GUI.

---

## 🚀 System Architecture

Nexus-OS operates on a **Master-Worker** model:

*   **The Core (MCU):** A robust kernel managing task scheduling, Bluetooth/Wi-Fi stacks, and deterministic hardware control.
*   **The Shell (Remote):** A decoupled interface (GUI/CLI) that communicates with the Core via a structured RPC (Remote Procedure Call) protocol.

---

## 🛠 Key Features

*   **Command-Driven Kernel:** Every OS function is mapped to a command reachable via UART, BLE, or WebSockets.
*   **Distributed Tasking:** Offloads "Heavy Tasks" (complex calculations, database queries) to a connected Remote OS while maintaining real-time stability.
*   **Multi-Protocol Bridge:** Seamlessly switch between **Bluetooth Low Energy**, **Wi-Fi**, and **Serial CLI** for system management.
*   **Telemetry Engine:** Real-time system health monitoring (CPU load, heap memory, and network latency) pushed to the remote interface.
*   **Modular Service Layer:** Dedicated services for Authentication, Logging, and Hardware Interfacing.

---

## 📂 Project Structure

```plaintext


simha-rtos/
├── api/
│   ├── rpc/
│   └── posix/                <-- NEW: POSIX Layer
│       ├── pthread.c         <-- Thread management mapping
│       ├── pthread_mutex.c   <-- Mutex mapping
│       └── include/
│           ├── pthread.h     <-- POSIX compliant definitions
│           └── semaphore.h
├── kernel/
│   └── include/
│       └── scheduler.h       <-- Your internal native kernel API
└── src/
    ├── scheduler.c
    └── arch/                 <-- Hardware dependent layer (Xtensa, ARM, 8051)
```
---

## 💻 Getting Started

### Prerequisites

*   **Hardware:** ESP32 (Inspiron-15-3520 development environment recommended).
*   **Toolchain:** Xtensa-gcc / ESP-IDF or Bare-metal C toolchain.
*   **Remote Shell:** Any Serial Monitor (115200 baud) or the Nexus Remote GUI application.

### Installation

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-repo/nexus-os.git](https://github.com/your-repo/nexus-os.git)
    ```

2.  **Configure the kernel:**
    Modify settings in `config/system_config.h`.

3.  **Build and Flash:**
    ```bash
    make all
    make flash
    ```

---

## 📡 Remote GUI Communication

Nexus-OS uses a structured frame format for robustness to ensure data integrity over wireless links:

| Header | Cmd ID | Length | Payload | CRC |
| :--- | :--- | :--- | :--- | :--- |
| `0xAA55` | 1 Byte | 1 Byte | N Bytes | 1 Byte |

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.