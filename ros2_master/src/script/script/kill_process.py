import subprocess
import signal
import time
import os


def kill_process(process_list: list):

    pids = set()

    for kw in process_list:
        try:
            out = subprocess.check_output(["pgrep", "-f", kw], stderr=subprocess.DEVNULL, text=True)
            print(f"找到进程 {kw} : {out.strip()}")
            for pid in out.split():
                pids.add(int(pid))
        except subprocess.CalledProcessError:
            pass

    # 先优雅关闭
    for pid in pids:
        try:
            os.kill(pid, signal.SIGTERM)
        except ProcessLookupError:
            pass

    time.sleep(0.5)

    # 再强制兜底
    for pid in pids:
        try:
            os.kill(pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
