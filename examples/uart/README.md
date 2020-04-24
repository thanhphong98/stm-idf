# Example: UART

This example shows how to configure UART.

### Feature

 - UART4: PA0 TX_Pin, PA1 RX_Pin.
 - Baudrate: 115200.
 - Frame format: 8N1.
 - Mode: both TX and RX.
 - Hardware flow control: None.

### How to use

- Follow this [link](https://github.com/thanhphong98/stm-idf) to setup STM-IDF on your computer.

- Copy example project into your workspace.
- Go to uart project:

```
cd path_to_uart
```

- Build the project by running command below. If there are no error occurs, project binary .bin file will generate into build folder.

```
make build all
```

- This SDK flash to STM32 target and send log output over USART3 (default). Make sure you have already connected  USB UART to USART3, then run this command:

```
make flash
```

- To view log output, run this command:

```
make monitor
```
