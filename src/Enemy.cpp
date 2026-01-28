#include "Enemy.h"
#include "FSM/State.h"
#include "FSM/States/IdleState.h"
#include "FSM/States/PatrolState.h"
#include "FSM/States/AttackState.h"

#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

// Skills
#include "Skills/SkillFireCone.h"

void Enemy::_bind_methods() 
{
  UtilityFunctions::print("Enemy::_bind_methods called");

  ClassDB::bind_method(D_METHOD("GetSkillSet"), &Enemy::GetSkillSet);
  ClassDB::bind_method(D_METHOD("SetSkillSet", "skillSet"), &Enemy::SetSkillSet);
  ClassDB::bind_method(D_METHOD("OnNavigationFinished"), &Enemy::OnNavigationFinished);

  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
                            "skillSet",
                            PROPERTY_HINT_RESOURCE_TYPE, 
                            "SkillSet"), 
               "SetSkillSet", "GetSkillSet");
}

void Enemy::OnNavigationFinished()
{
  // Destination reached
  UtilityFunctions::print("Enemy::OnNavigationFinished");
  set_velocity(Vector3(0.f, 0.f, 0.f));

  m_fsm->SetState(StateID::ATTACK);
}

void Enemy::_ready()
{
  m_navigationAgent = get_node<NavigationAgent3D>("NavigationAgent3D");
  DEV_ASSERT(m_navigationAgent);

  m_navigationAgent->set_target_desired_distance(1.2f);
  m_navigationAgent->connect("navigation_finished",
    Callable(this, "OnNavigationFinished"));

  m_player = get_node<Player>("../Player");
  DEV_ASSERT(m_player);

  // Create and initialize finite state machine
  m_fsm = make_shared<FiniteStateMachine>();
  DEV_ASSERT(m_fsm);

  m_fsm->Initialize();
  
  // Subscribe states
  shared_ptr<IdleState> ptrIdleState = make_shared<IdleState>(m_fsm);
  m_fsm->AddState(StateID::IDLE, ptrIdleState);
  shared_ptr<PatrolState> ptrPatrolState = make_shared<PatrolState>(m_fsm, this);
  m_fsm->AddState(StateID::PATROL, ptrPatrolState);
  shared_ptr<AttackState> ptrAttackState = make_shared<AttackState>(m_fsm, this);
  m_fsm->AddState(StateID::ATTACK, ptrAttackState);

  // Set initial state
  m_fsm->SetState(StateID::IDLE);

  // Initialize skill set
  if (!m_skillSet.is_valid())
  {
    UtilityFunctions::push_warning("Player has no SkillSet assigned");
    return;
  }

  m_skillSet->InstantiateSkills(this);
}

void Enemy::_process(double delta)
{
  // Update State Machine
  m_fsm->Update();
}

void Enemy::MoveTo(const Vector3 &position)
{
  // Apparently just calculates the path to the point
  m_navigationAgent->set_target_position(position);

  // Move agent to position
  m_destination = m_navigationAgent->get_next_path_position();
  m_direction = (m_destination - get_global_position()).normalized();

  set_velocity(m_direction * 2.0f);
  move_and_slide();
}

void Enemy::ExecuteAbility()
{
  Vector<ActiveSkillNode*> skills = m_skillSet->GetActiveSkills();
  skills[0]->Execute();
}
