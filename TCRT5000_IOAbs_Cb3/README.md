@mainpage TCRT500_IOAbs_Cb3

# TCRT500_IOAbs_Cb3

@section description An example of IOAbs callback using a class.

This is one of the examples showing how IoAbstraction can be used to regulate calling to various external operations.

The advantage of using the class is that several copies of the same operation can be carried out at the same time.

@author John Fletcher (john@bunbury28.plus.com)

## Description from the top of the program file.

TCRT5000_IOAbs_Cb3  
IR detector circuit  
It has an LED to indicate that a detection has been made.  
(c) John Fletcher (M6777)

This version is adapted from an IoAbstraction example exampleDirect with taskmanager additions.

This is extended to use a class for the executable task.  
This makes it possible to have more than one detector.

 https://www.thecoderscorner.com/products/arduino-libraries/io-abstraction/

This compiles on UNO and also DUE and RP2040

