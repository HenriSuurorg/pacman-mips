/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
void labwork(void);
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
/* Declare text buffer for display output */
extern char textbuffer[4][16];

void enable_interrupt(void);

void setDisplay2d(int, int, int, int);
void clearDisplay(void);
uint8_t display2d[32][128];
uint8_t display[512];

void checkButtons();

void displayGhost(int, int);
void displayPacman(int, int);

typedef struct entity entity;
struct entity{
   int x;
   int y;
   char dir; // direction: either 'n', 'e', 's' or 'w'
};
