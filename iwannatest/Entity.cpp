#include "Entity.h"
Entity::Entity() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->imageState = 0; // ��������Ʈ�� �� �� �̹����� ���
	this->imageNumber = 0; // �̹��� ����
	this->imageFrame = 0; // �� �̹��� ���¿��� ����� ������
	this->imageFlip = 0; // �¿� ��������
}
void Entity::enterFrame() {
	
}