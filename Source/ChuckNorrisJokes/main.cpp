#include "raylib.h"

#if defined(_WIN32)
#define NOGDI   // All GDI defines and routines
#define NOUSER  // All USER defines and routines
#endif

#include <Windows.h>  // or any library that uses Windows.h

#if defined(_WIN32)  // raylib uses these names as function parameters
#undef near
#undef far
#endif

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

std::string requestJoke()
{
    std::string joke{};
    cpr::Response response = cpr::Get(cpr::Url{CHUCK_URL});
    std::cout << response.status_code << std::endl;

    if (response.status_code == httpCodes::HTTP_OK)
    {
        std::cout << response.header["content-type"] << std::endl;
        std::cout << response.text << std::endl;

        if (const auto chuckResponse = parse<ChuckResponse>(response.text))
        {
            joke = chuckResponse->value;
            std::cout << "======================" << std::endl;
            std::cout << chuckResponse->value << std::endl;
            std::cout << chuckResponse->id << std::endl;
            std::cout << chuckResponse->url << std::endl;
        }
    }
    return joke;
}

void DrawTextCentered(const std::string& text, int fontSize, const Color& color, int screenWidth, int screenHeight, int padding = 20)
{
    const int maxWidth = screenWidth - padding * 2;
    std::vector<std::string> lines;
    std::string currentLine;
    std::string word;

    const auto exceedsMaxWidth = [&](const std::string& line, const std::string& newWord)
    { return !line.empty() && MeasureText((line + newWord).c_str(), fontSize) > maxWidth; };

    // Split by spaces to wrap words
    for (char letter : text)
    {
        if (letter == ' ')
        {
            if (exceedsMaxWidth(currentLine, word))
            {
                lines.push_back(currentLine);
                currentLine = word + " ";
                word.clear();
            }
            else
            {
                currentLine += word + " ";
                word.clear();
            }
        }
        else
        {
            word += letter;
        }
    }

    // Handle the last word and line
    if (!word.empty())
    {
        if (exceedsMaxWidth(currentLine, word))
        {
            lines.push_back(currentLine);
            lines.push_back(word);
        }
        else
        {
            lines.push_back(currentLine + word);
        }
    }
    else if (!currentLine.empty())
    {
        lines.push_back(currentLine);
    }

    const int lineSpacing = fontSize / 4;
    const int totalHeight = lines.size() * fontSize + (lines.size() - 1) * lineSpacing;
    const int startY = (screenHeight - totalHeight) / 2;

    // Draw each line
    for (size_t i = 0; i < lines.size(); i++)
    {
        const int textWidth = MeasureText(lines[i].c_str(), fontSize);
        const int posX = (screenWidth - textWidth) / 2;
        const int posY = startY + i * (fontSize + lineSpacing);
        DrawText(lines[i].c_str(), posX, posY, fontSize, color);
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Chuck Norris jokes");
    SetTargetFPS(60);

    std::string joke = requestJoke();

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            joke = requestJoke();
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawTextCentered(joke, 20, LIGHTGRAY, screenWidth, screenHeight);
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}