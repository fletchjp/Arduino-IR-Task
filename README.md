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

## FreeRTOS

There is one example. I have focussed on IO_Abstraction for further work and not developed this example.

John Fletcher (M6777)
