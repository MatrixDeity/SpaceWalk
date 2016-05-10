#pragma once

#include <vector>

#include "SFML\Graphics.hpp"

using namespace sf;

class AnimatedSprite : public Drawable, public Transformable
{
public:
    class Animation
    {
    public:
        Animation(const IntRect& firstFrame, Uint16 number, float speed, bool isLoop) :
        mFrames(),
        mNumber(number),
        mSpeed(speed),
        mCurrentFrame(0.0F),
        mIsLoop(isLoop)
        {
            mFrames.reserve(number);
            for (Uint16 i = 0; i < number; ++i)
                mFrames.push_back(IntRect(firstFrame.left + i * firstFrame.width, firstFrame.top, firstFrame.width, firstFrame.height));
        }

        void play()
        {
            mCurrentFrame = 0.0F;
        }

        void tick(float time)
        {
            if (mCurrentFrame < static_cast<float>(mNumber))
                mCurrentFrame += time * mSpeed;
            else
                if (mIsLoop)
                    mCurrentFrame = 0.0F;
        }

        const IntRect& getFrame() const
        {
            return mFrames.at(static_cast<int>(mCurrentFrame));
        }

    AnimatedSprite(const Texture& texture, Animation& animation) :
    mTexture(&texture),
    mAnimation(animation)
    {
    }

    virtual ~AnimatedSprite()
    {
    }

    void tick(float time)
    {
        mAnimation.tick(time);
        const IntRect& rect = mAnimation.getFrame();

        mVertices[0].position = Vector2f(0.0F, 0.0F);
        mVertices[1].position = Vector2f(0.0F, static_cast<float>(rect.height));
        mVertices[2].position = Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        mVertices[3].position = Vector2f(static_cast<float>(rect.width), 0.0F);

        float left = static_cast<float>(rect.left) + 0.0001F;
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        mVertices[0].texCoords = Vector2f(left, top);
        mVertices[1].texCoords = Vector2f(left, bottom);
        mVertices[2].texCoords = Vector2f(right, bottom);
        mVertices[3].texCoords = Vector2f(right, top);
    }

    void setAnimation(const String& name)
    {
        if (name == mCurrentAnimation || mAnimations.find(name) == mAnimations.end())
            return;

        mCurrentAnimation = name;
        mAnimations[mCurrentAnimation].play();
    }

    const Animation& getAnimation() const
    {
        return mAnimation;
    }

    FloatRect getLocalBounds() const
    {
        const IntRect& rect = mAnimations[mCurrentAnimation].getFrame();

        return FloatRect(0.0F, 0.0F, static_cast<float>(rect.width < 0 ? -rect.width : rect.width),
            static_cast<float>(rect.height < 0 ? -rect.height : rect.height));
    }

    FloatRect getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

private:
    virtual void draw(RenderTarget& target, RenderStates states) const override
    {
        if (!mTexture || mCurrentAnimation == "")
            return;

        states.transform *= getTransform();
        states.texture = mTexture;
        target.draw(mVertices, 4, sf::Quads, states);
    }

    private:
        std::vector<IntRect> mFrames;
        Uint16 mNumber;
        float mSpeed;
        float mCurrentFrame;
        bool mIsLoop;
    };

    const Texture* mTexture;
    Vertex mVertices[4];
    Animation& mAnimation;
};
