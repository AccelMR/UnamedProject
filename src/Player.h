#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D);

private:
    CollisionShape3D *collision = nullptr;
    float speed = 5.0f;
    float jump_velocity = 5.0f;

protected:
    static void _bind_methods();

public:
    Player() = default;
    ~Player() = default;

    void _ready() override;
    void _physics_process(double delta) override;
};

#endif
