/* sf2types.h */
#ifndef INC_SF2TYPES
#define INC_SF2TYPES

#define u32 unsigned int	
#define u16 unsigned short
#define u8  unsigned char
#define Point unsigned int


#ifdef __LINUX__
#inlude <linux/types.h>
#else
#define __u16 unsigned short
#define __u8  unsigned char
#endif

// Little Endian CPUs

#ifdef __i386__
#define SF2_ENDIAN_LITTLE
#define SF2_CPU_I386
#endif

#ifdef __amd64__
#define SF2_ENDIAN_LITTLE
#define SF2_CPU_AMD64
#endif


// Big Endian CPUs

#ifdef __POWERPC__
#define SF2_ENDIAN_BIG
#define SF2_CPU_POWERPC
#endif

#ifdef __m68k__
#define SF2_ENDIAN_BIG
#define SF2_CPU_M68K
#endif


// Microsoft Visual Studio

#ifdef _M_PPC
#define SF2_ENDIAN_BIG
#define SF2_CPU_POWERPC
#endif

#ifdef _M_IX86
#define SF2_ENDIAN_LITTLE
#define SF2_CPU_I386
#endif

typedef  u16 * CPSCOORD;

	
#ifndef NULL
#define NULL 0
#endif

/* the fixed precision 16:16bit used in coordinates and vectors */

#ifdef SF2_ENDIAN_LITTLE

typedef union FIXED16_16tag {
    int full;
    struct part16_16tag {
        unsigned int fraction: 16;
        signed int integer: 16;
    } __attribute__((packed)) part;
} FIXED16_16;

typedef union FIXED8_8tag {
    short full;
    struct part8_8tag {
        unsigned int fraction: 8;
        signed int integer: 8;
    } __attribute__((packed)) part;
} FIXED8_8;

typedef union DUALtag {
    u16 full;
    struct dualtag {
        u8 p0;
        u8 p1;
    }  __attribute__((packed)) part;
} DUAL;


#endif
#ifdef SF2_ENDIAN_BIG

typedef union FIXED16_16tag {
    int full;
    struct part16_16tag {
        signed int integer: 16;
        unsigned int fraction: 16;
    }  __attribute__((packed))part;
} FIXED16_16;

typedef union FIXED8_8tag {
    short full;
    struct part8_8tag {
        signed int integer: 8;
        unsigned int fraction: 8;
    } __attribute__((packed)) part;
} FIXED8_8;

typedef union DUALtag {
    u16 full;
    struct dualtag {
        u8 p1;
        u8 p0;
    }  __attribute__((packed))part;
} DUAL;

#endif

struct adjust {
    char x;
    char y;
    u8   flips;
    u8   frame;
};

struct smalladjust {
    char x;
    char y;
};

struct Point8 {
	char x;
	char y;
};
typedef struct Point8 POINT8;
struct Point16 {
	short x;
	short y;
};
typedef struct Point16 POINT16;
struct Size8 {
	char width;
	char height;
};
typedef struct Size8 SIZE8;
struct Rect8 {
	struct Point8 origin;
	struct Size8  size;
};
typedef struct Rect8 RECT8;
struct Vect16 {
	FIXED8_8 x;
	FIXED8_8 y;
} __attribute__((packed));
typedef struct Vect16 VECT16;
struct Traj16 {
	VECT16 Vel;
	VECT16 Acl;
};
typedef struct Traj16 TRAJ16;

struct extrasprite {
	POINT16			Offset;
    struct image	*Image;
};    


#endif /* INC_SF2TYPES */
