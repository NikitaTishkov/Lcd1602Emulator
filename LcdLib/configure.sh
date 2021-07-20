#!/bin/bash
echo $1
if [ $1 = 'Qt' ]
then
    mkdir LcdLib_qt
    mkdir LcdLib_qt/LcdLib
    mkdir LcdLib_qt/LcdLib/Inc
    mkdir LcdLib_qt/LcdLib/Src
    cat Inc/pin.h > LcdLib_qt/LcdLib/Inc/pin.h
    cat Inc/QCell.h > LcdLib_qt/LcdLib/Inc/QCell.h
    cat Inc/lcd.h > LcdLib_qt/LcdLib/Inc/lcd.h
    cat Inc/mainfunction.h > LcdLib_qt/LcdLib/Inc/mainfunction.h
    cat Src/pin.cpp > LcdLib_qt/LcdLib/Src/pin.cpp
    cat Src/QCell.cpp > LcdLib_qt/LcdLib/Src/QCell.cpp
    cat Src/lcd.cpp > LcdLib_qt/LcdLib/Src/lcd.cpp
    cat Src/mainfunction.c > LcdLib_qt/LcdLib/Src/mainfunction.c
    cat Qt/main.cpp > LcdLib_qt/main.cpp
    cat Qt/mainwindow.h > LcdLib_qt/mainwindow.h
    cat Qt/mainwindow.cpp > LcdLib_qt/mainwindow.cpp
    cat Qt/mainwindow.ui > LcdLib_qt/mainwindow.ui
    cat Qt/CMakeLists.txt > LcdLib_qt/CMakeLists.txt
elif [ $1 = 'Lcd' ]
then
    mkdir LcdLib_1602
    sed 's!USE_EMULATOR 1!USE_EMULATOR 0!g' Inc/pin.h > LcdLib_1602/pin.h
    sed 's!#include "LcdLib/Inc/pin.h"!#include "pin.h"!g' Inc/lcd.h > LcdLib_1602/lcd.h
    sed 's!#include "LcdLib/Inc/pin.h"!#include "pin.h"!g' Src/pin.cpp > LcdLib_1602/pin.c
    sed 's!#include "LcdLib/Inc/lcd.h"!#include "lcd.h"!g' Src/lcd.cpp > LcdLib_1602/lcd.c
    sed 's!#include "LcdLib/Inc/lcd.h"!#include "lcd.h"!g' Inc/mainfunction.h > LcdLib_1602/mainfunction.h
    sed 's!#include "LcdLib/Inc/mainfunction.h"!#include "mainfunction.h"!g' Src/mainfunction.c > LcdLib_1602/mainfunction.c
else
    echo "Wrong arguments configure.sh [Qt or Lcd]"
fi