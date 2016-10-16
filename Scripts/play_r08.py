import serial, sys, time, psutil, os, bz2, gc

# disable gc
gc.disable()
	
# give us high priority
p = psutil.Process(os.getpid())
p.nice(psutil.REALTIME_PRIORITY_CLASS)

# connect to device
ser = serial.Serial('COM3', 2000000, timeout=0.1)

# send "ping" command to make sure device is there
ser.write(b'\xFF')
data = ser.read()
if data == b'\xFF':
	print("+++ Connected to device, device is ready to receive commands...")
else:
	print("!!! Device is not ready, exiting...")
	sys.exit()

f = None
filename = sys.argv[1]
if filename[-3:].lower() == "bz2":
	f = bz2.BZ2File(filename, "r")
else:	
	f = open(filename, "rb")

# reset device
print("--- Sending reset command to device")
ser.write(b'\x00')
time.sleep(0.1)

# set window size
#ser.write(bytes([0xA0, 0x40, 0x00]))  # 16384 = ~0.68ms

# set window off at
#ser.write(bytes([0xA1, 0x08, 0x49])) # 2122

# set clock filter timers (DPCM fix)
#ser.write(bytes([0xA4, 128])) # Port 1 timer (128 = 5us)
#ser.write(bytes([0xB4, 128])) # Port 2 timer (128 = 5us)

# start run
print("--- Sending start command to device")
ser.write(b'\x01\x01\x02\x01\x00\x01\x00') # command 1 (play), 8-bits, 2 ports, 1 dataline, sync, use window on port 1, unused in sync mode

latches = 0
skip = 0
extra = 0

for n in range(0, skip):
	f.read(2)

cmd = None
data = None
inputs = None	
tmp = None
	
print("--- Starting read loop")
while True:
	cmd = ser.read()
	if cmd == b'\x0F':
		# device wants input
		if extra > 0:
			inputs = f.read(60 - (extra*2))
			tmp = ([0]*(extra*2)) + [x for x in inputs]
			ser.write(bytes([0x0F] + tmp))
			extra = 0
		else:
			inputs = f.read(60)
			ser.write(bytes([0x0F] + [x for x in inputs]))
			
		latches = latches + 30
		if latches % 60 == 0:
			print('*** Latches: [%d] - Data: [%x]' % (latches, inputs[0]))
