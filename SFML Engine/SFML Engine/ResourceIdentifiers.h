#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		Playo,
		Astro,
		Nest,
		GameBackground,
		PauseBackground,
		MainMenuBG,
		Button,
		HUD,
		GasCloud,
	};
}

namespace Shaders
{
	enum ID
	{
		Shockwave,
		Ripple,
	};
}

namespace Fonts
{
	enum ID
	{
		PS2P
	};
}

namespace SoundEffect
{
	enum ID
	{
		Charge
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>	FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>	ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;
