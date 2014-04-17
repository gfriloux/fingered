#include <Eina.h>
#include <Ecore.h>
#include <Ecore_Con.h>

typedef struct _Fingered Fingered;

extern int FINGERED_EVENT_USER;

int fingered_init(void);
int fingered_shutdown(void);
Fingered * fingered_new(void);
