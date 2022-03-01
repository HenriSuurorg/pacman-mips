/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
/* Declare text buffer for display output */
extern char textbuffer[4][16];

void enable_interrupt(void);

void setDisplay2d(int, int, int, int);
void display2dToArray(void);
void clearDisplay(void);
uint8_t display2d[32][128];
uint8_t display[512];

void checkButtons();

void moveGhost(int, int);
void movePacman(int, int);
void updatePacman();

typedef struct entity entity;
struct entity{
   int x;
   int y;
   int nextX;
   int nextY;
   int height;
   int width;
   char dir; // direction: either 'n', 'e', 's' or 'w'
};

const uint8_t walls2d[32][128];
const uint8_t walls[512];
const uint8_t orbs2d[32][128];
const uint8_t orbs[512];
void addWallsAndOrbs(void);

int checkCollisionWithWall(char, entity *);
void updateGhost(entity *);