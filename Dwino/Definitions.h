
#define LengthBuffer	100
#define MaxNumWindows	10


//#define USE_RTOS
#define MIN_TIMEOUT	200

//ERRORS
#define	SUCCESSFULL		1
#define	ERROR_TIMEOUT	-20



#define READBIT(A, B) ((A >> (B & 31)) & 1)
#define SETBIT(T, B, V) (T = V ? T | (1<<B) : T & ~(1<<B))
