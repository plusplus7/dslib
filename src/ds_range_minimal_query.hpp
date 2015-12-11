#ifndef DSLIB_DS_RANGE_MINIMAL_QUERY_HPP_
#define DSLIB_DS_RANGE_MINIMAL_QUERY_HPP_

#include "ds_multiple_precision.h"

namespace dslib {

int _hibit32(unsigned int n)
{
    n |= (n >>  1);
    n |= (n >>  2);
    n |= (n >>  4);
    n |= (n >>  8);
    n |= (n >> 16);
    return n - (n >> 1);
}

int _bit2(unsigned int n)
{
    int cnt = 0;
    while (n) n>>=1, cnt++;
    return cnt-1;
}

template<typename T>
class DsRmqInstance
{
public:
    void _init(T *array) {
        for (int i=0; i<m_len; i++) {
            m_sparse_table[0][i] = array[i];
        }
        for (int j=1; (1<<j) <= m_len; j++) {
            for (int i=0; i+(1<<j)-1 <= m_len; i++) {
                m_sparse_table[j][i] = DMP_MIN(m_sparse_table[j-1][i], m_sparse_table[j-1][i+(1<<(j-1))]);
            }
        }
    }
    void init(T *array, int n)
    {
        m_len = n;
        m_sparse_table = new T *[_bit2(_hibit32(m_len)) + 1];
        for (int j=0; (1<<j) <= m_len; j++) {
            m_sparse_table[j] = new T [m_len-(1<<j)+1];
        }
        _init(array);
    }

    void init(T *array, int n, T **stable)
    {
        m_len = n;
        m_sparse_table = stable;
        _init(array);
    }
    int query(int l, int r)
    {
        int k=0;
        while ((1<<(k+1)) <= r-l+1) k++;
        return DMP_MIN(m_sparse_table[k][l], m_sparse_table[k][r-(1<<k)+1]);
    }

    void clear()
    {
        for (int i=0; (1<<i)<=m_len; i++) {
            delete [] m_sparse_table[i];
        }
        delete [] m_sparse_table;
    }

private:
    T **m_sparse_table;
    int m_len;
};

} /* dslib */

#endif /* end of include guard: DS_RANGE_MINIMAL_QUERY_HPP_ */
