#include "Rendering/Renderable_Object_2D.hpp"

namespace Isaac::Rendering
{
    Renderable_Object_2D::Renderable_Object_2D() noexcept = default;

    Renderable_Object_2D::Renderable_Object_2D(const RigidBody2D& body_, const std::vector<float>& color_,
                                               const int& screen_Width_, const int& screen_Height_) noexcept
        : screen_Width(screen_Width_), screen_Height(screen_Height_), body(body_), color(color_)
    {
        Coordinates.resize(3 * body.getVertexCount());
        for (int i = 0; i < 3 * body.getVertexCount(); i += 3)
        {
            std::vector<float> decomposedCoordinates = decompose_2D_Coordinates(
                screen_Width, screen_Height, body.getPosition() + body.getVertex(i / 3));
            Coordinates[i] = decomposedCoordinates[0];
            Coordinates[i + 1] = decomposedCoordinates[1];
            Coordinates[i + 2] = decomposedCoordinates[2];
        }

        indices.resize(3 * (body.getVertexCount() - 2));
        int x = 1;
        for (int i = 0; i < 3 * (body.getVertexCount() - 2); i += 3)
        {
            indices[i] = 0;
            indices[i + 1] = x;
            indices[i + 2] = x + 1;
            ++x;
        }
    }

    Renderable_Object_2D::Renderable_Object_2D(const Renderable_Object_2D& renderable_Object_2D_) noexcept
        : Renderable_Object_2D(renderable_Object_2D_.getBody(), renderable_Object_2D_.getColor(),
                               renderable_Object_2D_.getScreenWidth(), renderable_Object_2D_.getScreenHeight())
    {
    }

    Renderable_Object_2D& Renderable_Object_2D::operator=(const Renderable_Object_2D& other)
    {
        if (this != &other)
        {
            body = other.getBody();
            color = other.getColor();
            screen_Width = other.getScreenWidth();
            screen_Height = other.getScreenHeight();

            Coordinates = other.getCoordinates();
            indices = other.getIndices();
        }
        return *this;
    }

    int Renderable_Object_2D::getVertexCount() const noexcept { return body.getVertexCount(); }

    RigidBody2D Renderable_Object_2D::getBody() const noexcept { return body; }

    int Renderable_Object_2D::getScreenWidth() const noexcept { return screen_Width; }

    int Renderable_Object_2D::getScreenHeight() const noexcept { return screen_Height; };

    std::vector<float> Renderable_Object_2D::getCoordinates() const noexcept { return Coordinates; }

    std::vector<int> Renderable_Object_2D::getIndices() const noexcept { return indices; }

    std::vector<float> Renderable_Object_2D::getColor() const noexcept { return color; }

    std::vector<float> Renderable_Object_2D::decompose_2D_Coordinates(const int& screenWidth_, const int& screenHeight_,
                                                                      const Vector2f& vector_) noexcept
    {
        const float aspectRatio = std::max(screenHeight_, screenWidth_) / std::min(screenHeight_, screenWidth_);

        if (screenWidth_ > screenHeight_)
        {
            return {vector_.x() / screenWidth_, aspectRatio * vector_.y() / screenHeight_, 0.0};
        }
        if (screenHeight_ > screenWidth_)
        {
            return {aspectRatio * vector_.x() / screenWidth_, vector_.y() / screenHeight_, 0.0};
        }

        return {vector_.x() / screenWidth_, vector_.y() / screenHeight_, 0.0};
    }
} // namespace Isaac::Rendering
