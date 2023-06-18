# Linux userspace examples
This repository shows how to manage the LED controller PCA9532 from Linux userspace. For many types of devices, creating a Linux kernel driver is overkill. The logic of controlling the device does not necessarily have to be within the kernel. Running the driver in userspace simplifies development and reduces the risk of serious bugs within a kernel module.

Power ON/OFF is controlled by GPIO. The output LED configuration is sent through I2C communication bus to PCA9532.

![pinout](http://mbed.org/media/uploads/chris/pca9532pinout.png)

LED controller users shouldn't care about the low level (if the communication between device and processor is through I2C, SPI, UART, or another). They only need to know the public API of libPCA9532 to control it. 

Scheme below shows how shared libraries are loaded by other low level shared libraries and by the test application.

![structure](https://imgur.com/05qfkYi.jpg)

**libPCA9532 API:**

| Function | Description |
| :--- | :--- | 
| `pca9532_open` | Initialize PCA9532 |
| `pca9532_set_led` | Set led value |
| `pca9532_set_mask_out` | Set LED 12 to LED 1 values from uint16 mask  |
| `set_led_rgb` | Set led RGB color (if you had) |

**libI2C API:**

| Function | Description |
| :--- | :--- | 
| `i2c_read` | Read I2C message |
| `i2c_write` | Send I2C message |

**libGPIO API:**

| Function | Description |
| :--- | :--- | 
| `gpio_config` | Config GPIO as input/output |
| `gpio_free` | Free GPIO |
| `gpio_get_direction` | Get GPIO input/output direction  |
| `gpio_get_value` | Get GPIO input value |
| `gpio_set_value` | Set GPIO output value |

# References
- [Desarrollo de un sistema de soporte para sondas moviles Android con Yocto Project](https://riunet.upv.es/bitstream/handle/10251/181908/Lopez%20-%20DESARROLLO%20DEL%20SOFTWARE%20DE%20UN%20SISTEMA%20DE%20SOPORTE%20PARA%20SONDAS%20MOVILES%20ANDROID%20CON%20YOCTO%20PR....pdf?sequence=1&isAllowed=y)
- [Yocto Project example layer](https://github.com/bloppan/meta-app)
















