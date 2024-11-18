# Standard Control Library for Pico

<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/raspberrypi/raspberrypi-original.svg" width=64/>
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cplusplus/cplusplus-original.svg" width=64/>

## Overview

- This library provides a set of standard control functions for some modules.
- The library is designed to be used with the Pico SDK.
- The library is written in C++.

## Modules

- QEI : Rotary Encoder
- MD : Motor Driver

## Control Functions

- PID : Proportional-Integral-Derivative Controller

## Setup

### Clone this repository.

```
git clone https://github.com/Oya-Tomo/sclp.git
```

### Add the following line to your CMakeLists.txt.

```
add_subdirectory(sclp)
target_link_libraries([your project name] sclp)
```
