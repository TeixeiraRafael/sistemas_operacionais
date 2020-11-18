import sys
import threading
from random import randint

reverse = []

#inverts a given vector
def invert(vector):
    for x in vector[::-1]:
        reverse.append(x)

#splits a given vector in N subdivisions
def split(a, n):
    k, m = divmod(len(a), n)
    return (a[i * k + min(i, m):(i + 1) * k + min(i + 1, m)] for i in range(n))

thread_count = int(sys.argv[1])
n = int(sys.argv[2])

v = [randint(0,9) for i in range(n)]

subs = list(split(v, thread_count))

#inverts each subdivision in a separate thread
for i in range(thread_count):
    section = (thread_count - i - 1)
    t = threading.Thread(target=invert, args=(subs[section],))
    t.start()

print(v)
print(reverse)