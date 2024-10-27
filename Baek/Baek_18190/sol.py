from sys import stdin
from decimal import Decimal, getcontext

# for test
# stdin=open("input.txt","r")

N, M, Q = list(map(int, stdin.readline().split()))
getcontext().prec = 35

convexBig = []
convexSmall = []
query = []

# Prefix use for calculate area
prefixSumConvexBig = []
prefixSumConvexSmall = []

convexSmallCoord2Index = {}

# check twice
uphullBig = []
downHullBig = []

uphullSmall = []
downHullSmall = []

def dot(x1, y1, x2, y2):
    return x1 * x2 + y1 * y2

def cross(x1, y1, x2, y2):
    return x1 * y2 - y1 * x2

def ccw(x1, y1, x2, y2, x3, y3):
    # a->b 직선에 대해 c 의 방향
    ax = x2 - x1
    ay = y2 - y1
    bx = x3 - x1
    by = y3 - y1
    return cross(ax, ay, bx, by)

def ccw_vec(v1x, v1y, v2x, v2y):
    c = cross(v1x, v1y, v2x, v2y)
    if c > 0:
        return 1
    elif c < 0:
        return -1
    return 0

def read():
    global N
    global M
    # 직선상에 있는 점은 제거하기 위해 tmp 로 사용
    tmpConvex1 = [list(map(int, stdin.readline().split())) for _ in range(N)]
    tmpConvex2 = [list(map(int, stdin.readline().split())) for _ in range(M)]

    global convexBig
    convexBig = [(0,0) for _ in range(N)]

    global convexSmall
    convexSmall = [(0,0) for _ in range(M)]

    count = 0
    for i in range(len(tmpConvex1)):
        a = (i + N - 1) % N # 이전 점
        b = (i + 1) % N     # 다음 점

        # i 번째가 일찍선 상에 없을때만 추가
        if ccw(
            tmpConvex1[a][0], tmpConvex1[a][1],
            tmpConvex1[i][0], tmpConvex1[i][1],
            tmpConvex1[b][0], tmpConvex1[b][1]) != 0:
            convexBig[count] = tmpConvex1[i]
            count += 1
    N = count
    convexBig = convexBig[0:N]

    count = 0
    for i in range(len(tmpConvex2)):
        a = (i + M - 1) % M # 이전 점
        b = (i + 1) % M     # 다음 점

        # i 번째가 일찍선 상에 없을때만 추가
        if ccw(
            tmpConvex2[a][0], tmpConvex2[a][1],
            tmpConvex2[i][0], tmpConvex2[i][1],
            tmpConvex2[b][0], tmpConvex2[b][1]) != 0:
            convexSmall[count] = tmpConvex2[i]
            count += 1
    M = count
    convexSmall = convexSmall[0:M]

    global query
    query = [list(map(int, stdin.readline().split())) for _ in range(Q)]

def decompose(convex, uphull, downhull):
    start = 0
    end = 0
    sz = len(convex)

    for here in range(sz):
        prev = (here + sz - 1) % sz
        next = (here + 1) % sz
        # start = right most
        if convex[prev][0] <= convex[here][0] and convex[here][0] > convex[next][0]:
            start = here
            break
    
    uphull[:] = [(0, 0) for _ in range(sz)]
    downhull[:] = [(0, 0) for _ in range(sz)]

    count = 0
    for i in range(sz):
        here = (start + i) % sz
        next = (start + i + 1) % sz

        # 반시계로 도는데 이전께 더 크다 <-- 방향으로 가는 것들
        if convex[here][0] > convex[next][0]:
            uphull[count] = convex[here]
            count += 1
        else:
            uphull[count] = convex[here]
            count += 1
            end = here
            break
    uphull = uphull[:count]
    
    count = 0
    while end != start:
        downhull[count] = convex[end]
        count += 1
        end = (end + 1) % sz
    
    downhull[count] = convex[start]
    count += 1
    downhull = downhull[:count]

def preprocess():
    prev = 0
    global prefixSumConvexBig
    global prefixSumConvexSmall
    prefixSumConvexBig = [None] * 2 * N
    for i in range(2 * N):
        cur = i % N
        next = (i + 1) % N
        prefixSumConvexBig[i] = prev + cross(
            convexBig[cur][0], convexBig[cur][1],
            convexBig[next][0], convexBig[next][1])
        prev = prefixSumConvexBig[i]

    prev = 0
    prefixSumConvexSmall = [None] * 2 * M
    for i in range(2 * M):
        cur = i % M
        next = (i + 1) % M
        prefixSumConvexSmall[i] = prev + cross(
            convexSmall[cur][0], convexSmall[cur][1],
            convexSmall[next][0], convexSmall[next][1])
        prev = prefixSumConvexSmall[i]

    for i in range(M):
        convexSmallCoord2Index[(convexSmall[i][0], convexSmall[i][1])] = i
    
    decompose(convexBig, uphullBig, downHullBig)
    decompose(convexSmall, uphullSmall, downHullSmall)

def isInside(convex, point):
    OUT = -1
    BOUNDARY = 0
    IN = 1

    # convex size >= 3
    l = 1
    r = len(convex) - 1

    lx = convex[l][0] - convex[0][0]
    ly = convex[l][1] - convex[0][1]
    rx = convex[r][0] - convex[0][0]
    ry = convex[r][1] - convex[0][1]
    px = point[0] - convex[0][0]
    py = point[1] - convex[0][1]

    # check left most
    if ccw_vec(lx, ly, px, py) < 0:
        return OUT
    if ccw_vec(lx, ly, px, py) == 0:
        dist = dot(lx, ly, px, py)
        if dist > lx * lx + ly * ly:
            return OUT
        if dist < 0:
            return OUT
        return BOUNDARY
    
    # check right most
    if ccw_vec(rx, ry, px, py) > 0:
        return OUT
    if ccw_vec(rx, ry, px, py) == 0:
        dist = dot(rx, ry, px, py)
        if dist > rx * rx + ry * ry:
            return OUT
        if dist < 0:
            return OUT
        return BOUNDARY
    
    while l + 1 < r:
        mid = l + (r - l) // 2

        mx = convex[mid][0] - convex[0][0]
        my = convex[mid][1] - convex[0][1]

        clockwise = ccw_vec(mx, my, px, py)
        if clockwise == 0:
            dist = dot(mx, my, px, py)
            msquare = mx * mx + my * my
            if dist > msquare:
                return OUT
            if dist == msquare:
                return BOUNDARY
            if dist < 0:
                return OUT
            return IN
        elif clockwise > 0:
            l = mid
        else:
            r = mid
    
    # l -> p -> r.
    plx = point[0] - convex[l][0]
    ply = point[1] - convex[l][1]

    rpx = convex[r][0] - point[0]
    rpy = convex[r][1] - point[1]

    clockwise = ccw_vec(plx, ply, rpx, rpy)
    if clockwise < 0:
        return IN
    elif clockwise == 0:
        return BOUNDARY
    return OUT

def tangent(hull, point, counter_clock_dir):
    # counter_clock_dir : true 반시계, false 시계
    retx = hull[0][0] - point[0]
    rety = hull[0][1] - point[1]

    l = 0
    r = len(hull) - 1
    while l + 3 < r:
        p1 = (l * 2 + r) // 3
        p2 = (l + r * 2) // 3
        if ccw_vec(
            hull[p1][0] - point[0], hull[p1][1] - point[1],
            hull[p2][0] - point[0], hull[p2][1] - point[1]) >= 0:
            l = p1
        else:
            r = p2

    for i in range(l, r + 1):
        if (counter_clock_dir):
            if ccw_vec(hull[i][0] - point[0], hull[i][1] - point[1], retx, rety) >= 0:
                retx = hull[i][0] - point[0]
                rety = hull[i][1] - point[1]
        else:
            if ccw_vec(hull[i][0] - point[0], hull[i][1] - point[1], retx, rety) <= 0:
                retx = hull[i][0] - point[0]
                rety = hull[i][1] - point[1]
    
    l = 0
    r = len(hull) - 1
    while l + 3 < r:
        p1 = (l * 2 + r) // 3
        p2 = (l + r * 2) // 3
        if ccw_vec(
            hull[p1][0] - point[0], hull[p1][1] - point[1],
            hull[p2][0] - point[0], hull[p2][1] - point[1]) <= 0:
            l = p1
        else:
            r = p2

    for i in range(l, r + 1):
        if (counter_clock_dir):
            if ccw_vec(hull[i][0] - point[0], hull[i][1] - point[1], retx, rety) >= 0:
                retx = hull[i][0] - point[0]
                rety = hull[i][1] - point[1]
        else:
            if ccw_vec(hull[i][0] - point[0], hull[i][1] - point[1], retx, rety) <= 0:
                retx = hull[i][0] - point[0]
                rety = hull[i][1] - point[1]
    
    return (retx, rety)

def nearIndex(hull, point, dir):
    l = 0
    r = len(hull) - 1

    # hull 에서 접선에 가까운 인덱스를 구함
    while True:
        a = ccw_vec(
            hull[r][0] - point[0], hull[r][1] - point[1],
            dir[0], dir[1]) >= 0
        b = ccw_vec(
            hull[l][0] - point[0], hull[l][1] - point[1],
            dir[0], dir[1]) >= 0
        if a and not b:
            l = r
            break

        while (l + 1 < r):
            mid = l + (r - l) // 2

            vmid_x = hull[mid][0] - point[0]
            vmid_y = hull[mid][1] - point[1]
            vl_x   = hull[l][0] - point[0]
            vl_y   = hull[l][1] - point[1]
            vr_x   = hull[r][0] - point[0]
            vr_y   = hull[r][1] - point[1]

            if ccw_vec(vl_x, vl_y, vmid_x, vmid_y) >= 0:
                a = ccw_vec(
                    vl_x, vl_y,
                    dir[0], dir[1]) >= 0
                b = ccw_vec(
                    vmid_x, vmid_y,
                    dir[0], dir[1]) >= 0
                if a and not b:
                    r = mid
                else:
                    l = mid
            else:
                a = ccw_vec(
                    vmid_x, vmid_y,
                    dir[0], dir[1]) >= 0
                b = ccw_vec(
                    vr_x, vr_y,
                    dir[0], dir[1]) >= 0
                if a and not b:
                    l = mid
                else:
                    r = mid
        break
    return l

def lineIntersect(x1, y1, x2, y2, x3, y3, x4, y4):
    ux = Decimal((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
    dx = Decimal((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))

    uy = Decimal((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4))
    dy = Decimal((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))

    x = ux / dx
    y = uy / dy
    return (x, y)

read()

preprocess()

for q in query:
    if isInside(convexBig, q) <= 0:
        print("OUT")
        continue

    if isInside(convexSmall, q) >= 0:
        print("IN")
        continue

    # 작은 convex 와 접선 구하기
    up_tangent1 = tangent(uphullSmall, q, True)
    up_tangent2 = tangent(downHullSmall, q, True)

    down_tangent1 = tangent(uphullSmall, q, False)
    down_tangent2 = tangent(downHullSmall, q, False)

    up_tangent = up_tangent1 if ccw_vec(
        up_tangent1[0], up_tangent1[1],
        up_tangent2[0], up_tangent2[1]) >= 0 else up_tangent2

    down_tangent = down_tangent1 if ccw_vec(
        down_tangent1[0], down_tangent1[1],
        down_tangent2[0], down_tangent2[1]) <= 0 else down_tangent2

    up_tangent_index = nearIndex(convexBig, q, up_tangent)
    down_tangent_index = nearIndex(convexBig, q, down_tangent)

    # 구러면.. 여기까진 정수로 구했음
    # 이제부터 Decimal 로 가볼까?
    upIntersect = lineIntersect(
        convexBig[up_tangent_index][0], convexBig[up_tangent_index][1],
        convexBig[(up_tangent_index + 1) % N][0], convexBig[(up_tangent_index + 1) % N][1],
        q[0], q[1],
        q[0] + up_tangent[0], q[1] + up_tangent[1])
    downIntersect = lineIntersect(
        convexBig[down_tangent_index][0], convexBig[down_tangent_index][1],
        convexBig[(down_tangent_index + 1) % N][0], convexBig[(down_tangent_index + 1) % N][1],
        q[0], q[1],
        q[0] + down_tangent[0], q[1] + down_tangent[1])

    big: Decimal = 0
    if up_tangent_index == down_tangent_index:
        # 한 선분내에 점이 두개있다면 따로 처리
        vup_x = upIntersect[0] - q[0]
        vup_y = upIntersect[1] - q[1]
        vdown_x = downIntersect[0] - q[0]
        vdown_y = downIntersect[1] - q[1]

        big = cross(vup_x, vup_y, vdown_x, vdown_y)
        if big < 0:
            big = -big
    else:
        if down_tangent_index < up_tangent_index:
            down_tangent_index += N
        
        start = convexBig[(up_tangent_index + 1) % N]
        end = convexBig[down_tangent_index % N]

        # get upTriangle
        upTriangleBig = cross(
            upIntersect[0] - q[0], upIntersect[1] - q[1],
            start[0] - q[0], start[1] - q[1]
        )
        if upTriangleBig < 0:
            upTriangleBig = -upTriangleBig

        # get downTriangle
        downTriangleBig = cross(
            downIntersect[0] - q[0], downIntersect[1] - q[1],
            end[0] - q[0], end[1] - q[1]
        )
        if downTriangleBig < 0:
            downTriangleBig = -downTriangleBig
        
        fan: Decimal = 0
        fan = fan + cross(q[0], q[1], start[0], start[1])
        fan = fan + prefixSumConvexBig[down_tangent_index - 1]
        fan = fan - prefixSumConvexBig[up_tangent_index]
        fan = fan + cross(end[0], end[1], q[0], q[1])
        if fan < 0:
            fan = -fan
        big = upTriangleBig + fan + downTriangleBig

    small: Decimal = 0
    ux = q[0] + up_tangent[0]
    uy = q[1] + up_tangent[1]
    dx = q[0] + down_tangent[0]
    dy = q[1] + down_tangent[1]

    up_index_for_small_convex = convexSmallCoord2Index.get((ux, uy))
    down_index_for_small_convex = convexSmallCoord2Index.get((dx, dy))

    small = small + cross(
        q[0], q[1],
        convexSmall[up_index_for_small_convex][0], convexSmall[up_index_for_small_convex][1])
    small = small + cross(
        convexSmall[down_index_for_small_convex][0], convexSmall[down_index_for_small_convex][1],
        q[0], q[1])
    
    if (down_index_for_small_convex < up_index_for_small_convex):
        down_index_for_small_convex = down_index_for_small_convex + M
    
    small = small + prefixSumConvexSmall[down_index_for_small_convex - 1]
    if up_index_for_small_convex > 0:
        small = small - prefixSumConvexSmall[up_index_for_small_convex - 1]
    
    if small < 0:
        small = -small

    ret: Decimal = (big - small) / 2

    print(ret.quantize(Decimal('1.0000000000')))
