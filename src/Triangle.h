//
// Created by Karthik Rao on 9/6/20.
//

#ifndef PANTHEON_TRIANGLE_H
#define PANTHEON_TRIANGLE_H


#include <vector>

class Triangle {
private:
    std::vector<float> vertices;
    std::vector<unsigned short> indices;

public:
    void init();
    void render();
};


#endif //PANTHEON_TRIANGLE_H
