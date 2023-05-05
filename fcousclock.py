import time

focus_time = 1500  # 专注时间（以秒为单位）

while focus_time > 0:
    mins, secs = divmod(focus_time, 60)
    timer = '{:02d}:{:02d}'.format(mins, secs)
    print("专注倒计时: ", timer, end="\r")
    time.sleep(1)
    focus_time -= 1

print("时间到！")
