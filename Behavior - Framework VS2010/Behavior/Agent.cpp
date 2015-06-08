// Agent.cpp: implementation of the CAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "Agent.h"

//Construct static variables
//Their real values are set in static function CAgent::InitValues()
vector<CAgent*> CAgent::agents;
bool CAgent::debug = false;
float CAgent::radius = 20.0;
float CAgent::Mass = 1.0;
float CAgent::Inertia = 1.0;
float CAgent::MaxVelocity = 15.0;
float CAgent::MaxForce = 10.0;
float CAgent::MaxTorque = 40.0;
float CAgent::MaxAngVel = 10.0;
float CAgent::Kv0 = 1.0;
float CAgent::Kp1 = 1.0;
float CAgent::Kv1 = 1.0;
float CAgent::KArrival = 1.0;
float CAgent::KDeparture = 1.0;
float CAgent::KNoise = 1.0;
float CAgent::KWander = 1.0;
float CAgent::KAvoid = 1.0;
float CAgent::TAvoid = 1.0;
float CAgent::RNeighborhood = 1.0;
float CAgent::KSeparate = 1.0;
float CAgent::KAlign = 1.0;
float CAgent::KCohesion = 1.0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
vec2 CAgent::WorldToLocal(vec2 &w)
{
	vec2 l;
	float s = sin(state[1]);
	float c = cos(state[1]);
	l[0] = c * w[0] + s * w[1];
	l[1] = -s * w[0] + c * w[1];
	return l;
}

vec2 CAgent::LocalToWorld(vec2 &l)
{
	vec2 w;
	float s = sin(state[1]);
	float c = cos(state[1]);
	w[0] = c * l[0] - s * l[1];
	w[1] = s * l[0] + c * l[1];
	return w;
}

void CAgent::SetVTheta(vec2 &V)
{
	vd = V.Length();
	if (vd < 0.0001){
		thetad = 0.0;
	}
	else{
		if (abs(V[0]) < 0.0001){
			if (V[1] > 0)
				thetad = M_PI / 2.0;
			else
				thetad = M_PI / -2.0;
		}
		else
			thetad = atan2(V[1], V[0]);
	}
	
	ClampAngle(thetad);
}

CAgent::CAgent()
{

}

CAgent::~CAgent()
{

}

void CAgent::Display()
{
	glPushMatrix();
	glTranslatef(GPos[0], rootHeight[frameNum], GPos[1]);
	if (showLeader && this == CAgent::agents[0]){
		float red[] = {1.0, 0.0, 0.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidCone(10.0, 20.0, 24, 24);
		glPopMatrix();
	}
	
	float specular[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);	
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	
	if (CAgent::debug){
		glutSolidSphere(10.0, 24, 24);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glRotatef(-state[1] / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + state[2], 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glRotatef(-thetad / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + vd, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0);
		glEnable(GL_LIGHTING);
	}
	else{
		glRotatef(90.0f - state[1] * Rad2Deg , 0.0, 1.0, 0.0);
		//glutSolidSphere(6.0f, 12, 12);
		glCallList(AgentDisplay::listNames + frameNum);
	}
	glPopMatrix();
}

void CAgent::ClearAgents(){
	for (unsigned int i = 0; i < agents.size(); i++)
		delete CAgent::agents[i];
	CAgent::agents.clear();	
}

CAgent::CAgent(float* color, CEnvironment* env){
	memcpy(this->color, color, sizeof(float) * 3);
	dimState = 4;
	dimInput = 2;
	frameNum = rand() % totalFrames;
	this->env = env;
	float angle = float(rand() % 360) / 180.0 * M_PI;
	vWander[0] = cos(angle) * CAgent::KWander;
	vWander[1] = sin(angle) * CAgent::KWander;
	angle = float(rand() % 360) / 180.0 * M_PI;
	v0[0] = cos(angle) * CAgent::MaxVelocity / 2.0;
	v0[1] = sin(angle) * CAgent::MaxVelocity / 2.0;
	CAgent::agents.push_back(this);
}

void CAgent::SetInitState(float pos[], float angle)
{
	int i;
	GPos[0] = pos[0];
	GPos[1] = pos[1];
	for (i = 0; i < dimState; i++){
		state[i] = 0.0;
	}
	for (i = 0; i < dimInput; i++)
		input[i] = 0.0;
	state[1] = angle;
}

void CAgent::Sense(int type)
{
	showLeader = (type == LEADER);
	goal = env->goal;
	switch(type) {
	case SEEK: Seek(); break;
	case FLEE: Flee(); break;
	case ARRIVAL: Arrival(); break;
	case DEPARTURE: Departure(); break;
	case WANDER: Wander(); break;
	case AVOID: Avoid(); break;
	case SEPARATION: Separation(); break;
	case ALIGNMENT: Alignment(); break;
	case COHESION: Cohesion(); break;
	case FLOCKING: Flocking(); break;
	case LEADER: Leader(); break;
	}
}

void CAgent::Act(float deltaT)
{
	int dframe;
	this->deltaT = deltaT;
	FindDeriv();
	UpdateState();
	if (abs(state[2]) < 0.001)
		dframe = 0;
	else{
		dframe= int(state[2] / CAgent::MaxVelocity * 2 + 1); 
	}
	frameNum += dframe;
	if (frameNum >= totalFrames){
		frameNum = frameNum - totalFrames;
	}
}

void CAgent::SetV0()
{
	v0 = env->goal - GPos;
	v0 = v0.Normalize() * CAgent::MaxVelocity / 2;
}

/*
 *	Set initial value for control and behavior settings
 *  You need to find out appropriate values for:
 *  CAgent::Kv0, CAgent::Kp1, CAgent::Kv1, CAgent::KArrival, CAgent::KDeparture,
 *  CAgent::KNoise,	CAgent::KWander, CAgent::KAvoid, CAgent::TAvoid, CAgent::RNeighborhood,
 *  CAgent::KSeparate, CAgent::KAlign, CAgent::KCohesion.
 */
void CAgent::InitValues()
{
	// Add your code here
	Kv0 = 10.0;
	Kp1 = 256;
	Kv1 = 32;
	KArrival = 0.05;
	KDeparture = 10000;
	KNoise = 10.0;
	KWander = 8.0;
	KAvoid = 1.0;
	TAvoid = 20.0;
	RNeighborhood = 800;
	KSeparate = 1000;
	KAlign = 20.0;
	KCohesion = 0.05;
}

/*
 *	You should apply the control rules given desired velocity vd and desired orientation thetad.
 *  Velocity control: input[0] = f = m * Kv0 * (vd - v)
 *  Heading control: input[1] = tau = I * ( -Kv1 * thetaDot - Kp1 * theta + Kp1 * thetad)
 *  This function sets input[0] and input[1] appropriately after being called.
 */
void CAgent::Control()
{
	// Add your code here
	input[0] = Mass * Kv0 * (vd - state[2]);
	input[1] = Inertia * ( -Kv1 * state[3] - Kp1 * state[1] + Kp1 * thetad); 
    
	//Make sure f and tau are within certan range
	Truncate(input[0], -MaxForce, MaxForce);
    Truncate(input[1], -MaxTorque, MaxTorque); 
}

/*
 *	Compute derivative vector given input and state vectors
 *  This function sets derive vector to appropriate values after being called
 */
void CAgent::FindDeriv()
{
	// Add your code here
	vec4 x(state[0], state[1], state[2], state[3]);
	vec2 u(input[0], input[1]);

	deriv[0] = 0;
    deriv[1] = state[3];
    deriv[2] = input[0]/Mass;
    deriv[3] = input[1]/Inertia - state[3];
}

/*
 *	Update the state vector given derivative vector
 *  Compute global position and store it in GPos
 *  Perform validation check to make sure all values are within MAX values
 */
void CAgent::UpdateState()
{
	// Add your code here
	for(int i = 0; i < 4; i++)
		state[i] += deriv[i] * deltaT; 

	//Make sure velocity and angular velocity are within certain range
	Truncate (state[2], -MaxVelocity, MaxVelocity);
    Truncate (state[3], -MaxAngVel, MaxAngVel); 

	float xDif = cos(state[1]) * state[2];
    float yDif = sin(state[1]) * state[2];

	GPos[0] += xDif;
    GPos[1] += yDif;
}

/*
 *	Seek behavior
 *  Global goal position is in goal
 *  Agent's global position is in GPos
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Seek()
{
	// Replace the following with your code
	vec2 tmp;
	vec2 error = WorldToLocal(goal - GPos); // Contain ey and ex

	vd = MaxVelocity; 
	thetad = state[1] + atan2(error[1], error[0]);

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);

	return tmp;
}

/*
 *	Flee behavior
 *  Global goal position is in goal
 *  Agent's global position is in GPos
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Flee()
{
	// Replace the following with your code
	vec2 tmp;

	vec2 error = WorldToLocal(goal - GPos); // Contain ey and ex

	vd = MaxVelocity;

	//thetad = state[1] + atan2(error[1], error[0]) + PI;
	thetad = state[1] + atan2(-error[1], -error[0]);

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);

	return tmp;
}

/*
 *	Arrival behavior
 *  Global goal position is in goal
 *  Agent's global position is in GPos
 *  Arrival setting is in CAgent::KArrival
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Arrival()
{
	// Replace the following with your code
	vec2 tmp;

	vec2 error = WorldToLocal(goal - GPos); // Contain ey and ex

	vec2 Varrival = KArrival * error;
	vd = Varrival.Length(); // Vd is the abs of Varrival

	thetad = state[1] + atan2(error[1], error[0]); //Same as in Seek

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);

	return tmp;
}

/*
 *	Departure behavior
 *  Global goal position is in goal
 *  Agent's global position is in GPos
 *  Departure setting is in KDeparture
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Departure()
{
	// Replace the following with your code
	vec2 tmp;
	
	vec2 error = WorldToLocal(goal - GPos); // Contain ey and ex

	vec2 Varrival = KDeparture * (-1.0) * error / ( error.Length() * error.Length() );
	vd = Varrival.Length(); // Vd is the abs of Varrival

	thetad = state[1] + atan2(-error[1], -error[0]); //Same as in Flee

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);

	return tmp;
}

/*
 *	Wander behavior
 *  VWander is in vWander
 *  V0(nominal velocity) is in v0
 *  Wander setting is in KWander
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Wander()
{
	// Replace the following with your code
	vec2 tmp;


	float Rangle = float(rand() % 360) / 180.0 * M_PI;
	vec2 n(cos(Rangle), sin(Rangle));
	vec2 Rnoise = KNoise * n / n.Length();
    vWander = KWander * (vWander + Rnoise) / (vWander + Rnoise).Length();

	vd =  (v0 + vWander).Length();
	thetad = atan2((v0 + vWander)[1], (v0 + vWander)[0]); //Same as in Seek

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);

	return tmp;
}

/*
 *	Avoid behavior
 *  Obstacles are in env->obstacles
 *  Number of obstacles is env->obstaclesNum
 *  env->obstacles[i][0] and env->obstacles[i][1] are the global position of the ith obstacle
 *  env->obstacles[i][2] is the radius of the ith obstacle
 *  Agent bounding sphere radius is in CAgent::radius
 *  Avoidance settings are in CAgent::TAvoid and CAgent::KAvoid
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Avoid()
{
	// Replace the following with your code
	vec2 tmp;
	float LB;
	vec2 dWorld, dLocal;
	vec2 vAvoid;//(0.0, 0.0);

	for(int i = 0; i < env->obstaclesNum; ++i)
	{
		
		LB = abs(TAvoid * state[2]);
		dWorld = vec2( env->obstacles[i][0], env->obstacles[i][1] ) - GPos;
		dLocal = WorldToLocal(dWorld);
		if( abs(dLocal[0]) >  (LB + radius + abs(env->obstacles[i][2])))
		{
			tmp = Arrival();
			continue;
		}

		if( abs(dLocal[0]) <= (LB + radius + abs(env->obstacles[i][2])))
		{
			if( abs(dLocal[1]) > (radius + env->obstacles[i][2]) )
			{
				tmp = Arrival();
				continue;
			}
			if( abs(dLocal[1]) <= ( radius + abs(env->obstacles[i][2]) ) )
			{
				vec2 nAvoid = -1.0 * dLocal/dLocal.Length();

				thetad = state[1] + atan2(nAvoid[1], nAvoid[0]);
				vd = abs( KAvoid  / (1 - abs(dLocal[1])/(radius - env->obstacles[i][2]))); 

			    tmp[0] = vd * cos(thetad);
	            tmp[1] = vd * sin(thetad);
	            return tmp;
			}
		}
		
		
	}
}

/*
 *	Separation behavior
 *  CAgent::agents[i] gives the pointer to the ith agent in the environment
 *  Separation settings are in CAgent::RNeighborhood and CAgent::KSeperate
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Separation()
{
	// Replace the following with your code
	vec2 tmp;

	vec2 vTmp(0.0, 0.0);
	
	for(int i = 0; i < agents.size(); i++)
	{
		vec2 dis = GPos - agents[i]->GPos; 
		if(dis.Length() == 0)
			continue;
		if(dis.Length() < RNeighborhood)
			vTmp += dis / (dis.Length() * dis.Length());
	}
	
	vec2 vSeperate = KSeparate * vTmp;

	vd = vSeperate.Length();
	thetad = atan2(vSeperate[1], vSeperate[0]); 

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);
	return tmp;
}

/*
 *	Alignment behavior
 *  CAgent::agents[i] gives the pointer to the ith agent in the environment
 *  Alignment settings are in CAgent::RNeighborhood and CAgent::KAlign
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Alignment()
{
	// Replace the following with your code
	vec2 tmp;
	vec2 vTmp = Arrival();
	float number = 0.0;
	vec2 vAlignment;
	for(int i = 0; i < agents.size(); i++)
	{
		vec2 dis = GPos - agents[i]->GPos; 
		if(dis.Length() == 0)
			continue;
		if(dis.Length() < RNeighborhood * 10)
		{
			vTmp[0] += cos(agents[i]->state[1]) * (agents[i]->state[2]);
			vTmp[1] += sin(agents[i]->state[1]) * (agents[i]->state[2]);
			number += 1.0;
		}
	}

	vAlignment = KAlign * vTmp / number;
	vd = vAlignment.Length();
	thetad = atan2(vAlignment[1], vAlignment[0]); 

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);
	return tmp;
}

/*
 *	Cohesion behavior
 *  CAgent::agents[i] gives the pointer to the ith agent in the environment
 *  Cohesion settings are in CAgent::RNeighborhood and CAgent::KCohesion
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Cohesion()
{
	// Replace the following with your code
	vec2 tmp;

	vec2 vTmp(0.0, 0.0);
	float number = 0.0;
	vec2 vCohesion;
	for(int i = 0; i < agents.size(); i++)
	{
		vec2 dis = GPos - agents[i]->GPos; 

		if(dis.Length() < RNeighborhood)
		{
			vTmp += agents[i]->GPos;
			number += 1.0;
		}
	}

	vec2 Xcm = vTmp/number;
	vCohesion = KCohesion * (Xcm - GPos);
	vd = vCohesion.Length();
	thetad = atan2(vCohesion[1], vCohesion[0]); 

	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);
	return tmp;
}

/*
 *	Flocking behavior
 *  Utilize the Separation, Cohesion and Alignment behaviors to determine the desired velocity vector
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Flocking()
{
	// Replace the following with your code
	vec2 tmp;
	float Cseparate = 200, Ccohesion = 0.1, Calignment = 6;
	vec2 vFlock = Cseparate * Separation() + Ccohesion * Cohesion() + Calignment * Alignment(); 
	vd = vFlock.Length();
	thetad = atan2(vFlock[1], vFlock[0]); 
	tmp[0] = vd * cos(thetad);
	tmp[1] = vd * sin(thetad);
	return tmp;
}

/*
 *	Flocking behavior
 *  Utilize the Separation, Arrival behaviors to determine the desired velocity vector
 *  You need to find the leader, who is always the first agent in CAgent::agents
 *  You need to compute the desired velocity and desired orientation
 *  Store them into vd and thetad respectively
 *  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
 */
vec2 CAgent::Leader()
{
	// Replace the following with your code
	vec2 tmp;
	float Csep = 0.7, Carr = 0.9;
	vec2 vLeader;
	if( (GPos[0] == agents[0]->GPos[0])&&(GPos[1] == agents[0]->GPos[1]) )
	{
		vLeader = Arrival();
		vd = vLeader.Length();
		thetad = atan2(vLeader[1], vLeader[0]); 
	    tmp[0] = vd * cos(thetad);
	    tmp[1] = vd * sin(thetad);
	}
	else
	{
		vLeader = Csep * Separation() + Carr * Arrival();
	    vd = vLeader.Length();
	    thetad = atan2(vLeader[1], vLeader[0]); 
	    tmp[0] = vd * cos(thetad);
	    tmp[1] = vd * sin(thetad);
	}
	return tmp;
}
