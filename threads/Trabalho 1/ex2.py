import sys
import numpy as np
import threading, queue
from random import randint

def mul(indexes, thread_id, result):
    for index in indexes:
        i = index[0]
        j = index[1]
        C[i,j] = sum(A[i, :] * B[:, j])

    print("Thread " + str(thread_id) + " finished.")

def random_matrix(x, y):
    return np.array([[randint(0,9) for j in range(y)] for i in range(x)])

def empty_matrix(x, y):
    return np.array([[0 for j in range(y)] for i in range(x)])

m = int(sys.argv[1])
n = int(sys.argv[2])
p = int(sys.argv[3])
q = int(sys.argv[4])
thread_count = int(sys.argv[5])

A = random_matrix(m, n)
B = random_matrix(p, q)
C = empty_matrix(m, q)

if(thread_count >= m*q):
    thread_count = m*q

element_count = (m*q)//thread_count
remainder = (m*q) % thread_count

thread_ids = [[] for i in range(thread_count)]
thread_id = 0
elements = 0

'''
    Atribui uma lista de índices da matriz resultante para thread_ids
'''
for i in range(m):
    for j in range(q):
        thread_ids[thread_id].append((i,j))
        elements += 1
        if(elements > element_count-1):
            elements = 0
            if(thread_id < thread_count-1):
                thread_id += 1

threads = []
'''
    Cria uma thread para cada thread_id que computa o somatório dos produtos dos seus índices associados com a função "mul"
'''
for indexes in thread_ids:
    thread_id = thread_ids.index(indexes)
    t = threading.Thread(target=mul, args=(indexes, thread_id, C))
    t.start()
    threads.append(t)

for t in threads:
    t.join()

print(A)
print(B)
print(C)