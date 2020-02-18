#include "DeltaTime.h"


float DeltaTime::m_CurrentTime;
float DeltaTime::m_PreviousTime;
float DeltaTime::m_DeltaTime;
/*
initialise m_SecondsChecker to 0; 
later it will be incremented inside loop by spawn frequency; 
m_SpawnFrequency is a member variable of class MeteoritePool
*/
int DeltaTime::m_SecondsChecker = 0;