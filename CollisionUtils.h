#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

struct Boundary {
    float left, right, top, bottom;
};

inline bool isColliding(float x, float y, float width, float height, const Boundary& boundary) {
    return !(x + width < boundary.left || x > boundary.right || y + height < boundary.bottom || y > boundary.top);
}
std::vector<Boundary> overlayBoundaries;



#endif // COLLISION_UTILS_H
