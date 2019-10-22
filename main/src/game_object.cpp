#include "game_object.hpp"

int GameObject::Write(OutputStream &stream) {
    return 1;
}
int GameObject::Read(InputStream &stream) {
    return 1;
}
void GameObject::setPosition(float x,float y,float z){
    this->position.pos_x=x;
    this->position.pos_y=y;
    this->position.pos_z=z;
}

void GameObject::setRotation(float r_x,float r_y,float r_z,float r_w){
    this->rotation.r_x=r_x;
    this->rotation.r_y=r_y;
    this->rotation.r_z=r_z;
    this->rotation.r_w=r_w;
}
