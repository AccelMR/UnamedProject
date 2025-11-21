#include "Player.h"
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Player::_bind_methods() {
    // Si quieres luego, aquí puedes bindear getters/setters de speed, etc.
}

void Player::_ready() {
    // Buscar el CollisionShape3D que ya pusiste en la escena:
    collision = get_node<CollisionShape3D>("CollisionShape3D");
    // Si quieres, aquí podrías ajustar el tamaño de la cápsula por código.
}

void Player::_physics_process(double delta) {
    Vector3 vel = get_velocity();

    // WASD
    Vector2 input_dir(
        Input::get_singleton()->get_action_strength("move_right") -
        Input::get_singleton()->get_action_strength("move_left"),
        Input::get_singleton()->get_action_strength("move_backward") -
        Input::get_singleton()->get_action_strength("move_forward")
    );

    Vector3 dir(input_dir.x, 0, input_dir.y);

    if (dir.length() > 0.01f) {
        dir = dir.normalized();
        vel.x = dir.x * speed;
        vel.z = dir.z * speed;
    } else {
        vel.x = 0.0f;
        vel.z = 0.0f;
    }

    // Salto
    if (is_on_floor() && Input::get_singleton()->is_action_just_pressed("jump")) {
        vel.y = jump_velocity;
    }

    set_velocity(vel);
    move_and_slide();
}
