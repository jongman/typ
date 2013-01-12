# -*- coding: utf-8 -*-

def closer(a1, a2, b):
    "a1 과 a2 중 b에 더 가까운 값을 반환한다."
    if a1 is None: return a2
    if a2 is None: return a1
    return a1 if abs(a1 - b) < abs(a2 - b) else a2

def brute_force(A, B):
    C = []
    for b in B:
        closest = None
        for a in A:
            closest = closer(closest, a, b)
        C.append(closest)
    return C

import bisect
def binary_search(A, B):
    clip = lambda idx: max(min(len(A) - 1, idx), 0)
    C = []
    for b in B:
        idx = bisect.bisect(A, b)
        # A[idx-1] < b <= A[idx]
        C.append(closer(A[clip(idx - 1)], A[clip(idx)], b))
    return C

def sweeping(A, B):
    # assume B is sorted
    clip = lambda idx: max(min(len(A) - 1, idx), 0)
    C = []
    idx_a = 0
    for b in B:
        while idx_a + 1 < len(A) and A[idx_a + 1] < b:
            idx_a += 1
        C.append(closer(A[clip(idx_a)], A[clip(idx_a + 1)], b))
    return C

import numpy as np
def binary_search_np(A, B):
    # assume A and B are numpy arrays
    idx2 = np.minimum(len(A) - 1, np.searchsorted(A, B)) 
    idx1 = np.maximum(0, idx2 - 1)
    idx2_is_better = np.abs(A[idx1] - B) > np.abs(A[idx2] - B)
    np.putmask(idx1, idx2_is_better, idx2)
    return A[idx1]


def scaffolding_closest_index():
    from random import randint
    for repeat in xrange(100):
        A = sorted(set(randint(1, 5000) for i in xrange(1000)))
        B = sorted(set(randint(1, 5000) for i in xrange(100)))

        c1 = brute_force(A, B) 
        c2 = binary_search(A, B)
        c3 = sweeping(A, B)
        c4 = list(binary_search_np(np.array(A), np.array(B)))

        d1 = list(np.abs(np.array(B) - np.array(c1)))
        d2 = list(np.abs(np.array(B) - np.array(c2)))
        d3 = list(np.abs(np.array(B) - np.array(c3)))
        d4 = list(np.abs(np.array(B) - np.array(c4)))

        if not (d1 == d2 == d3 == d4):
            import pdb; pdb.set_trace()

    print 'all tests pass.'

def main():
    scaffolding_closest_index()

if __name__ == '__main__':
    main()

