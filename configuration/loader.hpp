#include <string>

namespace srng{

struct Configuration;

class ConfigurationLoader
{
public:
    virtual ~ConfigurationLoader() = default;
    virtual Configuration get_configuration() = 0;
};

}//namespace srng
