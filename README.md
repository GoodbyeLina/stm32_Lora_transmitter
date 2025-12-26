# demo2 (DAPLink) 项目

> 仓库说明文件（来源：`User/README.md`）

**简要说明** ✅

这是一个基于 STM32F4 系列 (STM32F407) 的示例工程，使用 Keil MDK-ARM 开发、DAPLink 或兼容 CMSIS-DAP 固件进行烧录与调试。该工程包含 GPIO、USART、LoRa 等示例模块，便于在目标板上快速验证与调试。

---

## 主要特性 🔧

- 基于 STM32F4 HAL 驱动（CMSIS / HAL）
- Keil MDK-ARM 工程文件（`.uvprojx`, `.uvoptx`）
- 支持通过 DAPLink 拖拽 `.bin` 烧录或使用调试器在线调试
- 示例模块：GPIO、USART、LoRa (位于 `User/lora`) 

### 实现的功能 ✅

- **串口调试输出**：将 `printf` 重定向到 `USART1`（115200），方便在 PC 端查看日志。
- **LoRa 模块控制**：通过 `LoRa_SetMode()` 切换 LoRa 工作/配置模式（控制 M0/M1 引脚）。
- **LoRa 数据发送**：按下 `KEY0`（PA0）会触发通过 `USART2` 向 LoRa 模块发送字符串（示例：`LoRa_SendString()`）。
- **串口中断接收与转发**：`USART2` 使用中断接收，收到字节后通过 `USART1` 转发并翻转绿灯（`LED_G`）作提示。
- **LED 指示功能**：红灯（`LED_R`）作心跳闪烁，蓝灯（`LED_B`）在发送期间点亮作为发送指示，绿灯（`LED_G`）在接收时闪烁。
- **串口错误自动恢复**：在 `HAL_UART_ErrorCallback` 中检测并清除溢出（ORE）错误，重启中断接收以防止锁死。
- **硬件初始化**：GPIO、USART 初始化与系统时钟已配置，便于直接运行和调试。

---

## 硬件连接（引脚映射） 🔌

下面列出 MCU 与外设（LoRa、LED、按键、串口）之间在本项目中的实际连接（基于 `Core/Inc/main.h` 与 `User/lora/lora.h`）：

- **LoRa 模块**
  - VCC -> **3.3V**（注意：不要接 5V）
  - GND -> **GND**
  - TX -> **PA3** (对应 `USART2_RX`)
  - RX -> **PA2** (对应 `USART2_TX`)
  - M0 -> **PE2** (`LORA_M0`)
  - M1 -> **PE3** (`LORA_M1`)
  - AUX（可选）-> 建议接到任意 GPIO 输入以检测模块空闲，本工程中未使用

- **串口（调试）**
  - `USART1`（调试）：PA9 = TX, PA10 = RX，波特率 **115200**
  - 可用 USB↔TTL 转换器连接至 PC，**注意共地**

- **LED 指示（GPIOF）**
  - `LED_R` -> **PF6**（心跳）
  - `LED_G` -> **PF7**（接收指示）
  - `LED_B` -> **PF8**（发送指示）
  - 说明：板上 LED 为 **低电平点亮（active-low）**；驱动中写 0 点亮，写 1 熄灭

- **按键**
  - `KEY0` -> **PA0**（无上下拉，按下通常为高电平；软件有简单消抖）

**其他提示**：
- 所有外设均以 **3.3V** 供电，确保电平兼容并共地。
- 如果需要更稳定的 LoRa 模块模式切换，请接入 `AUX` 引脚并在驱动中等待其变高后再继续。

---

## 目录结构 📁

- `Core/` - 主程序源代码（`Inc/`, `Src/`）
- `MDK-ARM/` - Keil 工程配置和输出文件（`demo2.uvprojx`、生成的 `demo2.axf` 等）
- `User/` - 用户模块（如 `lora/`、`led/`）

---

## 依赖环境 ⚙️

- Keil MDK-ARM (uVision)
- ARM GCC 或 Keil 编译器（如果使用其他工具链）
- DAPLink / CMSIS-DAP 兼容的调试器（用于拖拽烧写或在线调试）

---

## 构建说明 🛠️

1. 使用 Keil 打开 `MDK-ARM/demo2.uvprojx`。
2. 选择目标设备 (STM32F407xx) 并构建（Build）。
3. 在输出目录中会生成 `*.axf`，可在 Keil 中配置导出为 `.hex` 或 `.bin`。

示例命令（若使用命令行工具链，请根据实际工具改写）:

```bash
# 示例：使用 Arm-none-eabi 工具链的转换步骤（按需执行）
arm-none-eabi-objcopy -O binary MDK-ARM/demo2.axf build/demo2.bin
```

---

## 烧录与调试 🔌

- 使用 DAPLink（若板上已刷入 DAPLink 固件），将 `*.bin` 文件拖拽到出现的可移动磁盘即可完成烧写。
- 使用 Keil 或其他调试器可直接在线调试（通过 CMSIS-DAP / ST-Link 等）。

> 注意：实际烧写方法取决于开发板和调试器，请根据硬件手册操作。

---

## 常见问题 & 调试提示 💡

- 如果串口不输出，检查 `usart` 波特率设置与接线。
- 若外设无响应，确认时钟配置（`system_stm32f4xx.c`）是否正确。

---

## 贡献与许可 🤝

欢迎 Merge 请求与 Issue。该示例项目建议采用 **MIT 许可证**（或根据你的需要替换）。

---

## 联系方式

若需帮助或有改进建议，请在仓库中提交 Issue 或联系维护者。

---

*已自动生成 — 简明项目说明文件*