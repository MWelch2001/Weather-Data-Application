#include "Util.h"
namespace Util 
{

    void Util::Pause()
    {
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    int ValidateIntInput(int minBound, int maxBound)
    {
        int input;
        std::cin >> input;
        while (1)
        {
            if (std::cin.fail() || input < minBound || input > maxBound)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please try again" << std::endl;
                std::cin >> input;
            }
            if (!std::cin.fail())
                break;
        }
        return input;
    }

    float ValidateFloatInput(int minBound, int maxBound)
    {
        float input;
        std::cin >> input;
        while (1)
        {
            if (std::cin.fail() || input < minBound || input > maxBound)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please try again" << std::endl;
                std::cin >> input;
            }
            if (!std::cin.fail())
                break;
        }
        return input;
    }

}