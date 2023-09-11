#ifndef CACHE_H
#define CACHE_H

#include <cstddef>
#include <list>
#include <unordered_map>
#include <stdlib.h>

struct page
{
    unsigned index;
    unsigned frequency = 0;

    page(size_t id) : index(id) {};

    void add_to_cache()
    {
        frequency++;
    }
};

int page_comp(page& first, page& second)
{
        return first.frequency - second.frequency;
}

template <typename elem_t, typename key_t = unsigned>
struct cache_t
{
        size_t max_size;        
        std::list<elem_t> cache;
        
        using list_it = typename std::list<elem_t>::iterator;
        std::unordered_map<key_t, list_it> hash;

        cache_t(size_t sz) : max_size(sz) {};

        bool full()
        {
            if (cache.size() == max_size) return true;
            else return false;
        }

        elem_t& elem_out(int comp(elem_t&, elem_t&))
        {
            elem_t& elem_out = cache.begin();
            for (auto now : cache)
            {
                if (comp(now, elem_out) <= 0)
                    elem_out = now;
            }
            return elem_out;
        }

        bool lookup_update(key_t key, elem_t& elem, int comp(elem_t&, elem_t&))
        {
            auto hit = hash.find(key);

            if (hit == hash.end())
            {
                if (full())
                {
                    elem_t& elem_delete = elem_out(comp);
                    hash.erase(elem_delete);
                    cache.erase(elem_delete);
                }
                cache.push_front(elem);
                elem.add_to_cache();
                hash[key] = cache.begin();
                return false;
            }
            
            if (hit != cache.begin())
            {
                hit.add_to_cache();
                cache.splice(cache.begin(), cache, hit, std::next(hit));
            }            
            return true;
        }

};

#endif