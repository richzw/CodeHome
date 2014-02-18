#include <vector>

template <typename key, typename container >
void parallel_sort(container & _container){}

template <typename key, typename container >
void partition_less(std::vector<key> * vless, container * _container, key privot){
for(size_t i = 0; i < (*_container).size(); i++){
        if ((*_container)[i] < privot){
            vless->push_back((*_container)[i]);
        }
    }
}

template <typename key,  typename container >
void partition_more(std::vector<key> * vmore, container * _container, key privot){
for(size_t i = 0; i < (*_container).size(); i++){
        if ((*_container)[i] >= privot){
            vmore->push_back((*_container)[i]);
        }
    }
}

template <typename key, typename container >
int sort_less(container * _container, std::vector<key> & vless, boost::atomic_uint32_t * depth){
    parallel_sort_impl<key>(&vless, *depth);

    for(size_t i = 0; i < vless.size(); i++){
        (*_container)[i] = vless[i];
    }

    return 0;
}

template <typename key, typename container >
int sort_more(container * _container, std::vector<key> & vmore, boost::atomic_uint32_t * depth){
    parallel_sort_impl<key>(&vmore, *depth);

    size_t pos = (*_container).size()-vmore.size();
    for(size_t i = 0; i < vmore.size(); i++){
        (*_container)[i+pos] = vmore[i];
    }

    return 0;
}

template <typename key, typename container >
void parallel_sort_impl(container * _container, boost::atomic_uint32_t & depth){
    if (_container->size() < threshold || depth.load() > processors_count()){
        std::sort(_container->begin(), _container->end());
    }else{
        key privot = (*_container)[_container->size()/2];

    std::vector<key> vless, vmore;
    auto partition_result = std::async(std::launch::async, partition_less<key, container>, &vless, _container, privot);
    partition_more(&vmore, _container, privot);
    partition_result.get();

        auto result = std::async(std::launch::async, sort_less<key, container>, _container, vless, &depth);
        sort_more(_container, vmore, &depth);
        result.get();
    }
}
