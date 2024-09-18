#include <iostream>
#include <optional>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

template <typename T>
// static bool parse(T& data, const std::string& JSONstr)
static std::optional<T> parse(const std::string& JSONstr)
{
    try
    {
        const auto json = nlohmann::json::parse(JSONstr);
        return json.get<T>();
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cout << "JSON parse error : " << e.what() << std::endl;
    }

    return std::nullopt;
}

struct ChuckResponse
{
    std::string value;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChuckResponse, value)
};

int main(void)
{
    cpr::Response response = cpr::Get(cpr::Url{"http://api.chucknorris.io/jokes/random"});

    std::cout << response.status_code << std::endl;
    std::cout << response.header["content-type"] << std::endl;
    std::cout << response.text << std::endl;

    if (response.status_code == 200)
    {
        if (const auto chuckResponse = parse<ChuckResponse>(response.text))
        {
            std::cout << std::endl << chuckResponse->value << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
