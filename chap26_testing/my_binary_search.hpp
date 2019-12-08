#ifndef MY_GUARD_BINARY_SEARCH
#define MY_GUARD_BINARY_SEARCH
template<typename Iterator, typename T>
bool my_binary_search(Iterator s, Iterator e, const T& to_find){
    //obvious error
    if(e<=s) return false;
    
    int num_elems = e-s;
    if(s[num_elems/2] == to_find) return true;
    //end condition, the only element available is not it
    if(num_elems == 1){
        return false;
    }
    if(s[num_elems/2] < to_find){
        return my_binary_search(s+num_elems/2 ,e, to_find);
    }
    if(s[num_elems/2] > to_find){
        return my_binary_search(s, e-num_elems/2, to_find);
    }
}

template<typename Iterator, typename T, typename Comp>
    //requires ForwardIterator<Iterator>() && BinaryPredicate<Comp, T>()
bool my_binary_search(Iterator s, Iterator e, const T& to_find, const Comp comp){
    if(e<=s) return false; //obvious error
    
    int num_elems = e-s;
    if(s[num_elems/2] == to_find) return true;
    //end condition, the only element available is not it
    if(num_elems == 1){
        return false;
    }
    if(comp(s[num_elems/2], to_find)){
        return my_binary_search(s+num_elems/2 ,e, to_find, comp);
    }
    if(comp(s[num_elems/2], to_find)){
        return my_binary_search(s, e-num_elems/2, to_find, comp);
    }
}

#endif
