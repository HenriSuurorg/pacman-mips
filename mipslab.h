/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
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

typedef struct pman pman;

struct pman{
   int x;
   int y;
};

pman pacman;
