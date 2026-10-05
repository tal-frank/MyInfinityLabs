
template <typename BASE, typename KEY, typename ...>
class factory
{
public:
    std::shared_ptr<BASE> Create(KEY key ...);
    register(); 
private:

}