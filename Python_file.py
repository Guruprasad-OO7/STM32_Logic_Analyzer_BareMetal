import serial
import matplotlib.pyplot as plt

COM_PORT = "COM21"
BAUD_RATE = 115200

ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)

print("Reading samples from STM32...")
samples = []

while True:
    line = ser.readline().decode(errors='ignore').strip()
    if not line:
        continue
    if "Done" in line:
        break
    try:
        samples.append(int(line))
    except ValueError:
        pass  # Ignore any non-integer lines

ser.close()
print(f"Captured {len(samples)} samples")

plt.figure(figsize=(10, 4))
plt.step(range(len(samples)), samples, where='post')
plt.ylim(-0.5, 1.5)
plt.xlabel("Sample Number")
plt.ylabel("Logic Level")
plt.title("STM32 Logic Analyzer Output")
plt.grid(True)
plt.show()
