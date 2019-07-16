# Vision-Tracking-Format

A simple vision tracking format to use and create other programs with, by default it should be somewhat setup for the 2019 FRC game Deep Space

**All Vision Tracking code is located in the folder [src/main/](src/main)**


# Getting started

## With your computer

### 1. Install [WPILib](https://github.com/wpilibsuite/allwpilib/releases)

### 2. Install [Java 11](https://www.oracle.com/technetwork/java/javase/downloads/jdk11-downloads-5066655.html)

### 3. Install a compiler
  - [Visual Studio](https://visualstudio.microsoft.com/fr/downloads/) on Windows (in the Visual Studio Installer program, choose "Desktop Developement in C++")
  - Gcc on Linux

### 4. Install the raspbian cross-compiler
  - Run the following command in the root directory of this project :
  ```bash
  .\gradlew installRaspbianToolchain
  ```


## With the Raspberry Pi

### 1. Grab the [Raspberry Pi image](https://downloads.raspberrypi.org/raspbian_lite_latest)

### 2. Flash the image onto a microSD card using etcher: https://etcher.io/
  - You will need to grab the .img file from the zip. The .img file is what you give to etcher.
  - After complete, insert the microSD card and startup the coprocessor. It may take a minute or two.

### 3. SSH into the Coprocessor
  - On Mac/Linux, use `ssh username@hostname`
  - On Windows, download [puTTY](https://www.putty.org/) and use that.
  - **Hostname: `raspberrypi.local`, Username: `pi`, Password: `raspberry`**

### 4. Run the following command:
  ```bash
  wget --no-check-certificate -qO - https://github.com/nathanmutin/Vision-Tracking-Format/blob/master/bootstrap.sh?raw=1 | bash
  ```

### 5. Your Coprocessor will now restart
  - Hostname: `pi5553.local`
  - Username: `vision`
  - Password: `5553`



# Usage

## Running your code locally on your computer :
```bash
.\gradlew runVision
```

## Deploying your code to the Raspberry Pi
```bash
.\gradlew deploy
```

## Build all
```bash
.\gradlew build
```

## Test code
```bash
.\gradlew check
```
