#include <iostream>
#include "cache.h"

int main()
{
    size_t m = 0, n = 0;
    std::cin >> m >> n;
    
    cache_t <page> c{m};

    unsigned hits = 0;
    for (unsigned i = 0; i < n; i++)
    {
        size_t id;
        std::cin >> id;
        page& p = *new page{id};

        if (c.lookup_update(p.index, p, page_comp));
    }
    return 0;
}