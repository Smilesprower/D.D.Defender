#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures	/*!< ID of all game textures*/
{
	enum ID
	{
		Playo,
		Astro,
		Nest,
		GameBackground,
		PauseBackground,
		MainMenuBG,
		GameOverBG,
		GameWinBG,
		Button,
		HUD,
		GasCloud,
	};
}

namespace Shaders	/*!< ID of all game shaders*/
{
	enum ID
	{
		Shockwave,
		Ripple,
	};
}

namespace Fonts	/*!< ID of all game fonts*/
{
	enum ID
	{
		PS2P
	};
}

namespace SoundEffect	/*!< ID of all game SFX*/
{
	enum ID
	{
		Charge,
		Teleport,
		Lazer,
		Explosion,
		AlienBullet,
		Missile,
	};
}

namespace Music		/*!< ID of all game music*/
{
	enum ID
	{
		MenuTheme,
		GameTheme,
		GameOverTheme
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>	FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>	ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;
