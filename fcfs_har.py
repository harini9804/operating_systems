class proc:
	ct = 0
	def __init__(self,pid):
		self.pid = pid
		print("\nPID: "+str(pid))
		self.at = int(input("Enter arrival time:"))
		self.bt = int(input("Enter burst time: "))
		print("--------------")

	def output(self):
		print("\n")
		print("PID: "+str(self.pid),end = ' ')
		print("AT: "+str(self.at),end = ' ')
		print("BT: "+str(self.bt),end = ' ')
		print("CT: "+str(self.ct),end = ' ')
		print("TAT: "+str(self.tat),end = ' ')
		print("WT: "+str(self.wt))


no = input("\nEnter the number of processes: ")

no = int(no)

idleTime = 0

procList = [proc(i) for i in range(no)]
procList.sort(key= lambda x: x.at)

for i in range(no):
	if(i==0):
		procList[i].ct = procList[i].bt + procList[i].at
	else:
		if(procList[i].at >= procList[i-1].ct):
			procList[i].ct = procList[i].at + procList[i].bt
			idleTime+=procList[i].at - procList[i-1].ct
		else:
			procList[i].ct = procList[i-1].ct + procList[i].bt

	procList[i].tat = procList[i].ct - procList[i].at
	procList[i].wt = procList[i].tat - procList[i].bt

sum = 0
for i in range(no):
	procList[i].output()
	sum += procList[i].wt

avg = round(sum / no, 4)

print("\nAverage waiting time: "+str(avg))
print("System idle time: "+str(idleTime))
