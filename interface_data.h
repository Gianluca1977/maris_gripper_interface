/*
 * interface_data.h
 *
 *  Created on: Aug 29, 2015
 *      Author: Gianluca Palli
 */

#ifndef INTERFACE_DATA_H_
#define INTERFACE_DATA_H_

#define RAD_TO_GRAD			(180/M_PI)
#define GRAD_TO_RAD			(M_PI/180)

#define BIT16_	1U<<15	//0x8000
#define BIT32_	1U<<31	//0x80000000
#define ERR_VAL BIT32_

//#define HOME_MAXPEAK				3000
//#define HOME_MAXCONT				2300
//#define MAX_GRASPCURR				10000	//maximo assorbimento totale
#define NUM_MOT	3
//#define STDMAXVEL					3000

#pragma pack(8)

/* struct aggiormanento interfaccia */

typedef struct
{
    int JointID[NUM_MOT];

    int State[NUM_MOT];

    long long Velocity[NUM_MOT];	//velocita attuale
    long long Current[NUM_MOT];	//corrente attuale
    long long Control[NUM_MOT];		//velocita impostata
    double PositionGrad[NUM_MOT];	//posizione in gradi
    double MaxPosGrad[NUM_MOT];	//massima apertura

    bool Operational[NUM_MOT];
    bool MotorFault[NUM_MOT];
    bool isHomeDone;
    bool SystemFault;
    //bool isInitialized;

    //std::string strStatus;

    /* ***** strees test stuff ** */

    long long actCycle;

    /*******************************/

    int homePhase;
    int initPhase;
    int srv_mode;
    int srv_preshape;

    bool isInitialized_;
    bool emerg_stop;
    bool resetSensors;

    bool fake_align[12];	//align with 64 bit grafic interface
} SystemStatus;

/* ****************************** */
#define DO_NOTHING      0
#define GO_POSITION     1
#define GO_VELOCITY     2
#define RECOVER         3
#define SET_INIT_POS    4
#define SET_FINAL_POS   5
#define EMERGENCY       6
#define GO_FINAL_POS    7
#define PRESHAPE        8

/* struct setting (user -> control) */
typedef struct
{
    uint64_t command;
    uint64_t preshape;
    //uint32_t fake;
    union
    {
        int64_t req_pos[NUM_MOT];
        int64_t req_vel[NUM_MOT];
        bool motor_selection[NUM_MOT];
    };

} SystemRequest_2;

/* struct setting (user -> control) */

typedef struct{

    long long req_vel[NUM_MOT];
    long long req_pos[NUM_MOT];
    long long conf_geom[3][2]; //riga - dito / colonna - info
/*							  d  i
     * 0 - dito 1		conf_geom[0][0] = apert. dito 1
     * 1 - dito 2  		conf_geom[1][0] = apert. dito 2
     * 2 - dito 3		conf_geom[2][1] = offset fito 3
     */
    /*
     * ***   info
     * 0 - apertura (0 - 100)
     * 1 - thumb offset (-20 - +100) //TODO: da verificare il range
     */

    long long repeat;
    long long butNum;	// (0-px 1-th 2-pl)
    long long dummyForce;

    bool doHome;
    bool parking;
    bool emerg_stop;
    bool recover;
    //float forza;

    bool highLevel;  // true - using high level / false - using low level


/* *** tcp interface stuffs ***** */


    bool setIniPos;
    bool setFinPos;
    bool goIniPos;
    bool goFinPos;

    bool pos;
    bool manualHomeDone;
    bool tcpActive;
/* ********** **************** */

    int desired_conf;

    bool fake_align[6];


} SystemRequest;

/* ******************************** */


#endif /* INTERFACE_DATA_H_ */

