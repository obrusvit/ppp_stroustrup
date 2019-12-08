#ifndef MY_GUARD_LINEAR_SEARCH
#define MY_GUARD_LINEAR_SEARCH

template<typename Iterator, typename T>
bool my_linear_search(Iterator s, Iterator e, const T& to_find){
    for(Iterator it = s; it != e; it++){
        if((*it) == to_find){
            return true;
        }
    }
    return false;
}

#endif
