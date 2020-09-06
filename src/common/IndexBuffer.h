//
// Created by Karthik Rao on 9/6/20.
//

#ifndef PANTHEON_INDEXBUFFER_H
#define PANTHEON_INDEXBUFFER_H

class IndexBuffer {
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned short*, unsigned int count);
    ~IndexBuffer(); //C++ destructor

    void bind() const;
    void unBind() const;

    inline unsigned int getCount() const { return m_Count; }
};
#endif //PANTHEON_INDEXBUFFER_H
