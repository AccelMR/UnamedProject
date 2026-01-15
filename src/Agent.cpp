#include "Agent.h"

void Agent::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("dummyPureVirtualFunction"), &Agent::dummyPureVirtualFunction);
}