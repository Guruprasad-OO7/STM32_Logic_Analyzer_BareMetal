STM32 Logic Analyzer – Bare-Metal + Python Visualization.

This project is a simple yet powerful experiment in building a mini logic analyzer using an STM32 microcontroller programmed entirely at the register level (no HAL, no CubeMX) and visualizing the captured data in real time using Python and Matplotlib.

It captures digital input samples, sends them over UART to a PC, and plots the waveform — allowing you to see exactly what’s happening on a pin. The setup is designed to be minimal but educational, making it a perfect hands-on project for embedded enthusiasts who want to go deeper into microcontroller internals.

What this project does
The STM32 toggles one output pin (PA5) rapidly, while reading the state of another pin (PA0) as a digital input. The input states are stored in a buffer for a fixed number of samples. Once sampling is complete, the data is sent over UART as a series of ASCII `0` and `1` characters.

A Python script running on the PC receives this data and plots it as a digital waveform. This makes it possible to visualize signal behavior, transitions, and timing patterns without needing expensive test equipment.

**Hardware setup**:-
1. STM32 Nucleo-F401RE development board
2. PA5 configured as output for square-wave generation
3. PA0 configured as digital input for sampling
4. USB cable connected to PC via the on-board ST-Link (Virtual COM Port)
5. Optional: jumper wire connecting PA5 to PA0 for a simple self-test
6. Computer with Python installed

How it works:-
1. The STM32 continuously toggles PA5 at a set delay interval.
2. PA0 is read at each toggle and its state (0 or 1) is stored in an array.
3. When the desired number of samples is reached, the data is sent over UART to the PC.
4. The Python script listens to the COM port, reads the incoming values, and stores them in a list.
5. Once the “Done” signal is received from the STM32, the script plots the data as a step waveform using Matplotlib.

Firmware features:-
1. Pure register-level programming using CMSIS headers
2. Adjustable sampling count (default: 50 samples for faster plotting)
3. Adjustable delay between samples for controlling capture speed
4. UART transmission at 115200 baud for fast data transfer
5. Minimal RAM footprint — ideal for low-resource MCUs

Python visualization script:-
The PC-side script is written in Python and requires only two libraries: `pyserial` for reading UART data, and `matplotlib` for plotting.

Installation:
pip install pyserial matplotlib

Usage:
1. Update the COM port in the script to match your system (e.g., "COM21" on Windows or "/dev/ttyUSB0" on Linux).
2. Run the script while the STM32 firmware is active.
3. The digital waveform will appear in a window, showing logic level changes over time.

Getting started:-
1. Flash the STM32 firmware from the `firmware` folder to your board.
2. Connect PA0 to the signal you want to observe (or loop PA5 to PA0 for testing).
3. Connect the STM32 to your PC over USB.
4. Run the Python script in `python_plot` folder.
5. Watch the waveform appear live on your screen.
