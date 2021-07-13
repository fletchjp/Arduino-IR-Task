 <img align="right" src="arduino_merg_logo.png"  width="150" height="75">

# Arduino-IR-Task

 Examples codes for IR detection using TCRT 5000 detectors and various options for Task Scheduling.

## Introduction

These codes were put together to explore the best way to use the TCRT 5000 detectors.
Example use is illustrated on the Arduino Hardware page on the Knowledgebase.

https://www.merg.org.uk/merg_wiki/doku.php?id=arduino:hardware

I then extended the codes as a test for several alternative libraries for task scheduling.

https://www.merg.org.uk/merg_wiki/doku.php?id=arduino:codeing:scheduling

The task scheduling codes are based on one of two libraries, IO_Abstraction and FreeRTOS. Information on these is available from the link above.

## No scheduling

There are two examples, one of which has an added LED to show the result of the input.

TCRT5000_Terry - basic example  
TCRT5000_LED   - add external LED

## IO_Abstraction

There are two examples.

TCRT5000_IOAbs_Callback - simple callback  
TCRT5000_IOAbs_Cb3      - callback using class

The second method makes it possible to have more than one task in the same code.

I have since made a lot of use of IoAbstraction. I have found a lot of different ways to use it, some of which are not clearly explained in the documentation. I have now some cases which use several different tasks.

It makes it easy to do things without having to set a lot of parameters. This may be a limitation for large systems which make a heavy use of the CPU as there is no priority scheme.

It is for this reason that I want to explore some alternatives.

## FreeRTOS

There is one example. I have focussed on IO_Abstraction for further work and have not developed this example.

TCRT5000_FreeRTOS

I have now had a further look at FreeRTOS as I wanted to compare its use with work I have been doing with IoAbstraction. I have not for example found a way to do the callbacks and class structure which are available in IoAbstraction.

## Simba

I started to look at Simba and I have now stopped as the current version 15 does not support PIN_INPUT_PULL_UP which is needed for my code. This turns out to be a mysterious error where the wrong version of the source code is being picked up.

## Requirements

All of these examples will run on an Arduino UNO. There is a need for a TCRT5000 IR detector and connecting wiring.

The Task scheduling examples require the libraries as indicated which are available from the Arduino IDE.

Library documentation is available from the links on the Knowledgebase.

## Location

The local files are located at E:\GitHub\Arduino\Arduino-IR-Task

**John Fletcher (M6777)**
