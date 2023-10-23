from math import *

L1 = 105 # mm
L2 = 162
L3 = 130
d1 = 270
d3 = 55


def Forward_Kinematic(t1, t2, t3):
    t1 = radians(t1)
    t2 = radians(t2)
    t3 = radians(t3)

    Px = (
        L1 * cos(t1)
        + d3 * sin(t1)
        + L2 * cos(t1) * cos(t2)
        + L3 * cos(t1) * cos(t2) * cos(t3)
        - L3 * cos(t1) * sin(t2) * sin(t3)
    )
    Py = (
        L1 * sin(t1)
        - d3 * cos(t1)
        + L2 * cos(t2) * sin(t1)
        + L3 * cos(t2) * cos(t3) * sin(t1)
        - L3 * sin(t1) * sin(t2) * sin(t3)
    )
    Pz = d1 + L3 * sin(t2 + t3) + L2 * sin(t2)
    Px = round(Px, 3)
    Py = round(Py, 3)
    Pz = round(Pz, 3)
    return Px, Py, Pz


def Inverse_Kinematic(Px, Py, Pz, theta):
    # Tính anpha
    cos_a = Px / sqrt(Px * Px + Py * Py)
    sin_a = -Py / sqrt(Px * Px + Py * Py)
    a = atan2(sin_a, cos_a)

    # Tính theta1
    theta1 = asin(d3 / (sqrt(Px * Px + Py * Py))) - a
    theta1 = degrees(theta1)

    # Tính theta2
    a1 = sin(radians(theta))
    h = (Pz - d1 - L3 * a1) / L2
    theta2 = asin(h)
    theta2 = degrees(theta2)

    # Tính theta3
    theta3 = theta - theta2

    # Làm tròn theta1, theta2, theta3 đến 2 chữ số thập phân
    theta1 = round(theta1, 2)
    theta2 = round(theta2, 2)
    theta3 = round(theta3, 2)
    return theta1, theta2, theta3
