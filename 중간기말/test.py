from collections import deque

hit, miss = 0, 0
q = deque([])
q_set = set()
length = 0

f = open("test_trace.txt", 'r')
while True:
    line = f.readline()
    if not line:
        break
    data = int(line)
    if data not in q_set:
        if length >= 8192:
            temp = q.popleft()
            q_set.remove(temp)
            length -= 1
        q.append(data)
        q_set.add(data)
        length += 1
        miss += 1
    else:
        hit += 1

f.close()
print(hit, miss, hit/(hit+miss))
