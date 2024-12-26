# STM32 Doze Clock

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

本项目是一个基于 STM32F407IG 微控制器和 SPI OLED 双色屏的打盹时钟。它不使用 HAL 库，而是采用标准库进行开发。

## 项目概述

本打盹时钟具有以下功能：

*   计时精度达到 0.01 秒。
*   可设置 0 到 30 分钟的打盹时间。
*   初始状态为停止，按下按键开始计时。
*   按键持续按下 1 秒，将恢复到设定时间并重新开始计时。
*   使用 6 位数字显示时间 (xx:xx:xx)。
*   ~~时间到达时，板载蜂鸣器会发出蜂鸣声。~~
*   ~~允许按键延时，再睡 5 分钟（或拍击电路板触发）。~~

## 硬件和软件

*   **开发板:** STM32F407IG
*   **显示屏:** SPI OLED 双色屏 (128x64 分辨率)
*   **按键:**
    *   BTN_LEFT (PI8): 向上/向左
    *   BTN_RIGHT (PC13): 向下/向右
    *   BTN_ENTER (PI11): 确认
*   **开发环境:* Keil C
*   **库:** 标准库 (Standard Peripheral Library)

## 界面设计

该打盹时钟包含一个主菜单和四个子菜单：

### 1. 主菜单 (MainMenu)

*   **[进入计时界面]:** 进入打盹计时界面。
*   **[打盹时间设置]:** 进入打盹时间设置界面。
*   **[个性铃声选择]:** 进入个性铃声选择界面。
*   **[关于作者]:** 进入关于作者界面。

### 2. 打盹计时 (DozeCounting) 界面

*   第二行显示倒计时：分分:秒秒.毫秒
*   第三行显示按钮：
    *   **[打盹]:** 开始打盹倒计时。按下后变为 **[停止]**。
    *   **[暂停]:** 暂停倒计时。开始打盹后可用，按下后变为 **[继续]**。
    *   **[退出]:** 返回主菜单。

### 3. 打盹时间设置 (DozeTimeSetting) 界面

*   第二行显示时间设置：**[分分]:[秒秒].[毫秒]**
    *   可以通过 BTN_LEFT/BTN_RIGHT 选中需要调整的时间位。
    *   按下 BTN_ENTER 进入时间调整模式，此时 BTN_LEFT/BTN_RIGHT 用于减少/增加时间。
    *   再次按下 BTN_ENTER 或 BTN_EXIT 退出时间调整模式。
*   第三行显示按钮：**[完成]** - 返回主菜单。

### 4. 个性铃声选择 (CustomRing) 界面

*   第一行至第四行分别显示：**[铃声1]**, **[铃声2]**, **[铃声3]**, **[铃声4]**
*   按下 BTN_ENTER 选择对应的铃声。

## 演示视频

请观看以下演示视频以了解项目的实际运行效果：

<video width="640" height="480" controls>
  <source src="sample.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

## 使用方法

1. 克隆本仓库：

    ```bash
    git clone https://github.com/255doesnotexist/stm32_dozeclock.git
    ```

2. 使用您偏好的 STM32 开发环境打开项目。

3. 编译并烧录程序到您的 STM32F407IG 开发板。

4. 通过 BTN_LEFT, BTN_RIGHT 和 BTN_ENTER 按钮操作打盹时钟。

## 许可证

本项目使用 [GPLv3 许可证](https://www.gnu.org/licenses/gpl-3.0)。
