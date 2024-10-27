import math

def generate_polygon(n, center=(0, 0), radius=1):
    points = []
    x_center, y_center = center

    for i in range(n):
        angle = 2 * math.pi * i / n  # 각도 계산
        x = x_center + radius * math.cos(angle)
        y = y_center + radius * math.sin(angle)
        points.append((round(x), round(y)))  # 정수 좌표로 변환

    return points

N = 100000
M = 100000
Q = 100000

print(N, M, Q)

# 예제 사용
n = N  # 5각형
center = (0, 0)  # 중심점
radius = 250000  # 반지름

polygon_points = generate_polygon(n, center, radius)
polygon_points = generate_polygon(n, center, radius)
for i, item in enumerate(polygon_points):
    print(item[0], item[1])

n = M  # 5각형
center = (0, 0)  # 중심점
radius = 500000  # 반지름

polygon_points = generate_polygon(n, center, radius)
for i, item in enumerate(polygon_points):
    print(item[0], item[1])

for i in range(Q):
    print(250001, 0)