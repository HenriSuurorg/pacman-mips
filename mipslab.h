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
void movePacman(int, int, char);
void updatePacman();

typedef struct entity entity;
struct entity{
   int x;
   int y;
   char dir; // direction: either 'n', 'e', 's' or 'w'
   int lives;
};

const uint8_t walls2d[32][128];
const uint8_t walls[512];
uint8_t orbs2d[32][128];
uint8_t orbs[512];
void addWallsAndOrbs(void);

int checkCollisionWithWall(char, entity *);
void updateGhost(entity *);

unsigned int seed(void);
void init_pin(void);

int gameState;
int score;
void orbs2dToArray(void);
void checkCollisionWithOrb(entity *);
void checkCollisionWithGhost(entity *, entity[]);
void updatePacman(entity *);

void credits();
void menu();
void instructions();
void highscore();

int btn1;
int btn2;
int btn3;
int btn4;

// int btn3count;
// int btn4count;
char* highscoresNames[4];
int highscoreIndex;
int highscores[4];
char highScoreStringSaved[16];

int livesAtTheEndOfTheGame;

void gameOver();
void orbsRemap();
const uint8_t orbs2dConstant [32][128];

int calculateScore(int, int);
int nofOrbs;