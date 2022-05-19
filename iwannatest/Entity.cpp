#include "Entity.h"
Entity::Entity() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->imageState = 0; // 스프라이트의 몇 번 이미지를 사용
	this->imageNumber = 0; // 이미지 진행
	this->imageFrame = 0; // 한 이미지 상태에서 진행된 프레임
	this->imageFlip = 0; // 좌우 반전여부
}
void Entity::enterFrame() {
	
}