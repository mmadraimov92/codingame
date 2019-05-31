class Side:
    def __init__(self, face):
        self.face = face
        self.previous_rotation = None

    def rotate_x(self, clockwise=True):
        if self.face == 'F':
            self.face = 'U' if clockwise else 'D'
        elif self.face == 'U':
            self.face = 'B' if clockwise else 'F'
        elif self.face == 'B':
            self.face = 'D' if clockwise else 'U'
        elif self.face == 'D':
            self.face =  'F' if clockwise else 'B'
        self.previous_rotation = self.rotate_x

    def rotate_y(self, clockwise=True):
        if self.face == 'F':
            self.face = 'L' if clockwise else 'R'
        elif self.face == 'L':
            self.face = 'B' if clockwise else 'F'
        elif self.face == 'B':
            self.face = 'R' if clockwise else 'L'
        elif self.face == 'R':
            self.face = 'F' if clockwise else 'B'
        self.previous_rotation = self.rotate_y

    def rotate_z(self, clockwise=True):
        if self.face == 'D':
            self.face = 'L' if clockwise else 'R'
        elif self.face == 'L':
            self.face = 'U' if clockwise else 'D'
        elif self.face == 'U':
            self.face = 'R' if clockwise else 'L'
        elif self.face == 'R':
            self.face = 'D' if clockwise else 'U'
        self.previous_rotation = self.rotate_z


rotations = input()
face_1 = Side(input())
face_2 = Side(input())

for char in rotations:
    if char == '\'':
        face_1.previous_rotation(clockwise=False)
        face_1.previous_rotation(clockwise=False)
        face_2.previous_rotation(clockwise=False)
        face_2.previous_rotation(clockwise=False)
    elif char == 'x':
        face_1.rotate_x(clockwise=True)
        face_2.rotate_x(clockwise=True)
    elif char == 'y':
        face_1.rotate_y(clockwise=True)
        face_2.rotate_y(clockwise=True)
    elif char == 'z':
        face_1.rotate_z(clockwise=True)
        face_2.rotate_z(clockwise=True)


print(face_1.face)
print(face_2.face)
