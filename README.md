# 我使用的环境/My Env
- Vs Code
- Arduino 1.8.19
- ESP32-C3-mini
# 库/Lib
1. INA226
```
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.4
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA226 power sensor
//     URL: https://github.com/RobTillaart/INA226
```
2. CH1115
```
@file ER_OLEDM1_CH1115.hpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller header file
	Project Name: ER_OLEDM1_CH1115 , URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@author  Gavin Lyons
```
# 硬件配置/Hardware Config
```JSON
{
    "configuration": "JTAGAdapter=default,CDCOnBoot=default,PartitionScheme=default,CPUFreq=160,FlashMode=dio,FlashFreq=40,FlashSize=4M,UploadSpeed=115200,DebugLevel=none,EraseFlash=none",
    "board": "esp32:esp32:esp32c3",
    "sketch": "ina226c3.ino",
    "output": "./build",
    "port": "COM18"
}
```
# 硬件链接/Hardware Project Link
[oshw link](https://oshwhub.com/fmnaggar/powermeterxt90_copy_copy)