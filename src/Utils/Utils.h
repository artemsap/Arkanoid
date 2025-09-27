#pragma once

#include <stdint.h>
#include <glm.hpp>

class Utils
{
public:
	static constexpr uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b)
	{
		// Устанавливаем альфа-канал в 0xFF (255) и компоненты цветов
		return (0xFF << 24) | (r << 16) | (g << 8) | b;
	}

	static bool checkAABBIntersection(const glm::vec2& pos1, const glm::vec2& size1,
                                      const glm::vec2& pos2, const glm::vec2& size2)
    {
        glm::vec2 min1 = pos1;
        glm::vec2 max1 = pos1 + size1;
        glm::vec2 min2 = pos2;
        glm::vec2 max2 = pos2 + size2;

        return (max1.x > min2.x && min1.x < max2.x &&
                max1.y > min2.y && min1.y < max2.y);
    }
};