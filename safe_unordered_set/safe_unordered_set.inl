
namespace srng{

template<typename T>
inline std::pair<typename std::unordered_set<T>::iterator, bool> SafeUnorderedSet<T>::insert(T const& variable)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_unordered_set.insert(variable);
}

template <typename T>
inline std::unordered_set<T> SafeUnorderedSet<T>::get_set() const
{
    std::lock_guard<std::mutex> locker(m_mutex);
    return m_unordered_set;
}

}//namespace srng
