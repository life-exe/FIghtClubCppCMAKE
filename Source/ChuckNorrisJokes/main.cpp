#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include <optional>

namespace httpCodes
{
constexpr int HTTP_OK = 200;
constexpr int HTTP_NOT_FOUND = 404;
}  // namespace httpCodes

constexpr const char* CHUCK_URL = "https://api.chucknorris.io/jokes/random";

template <typename T>
static std::optional<T> parse(const std::string& jsonStr)
{
    try
    {
        const auto json = nlohmann::json::parse(jsonStr);
        return json.get<T>();
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cout << "Wrong JSON field: " << e.what() << std::endl;
    }
    catch (nlohmann::json::parse_error& e)
    {
        std::cout << "Parse error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Something wrong with JSON." << std::endl;
    }

    return std::nullopt;
}

struct ChuckResponse
{
    std::string value;
    std::string url;
    std::string id;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChuckResponse, value, url, id);
};

int main()
{
    cpr::Response response = cpr::Get(cpr::Url{CHUCK_URL});
    std::cout << response.status_code << std::endl;

    if (response.status_code == httpCodes::HTTP_OK)
    {
        std::cout << response.header["content-type"] << std::endl;
        std::cout << response.text << std::endl;

        if (const auto chuckResponse = parse<ChuckResponse>(response.text))
        {
            std::cout << "======================" << std::endl;
            std::cout << chuckResponse->value << std::endl;
            std::cout << chuckResponse->id << std::endl;
            std::cout << chuckResponse->url << std::endl;
        }
    }

    std::cin.get();

    return EXIT_SUCCESS;
}