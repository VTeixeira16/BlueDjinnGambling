#ifndef BD_ANIMATION_TEXTURE_HPP
#define BD_ANIMATION_TEXTURE_HPP

#include <string>
#include <vector>

class AnimationTexture {
public:
	std::vector<std::string> textureList;
	int velocity;
private:
	AnimationTexture();
	int AddTextureToAnimation();
	int GetAnimationSize();


};

#endif //BD_ANIMATION_TEXTURE_HPP
