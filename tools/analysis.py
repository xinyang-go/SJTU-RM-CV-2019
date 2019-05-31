import matplotlib.pyplot as plt
import numpy as np

fsend = open("send.info")
frecv = open("recv.info")

send_lines = fsend.readlines()[:-1]
recv_lines = frecv.readlines()[:-1]

send_infos = [line.split(" ") for line in send_lines]
recv_infos = [line.split(" ") for line in recv_lines]

send_times = [float(info[0]) for info in send_infos]
recv_times = [float(info[0]) for info in recv_infos]

send_yaw   = [float(info[1]) for info in send_infos]
TargetAngle= [float(info[1]) for info in recv_infos]
RealAngle  = [float(info[2]) for info in recv_infos]

length = min(len(send_times), len(recv_times))

send_times = send_times[:length]
recv_times = recv_times[:length]
send_yaw   = send_yaw[:length]
TargetAngle= TargetAngle[:length]
RealAngle  = RealAngle[:length]

time_base = min(send_times[0], recv_times[0])

send_times = np.array(send_times) - time_base
recv_times = np.array(recv_times) - time_base

TargetAngle = TargetAngle[:300]
RealAngle = RealAngle[:300]
send_times = send_times[:300]
recv_times = recv_times[:300]
send_yaw = send_yaw[:300]

TargetAngle = np.array(TargetAngle)
TargetAngle -= TargetAngle.mean()
RealAngle = np.array(RealAngle)
RealAngle -= RealAngle.mean()

plt.plot(send_times, send_yaw,   label="send-yaw")
plt.plot(recv_times, TargetAngle,label="TargetAngle")
plt.plot(recv_times, RealAngle,  label="RealAngle")
plt.scatter(send_times, send_yaw,   label="send-yaw")
plt.scatter(recv_times, TargetAngle,label="TargetAngle")
plt.scatter(recv_times, RealAngle,  label="RealAngle")
plt.legend()
plt.show()

