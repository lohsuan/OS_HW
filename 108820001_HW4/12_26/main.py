def fcfs(cur, req):
    result = abs(cur - req[0])
    for i in range(len(req) - 1):
        result = result + abs(req[i + 1] - req[i])
    print("(FCFS)The total distance: " + str(result))

def sstf(cur, req, max):
    tmp = req[:]
    tmp.sort()
    result = 0
    index = 0
    while len(tmp) != 0:
        min = max
        for i in range(len(tmp)):
            if min > abs(cur - tmp[i]):
                min = abs(cur - tmp[i])
                index = i
        result = result + abs(tmp[index] - cur)
        cur = tmp[index]
        tmp.pop(index)
    print("(SSTF)The total distance: " + str(result))

def scan(cur, req, max):
    tmp = req[:]
    tmp.append(cur)
    tmp.sort()
    lresult = 2 * cur + abs(cur - tmp[-1])
    print("(SCAN-left)The total distance: " + str(lresult))

    rresult = 2 * (max - cur) + abs(cur - tmp[0])
    print("(SCAN-right)The total distance: " + str(rresult))

def cscan(cur, req, max):
    tmp = req[:]
    tmp.append(cur)
    tmp.sort()
    # lresult = 2 * max - abs(cur - tmp[tmp.index(cur) + 1])
    # print("(CSCAN-left)The total distance: " + str(lresult))

    rresult = 2 * max - abs(cur - tmp[tmp.index(cur) - 1])
    print("(CSCAN-right)The total distance: " + str(rresult))

def main():
    max = int(input("Enter the maximum of the disk storage: ")) - 1
    cur = int(input("Enter the current cylinder: "))
    reqstr = input("Enter the queue of pending requests in FIFO order: ")
    reqstr = reqstr.split()
    req = []
    for i in range(len(reqstr)):
        req.append(int(reqstr[i]))
    fcfs(cur, req)
    sstf(cur, req, max)
    scan(cur, req, max)
    cscan(cur, req, max)

main()
