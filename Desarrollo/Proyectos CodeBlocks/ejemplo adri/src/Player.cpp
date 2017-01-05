#include "Player.h"
#include <Box2D/Box2D.h>



Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 8;
    vida=100;
    smgr1=smgr;
    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    //modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
   // modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(0,0,10));

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(0, 10);
    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body->CreateFixture(&bodyShape, 1.0f);

    cuboProta = modelo->getPosition();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 1.f;
    body->CreateFixture(&fixtureDef);
}

core::vector3df Player::getCuboProta(){
    return modelo->getPosition();
}

void Player::setPosition(core::vector3df vec){
    modelo->setPosition(vec);
}

b2Body* Player::getBody(){
    return body;
}

void Player::setPosicionBody(float ang){
    //body->SetTransform(b2Vec2(cuboProta.X, cuboProta.Z), ang);
    /*std::cout << "cubo X: "<<cuboProta.Z<<" \n";
    std::cout << "cubo Z: "<<cuboProta.Z<<" \n";
    std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    std::cout << "body Z: "<<body->GetPosition().y  <<" \n";
    std::cout << "-------------- \n";*/
}

void Player::moverBody(core::vector3df vec){
    //body->ApplyLinearImpulse(b2Vec2(0, 5.0), b2Vec2(vec.X, vec.Z), true);
    movx = vec.X;
    movy = vec.Z;
    double modulo = sqrt((movx*movx) + (movy*movy));
    if(modulo != 0){
        movx = (movx / modulo) * velocidad;
        movy = (movy / modulo) * velocidad;
    }

    body->SetLinearVelocity(b2Vec2(movx, movy));
    //body->ApplyForce(b2Vec2(movx, movy), b2Vec2(movx, movy), true);
    //std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    //std::cout << "body Z: "<<body->GetPosition().y  <<" \n";

    //body->ApplyLinearImpulse(b2Vec2(0.1, 0.1), body->GetPosition());
    /*if(vec.X != body->GetPosition().x){
       //body->ApplyForce( b2Vec2(force,0), body->GetWorldCenter() );
    }
    if(vec.Y != body->GetPosition().y){
        //body->SetLinearVelocity(b2Vec2(0.0, 15.0));
    }*/
}

void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}
float Player::getVida(){
    return vida;
}
void Player::setVida(float v){
vida=v;
}
void Player::muerte(){
 smgr1->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(255, 255, 0, 0));
}
